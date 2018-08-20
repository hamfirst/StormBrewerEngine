cmake_minimum_required(VERSION 3.0)

include_directories(. ../../. ../.././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_mbedtls 
            ./aes.c
            ./aesni.c
            ./arc4.c
            ./asn1parse.c
            ./asn1write.c
            ./base64.c
            ./bignum.c
            ./blowfish.c
            ./camellia.c
            ./ccm.c
            ./certs.c
            ./cipher.c
            ./cipher_wrap.c
            ./cmac.c
            ./ctr_drbg.c
            ./debug.c
            ./des.c
            ./dhm.c
            ./ecdh.c
            ./ecdsa.c
            ./ecjpake.c
            ./ecp.c
            ./ecp_curves.c
            ./entropy.c
            ./entropy_poll.c
            ./error.c
            ./gcm.c
            ./havege.c
            ./hmac_drbg.c
            ./md.c
            ./md2.c
            ./md4.c
            ./md5.c
            ./md_wrap.c
            ./memory_buffer_alloc.c
            ./net_sockets.c
            ./oid.c
            ./padlock.c
            ./pem.c
            ./pk.c
            ./pkcs11.c
            ./pkcs12.c
            ./pkcs5.c
            ./pkparse.c
            ./pkwrite.c
            ./pk_wrap.c
            ./platform.c
            ./ripemd160.c
            ./rsa.c
            ./rsa_internal.c
            ./sha1.c
            ./sha256.c
            ./sha512.c
            ./ssl_cache.c
            ./ssl_ciphersuites.c
            ./ssl_cli.c
            ./ssl_cookie.c
            ./ssl_srv.c
            ./ssl_ticket.c
            ./ssl_tls.c
            ./threading.c
            ./timing.c
            ./version.c
            ./version_features.c
            ./x509.c
            ./x509write_crt.c
            ./x509write_csr.c
            ./x509_create.c
            ./x509_crl.c
            ./x509_crt.c
            ./x509_csr.c
            ./xtea.c
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_mbedtls 
            ./aes.h
            ./aesni.h
            ./arc4.h
            ./asn1.h
            ./asn1write.h
            ./base64.h
            ./bignum.h
            ./blowfish.h
            ./bn_mul.h
            ./camellia.h
            ./ccm.h
            ./certs.h
            ./check_config.h
            ./cipher.h
            ./cipher_internal.h
            ./cmac.h
            ./compat-1.3.h
            ./config.h
            ./ctr_drbg.h
            ./debug.h
            ./des.h
            ./dhm.h
            ./ecdh.h
            ./ecdsa.h
            ./ecjpake.h
            ./ecp.h
            ./ecp_internal.h
            ./entropy.h
            ./entropy_poll.h
            ./error.h
            ./gcm.h
            ./havege.h
            ./hmac_drbg.h
            ./md.h
            ./md2.h
            ./md4.h
            ./md5.h
            ./md_internal.h
            ./memory_buffer_alloc.h
            ./net.h
            ./net_sockets.h
            ./oid.h
            ./padlock.h
            ./pem.h
            ./pk.h
            ./pkcs11.h
            ./pkcs12.h
            ./pkcs5.h
            ./pk_internal.h
            ./platform.h
            ./platform_time.h
            ./ripemd160.h
            ./rsa.h
            ./rsa_internal.h
            ./sha1.h
            ./sha256.h
            ./sha512.h
            ./ssl.h
            ./ssl_cache.h
            ./ssl_ciphersuites.h
            ./ssl_cookie.h
            ./ssl_internal.h
            ./ssl_ticket.h
            ./threading.h
            ./timing.h
            ./version.h
            ./x509.h
            ./x509_crl.h
            ./x509_crt.h
            ./x509_csr.h
            ./xtea.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_mbedtls 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../.././External/Windows)
  set(PLATFORM_SRC_mbedtls 
            #CPP_WINDOWS_PLACEHOLDER
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(../.././External/Web)
  set(PLATFORM_SRC_mbedtls 
            #CPP_WEB_PLACEHOLDER
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(../.././External/IOS)
  set(PLATFORM_SRC_mbedtls 
            #CPP_IOS_PLACEHOLDER
            )
endif()
if (APPLE && NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(../.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_mbedtls 
            #CPP_MACOS_PLACEHOLDER
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../.././External/Android)
  set(PLATFORM_SRC_mbedtls 
            #CPP_ANDROID_PLACEHOLDER
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(../.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_mbedtls 
            #CPP_LINUX_PLACEHOLDER
            )
endif()

foreach(REFL_FILE mbedtls ${GENERIC_REFL_mbedtls} ${PLATFORM_REFL_mbedtls})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFIL_FILE})
  add_custom_command(OUTPUT ${META_FILE}
                     COMMAND StormRefl -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I. -I../../. -I../.././External
                     MAIN_DEPENDENCY ${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${REFL_FILE})
endforeach()

add_library(mbedtls ${GENERIC_SRC_mbedtls} ${PLATFORM_SRC_mbedtls}
            mbedtls ${GENERIC_HEADER_mbedtls} ${PLATFORM_HEADER_mbedtls})