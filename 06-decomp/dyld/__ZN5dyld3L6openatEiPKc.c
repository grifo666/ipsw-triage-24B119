
/* dyld3::openat(int, char const*) */

undefined8 dyld3::openat(int param_1,char *param_2)

{
  undefined8 uVar1;
  int *piVar2;
  
  do {
    uVar1 = _openat(param_1,param_2,0);
    if ((int)uVar1 != -1) {
      return uVar1;
    }
    piVar2 = ___error();
  } while ((*piVar2 == 0x23) || (piVar2 = ___error(), *piVar2 == 4));
  return 0xffffffff;
}

