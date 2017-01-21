#pragma once

#include <cstdint>
#include <string>

#include <sb/cstr.h>

static constexpr uint64_t crc64_table[256] = {
  0xaa75cfd903e58055ULL, 0x802bcac7182fa575ULL,
  0xdd9a29a3f400cfc5ULL, 0xcc07ada0c63e8926ULL,
  0x7417e422cf4838acULL, 0x6571f16f7e182010ULL,
  0xf4942ecac7dd8846ULL, 0x3e5bb458dc142125ULL,
  0xa4fcbbf59ffe2865ULL, 0xc343f765a8c6b345ULL,
  0x609f5f058fa7483aULL, 0x13ba0e6ddf48f67cULL,
  0xf9b4e8a737af0b66ULL, 0xbfcf9c6132074326ULL,
  0x69590ec2b5e34192ULL, 0xdd1a0d8ff387aec4ULL,
  0x738914a04da5e9a4ULL, 0xd2091e7d274d8b7bULL,
  0x5a34ca0a3ab6009bULL, 0x3e3e2c3419f709a6ULL,
  0xf218d7254eaef74dULL, 0xdad709484b97d784ULL,
  0x8f1ffaf2667b6b2aULL, 0x7292f0dfd42ad02bULL,
  0xc932ca513ae4bc9eULL, 0x2d7aa730e351e6bbULL,
  0xd03888b2a3a30ac2ULL, 0xf1951a29409a86b3ULL,
  0x8a84853ae6cfe956ULL, 0x36ef769fb8165f7fULL,
  0x4a286de273e7d3f0ULL, 0x8bd5d36c365fc659ULL,
  0x649a012a839a86f7ULL, 0x0c5ffc6bf3ebb319ULL,
  0xbe9c433a6bd1304dULL, 0x71d2c2fd1ed52110ULL,
  0x6e59d8d2fd90b717ULL, 0x08595e11fa13e838ULL,
  0xb118864f37bb398aULL, 0xa9f09d23d7134c9bULL,
  0xf62cb620629d5ff3ULL, 0xfa3854b4c8affeecULL,
  0x7df5a3f54fb528f8ULL, 0x913b8da778862a0fULL,
  0x05e62d041cfe68a1ULL, 0x225b5afe976198b9ULL,
  0xa9c8cd74d5ab6ee9ULL, 0xe1a310dbc4a51cf0ULL,
  0xe1781a9d2703f759ULL, 0x7fa71267732dce30ULL,
  0xbf63454f0ce37b14ULL, 0xb71a90f16fba41e0ULL,
  0xd0ff752f07f0cb9cULL, 0x6f276230affc5eb5ULL,
  0x225cf2fc358f6f41ULL, 0xe8c58c3dcd7775fcULL,
  0xf39ab3f60b79dde6ULL, 0x41a2f5010cc34a2bULL,
  0x28ff27b4788b1155ULL, 0x2ec31311bdb2c701ULL,
  0xc00663809b022100ULL, 0x04f71cb924ea18e8ULL,
  0x4ae518082eaafc12ULL, 0x1e62c633d85d6a66ULL,
  0xbc09bab4ddba5282ULL, 0xcf1076475e790a74ULL,
  0x65166d59d986006eULL, 0x0169d21c6c411401ULL,
  0xaca79117f2137696ULL, 0xd8ad4dbdff2c9113ULL,
  0x2f956a825323299cULL, 0xc6fb844ea4facd13ULL,
  0x9f3fd703d6f7b3d0ULL, 0x98af7d8fb341c448ULL,
  0xb0191b0a7987a5d8ULL, 0x1cdf42d26e2ae67bULL,
  0x3d8b038f3e12f43bULL, 0xa0386f1604b479c4ULL,
  0x9c210b32a940530aULL, 0xa7eba699fac1012bULL,
  0xf1793a1338955463ULL, 0xde94923672db89a6ULL,
  0xd52ffa60135c240fULL, 0x6ec5f13d780a39d5ULL,
  0x81a22b9fbc877e2eULL, 0xd0620623cd49aedcULL,
  0x17310dddfbb49a27ULL, 0xfaa88db1df4b6310ULL,
  0xcc9d81d3e62fa75bULL, 0x63555503ca4629aaULL,
  0x26ce508204906643ULL, 0x1a64df3c6e74283dULL,
  0x51cebaedb2f514d8ULL, 0xb053e83c29e8d3c5ULL,
  0x0d4fbf8215a1e37eULL, 0x48cfa52c367f1636ULL,
  0x1e1002a619c25dc4ULL, 0x67b7b5ce198e1cbaULL,
  0xecae962b68dd67deULL, 0xa6df701437fe2ff8ULL,
  0x4a9924787a32c081ULL, 0x2ff1ae37b31d1992ULL,
  0x80c9f05f0a3a05d4ULL, 0x43455fc6e9201af2ULL,
  0xb7727ca9c2b7046cULL, 0x780de3ef525290a4ULL,
  0xc9accd217869bfe0ULL, 0xacae793661f38636ULL,
  0x3929af3216e2d23eULL, 0x100a74e803f76ce6ULL,
  0x546fb302006addefULL, 0x3756c3e02961e9b9ULL,
  0x98cb2c59359fe99aULL, 0x3b09e5dd4e2a0800ULL,
  0x34605910414bc01dULL, 0x3bd176b597e00526ULL,
  0xf8bb6a2ca0cc7ac5ULL, 0xb9897211cca391f3ULL,
  0x2a9250c8899607f1ULL, 0xa8a85ad25bf23390ULL,
  0x2d3658e00f6cd8b0ULL, 0x0a23017ee0fdc0bcULL,
  0x9812a85f376e924aULL, 0x58f05dcf357f62e6ULL,
  0x27871d515c4572ceULL, 0xab83a12980c5484cULL,
  0xef4c05509cbe327dULL, 0x1f6a540aff738695ULL,
  0x14b3a81315813fa2ULL, 0x672534a4a2405847ULL,
  0x0198d04b5826e86cULL, 0x5f3bc879fe699a5bULL,
  0xf75dfff1fb03a57aULL, 0xef3a6467762c070dULL,
  0x68820264c65423e4ULL, 0x3eb1fd3a991362d8ULL,
  0x391468f901ff1d62ULL, 0xe72237e222ef8154ULL,
  0xe704e8c400b2e1d9ULL, 0x2299a9d31ec2d4b4ULL,
  0xf646b8fbe434e583ULL, 0xc24c2ed057150243ULL,
  0xf3255b933d6b7c60ULL, 0xfefe8546259d54f2ULL,
  0x362282f9b132e022ULL, 0x558e40e51e83940fULL,
  0xa7578715c7b1b925ULL, 0xc5c96757a6eb46ebULL,
  0xd3bd63d9dc68496fULL, 0x789a0a30bfff956bULL,
  0xef29434b3617e246ULL, 0x9952fc52a91f755aULL,
  0xf853fa2f03376311ULL, 0xd02156a901fd1554ULL,
  0x6cdb7c60d95db829ULL, 0xbecd6aa27eed4d9bULL,
  0xc0f5acfa08212a41ULL, 0x0a0753fe827a8910ULL,
  0x4ba80933f26c7a28ULL, 0x4e2d3808b80b1dfeULL,
  0x7d2a02dff8639166ULL, 0x92e32e4a21eda33fULL,
  0x1fdc3897806a147cULL, 0x1fe711d0a78b155dULL,
  0xe17c16c6a8ce61b1ULL, 0x872d27455848c529ULL,
  0xd3efb53b68aa4fabULL, 0xc0cf74460dd15d7bULL,
  0x4db418d0ab75facdULL, 0xf3efda9b3d174692ULL,
  0xa680edcddc8a0615ULL, 0x01688f6f0b025bd1ULL,
  0x12ae27490ceb8d93ULL, 0xc7faec89c6dc31cfULL,
  0xcceaa580b47d6357ULL, 0x47a820f788d4af0fULL,
  0xd04a9623d48c9532ULL, 0x9bcb485242c840a6ULL,
  0x2dda9da4922abeddULL, 0x7e35b21df13d448bULL,
  0xddf7d2db976f1bd4ULL, 0x789c6bd7d1421249ULL,
  0xc443ae4e22ed4522ULL, 0x29ac0b07dfa0de7fULL,
  0x66bcabe1b172b731ULL, 0x55095f6cfc9f012aULL,
  0xe1bbbfca5546bc6bULL, 0xd04eae5fd9a3433dULL,
  0x44b8ab349fec7adbULL, 0xb50937f450978177ULL,
  0xb73630cd0644a532ULL, 0xe3ee3b20924c7087ULL,
  0x57b1bdd2bd3a33b2ULL, 0x03f0be2dc0dc247eULL,
  0xa84a2359fdf6502fULL, 0xfebe755093850f14ULL,
  0xb993b40df83eab21ULL, 0x8edb8c1ad2160534ULL,
  0xdf128bf674f8d0abULL, 0xd3a12f25522f847dULL,
  0x937711647bf2ce3cULL, 0xe00e3e813dbd513aULL,
  0x474d2d53827ac644ULL, 0xcc5fbe70fdd46960ULL,
  0x8c0848d3f8deb180ULL, 0xdee92b8bc1fa657fULL,
  0xec61897513287105ULL, 0x0c365c0100b49c62ULL,
  0xace69f41427d67eeULL, 0xcd43e98d8f4bc8b3ULL,
  0x29f90fc14e6216cbULL, 0x50535e1998712452ULL,
  0xdee1b33be4435826ULL, 0xd7c5ded05af1cd02ULL,
  0x6c22bab84ac96eb4ULL, 0x20f15a6d65d2c7d3ULL,
  0x02aa625327709d3bULL, 0xb5cf035942902776ULL,
  0x50cf82be7f219b39ULL, 0xeb69aa1b3f12c453ULL,
  0x354677286ddb9d96ULL, 0x7f0d49ffc1730c2bULL,
  0x7bdfe30ccd826cf1ULL, 0x67d0f7df5923f829ULL,
  0xd9452a8925a6d280ULL, 0xf8783019b55bb252ULL,
  0xfcfc7b6940a09e9aULL, 0x357c5e558e907f94ULL,
  0x620be308800762daULL, 0x603ad429a784c046ULL,
  0xaee68c80cf6e4be8ULL, 0x6c0b895377a7620fULL,
  0xc5ae17039bba8251ULL, 0x72294eeab8a5a853ULL,
  0x114131b3b1316225ULL, 0xb2fed24c87cb5955ULL,
  0x85307d4f7d434008ULL, 0xddbc25082a5d740dULL,
  0xeb6afadf2e89819eULL, 0x871556e61de278a2ULL,
  0x8891c8b85f47aac8ULL, 0x8e9ecc4c10f2c487ULL,
  0x04baa0d291ef9b7cULL, 0x8c63110750925c1fULL,
  0x618852ad3708fea9ULL, 0x4687d0e4925a813aULL,
  0x048067f6aaf2855cULL, 0xef46411b612e839aULL,
  0x45117914b0e5b64aULL, 0x7901181f5dab3808ULL,
  0x50e6644568034fd9ULL, 0xc06da19acfb901f5ULL,
  0x1f22fb040e859857ULL, 0x5d7c6c89b6ad1872ULL,
  0x0258b8994535f79eULL, 0xe89a4debcd73d45cULL,
};

