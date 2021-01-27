#include "cpuinfo.h"

extern uint64_t g_cpuFeatures;

#if defined(__aarch32__)||defined(__arm__)||defined(_M_ARM)
uint32_t OPENSSL_armcap_P;

void cpuInit(void)
{
  g_cpuFeatures = 0;
  OPENSSL_armcap_P = 0;
}

#elif defined(__aarch64__)||defined(_M_ARM64)

#include <sys/auxv.h>
#include <asm/hwcap.h>
#include <arm_neon.h>

uint32_t OPENSSL_armcap_P;

void cpuInit(void)
{
  g_cpuFeatures = 0;

  unsigned long hwcaps= getauxval(AT_HWCAP);

// see <uapi/asm/hwcap.h> kernel header
  if(hwcaps & ARM_HWCAP_FP) g_cpuFeatures |= ARM_HWCAP_FP;
  if(hwcaps & ARM_HWCAP_ASIMD) g_cpuFeatures |= ARM_HWCAP_ASIMD;
  if(hwcaps & ARM_HWCAP_EVTSTRM) g_cpuFeatures |= ARM_HWCAP_EVTSTRM;
  if(hwcaps & ARM_HWCAP_AES) g_cpuFeatures |= ARM_HWCAP_AES;
  if(hwcaps & ARM_HWCAP_PMULL) g_cpuFeatures |= ARM_HWCAP_PMULL;
  if(hwcaps & ARM_HWCAP_SHA1) g_cpuFeatures |= ARM_HWCAP_SHA1;
  if(hwcaps & ARM_HWCAP_SHA2) g_cpuFeatures |= ARM_HWCAP_SHA2;
  if(hwcaps & ARM_HWCAP_CRC32) g_cpuFeatures |= ARM_HWCAP_CRC32;
  if(hwcaps & ARM_HWCAP_ATOMICS) g_cpuFeatures |= ARM_HWCAP_ATOMICS;
  if(hwcaps & ARM_HWCAP_FPHP) g_cpuFeatures |= ARM_HWCAP_FPHP;
  if(hwcaps & ARM_HWCAP_ASIMDHP) g_cpuFeatures |= ARM_HWCAP_ASIMDHP;
  if(hwcaps & ARM_HWCAP_CPUID) g_cpuFeatures |= ARM_HWCAP_CPUID;
  if(hwcaps & ARM_HWCAP_ASIMDRDM) g_cpuFeatures |= ARM_HWCAP_ASIMDRDM;
  if(hwcaps & ARM_HWCAP_JSCVT) g_cpuFeatures |= ARM_HWCAP_JSCVT;
  if(hwcaps & ARM_HWCAP_FCMA) g_cpuFeatures |= ARM_HWCAP_FCMA;
  if(hwcaps & ARM_HWCAP_LRCPC) g_cpuFeatures |= ARM_HWCAP_LRCPC;
  if(hwcaps & ARM_HWCAP_DCPOP) g_cpuFeatures |= ARM_HWCAP_DCPOP;
  if(hwcaps & ARM_HWCAP_SHA3) g_cpuFeatures |= ARM_HWCAP_SHA3;
  if(hwcaps & ARM_HWCAP_SM3) g_cpuFeatures |= ARM_HWCAP_SM3;
  if(hwcaps & ARM_HWCAP_SM4) g_cpuFeatures |= ARM_HWCAP_SM4;
  if(hwcaps & ARM_HWCAP_ASIMDDP) g_cpuFeatures |= ARM_HWCAP_ASIMDDP;
  if(hwcaps & ARM_HWCAP_SHA512) g_cpuFeatures |= ARM_HWCAP_SHA512;
  if(hwcaps & ARM_HWCAP_SVE) g_cpuFeatures |= ARM_HWCAP_SVE;
  if(hwcaps & ARM_HWCAP_ASIMDFHM) g_cpuFeatures |= ARM_HWCAP_ASIMDFHM;
  if(hwcaps & ARM_HWCAP_DIT) g_cpuFeatures |= ARM_HWCAP_DIT;
  if(hwcaps & ARM_HWCAP_USCAT) g_cpuFeatures |= ARM_HWCAP_USCAT;
  if(hwcaps & ARM_HWCAP_ILRCPC) g_cpuFeatures |= ARM_HWCAP_ILRCPC;
  if(hwcaps & ARM_HWCAP_FLAGM) g_cpuFeatures |= ARM_HWCAP_FLAGM;


  OPENSSL_setcap();
}

