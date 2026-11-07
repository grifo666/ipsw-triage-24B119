
/* dyld3::preflightMainCacheFile(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*,
   dyld3::CacheInfo*, char*, std::array<char [32], 128ul>*) */

void dyld3::preflightMainCacheFile
               (SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2,CacheInfo *param_3,
               char *param_4,array *param_5)

{
  SharedCacheOptions SVar1;
  SharedCacheOptions SVar2;
  undefined8 uVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  int *piVar8;
  char *pcVar9;
  long lVar10;
  long lVar11;
  stat sStack_420;
  stat sStack_390;
  stat sStack_300;
  char local_270 [8];
  undefined7 uStack_268;
  char cStack_261;
  undefined3 uStack_260;
  char acStack_170 [256];
  long local_70;
  
  uVar3 = s_dyld_shared_cache__18052f398._8_8_;
  uVar7 = s_dyld_shared_cache__18052f398._0_8_;
  lVar10 = 0;
  local_70 = ___stack_chk_guard;
  lVar11 = 0x10;
  do {
    iVar6 = *(int *)param_1;
    SVar1 = param_1[9];
    SVar2 = param_1[10];
    uStack_268 = (undefined7)uVar3;
    _cStack_261 = CONCAT31(0x5f65,SUB81(uVar3,7));
    local_270 = (char  [8])uVar7;
    _strlcat(local_270,*(undefined8 *)((long)&archNames + lVar10),0x100);
    _strlcpy(param_4,local_270,0x100);
    if (((byte)SVar1 & 1) == 0) {
      _strlcpy(acStack_170,local_270,0x100);
      _strlcat(acStack_170,".development",0x100);
      iVar5 = dyld4::fstatat(iVar6,acStack_170,&sStack_300,0);
      if (iVar5 == 0) {
        iVar6 = dyld4::fstatat(iVar6,local_270,&sStack_390,0);
        if ((iVar6 == 0) && (SVar2 == (SharedCacheOptions)0x0)) {
          iVar6 = dyld4::stat("/System/Library/Caches/com.apple.dyld/enable-dylibs-to-override-cache"
                              ,&sStack_420);
          if ((iVar6 == 0) && (sStack_420.st_size < 0x400)) {
            _strlcat(local_270,".development",0x100);
          }
        }
        else {
          _strlcpy(local_270,acStack_170,0x100);
        }
      }
    }
    iVar6 = openat(*(int *)param_1,local_270);
    lVar10 = lVar10 + 0x10;
    bVar4 = lVar11 != 0;
    lVar11 = lVar11 + -0x10;
  } while (iVar6 == -1 && bVar4);
  if (iVar6 == -1) {
    piVar8 = ___error();
    if (*piVar8 == 2) {
      param_2[0x18] = (SharedCacheLoadInfo)0x0;
      pcVar9 = "no shared cache file";
    }
    else {
      pcVar9 = "shared cache file open() failed";
    }
    uVar7 = 0;
    *(char **)(param_2 + 0x10) = pcVar9;
  }
  else {
    param_2[0x18] = (SharedCacheLoadInfo)0x1;
    uVar7 = preflightCacheFile(param_1,param_2,param_3,iVar6,param_5,(SharedCacheLoadInfo *)0x0);
  }
  if (___stack_chk_guard == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(uVar7);
}

