cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_mbedtls 
            pem.c
            platform.c
            pk_wrap.c
            ssl_ciphersuites.c
            cmac.c
            ssl_cache.c
            camellia.c
            hmac_drbg.c
            asn1parse.c
            padlock.c
            rsa.c
            aes.c
            pk.c
            x509_create.c
            x509write_crt.c
            ripemd160.c
            havege.c
            bignum.c
            ecdh.c
            sha256.c
            ecdsa.c
            ssl_cookie.c
            blowfish.c
            pkcs11.c
            sha512.c
            ssl_ticket.c
            ecp_curves.c
            md5.c
            certs.c
            debug.c
            xtea.c
            threading.c
            version.c
            net_sockets.c
            ecp.c
            arc4.c
            md_wrap.c
            error.c
            x509_csr.c
            ssl_srv.c
            dhm.c
            entropy.c
            md4.c
            pkcs5.c
            pkcs12.c
            gcm.c
            ccm.c
            pkparse.c
            cipher_wrap.c
            oid.c
            md2.c
            ecjpake.c
            x509_crt.c
            ssl_tls.c
            ssl_cli.c
            sha1.c
            aesni.c
            cipher.c
            des.c
            rsa_internal.c
            ctr_drbg.c
            x509write_csr.c
            x509.c
            timing.c
            asn1write.c
            md.c
            memory_buffer_alloc.c
            version_features.c
            x509_crl.c
            entropy_poll.c
            pkwrite.c
            base64.c
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_mbedtls 
            memory_buffer_alloc.h
            md_internal.h
            rsa_internal.h
            debug.h
            cipher_internal.h
            cmac.h
            x509.h
            ssl.h
            camellia.h
            ssl_cookie.h
            entropy.h
            net.h
            base64.h
            aes.h
            des.h
            bignum.h
            oid.h
            sha1.h
            xtea.h
            bn_mul.h
            platform.h
            ecdh.h
            ripemd160.h
            threading.h
            md.h
            check_config.h
            compat-1.3.h
            rsa.h
            timing.h
            x509_crl.h
            pem.h
            aesni.h
            ecdsa.h
            error.h
            arc4.h
            config.h
            sha512.h
            md5.h
            havege.h
            pk.h
            ctr_drbg.h
            pk_internal.h
            hmac_drbg.h
            pkcs11.h
            ssl_ticket.h
            ssl_internal.h
            sha256.h
            pkcs5.h
            gcm.h
            dhm.h
            ccm.h
            ecjpake.h
            asn1write.h
            md4.h
            asn1.h
            net_sockets.h
            ecp.h
            x509_crt.h
            ecp_internal.h
            platform_time.h
            md2.h
            ssl_cache.h
            pkcs12.h
            cipher.h
            padlock.h
            x509_csr.h
            version.h
            certs.h
            entropy_poll.h
            ssl_ciphersuites.h
            blowfish.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_mbedtls 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_mbedtls 
            )

set(PLATFORM_HEADER_mbedtls 
            )
endif()

foreach(REFL_FILE ${GENERIC_REFL_mbedtls})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH}
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()

add_library(mbedtls ${GENERIC_SRC_mbedtls} ${PLATFORM_SRC_mbedtls}
            ${GENERIC_HEADER_mbedtls} ${PLATFORM_HEADER_mbedtls})