#elif defined(__x86_64__)||defined(__i386__)||defined(_M_X64)||defined(_M_IX86)

// mask off avx if os does not support
static int AVX=0;
// OSXSAVE
static int OSXSAVE = 0;
static int vendorIsIntel = 0, vendorIsAMD = 0;

uint32_t OPENSSL_ia32cap_P[4];


#include <string.h>
#include <sys/utsname.h>
#if defined(__x86_64__)||defined(__i386__)

#include <cpuid.h>

#endif

#if defined(__x86_64__)||defined(__i386__)||defined(_M_X64)||defined(_M_IX86)
static int check_xcr0_ymm()
{
  uint32_t xcr0;
  __asm__ ("xgetbv" : "=a" (xcr0) : "c" (0) : "%edx" );
  return ((xcr0 & 6) == 6); /* checking if xmm and ymm state are enabled in XCR0 */
}
#endif

static __inline int
get_cpuid_count (unsigned int __level, unsigned int __count,
                 unsigned int *__eax, unsigned int *__ebx,
                 unsigned int *__ecx, unsigned int *__edx)
{
  unsigned int __ext = __level & 0x80000000;
  if ((int)__get_cpuid_max (__ext, 0) < (int)__level)
    return 0;

  __cpuid_count (__level, __count, *__eax, *__ebx, *__ecx, *__edx);
  return 1;
}

#define x86_cpuid(func, values) get_cpuid_count(func, 0, values, values+1, values+2, values+3)

void cpuInit(void)
{
  g_cpuFeatures = 0;

#if defined(__i386__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
  unsigned int regs[4];

  /* According to http://en.wikipedia.org/wiki/CPUID */

// $ echo -n GenuineIntel | hexdump -C
// 00000000  47 65 6e 75 69 6e 65 49  6e 74 65 6c              |GenuineIntel|
#define VENDOR_INTEL_b  0x756e6547
#define VENDOR_INTEL_c  0x6c65746e
#define VENDOR_INTEL_d  0x49656e69

// $ echo -n AuthenticAMD | hexdump -C
// 00000000  41 75 74 68 65 6e 74 69  63 41 4d 44              |AuthenticAMD|
#define VENDOR_AMD_b  0x68747541
#define VENDOR_AMD_c  0x444d4163
#define VENDOR_AMD_d  0x69746e65

  x86_cpuid(0, regs);
  int maxid = regs[0];
  vendorIsIntel = (regs[1] == VENDOR_INTEL_b &&
                   regs[2] == VENDOR_INTEL_c &&
                   regs[3] == VENDOR_INTEL_d);
  vendorIsAMD   = (regs[1] == VENDOR_AMD_b &&
                   regs[2] == VENDOR_AMD_c &&
                   regs[3] == VENDOR_AMD_d);

  x86_cpuid(1, regs);
  OPENSSL_ia32cap_P[0] = regs[3];
  OPENSSL_ia32cap_P[1] = regs[2];
  /*
  Index 0:
    EDX for CPUID where EAX = 1
    Bit 20 is always zero
    Bit 28 is adjusted to reflect whether the data cache is shared between
      multiple logical cores
    Bit 30 is used to indicate an Intel CPU
  Index 1:
    ECX for CPUID where EAX = 1
    Bit 11 is used to indicate AMD XOP support, not SDBG
  Index 2:
    EBX for CPUID where EAX = 7
  Index 3:
    ECX for CPUID where EAX = 7
  */
  OPENSSL_ia32cap_P[0] &= ~(1 << 20);
  OPENSSL_ia32cap_P[0] = (vendorIsIntel << 30) | ( OPENSSL_ia32cap_P[0] & ~(1 << 30));
  if(!vendorIsAMD) OPENSSL_ia32cap_P[1] &= ~(1 << 11);

  if ((regs[2] & (1 << 23)) != 0) {
    g_cpuFeatures |= CPU_X86_FEATURE_POPCNT;
  }
  if (vendorIsIntel && (regs[2] & (1 << 22)) != 0) {
    g_cpuFeatures |= CPU_X86_FEATURE_MOVBE;
  }
  if ((regs[2] & (1 << 25)) != 0) {
    g_cpuFeatures |= CPU_X86_FEATURE_AES_NI;
  }
  if ((regs[2] & (1 << 30)) != 0) {
    g_cpuFeatures |= CPU_X86_FEATURE_RDRAND;
  }
  if ((regs[2] & (1 << 12)) != 0) {
    g_cpuFeatures |= CPU_X86_FEATURE_FMA;
  }
  if ((regs[2] & (1 << 27)) != 0) {
    OSXSAVE = 1;
  }

  if (maxid>=7) {
    x86_cpuid(7, regs);
    OPENSSL_ia32cap_P[2] = regs[1];
    OPENSSL_ia32cap_P[3] = regs[2];
    if ((regs[1] & (1 << 29)) != 0) {
      g_cpuFeatures |= CPU_X86_FEATURE_SHA_NI;
    }
    if ((regs[1] & (1 << 18)) != 0) {
      g_cpuFeatures |= CPU_X86_FEATURE_RDSEED;
    }
  } else {
    OPENSSL_ia32cap_P[2] = 0;
    OPENSSL_ia32cap_P[3] = 0;
  }

  if (!(AVX&&OSXSAVE)) {
    g_cpuFeatures &= ~CPU_X86_FEATURE_FMA;
  }
#endif

  OPENSSL_setcap();
}

