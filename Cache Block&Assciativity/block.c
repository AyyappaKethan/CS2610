#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

static __inline__ long rdtsc_s(void)
{ 
  unsigned a,d;
  asm volatile ("CPUID\n\t"
  "RDTSC\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (a), "=r"
  (d):: "%rax", "%rbx", "%rcx", "%rdx");

  return ((unsigned long)d) | (((unsigned long)a) << 32);
}

static __inline__ long rdtsc_e(void)
{
  unsigned a,d;
  asm volatile("RDTSCP\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t"
  "CPUID\n\t": "=r" (a), "=r"
  (d):: "%rax", "%rbx", "%rcx", "%rdx");
  return ((unsigned long)d) | (((unsigned long)a) << 32);
}

int main()
{
    unsigned long a,b;
    int x[256];
    int block;
    for(int i=0;i<256;i++){
        _mm_clflush(&x[i]);
    }
    unsigned long time[256] = {0};
    for(int j=0; j<32 ; j++){
        for(int i=0;i<256;i++){
        a = rdtsc_s();
        block = x[i];
        b = rdtsc_e();
        time[i] = time[i]+b-a;
        }
        for(int k=0;k<256;k++)_mm_clflush(&x[k]);
    }
    for(int i = 0;i<256;i++){
        time[i]/=32;
        printf("%lu %d\n",time[i],i);
    }
    return 0;
}
