
/* dyld3::preflightSubCacheFile(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*,
   dyld3::CacheInfo*, char*, char const*, dyld3::SharedCacheLoadInfo const*) */

void dyld3::preflightSubCacheFile
               (SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2,CacheInfo *param_3,
               char *param_4,char *param_5,SharedCacheLoadInfo *param_6)

{
  int iVar1;
  undefined8 uVar2;
  int *piVar3;
  char *pcVar4;
  char acStack_158 [256];
  long local_58;
  
  local_58 = ___stack_chk_guard;
  iVar1 = *(int *)param_1;
  _strlcpy(acStack_158,param_4,0x100);
  _strlcat(acStack_158,param_5,0x100);
  iVar1 = openat(iVar1,acStack_158);
  if (iVar1 == -1) {
    piVar3 = ___error();
    if (*piVar3 == 2) {
      param_2[0x18] = (SharedCacheLoadInfo)0x0;
      pcVar4 = "no shared cache file";
    }
    else {
      pcVar4 = "shared cache file open() failed";
    }
    uVar2 = 0;
    *(char **)(param_2 + 0x10) = pcVar4;
  }
  else {
    param_2[0x18] = (SharedCacheLoadInfo)0x1;
    uVar2 = preflightCacheFile(param_1,param_2,param_3,iVar1,(array *)0x0,param_6);
  }
  if (___stack_chk_guard == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(uVar2);
}