#else

void cpuInit(void)
{
  g_cpuFeatures = 0;
}

#endif

uint64_t getCpuFeatures(void)
{
  return g_cpuFeatures;
}


intptr_t getCpuFamily(void)
{
#if defined(__aarch64__)||defined(_M_ARM64)
  return CPU_FAMILY_ARM64;
#elif defined(__arm__)||defined(_M_ARM)
  return CPU_FAMILY_ARM;
#elif defined(__x86_64__)||defined(_M_X64)
  return CPU_FAMILY_X86_64;
#elif defined(__i386__)||defined(_M_IX86)
  return CPU_FAMILY_X86;
#else
  return CPU_FAMILY_UNKNOWN ;
#endif
}

void OPENSSL_setcap(void)
{
#if defined(__aarch64__)||defined(_M_ARM64)
  OPENSSL_armcap_P = ARMV7_NEON;
  OPENSSL_armcap_P |= (g_cpuFeatures & ARM_HWCAP_AES) ? ARMV8_AES : 0;
  OPENSSL_armcap_P |= (g_cpuFeatures & ARM_HWCAP_SHA1) ? ARMV8_SHA1 : 0;
  OPENSSL_armcap_P |= (g_cpuFeatures & ARM_HWCAP_SHA2) ? ARMV8_SHA256 : 0;
  OPENSSL_armcap_P |= (g_cpuFeatures & ARM_HWCAP_PMULL) ? ARMV8_PMULL : 0;
  OPENSSL_armcap_P |= (g_cpuFeatures & ARM_HWCAP_SHA512) ? ARMV8_SHA512 : 0;
#elif defined(__x86_64__)||defined(__i386__)||defined(_M_X64)||defined(_M_IX86)
  if (!(AVX&&OSXSAVE)) {
    g_cpuFeatures &= ~CPU_X86_FEATURE_FMA;
  }
  // #CH TODO my guess is all of this stuff can be deleted
  OPENSSL_ia32cap_P[1] &= ~(1 << 23);
  OPENSSL_ia32cap_P[1] |= (g_cpuFeatures & CPU_X86_FEATURE_POPCNT) ? (1 << 23) : 0;
  OPENSSL_ia32cap_P[1] &= ~(1 << 22);
  OPENSSL_ia32cap_P[1] |= (g_cpuFeatures & CPU_X86_FEATURE_MOVBE) ? (1 << 22) : 0;
  OPENSSL_ia32cap_P[1] &= ~(1 << 25);
  OPENSSL_ia32cap_P[1] |= (g_cpuFeatures & CPU_X86_FEATURE_AES_NI) ? (1 << 25) : 0;
  OPENSSL_ia32cap_P[1] &= ~(1 << 30);
  OPENSSL_ia32cap_P[1] |= (g_cpuFeatures & CPU_X86_FEATURE_RDRAND) ? (1 << 30) : 0;
  OPENSSL_ia32cap_P[1] &= ~(1 << 12);
  OPENSSL_ia32cap_P[1] |= (g_cpuFeatures & CPU_X86_FEATURE_FMA) ? (1 << 12) : 0;
  OPENSSL_ia32cap_P[2] &= ~(1 << 29);
  OPENSSL_ia32cap_P[2] |= (g_cpuFeatures & CPU_X86_FEATURE_SHA_NI) ? (1 << 29) : 0;
  OPENSSL_ia32cap_P[2] &= ~(1 << 18);
  OPENSSL_ia32cap_P[2] |= (g_cpuFeatures & CPU_X86_FEATURE_RDSEED) ? (1 << 18) : 0;

#endif
}
