
/* mach_o::hash_rank(std::span<unsigned char const, 18446744073709551615ul>) */

int __thiscall mach_o::hash_rank(mach_o *this,ulong param_2)

{
  code *pcVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  
  if (param_2 < 0x58) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x180519cd8);
    (*pcVar1)();
  }
  lVar3 = 0;
  lVar4 = -4;
  do {
    if ((&hashPriorities)[lVar3] == (uint)(byte)this[0x25]) {
      return (int)lVar4 + 5;
    }
    lVar3 = lVar3 + 1;
    bVar2 = lVar4 != -1;
    lVar4 = lVar4 + 1;
  } while (bVar2);
  return 0;
}

