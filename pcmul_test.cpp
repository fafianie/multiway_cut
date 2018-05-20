using namespace std;

void cpuid(unsigned info, unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx)
{
    __asm__(
        "cpuid;"                                            /* assembly code */
        :"=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) /* outputs */
        :"a" (info)                                         /* input: info into eax */
                                                            /* clobbers: none */
    );
}

void pcmulsup()
{
  cout << endl << "  CPUID TEST" << endl << endl;

  unsigned int eax, ebx, ecx, edx;
  int i;

  bool sup;
 
  for (i = 0; i < 6; ++i)
  {
    cpuid(i, &eax, &ebx, &ecx, &edx);
    printf("eax=%i: %#010x %#010x %#010x %#010x\n", i, eax, ebx, ecx, edx);
    if (i == 1) sup = ecx & pw[1];
  }

  cout << endl << "  PCLMULQDQ SUPPORT: ";
  if (sup) cout << "YES";
  else cout << "NO";
  cout << endl;

}

int main () 
{
	pcmulsup();
	return 0;
}

