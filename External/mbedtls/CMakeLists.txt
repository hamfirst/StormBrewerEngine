cmake_minimum_required(VERSION 3.1.0)

include_directories(. ../../. ../.././External)
set(CMAKE_CXX_STANDARD 14)

set(GENERIC_SRC_mbedtls 
            ./arc4.c
            ./ecp.c
            ./gcm.c
            ./ssl_cache.c
            ./rsa.c
            ./ctr_drbg.c
            ./camellia.c
            ./bignum.c
            ./x509write_crt.c
            ./memory_buffer_alloc.c
            ./ripemd160.c
            ./pk.c
            ./timing.c
            ./aesni.c
            ./cmac.c
            ./blowfish.c
            ./xtea.c
            ./rsa_internal.c
            ./havege.c
            ./entropy_poll.c
            ./md_wrap.c
            ./pkparse.c
            ./pkcs5.c
            ./version_features.c
            ./ecdsa.c
            ./ecp_curves.c
            ./ssl_ticket.c
            ./sha512.c
            ./ssl_srv.c
            ./platform.c
            ./ssl_cli.c
            ./ecdh.c
            ./des.c
            ./sha256.c
            ./debug.c
            ./md2.c
            ./x509_create.c
            ./hmac_drbg.c
            ./pk_wrap.c
            ./sha1.c
            ./padlock.c
            ./md5.c
            ./version.c
            ./ssl_ciphersuites.c
            ./x509write_csr.c
            ./cipher.c
            ./x509_csr.c
            ./md4.c
            ./certs.c
            ./x509_crl.c
            ./pkwrite.c
            ./ssl_tls.c
            ./threading.c
            ./cipher_wrap.c
            ./pkcs12.c
            ./ecjpake.c
            ./aes.c
            ./net_sockets.c
            ./base64.c
            ./pkcs11.c
            ./asn1write.c
            ./x509_crt.c
            ./ccm.c
            ./md.c
            ./dhm.c
            ./asn1parse.c
            ./entropy.c
            ./oid.c
            ./ssl_cookie.c
            ./error.c
            ./x509.c
            ./pem.c
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_mbedtls 
            ./oid.h
            ./aes.h
            ./sha256.h
            ./bn_mul.h
            ./md.h
            ./ctr_drbg.h
            ./pk.h
            ./ecdsa.h
            ./pk_internal.h
            ./ecjpake.h
            ./ecdh.h
            ./ripemd160.h
            ./md4.h
            ./pkcs11.h
            ./xtea.h
            ./cipher_internal.h
            ./error.h
            ./ssl_ticket.h
            ./pkcs12.h
            ./certs.h
            ./asn1write.h
            ./debug.h
            ./rsa.h
            ./cipher.h
            ./camellia.h
            ./md5.h
            ./threading.h
            ./x509_crl.h
            ./check_config.h
            ./config.h
            ./ssl_cache.h
            ./sha1.h
            ./x509_crt.h
            ./net.h
            ./bignum.h
            ./arc4.h
            ./sha512.h
            ./gcm.h
            ./asn1.h
            ./net_sockets.h
            ./dhm.h
            ./version.h
            ./ecp.h
            ./pem.h
            ./base64.h
            ./x509.h
            ./ssl_cookie.h
            ./ecp_internal.h
            ./ccm.h
            ./cmac.h
            ./compat-1.3.h
            ./platform_time.h
            ./blowfish.h
            ./des.h
            ./x509_csr.h
            ./hmac_drbg.h
            ./havege.h
            ./padlock.h
            ./ssl_ciphersuites.h
            ./entropy_poll.h
            ./aesni.h
            ./ssl.h
            ./ssl_internal.h
            ./memory_buffer_alloc.h
            ./rsa_internal.h
            ./entropy.h
            ./md_internal.h
            ./platform.h
            ./md2.h
            ./pkcs5.h
            ./timing.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_mbedtls 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(../.././External/Windows)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(../.././External/Web)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(../.././External/IOS)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(../.././External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(../.././External/Android)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(../.././External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_mbedtls})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/../../. -I${CMAKE_CURRENT_SOURCE_DIR}/../.././External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(mbedtls ${GENERIC_SRC_mbedtls} ${PLATFORM_SRC_mbedtls}
            ${GENERIC_HEADER_mbedtls} ${PLATFORM_HEADER_mbedtls})