

#include "timing_alt.h"

#ifdef MBEDTLS_INCLUDEOS

int64_t IncludeOSGetTimeMs();

unsigned long mbedtls_timing_hardclock( void )
{
  unsigned int lo,hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return lo;
}

unsigned long mbedtls_timing_get_timer( struct mbedtls_timing_hr_time *val, int reset )
{
  int64_t * start_time = ((int64_t *)&val->opaque[0]);

  if(reset)
  {
    *start_time = IncludeOSGetTimeMs();
    return 0;
  }
  else
  {
    return (unsigned long)(IncludeOSGetTimeMs() - *start_time);
  }
}

void mbedtls_timing_set_delay( void *data, uint32_t int_ms, uint32_t fin_ms )
{
  mbedtls_timing_delay_context * ctx = (mbedtls_timing_delay_context *)data;

  ctx->int_ms = int_ms;
  ctx->fin_ms = fin_ms;

  if(fin_ms != 0)
  {
    mbedtls_timing_get_timer(&ctx->timer, 1);
  }
}

int mbedtls_timing_get_delay( void *data )
{
  mbedtls_timing_delay_context * ctx = (mbedtls_timing_delay_context *)data;
  unsigned long elapsed_ms;

  if( ctx->fin_ms == 0 )
    return -1;

  elapsed_ms = mbedtls_timing_get_timer(&ctx->timer, 0);

  if(elapsed_ms >= ctx->fin_ms)
    return 2;

  if( elapsed_ms >= ctx->int_ms )
    return 1;

  return 0;
}

#endif