using Hash64 = uint64_t;

template<size_t idx>
constexpr Hash64 crc64(czstr str)
{
  return (crc64<idx - 1>(str) >> 8) ^ crc64_table[(crc64<idx - 1>(str) ^ str[idx]) & 0x000000FF];
}

// This is the stop-recursion function
template<>
constexpr Hash64 crc64<size_t(-1)>(czstr str)
{
  return 0xFFFFFFFFFFFFFFFF;
}

#define COMPILE_TIME_CRC64_STR(x) (crc64<sizeof(x) - 2>(x) ^ 0xFFFFFFFFFFFFFFFF)

inline Hash64 crc64begin()
{
  return 0xFFFFFFFFFFFFFFFF;
}

inline Hash64 crc64end(Hash64 hash)
{
  return hash ^ 0xFFFFFFFFFFFFFFFF;
}

inline Hash64 crc64additive(Hash64 hash, char c)
{
  hash >>= 8;
  return hash ^ crc64_table[(hash ^ c) & 0xFF];
}

inline Hash64 crc64(czstr str)
{
  Hash64 hash = crc64begin();
  while (*str != 0)
  {
    hash = crc64additive(hash, *str);
    str++;
  }

  return crc64end(hash);
}

inline Hash64 crc64(const std::string & str)
{
  return crc64(str.data());
}

inline Hash64 crc64lowercase(czstr str)
{
  Hash64 hash = crc64begin();
  while (*str != 0)
  {
    char c = (*str >= 'A' && *str <= 'Z') ? *str - 'A' + 'a' : *str;

    hash = crc64additive(hash, c);
    str++;
  }

  return crc64end(hash);
}

inline Hash64 crc64lowercase(const std::string & str)
{
  return crc64(str.data());
}

template <typename IntegerType>
inline Hash64 crc64integer(IntegerType i)
{
  Hash64 hash = crc64begin();
  char val[21];
  char * c = &val[20];

  if (i < 0)
  {
    hash = crc64additive(hash, '-');
    do
    {
      *c = '0' - (i % 10);
      i /= 10;
      c--;
    } while (i != 0);
  }
  else
  {
    do
    {
      *c = (i % 10) + '0';
      i /= 10;
      c--;
    } while (i != 0);
  }


  c++;
  while (c != &val[21])
  {
    hash += crc64additive(hash, *c);
    c++;
  }

  return crc64end(hash);
}

