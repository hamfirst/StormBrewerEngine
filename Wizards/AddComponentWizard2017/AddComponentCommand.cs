using System;
using System.IO;
using System.ComponentModel.Design;
using System.Globalization;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using EnvDTE;

namespace AddComponentWizard2017
{
	/// <summary>
	/// Command handler
	/// </summary>
	internal sealed class AddComponentCommand
	{
		/// <summary>
		/// Command ID.
		/// </summary>
		public const int CommandId = 0x0100;

		/// <summary>
		/// Command menu group (command set GUID).
		/// </summary>
		public static readonly Guid CommandSet = new Guid("e290b2e4-9d75-4a06-b212-bf7df408c88a");

		/// <summary>
		/// VS Package that provides this command, not null.
		/// </summary>
		private readonly Package package;

		/// <summary>
		/// Initializes a new instance of the <see cref="AddComponentCommand"/> class.
		/// Adds our command handlers for menu (commands must exist in the command table file)
		/// </summary>
		/// <param name="package">Owner package, not null.</param>
		private AddComponentCommand(Package package)
		{
			if (package == null)
			{
				throw new ArgumentNullException("package");
			}

			this.package = package;

			OleMenuCommandService commandService = this.ServiceProvider.GetService(typeof(IMenuCommandService)) as OleMenuCommandService;
			if (commandService != null)
			{
				var menuCommandID = new CommandID(CommandSet, CommandId);
				var menuItem = new MenuCommand(this.MenuItemCallback, menuCommandID);
				commandService.AddCommand(menuItem);
			}
		}

		/// <summary>
		/// Gets the instance of the command.
		/// </summary>
		public static AddComponentCommand Instance
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the service provider from the owner package.
		/// </summary>
		private IServiceProvider ServiceProvider
		{
			get
			{
				return this.package;
			}
		}

		/// <summary>
		/// Initializes the singleton instance of the command.
		/// </summary>
		/// <param name="package">Owner package, not null.</param>
		public static void Initialize(Package package)
		{
			Instance = new AddComponentCommand(package);
		}

		/// <summary>
		/// This function is the callback used to execute the command when the menu item is clicked.
		/// See the constructor to see how the menu item is associated with this function using
		/// OleMenuCommandService service and MenuCommand class.
		/// </summary>
		/// <param name="sender">Event sender.</param>
		/// <param name="e">Event args.</param>
		private void MenuItemCallback(object sender, EventArgs e)
		{
			DTE dte;
			dte = (DTE)this.ServiceProvider.GetService(typeof(DTE));

			ProjectItem proj_item = null;
			foreach (SelectedItem item in dte.SelectedItems)
			{
				if (item.ProjectItem != null && item.ProjectItem.Kind == "{6BB5F8F0-4483-11D3-8BCF-00C04F8EC28C}")
				{
					proj_item = item.ProjectItem;
				}
				break;
			}

			if (proj_item != null)
			{
				string canonical_name = null;
				foreach (Property prop in proj_item.Properties)
				{
					if (prop.Name == "CanonicalName")
					{
						canonical_name = (string)prop.Value;
					}
				}

				if (canonical_name != null)
				{
					string project_root = null;
					foreach (Property prop in proj_item.ContainingProject.Properties)
					{
						if (prop.Name == "ProjectDirectory")
						{
							project_root = (string)prop.Value;
						}
					}

					if (project_root != null)
					{
						var base_path = Path.Combine(project_root, canonical_name);
						AddComponentCommandWindow window = new AddComponentCommandWindow(base_path);

						var result = window.ShowDialog();
						if (result == System.Windows.Forms.DialogResult.OK)
						{
							if (window.Type == AddComponentCommandType.Component)
							{
								var tab = window.AddComponent;
								AddComponentTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath,
									tab.SourceFile, tab.HeaderFile, tab.MetaFile, tab.RegFile, tab.InitDataClass, tab.CreateInitData, tab.SyncToServerObject);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.SourceFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.ServerObject)
							{
								var tab = window.AddServerObject;
								AddServerObjectTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath,
									tab.SourceFile, tab.HeaderFile, tab.MetaFile, tab.RegFile, tab.InitDataClass, tab.CreateInitData, tab.EntityLink, tab.IncludePositionData);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.SourceFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.Config)
							{
								var tab = window.AddConfig;
								AddConfigTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath, tab.HeaderFile, tab.MetaFile, tab.RegFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.PlayerState)
							{
								var tab = window.AddPlayerState;
								AddPlayerStateTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath,
									tab.SourceFile, tab.HeaderFile, tab.MetaFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.SourceFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
							}
							else if (window.Type == AddComponentCommandType.BotState)
							{
								var tab = window.AddPlayerState;
								AddPlayerStateTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath,
									tab.SourceFile, tab.HeaderFile, tab.MetaFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.SourceFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
							}
							else if (window.Type == AddComponentCommandType.Anchor)
							{
								var tab = window.AddAnchor;
								AddAnchorTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath, tab.HeaderFile, tab.MetaFile, tab.RegFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.Path)
							{
								var tab = window.AddPath;
								AddPathTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath, tab.HeaderFile, tab.MetaFile, tab.RegFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.Volume)
							{
								var tab = window.AddVolume;
								AddVolumeTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath, tab.HeaderFile, tab.MetaFile, tab.RegFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.EffectLayer)
							{
								var tab = window.AddEffectLayer;
								AddEffectLayerTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath,
									tab.SourceFile, tab.HeaderFile, tab.MetaFile, tab.RegFile, tab.InitDataClass);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.SourceFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
							else if (window.Type == AddComponentCommandType.AnimationEvent)
							{
								var tab = window.AddAnimationEvent;
								AddAnimationEventTemplate.CreateTemplate(
									tab.ComponentName, proj_item.ContainingProject.Name, project_root, tab.BasePath, tab.HeaderFile, tab.MetaFile, tab.RegFile);

								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.HeaderFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.MetaFile));
								proj_item.ProjectItems.AddFromFile(Path.Combine(tab.BasePath, tab.RegFile));
							}
						}
					}
				}
			}
		}
	}
}
