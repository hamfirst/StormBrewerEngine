

#include "DocumentServerVCSGit.refl.meta.h"

#include "Foundation/Assert/Assert.h"
#include "Foundation/FileSystem/Path.h"

#include "StormRefl/StormReflJsonStd.h"
#include "StormRefl/StormReflMetaEnum.h"

extern "C"
{
#include "libgit2/include/git2.h"
}

#include "gsl/gsl"
#include "hash/Hash64.h"

#include <unordered_map>

#include <filesystem>
namespace fs = std::filesystem;


#define CHECK_ERROR(Call) error = Call; if(error < 0) { m_ErrorCallback(std::string(#Call) + " " + std::to_string(error)); return; }

DocumentServerVCSGit::DocumentServerVCSGit()
{
  int error = git_libgit2_init();
  ASSERT(error >= 0, "Could not load git vcs library");
}

DocumentServerVCSGit::~DocumentServerVCSGit()
{
  int error = git_libgit2_shutdown();
  ASSERT(error >= 0, "Could not unload git vcs library");
}

bool DocumentServerVCSGit::Init(const std::string_view & settings, const std::string_view & project_dir,
                                const std::string & self_path, Delegate<void, const std::string &> && error_callback)
{
  m_ErrorCallback = std::move(error_callback);

  DocumentServerVCSGitInitData settings_data;
  if(!StormReflParseJson(settings_data, settings))
  {
    m_ErrorCallback("Could not parse settings");
    return false;
  }

  m_RootPath = settings_data.RootPath.size() > 0 ? settings_data.RootPath : project_dir;
  m_RootPath = std::filesystem::canonical(m_RootPath).string();
  m_SelfPath = std::filesystem::relative(self_path, m_RootPath).string();
  return true;
}

void DocumentServerVCSGit::GetStatus(std::vector<DocumentServerVCSQuery> & queries)
{
  int error;
  git_repository * repo;
  git_status_list * status;

  CHECK_ERROR(git_repository_open(&repo, m_RootPath.c_str()));
  auto repo_close = gsl::finally([&](){ git_repository_free(repo); });

  git_status_options status_opts = GIT_STATUS_OPTIONS_INIT;
  status_opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
  status_opts.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED;
  status_opts.flags |= GIT_STATUS_OPT_INCLUDE_UNMODIFIED;
  status_opts.flags |= GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH;

  std::vector<std::string> file_strs;
  std::vector<char *> file_ptrs;
  file_ptrs.reserve(queries.size());

  std::unordered_map<uint64_t, std::size_t> file_index_lookup;

  for(auto & elem : queries)
  {
    std::string converted_path = elem.m_FilePath;
    if(!ConvertPath(converted_path))
    {
      m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
    }

    file_strs.emplace_back(std::move(converted_path));
  }

  std::size_t lookup_index = 0;
  for(auto & elem : file_strs)
  {
    file_ptrs.push_back(elem.data());
    file_index_lookup.emplace(std::make_pair(crc64(elem), lookup_index));
    lookup_index++;
  }

  status_opts.pathspec.strings = file_ptrs.data();
  status_opts.pathspec.count = file_ptrs.size();

  CHECK_ERROR(git_status_list_new(&status, repo, &status_opts));
  auto status_close = gsl::finally([&](){ git_status_list_free(status); });

  auto num_query_responses = git_status_list_entrycount(status);
  for(std::size_t index = 0; index < num_query_responses; ++index)
  {
    auto status_info = git_status_byindex(status, index);
    auto status_file_path = status_info->index_to_workdir->old_file.path;
    auto file_name_hash = crc64(status_file_path);

    auto itr = file_index_lookup.find(file_name_hash);
    if(itr == file_index_lookup.end())
    {
      continue;
    }

    auto & elem = queries[itr->second];
    auto status_id = status_info->index_to_workdir->status;

    if(status_id == GIT_DELTA_UNMODIFIED)
    {
      elem.m_Status = VCSStatus::kCurrent;
    }
    else if(status_id == GIT_DELTA_UNTRACKED)
    {
      elem.m_Status = VCSStatus::kNew;
    }
    else if(status_id == GIT_DELTA_MODIFIED)
    {
      elem.m_Status = VCSStatus::kModified;
    }
    else if(status_id == GIT_DELTA_ADDED)
    {
      elem.m_Status = VCSStatus::kAdded;
    }
  }
}

