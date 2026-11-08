
/* dyld3::buildRootsBitmaps(dyld4::ProcessConfig const&, DyldSharedCache::DynamicRegion*, int,
   dyld_cache_header const&, bool, bool) */

void dyld3::buildRootsBitmaps
               (ProcessConfig *param_1,DynamicRegion *param_2,int param_3,dyld_cache_header *param_4
               ,bool param_5,bool param_6)

{
  ProcessConfig *pPVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  size_t sVar5;
  undefined8 uVar6;
  ulong uVar7;
  byte *pbVar8;
  long extraout_x12;
  ulong uVar9;
  size_t sVar10;
  ulong uVar11;
  byte *pbVar12;
  byte *pbVar13;
  byte *pbVar14;
  ulong uVar15;
  byte abStack_5b0 [4];
  uint local_5ac;
  ProcessConfig *local_5a8;
  ulong local_5a0;
  undefined8 local_598;
  stat sStack_590;
  stat sStack_500;
  char local_470 [8];
  char acStack_468 [5];
  char acStack_463 [3];
  char acStack_460 [1008];
  long local_70;
  
  local_70 = ___stack_chk_guard;
  uVar11 = (ulong)*(uint *)(param_4 + 0x1c4);
  if (*(uint *)(param_4 + 0x1c4) - 0x10001 < 0xffff0000) goto LAB_18050ab4c;
  uVar9 = uVar11 + 7 >> 3;
  local_598 = param_2;
  (*DAT_1e1f982d0)();
  pbVar12 = abStack_5b0 + -((ulong)((int)uVar9 + 0xf) & 0x7ffffff0);
  (*DAT_1e1f982d0)();
  pbVar13 = pbVar12 + -extraout_x12;
  ___bzero(pbVar12,uVar9);
  ___bzero(pbVar13,uVar9);
  if (param_6) {
    iVar3 = dyld4::SyscallDelegate::bootVolumeMutable();
    if (iVar3 == 0) {
      sVar10 = uVar11 * 0x20;
      (*DAT_1e1f982d0)();
      pbVar14 = pbVar13 + uVar11 * -0x20;
      ___bzero(pbVar14,sVar10);
      param_1 = (ProcessConfig *)_pread(param_3,pbVar14,sVar10,(ulong)*(uint *)(param_4 + 0x1c0));
      if (param_1 != (ProcessConfig *)(uVar11 * 0x20)) goto LAB_18050ab4c;
      uVar15 = 0;
      pbVar8 = pbVar14;
      do {
        uVar4 = *(uint *)(pbVar8 + 0x18);
        if (*(uint *)(pbVar8 + 0x18) <= (uint)uVar15) {
          uVar4 = (uint)uVar15;
        }
        uVar15 = (ulong)uVar4;
        pbVar8 = pbVar8 + 0x20;
      } while (pbVar8 != pbVar14 + sVar10);
      uVar4 = _fstat(param_3,&sStack_500);
      param_1 = (ProcessConfig *)(ulong)uVar4;
      if ((uVar4 != 0) || (sStack_500.st_size < 1)) goto LAB_18050ab4c;
      local_5a0 = uVar15 + 0x400;
      if ((ulong)sStack_500.st_size <= uVar15 + 0x400) {
        local_5a0 = sStack_500.st_size;
      }
      param_1 = (ProcessConfig *)_mmap(0,local_5a0,1,2,param_3,0);
      local_5a8 = param_1;
      if (param_1 == (ProcessConfig *)0xffffffffffffffff) goto LAB_18050ab4c;
      iVar3 = dyld4::stat("/System/Cryptexes/OS",&sStack_590);
      uVar15 = 0;
      local_5ac = (uint)(iVar3 != 0 || (sStack_590.st_mode & 0xf000) != 0x4000);
      do {
        cVar2 = param_5;
        if (pbVar14[uVar15 * 0x20 + 0x1c] == 1) {
          cVar2 = '\x01';
        }
        if (pbVar14[uVar15 * 0x20 + 0x1c] != 0 && cVar2 != '\0') {
          uVar7 = (ulong)*(uint *)(pbVar14 + uVar15 * 0x20 + 0x18);
          sVar10 = local_5a0 - uVar7;
          if (uVar7 <= local_5a0 && sVar10 != 0) {
            pPVar1 = local_5a8 + uVar7;
            sVar5 = __platform_strnlen((char *)pPVar1,sVar10);
            if (sVar5 != sVar10) {
              iVar3 = dyld4::stat((char *)pPVar1,&sStack_590);
              if ((iVar3 == 0) && ((short)sStack_590.st_mode < -0x7000)) {
                uVar7 = uVar15 >> 3 & 0x1fffffff;
                pbVar12[uVar7] = pbVar12[uVar7] | (byte)(1 << (uVar15 & 7));
              }
              if ((local_5ac & 1) == 0) {
                acStack_468[0] = s__System_Cryptexes_OS_1805287c1[8];
                acStack_468[1] = s__System_Cryptexes_OS_1805287c1[9];
                acStack_468[2] = s__System_Cryptexes_OS_1805287c1[10];
                acStack_468[3] = s__System_Cryptexes_OS_1805287c1[0xb];
                acStack_468[4] = s__System_Cryptexes_OS_1805287c1[0xc];
                local_470[0] = s__System_Cryptexes_OS_1805287c1[0];
                local_470[1] = s__System_Cryptexes_OS_1805287c1[1];
                local_470[2] = s__System_Cryptexes_OS_1805287c1[2];
                local_470[3] = s__System_Cryptexes_OS_1805287c1[3];
                local_470[4] = s__System_Cryptexes_OS_1805287c1[4];
                local_470[5] = s__System_Cryptexes_OS_1805287c1[5];
                local_470[6] = s__System_Cryptexes_OS_1805287c1[6];
                local_470[7] = s__System_Cryptexes_OS_1805287c1[7];
                acStack_463[0] = s__System_Cryptexes_OS_1805287c1[0xd];
                acStack_463[1] = s__System_Cryptexes_OS_1805287c1[0xe];
                acStack_463[2] = s__System_Cryptexes_OS_1805287c1[0xf];
                acStack_460[0] = s__System_Cryptexes_OS_1805287c1[0x10];
                acStack_460[1] = s__System_Cryptexes_OS_1805287c1[0x11];
                acStack_460[2] = s__System_Cryptexes_OS_1805287c1[0x12];
                acStack_460[3] = s__System_Cryptexes_OS_1805287c1[0x13];
                acStack_460[4] = s__System_Cryptexes_OS_1805287c1[0x14];
                _strlcat(local_470,pPVar1,0x400);
                iVar3 = dyld4::stat(local_470,&sStack_590);
                if ((iVar3 == 0) && ((short)sStack_590.st_mode < -0x7000)) {
                  uVar7 = uVar15 >> 3 & 0x1fffffff;
                  pbVar13[uVar7] = pbVar13[uVar7] | (byte)(1 << (uVar15 & 7));
                }
              }
            }
          }
        }
        uVar15 = uVar15 + 1;
      } while (uVar11 != uVar15);
      _munmap(local_5a8,local_5a0);
      goto LAB_18050ab2c;
    }
    __platform_memset(pbVar12,0xff,uVar9);
    __platform_memset(pbVar13,0xff,uVar9);
    uVar6 = 3;
  }
  else {
LAB_18050ab2c:
    uVar6 = 1;
  }
  param_1 = (ProcessConfig *)
            DyldSharedCache::DynamicRegion::setRootsBitmaps
                      (local_598,uVar11,pbVar12,uVar9,pbVar13,uVar9,uVar6);
LAB_18050ab4c:
  if (___stack_chk_guard == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(param_1);
}

