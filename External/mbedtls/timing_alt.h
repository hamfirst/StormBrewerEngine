
#ifndef MBEDTLS_TIMING_ALT_H
#define MBEDTLS_TIMING_ALT_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#ifdef MBEDTLS_INCLUDEOS

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mbedtls_timing_hr_time
{
  unsigned char opaque[32];
};

/**
 * \brief          Context for mbedtls_timing_set/get_delay()
 */
typedef struct
{
  struct mbedtls_timing_hr_time   timer;
  uint32_t                        int_ms;
  uint32_t                        fin_ms;
} mbedtls_timing_delay_context;

unsigned long mbedtls_timing_hardclock( void );
unsigned long mbedtls_timing_get_timer( struct mbedtls_timing_hr_time *val, int reset );

void mbedtls_timing_set_delay( void *data, uint32_t int_ms, uint32_t fin_ms );
int mbedtls_timing_get_delay( void *data );

#ifdef __cplusplus
}
#endif

#endif

#endif
