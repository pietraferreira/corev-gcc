/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int src1[] = {-2147483648,  -675, 0, 4358, 2147483647};
int src2[] = {-2147483648,  -675, 0, 4358, 2147483647};

int
main(void)
{
  if (__builtin_corev_addun(src1[0], src2[0], 0) != 0) abort();
  if (__builtin_corev_addun(src1[0], src2[1], 13) != 262143) abort();
  if (__builtin_corev_addun(src1[0], src2[4], 31) != 1) abort();

  if (__builtin_corev_addun(src1[1], src2[1], 1) != 2147482973) abort();
  if (__builtin_corev_addun(src1[1], src2[2], 17) != 32767) abort();
  if (__builtin_corev_addun(src1[1], src2[3], 10) != 3) abort();

  if (__builtin_corev_addun(src1[2], src2[0], 0) != -2147483648) abort();
  if (__builtin_corev_addun(src1[2], src2[2], 9) != 0) abort();
  if (__builtin_corev_addun(src1[2], src2[4], 23) != 255) abort();

  if (__builtin_corev_addun(src1[3], src2[1], 7) != 28) abort();
  if (__builtin_corev_addun(src1[3], src2[2], 14) != 0) abort();
  if (__builtin_corev_addun(src1[3], src2[3], 6) != 136) abort();

  if (__builtin_corev_addun(src1[4], src2[1], 31) != 0) abort();
  if (__builtin_corev_addun(src1[4], src2[3], 0) != -2147479291) abort();
  if (__builtin_corev_addun(src1[4], src2[4], 2) != 1073741823) abort();

  return 0;
}
