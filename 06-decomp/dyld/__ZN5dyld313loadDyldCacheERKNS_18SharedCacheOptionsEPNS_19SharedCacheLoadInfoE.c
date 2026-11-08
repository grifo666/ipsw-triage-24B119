
/* dyld3::loadDyldCache(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*) */

ulong dyld3::loadDyldCache(SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2)

{
  code *pcVar1;
  int iVar2;
  ulong uVar3;
  ulong unaff_x30;
  
  *(undefined8 *)param_2 = 0;
  *(undefined8 *)(param_2 + 8) = 0;
  *(undefined8 *)(param_2 + 0x10) = 0;
  if (param_1[4] == (SharedCacheOptions)0x1) {
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x18049d258);
      (*pcVar1)();
    }
    uVar3 = mapSplitCachePrivate(param_1,param_2);
    return uVar3;
  }
  iVar2 = reuseExistingCache(param_1,param_2);
  if (iVar2 != 0) {
    return (ulong)(*(long *)(param_2 + 0x10) == 0);
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x18049d234);
    (*pcVar1)();
  }
  uVar3 = mapSplitCacheSystemWide(param_1,param_2);
  return uVar3;
}