void DocumentServerVCSGit::Add(std::vector<DocumentServerVCSOperation> & files)
{
  std::vector<DocumentServerVCSQuery> status_queries;
  for(auto & elem : files)
  {
    status_queries.emplace_back(DocumentServerVCSQuery{ elem.m_FilePath });
  }

  GetStatus(status_queries);

  int error;
  git_repository * repo;
  git_index * index;

  CHECK_ERROR(git_repository_open(&repo, m_RootPath.c_str()));
  auto repo_close = gsl::finally([&](){ git_repository_free(repo); });

  CHECK_ERROR(git_repository_index(&index, repo));
  auto index_close = gsl::finally([&](){ git_index_free(index); });

  for(std::size_t elem_index = 0, end = files.size(); elem_index < end; ++elem_index)
  {
    auto & status = status_queries[elem_index];
    auto & elem = files[elem_index];

    if(status.m_Status == VCSStatus::kNew)
    {
      std::string converted_path = elem.m_FilePath;
      if (!ConvertPath(converted_path))
      {
        m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
      }

      auto result = git_index_add_bypath(index, converted_path.c_str());
      elem.m_Success = (result == 0);
    }
    else
    {
      elem.m_Success = false;
    }
  }

  CHECK_ERROR(git_index_write(index));
}

void DocumentServerVCSGit::Remove(const std::string_view & file_path)
{
  int error;
  git_repository * repo;
  git_index * index;

  std::string converted_path = std::string(file_path.data(), file_path.size());
  if(!ConvertPath(converted_path))
  {
    m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
    return;
  }

  CHECK_ERROR(git_repository_open(&repo, m_RootPath.c_str()));
  auto repo_close = gsl::finally([&](){ git_repository_free(repo); });

  CHECK_ERROR(git_repository_index(&index, repo));
  auto index_close = gsl::finally([&](){ git_index_free(index); });

  CHECK_ERROR(git_index_remove_bypath(index, converted_path.c_str()));
  CHECK_ERROR(git_index_write(index));
}

void DocumentServerVCSGit::Revert(const std::string_view & file_path)
{
  int error;
  git_repository * repo;
  git_index * index;

  std::string converted_path = std::string(file_path.data(), file_path.size());
  if(!ConvertPath(converted_path))
  {
    m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
    return;
  }

  auto path_ptr = converted_path.data();

  git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
  checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
  checkout_opts.paths.strings = &path_ptr;
  checkout_opts.paths.count = 1;

  CHECK_ERROR(git_repository_open(&repo, m_RootPath.c_str()));
  auto repo_close = gsl::finally([&](){ git_repository_free(repo); });

  CHECK_ERROR(git_checkout_head(repo, &checkout_opts));
}

bool DocumentServerVCSGit::ConvertPath(std::string & path)
{
  std::error_code ec;

  auto fs_path = fs::path(path);
  if(fs_path.is_absolute() == false)
  {
    auto abs_path = fs::path(m_RootPath) / fs::path(m_SelfPath) / fs_path;
    fs_path = fs::absolute(abs_path, ec);

    if(ec)
    {
      return false;
    }

    auto test_path = fs_path.string();
    fs_path = fs::canonical(fs_path, ec);

    if(ec)
    {
      return false;
    }
  }

  fs_path = fs::relative(fs_path, fs::path(m_RootPath), ec);
  if(ec)
  {
    return false;
  }

  path = fs_path.string();
  return true;
}

