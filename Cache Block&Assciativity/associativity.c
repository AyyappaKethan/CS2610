#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

static __inline__ long rdtsc_s(void)
{
  unsigned a, d;
  asm volatile ("CPUID\n\t"
  "RDTSC\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (a), "=r"
  (d):: "%rax", "%rbx", "%rcx", "%rdx");

  return ((unsigned long)d) | (((unsigned long)a) << 32);
}

static __inline__ long rdtsc_e(void)
{
    unsigned a, d;
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
    int asso;
    int x[10000];
    for(int i=0; i<10000; i++){
        _mm_clflush(&x[i]);
    }
    
    
    for(int i=0; i<10000; i+=1024){
        asso = x[i];
        for(int j=0; j<=i; j+=1024){
            a = rdtsc_s();
            asso =  x[j];
            b = rdtsc_e();
            printf("%lu\n",b-a);
        }
        printf("\n");
    }
}
