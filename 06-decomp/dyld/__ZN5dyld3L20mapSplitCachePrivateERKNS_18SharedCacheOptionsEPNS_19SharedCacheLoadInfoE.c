
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* dyld3::mapSplitCachePrivate(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*) */

byte dyld3::mapSplitCachePrivate(SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2)

{
  long *plVar1;
  undefined8 *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  code *pcVar8;
  bool bVar9;
  int iVar10;
  uint uVar11;
  ulong uVar12;
  long lVar13;
  uint *puVar14;
  DynamicRegion *this;
  void *pvVar15;
  void *pvVar16;
  Lock *pLVar17;
  MemoryManager *this_00;
  SharedCacheLoadInfo *pSVar18;
  SharedCacheOptions SVar19;
  byte bVar20;
  long lVar21;
  DyldSharedCache *pDVar22;
  long extraout_x8;
  ulong uVar23;
  ulong uVar24;
  long lVar25;
  undefined8 *extraout_x12;
  undefined8 *puVar26;
  undefined8 *puVar27;
  undefined8 *extraout_x13;
  long lVar28;
  ulong extraout_x14;
  ulong uVar29;
  DyldSharedCache *pDVar30;
  int *piVar31;
  ulong uVar32;
  undefined8 *puVar33;
  SharedCacheOptions *pSVar34;
  undefined8 uVar35;
  undefined8 uVar36;
  undefined8 uVar37;
  undefined1 auVar38 [16];
  long *local_fcc0;
  ulong uStack_fcb8;
  undefined8 local_fcb0;
  undefined1 local_fca8 [8];
  undefined8 local_fca0;
  ulong local_fc98 [2];
  undefined8 local_fc88;
  SharedCacheOptions *local_fc80;
  DyldSharedCache **local_fc78;
  long *local_fc70;
  int local_fc68;
  undefined4 local_fc64;
  undefined8 local_fc60;
  ulong local_fc58;
  undefined *local_fc50;
  undefined8 local_fc48;
  code *local_fc40;
  undefined *puStack_fc38;
  SharedCacheOptions *local_fc30;
  SharedCacheLoadInfo *pSStack_fc28;
  undefined *local_fc20;
  undefined8 local_fc18;
  code *local_fc10;
  undefined *puStack_fc08;
  SharedCacheOptions *local_fc00;
  SharedCacheLoadInfo *pSStack_fbf8;
  DyldSharedCache *local_fbf0;
  ulong local_fbe8;
  long local_fbe0;
  DyldSharedCache *local_fbd8;
  long *local_fbd0;
  DyldSharedCache *local_fbc8 [3];
  undefined2 local_fbb0 [2];
  undefined1 auStack_fbac [8];
  undefined8 uStack_fba4;
  uint local_fb9c [85];
  uint local_fa48;
  char acStack_fa20 [31];
  byte local_fa01;
  array aaStack_fa00 [4096];
  long local_ea00 [49];
  undefined4 local_e878;
  uint local_e858;
  long local_e850;
  SharedCacheLoadInfo *local_e840;
  undefined *local_e838;
  undefined8 local_e830;
  code *local_e828;
  undefined *local_e820;
  SharedCacheLoadInfo **local_e818;
  DyldSharedCache **local_e810;
  byte *local_e808;
  Lock *local_e718 [20];
  char local_e678;
  long alStack_e590 [128];
  long local_e190 [5];
  uint local_e168 [86];
  uint local_e010 [14240];
  char local_190 [264];
  long local_88;
  
  auVar38 = (*DAT_1e1f982d0)();
  pSVar18 = auVar38._8_8_;
  pSVar34 = auVar38._0_8_;
  local_88 = ___stack_chk_guard;
  local_e878 = 0;
  local_190[0xf8] = '\0';
  local_190[0xf9] = '\0';
  local_190[0xfa] = '\0';
  local_190[0xfb] = '\0';
  local_190[0xfc] = '\0';
  local_190[0xfd] = '\0';
  local_190[0xfe] = '\0';
  local_190[0xff] = '\0';
  local_190[0xf0] = '\0';
  local_190[0xf1] = '\0';
  local_190[0xf2] = '\0';
  local_190[0xf3] = '\0';
  local_190[0xf4] = '\0';
  local_190[0xf5] = '\0';
  local_190[0xf6] = '\0';
  local_190[0xf7] = '\0';
  local_190[0xe8] = '\0';
  local_190[0xe9] = '\0';
  local_190[0xea] = '\0';
  local_190[0xeb] = '\0';
  local_190[0xec] = '\0';
  local_190[0xed] = '\0';
  local_190[0xee] = '\0';
  local_190[0xef] = '\0';
  local_190[0xe0] = '\0';
  local_190[0xe1] = '\0';
  local_190[0xe2] = '\0';
  local_190[0xe3] = '\0';
  local_190[0xe4] = '\0';
  local_190[0xe5] = '\0';
  local_190[0xe6] = '\0';
  local_190[0xe7] = '\0';
  local_190[0xd8] = '\0';
  local_190[0xd9] = '\0';
  local_190[0xda] = '\0';
  local_190[0xdb] = '\0';
  local_190[0xdc] = '\0';
  local_190[0xdd] = '\0';
  local_190[0xde] = '\0';
  local_190[0xdf] = '\0';
  local_190[0xd0] = '\0';
  local_190[0xd1] = '\0';
  local_190[0xd2] = '\0';
  local_190[0xd3] = '\0';
  local_190[0xd4] = '\0';
  local_190[0xd5] = '\0';
  local_190[0xd6] = '\0';
  local_190[0xd7] = '\0';
  local_190[200] = '\0';
  local_190[0xc9] = '\0';
  local_190[0xca] = '\0';
  local_190[0xcb] = '\0';
  local_190[0xcc] = '\0';
  local_190[0xcd] = '\0';
  local_190[0xce] = '\0';
  local_190[0xcf] = '\0';
  local_190[0xc0] = '\0';
  local_190[0xc1] = '\0';
  local_190[0xc2] = '\0';
  local_190[0xc3] = '\0';
  local_190[0xc4] = '\0';
  local_190[0xc5] = '\0';
  local_190[0xc6] = '\0';
  local_190[199] = '\0';
  local_190[0xb8] = '\0';
  local_190[0xb9] = '\0';
  local_190[0xba] = '\0';
  local_190[0xbb] = '\0';
  local_190[0xbc] = '\0';
  local_190[0xbd] = '\0';
  local_190[0xbe] = '\0';
  local_190[0xbf] = '\0';
  local_190[0xb0] = '\0';
  local_190[0xb1] = '\0';
  local_190[0xb2] = '\0';
  local_190[0xb3] = '\0';
  local_190[0xb4] = '\0';
  local_190[0xb5] = '\0';
  local_190[0xb6] = '\0';
  local_190[0xb7] = '\0';
  local_190[0xa8] = '\0';
  local_190[0xa9] = '\0';
  local_190[0xaa] = '\0';
  local_190[0xab] = '\0';
  local_190[0xac] = '\0';
  local_190[0xad] = '\0';
  local_190[0xae] = '\0';
  local_190[0xaf] = '\0';
  local_190[0xa0] = '\0';
  local_190[0xa1] = '\0';
  local_190[0xa2] = '\0';
  local_190[0xa3] = '\0';
  local_190[0xa4] = '\0';
  local_190[0xa5] = '\0';
  local_190[0xa6] = '\0';
  local_190[0xa7] = '\0';
  local_190[0x98] = '\0';
  local_190[0x99] = '\0';
  local_190[0x9a] = '\0';
  local_190[0x9b] = '\0';
  local_190[0x9c] = '\0';
  local_190[0x9d] = '\0';
  local_190[0x9e] = '\0';
  local_190[0x9f] = '\0';
  local_190[0x90] = '\0';
  local_190[0x91] = '\0';
  local_190[0x92] = '\0';
  local_190[0x93] = '\0';
  local_190[0x94] = '\0';
  local_190[0x95] = '\0';
  local_190[0x96] = '\0';
  local_190[0x97] = '\0';
  local_190[0x88] = '\0';
  local_190[0x89] = '\0';
  local_190[0x8a] = '\0';
  local_190[0x8b] = '\0';
  local_190[0x8c] = '\0';
  local_190[0x8d] = '\0';
  local_190[0x8e] = '\0';
  local_190[0x8f] = '\0';
  local_190[0x80] = '\0';
  local_190[0x81] = '\0';
  local_190[0x82] = '\0';
  local_190[0x83] = '\0';
  local_190[0x84] = '\0';
  local_190[0x85] = '\0';
  local_190[0x86] = '\0';
  local_190[0x87] = '\0';
  local_190[0x78] = '\0';
  local_190[0x79] = '\0';
  local_190[0x7a] = '\0';
  local_190[0x7b] = '\0';
  local_190[0x7c] = '\0';
  local_190[0x7d] = '\0';
  local_190[0x7e] = '\0';
  local_190[0x7f] = '\0';
  local_190[0x70] = '\0';
  local_190[0x71] = '\0';
  local_190[0x72] = '\0';
  local_190[0x73] = '\0';
  local_190[0x74] = '\0';
  local_190[0x75] = '\0';
  local_190[0x76] = '\0';
  local_190[0x77] = '\0';
  local_190[0x68] = '\0';
  local_190[0x69] = '\0';
  local_190[0x6a] = '\0';
  local_190[0x6b] = '\0';
  local_190[0x6c] = '\0';
  local_190[0x6d] = '\0';
  local_190[0x6e] = '\0';
  local_190[0x6f] = '\0';
  local_190[0x60] = '\0';
  local_190[0x61] = '\0';
  local_190[0x62] = '\0';
  local_190[99] = '\0';
  local_190[100] = '\0';
  local_190[0x65] = '\0';
  local_190[0x66] = '\0';
  local_190[0x67] = '\0';
  local_190[0x58] = '\0';
  local_190[0x59] = '\0';
  local_190[0x5a] = '\0';
  local_190[0x5b] = '\0';
  local_190[0x5c] = '\0';
  local_190[0x5d] = '\0';
  local_190[0x5e] = '\0';
  local_190[0x5f] = '\0';
  local_190[0x50] = '\0';
  local_190[0x51] = '\0';
  local_190[0x52] = '\0';
  local_190[0x53] = '\0';
  local_190[0x54] = '\0';
  local_190[0x55] = '\0';
  local_190[0x56] = '\0';
  local_190[0x57] = '\0';
  local_190[0x48] = '\0';
  local_190[0x49] = '\0';
  local_190[0x4a] = '\0';
  local_190[0x4b] = '\0';
  local_190[0x4c] = '\0';
  local_190[0x4d] = '\0';
  local_190[0x4e] = '\0';
  local_190[0x4f] = '\0';
  local_190[0x40] = '\0';
  local_190[0x41] = '\0';
  local_190[0x42] = '\0';
  local_190[0x43] = '\0';
  local_190[0x44] = '\0';
  local_190[0x45] = '\0';
  local_190[0x46] = '\0';
  local_190[0x47] = '\0';
  local_190[0x38] = '\0';
  local_190[0x39] = '\0';
  local_190[0x3a] = '\0';
  local_190[0x3b] = '\0';
  local_190[0x3c] = '\0';
  local_190[0x3d] = '\0';
  local_190[0x3e] = '\0';
  local_190[0x3f] = '\0';
  local_190[0x30] = '\0';
  local_190[0x31] = '\0';
  local_190[0x32] = '\0';
  local_190[0x33] = '\0';
  local_190[0x34] = '\0';
  local_190[0x35] = '\0';
  local_190[0x36] = '\0';
  local_190[0x37] = '\0';
  local_190[0x28] = '\0';
  local_190[0x29] = '\0';
  local_190[0x2a] = '\0';
  local_190[0x2b] = '\0';
  local_190[0x2c] = '\0';
  local_190[0x2d] = '\0';
  local_190[0x2e] = '\0';
  local_190[0x2f] = '\0';
  local_190[0x20] = '\0';
  local_190[0x21] = '\0';
  local_190[0x22] = '\0';
  local_190[0x23] = '\0';
  local_190[0x24] = '\0';
  local_190[0x25] = '\0';
  local_190[0x26] = '\0';
  local_190[0x27] = '\0';
  local_190[0x18] = '\0';
  local_190[0x19] = '\0';
  local_190[0x1a] = '\0';
  local_190[0x1b] = '\0';
  local_190[0x1c] = '\0';
  local_190[0x1d] = '\0';
  local_190[0x1e] = '\0';
  local_190[0x1f] = '\0';
  local_190[0x10] = '\0';
  local_190[0x11] = '\0';
  local_190[0x12] = '\0';
  local_190[0x13] = '\0';
  local_190[0x14] = '\0';
  local_190[0x15] = '\0';
  local_190[0x16] = '\0';
  local_190[0x17] = '\0';
  local_190[8] = '\0';
  local_190[9] = '\0';
  local_190[10] = '\0';
  local_190[0xb] = '\0';
  local_190[0xc] = '\0';
  local_190[0xd] = '\0';
  local_190[0xe] = '\0';
  local_190[0xf] = '\0';
  local_190[0] = '\0';
  local_190[1] = '\0';
  local_190[2] = '\0';
  local_190[3] = '\0';
  local_190[4] = '\0';
  local_190[5] = '\0';
  local_190[6] = '\0';
  local_190[7] = '\0';
  local_e840 = pSVar18;
  uVar12 = preflightMainCacheFile(pSVar34,pSVar18,(CacheInfo *)local_ea00,local_190,aaStack_fa00);
  bVar20 = 0;
  if ((int)uVar12 != 0) {
    if (pSVar34[5] == (SharedCacheOptions)0x1) {
      iVar10 = FileIdTuple::getPath((FileIdTuple *)(pSVar18 + 0x1c),(char *)local_e190);
      if (iVar10 != 0) {
        local_fcc0 = local_e190;
        dyld4::console("mapped dyld cache file private to process (%s):\n");
      }
    }
    lVar21 = 0;
    local_fc88 = (ulong)local_e858;
    lVar25 = 0xe000;
    do {
      *(undefined4 *)((long)local_e010 + lVar21 + 8) = 0;
      lVar21 = lVar21 + 0x1c0;
      lVar25 = lVar25 + -0x1c0;
    } while (lVar25 != 0);
    if (1 < local_e858) {
      lVar25 = local_fc88 - 1;
      lVar21 = 1;
      do {
        uStack_fba4 = 0;
        auStack_fbac = (undefined1  [8])0x0;
        local_fbc8[1] = (DyldSharedCache *)0x0;
        local_fbc8[2] = (DyldSharedCache *)0x0;
        local_fbc8[0] = (DyldSharedCache *)0x0;
        local_fbb0[0] = 0;
        local_fb9c[1] = 0;
        local_fb9c[2] = 0;
        local_fb9c[3] = 0;
        local_fb9c[4] = 0;
        uVar12 = preflightSubCacheFile
                           (pSVar34,(SharedCacheLoadInfo *)local_fbc8,
                            (CacheInfo *)(local_e190 + lVar21 * 0x38),local_190,
                            acStack_fa20 + lVar21 * 0x20,local_e840);
        if ((int)uVar12 == 0) goto LAB_180508a30;
        if (pSVar34[5] == (SharedCacheOptions)0x1) {
          ___bzero(alStack_e590,0x400);
          iVar10 = FileIdTuple::getPath((FileIdTuple *)auStack_fbac,(char *)alStack_e590);
          if (iVar10 != 0) {
            local_fcc0 = alStack_e590;
            dyld4::console("mapped dyld cache file private to process (%s):\n");
          }
        }
        lVar21 = lVar21 + 1;
        lVar25 = lVar25 + -1;
      } while (lVar25 != 0);
    }
    __platform_memmove(local_e190,local_ea00,0x1c0);
    local_fc98[1] = local_ea00[0];
    deallocateExistingSharedCache();
    *(long *)local_e840 = local_e190[0];
    *(undefined8 *)(local_e840 + 8) = 0;
    if ((int)local_fc88 == 0) {
      lVar21 = 0;
    }
    else {
      uVar12 = 0;
      do {
        uVar32 = (ulong)local_e010[uVar12 * 0x70];
        local_fc58 = uVar12;
        if (local_e010[uVar12 * 0x70] != 0) {
          lVar21 = 0;
          lVar25 = local_fc98[1] + *(long *)(local_e840 + 8);
          uVar11 = local_e010[uVar12 * 0x70 + 2];
          do {
            plVar1 = local_e190 + uVar12 * 0x38 + lVar21 * 6;
            uVar3 = *(uint *)((long)plVar1 + 0x2c) & 7;
            uVar5 = 0x80012;
            uVar4 = uVar3 | 2;
            if (((uint)(byte)pSVar34[8] & (*(uint *)(plVar1 + 5) & 0x200) >> 9) == 0) {
              uVar5 = 0x12;
              uVar4 = uVar3;
            }
            lVar13 = _mmap((0x180000000 - lVar25) + *plVar1 + *(long *)(local_e840 + 8),plVar1[1],
                           uVar4,uVar5,uVar11,plVar1[2]);
            if (lVar13 == -1) {
              if (pSVar34[5] == (SharedCacheOptions)0x1) {
                puVar14 = (uint *)___error();
                local_fcc0 = (long *)(ulong)*puVar14;
                dyld4::console("mmap(%d, %d) the shared cache region failed due to: %d\n");
              }
              *(undefined8 *)local_e840 = 0;
              if (*(long *)(local_e840 + 0x10) == 0) {
                *(char **)(local_e840 + 0x10) = "mmap() the shared cache region failed";
              }
              lVar21 = 0;
              uVar32 = local_fc88;
              do {
                uVar11 = local_e010[lVar21 * 0x70 + 2];
                if (uVar11 != 0xffffffff) {
                  uVar11 = _close(uVar11);
                }
                uVar12 = (ulong)uVar11;
                lVar21 = lVar21 + 1;
                uVar32 = uVar32 - 1;
              } while (uVar32 != 0);
              goto LAB_180508a30;
            }
            lVar21 = lVar21 + 1;
            uVar32 = uVar32 - 1;
          } while (uVar32 != 0);
        }
        uVar12 = local_fc58 + 1;
      } while (uVar12 != local_fc88);
      lVar21 = *(long *)(local_e840 + 8);
    }
    uVar32 = local_fc88;
    this = (DynamicRegion *)DyldSharedCache::DynamicRegion::make(lVar21 + local_e850);
    if (this == (DynamicRegion *)0x0) {
      uVar12 = _mmap(0x180000000,0xe40000000,0,0x1012,0,0);
      *(undefined8 *)local_e840 = 0;
      *(char **)(local_e840 + 0x10) = "could not mmap() dynamic config memory";
      bVar20 = 0;
    }
    else {
      ___bzero(alStack_e590,0x400);
      iVar10 = FileIdTuple::getPath((FileIdTuple *)(local_e840 + 0x1c),(char *)alStack_e590);
      if (iVar10 != 0) {
        DyldSharedCache::DynamicRegion::setCachePath(this,(char *)alStack_e590);
      }
      DyldSharedCache::DynamicRegion::setDyldCacheFileID
                (this,*(undefined8 *)(local_e840 + 0x1c),*(undefined8 *)(local_e840 + 0x24));
      dyld4::ProcessConfig::evaluateProcessorSpecificFunctionVariantFlags
                (*(ProcessConfig **)(pSVar34 + 0x20));
      DyldSharedCache::DynamicRegion::setProcessorFlags((uint)this);
      dyld4::ProcessConfig::evaluateSystemWideFunctionVariantFlags
                (*(ProcessConfig **)(pSVar34 + 0x20));
      DyldSharedCache::DynamicRegion::setSystemWideFlags((uint)this);
      uVar12 = DyldSharedCache::DynamicRegion::setReadOnly(this);
      if (pSVar34[5] == (SharedCacheOptions)0x1) {
        uVar12 = verboseSharedCacheMappings(*(DyldSharedCache **)local_e840);
      }
      uVar7 = DAT_180523ea8;
      uVar6 = DAT_1805232b8;
      local_fa01 = 1;
      bVar20 = local_fa01;
      if ((int)uVar32 != 0) {
        uVar12 = 0;
        local_fca0 = &local_fc10;
        local_fcb0 = &local_e828;
        local_fca8 = (undefined1  [8])&local_fc40;
        local_fc80 = pSVar34;
        do {
          local_fc70 = local_e190 + uVar12 * 0x38;
          pvVar15 = __platform_memmove(local_fbc8,local_fc70,0x1c0);
          uVar32 = (ulong)local_fa48;
          if (local_fa48 != 0) {
            lVar21 = 0;
            uVar11 = 0;
            SVar19 = pSVar34[0xc];
            uVar23 = uVar32;
            do {
              if (*(long *)(local_fbb0 + lVar21 * 0x18) != 0) {
                uVar11 = uVar11 + 1;
                SVar19 = (SharedCacheOptions)
                         (**(int **)(auStack_fbac + lVar21 * 0x30 + 4) == 5 & (byte)SVar19);
              }
              lVar21 = lVar21 + 1;
              uVar23 = uVar23 - 1;
            } while (uVar23 != 0);
            if (uVar11 != 0) {
              if ((uVar11 < 6 & (byte)SVar19) == 1) {
                lVar21 = 0;
                pDVar22 = (DyldSharedCache *)local_e718;
                local_fbe8 = 8;
                local_fbd8 = (DyldSharedCache *)0x0;
                local_fbd0 = (long *)0x0;
                local_fbe0 = 0;
                local_fc78 = local_fbc8 + uVar12 * 6;
                local_fc98[0] = uVar12;
                local_fbf0 = pDVar22;
                do {
                  if (*(long *)(local_fbb0 + lVar21 * 0x18) != 0) {
                    piVar31 = *(int **)(auStack_fbac + lVar21 * 0x30 + 4);
                    if (*piVar31 != 5) {
                    /* WARNING: Subroutine does not return */
                      ___assert_rtn("mapSplitCachePrivate","SharedCacheRuntime.cpp",0x37d,
                                    "slideInfoHeader->version == 5");
                    }
                    uVar11 = local_fb9c[lVar21 * 0xc] & 7 | 0x200;
                    if (((uint)(byte)pSVar34[8] & (local_fb9c[lVar21 * 0xc + -1] & 0x200) >> 9) == 0
                       ) {
                      uVar11 = local_fb9c[lVar21 * 0xc] & 7;
                    }
                    local_fc58 = CONCAT44(local_fc58._4_4_,uVar11);
                    local_fc64 = (undefined4)local_fc70[0x31];
                    local_fc60 = *(undefined8 *)(local_fbb0 + lVar21 * 0x18 + -4);
                    pDVar30 = local_fbc8[lVar21 * 6];
                    lVar25 = *(long *)(local_e840 + 8);
                    local_fc68 = piVar31[1];
                    iVar10 = piVar31[2];
                    pvVar16 = (void *)DyldSharedCache::mappingName(*(uint *)(local_fc78 + 5),0);
                    plVar1 = local_fbd0;
                    pDVar22 = local_fbd8;
                    uVar12 = local_fbe0 + 1;
                    pvVar15 = pvVar16;
                    if (local_fbe8 < uVar12) {
                      uVar23 = local_fbe8 * 2;
                      if (uVar23 < uVar12 || uVar23 - uVar12 == 0) {
                        uVar23 = uVar12;
                      }
                      local_fbd0 = (long *)((__vm_page_size + uVar23 * 0x30) - 1 & -__vm_page_size);
                      uVar11 = _vm_allocate(_mach_task_self_,(vm_address_t *)&local_fbd8,
                                            (vm_size_t)local_fbd0,0x3c000001);
                      uStack_fcb8 = (ulong)uVar11;
                      if (uVar11 != 0) {
                        CStringBuilderBuffer<256>::CStringBuilderBuffer
                                  ((CStringBuilderBuffer<256> *)&local_e838,false);
                        local_fcc0 = local_fbd0;
                        CStringBuilder::sprintf
                                  ((CStringBuilder *)&local_e838,
                                   "OverflowSafeArray failed to allocate %llu bytes, vm_allocate returned: %d\n"
                                  );
                        DAT_1eaf94d48 = local_e838;
                    /* WARNING: Subroutine does not return */
                        ___assert_rtn("growTo","Array.h",0xbc,"0");
                      }
                      pvVar15 = __platform_memmove(local_fbd8,local_fbf0,local_fbe0 * 0x30);
                      local_fbe8 = (ulong)local_fbd0 / 0x30;
                      local_fbf0 = local_fbd8;
                      if (pDVar22 != (DyldSharedCache *)0x0) {
                        uVar11 = _vm_deallocate(_mach_task_self_,(mach_vm_address_t)pDVar22,
                                                (mach_vm_size_t)plVar1);
                        pvVar15 = (void *)(ulong)uVar11;
                      }
                    }
                    pDVar22 = local_fbf0 + local_fbe0 * 0x30;
                    *(undefined4 *)pDVar22 = local_fc64;
                    *(undefined4 *)(pDVar22 + 4) = (undefined4)local_fc58;
                    *(undefined8 *)(pDVar22 + 8) = local_fc60;
                    *(DyldSharedCache **)(pDVar22 + 0x10) = pDVar30 + lVar25;
                    *(ulong *)(pDVar22 + 0x18) = (ulong)(uint)(iVar10 * local_fc68);
                    *(void **)(pDVar22 + 0x20) = pvVar16;
                    *(int **)(pDVar22 + 0x28) = piVar31;
                    pDVar22 = local_fbf0;
                    pSVar34 = local_fc80;
                    local_fbe0 = local_fbe0 + 1;
                  }
                  lVar25 = local_fbe0;
                  lVar21 = lVar21 + 1;
                  uVar32 = uVar32 - 1;
                } while (uVar32 != 0);
                if (local_fbe0 == 0) {
                  bVar9 = true;
                  uVar12 = local_fc98[0];
                }
                else {
                  pDVar30 = pDVar22 + local_fbe0 * 0x30;
                  uVar11 = (int)local_fbe0 * 4 + 4;
                  do {
                    if (*(int *)*(Lock **)(pDVar22 + 0x28) != 5) {
                    /* WARNING: Subroutine does not return */
                      ___assert_rtn("mapSplitCachePrivate","SharedCacheRuntime.cpp",0x3a0,
                                    "slideInfoHeader->version == 5");
                    }
                    uVar11 = uVar11 + *(int *)(*(Lock **)(pDVar22 + 0x28) + 8) * 2 + 0x19 &
                             0xfffffffc;
                    pDVar22 = pDVar22 + 0x30;
                  } while (pDVar22 != pDVar30);
                  uVar3 = uVar11 + 0x2f & 0xfffffff8;
                  uVar23 = (ulong)uVar3;
                  (*DAT_1e1f982d0)(pvVar15);
                  lVar21 = -(uVar23 + 0xf & 0x1fffffff0);
                  puVar33 = (undefined8 *)((long)&local_fcb0 + lVar21);
                  ___bzero(puVar33,uVar23);
                  *puVar33 = 0xd400000000007;
                  *(uint *)(local_fca8 + lVar21) = uVar3;
                  *(undefined8 *)(local_fca8 + lVar21 + 4) = uVar7;
                  *(uint *)((long)&local_fca0 + lVar21 + 4) = uVar11;
                  uVar32 = local_fc98[1];
                  uVar12 = local_fc98[0];
                  lVar28 = *(long *)(local_e840 + 8);
                  *(long *)((long)local_fc98 + lVar21) = lVar28;
                  *(ulong *)((long)local_fc98 + lVar21 + 8) = uVar32;
                  lVar13 = local_fbe0;
                  pDVar22 = local_fbf0;
                  iVar10 = (int)local_fbe0;
                  *(int *)((long)&local_fc88 + lVar21) = iVar10;
                  pDVar30 = pDVar22 + lVar13 * 0x30;
                  if (lVar13 == 0) {
                    (*DAT_1e1f982d0)();
                    lVar21 = (long)&local_fcc0 + lVar21;
                    lVar13 = 0;
                  }
                  else {
                    uVar24 = 0;
                    uVar11 = iVar10 * 4 + 4;
                    do {
                      pLVar17 = *(Lock **)(pDVar22 + 0x28);
                      if (*(int *)pLVar17 != 5) {
                    /* WARNING: Subroutine does not return */
                        ___assert_rtn("mapSplitCachePrivate","SharedCacheRuntime.cpp",0x3ba,
                                      "slideInfoHeader->version == 5");
                      }
                      *(uint *)((long)&local_fc88 + uVar24 * 4 + lVar21 + 4) = uVar11;
                      piVar31 = (int *)((long)puVar33 + (ulong)(uVar11 + 0x28));
                      iVar10 = *(int *)(pLVar17 + 8) * 2 + 0x16;
                      *piVar31 = iVar10;
                      piVar31[1] = 0xd4000;
                      *(ulong *)(piVar31 + 2) = (long)*(Lock **)(pDVar22 + 0x10) - (lVar28 + uVar32)
                      ;
                      piVar31[4] = 0;
                      uVar3 = *(uint *)(pLVar17 + 8);
                      uVar29 = (ulong)uVar3;
                      *(short *)(piVar31 + 5) = (short)uVar3;
                      if (uVar3 != 0) {
                        lVar13 = 0;
                        do {
                          *(undefined2 *)((long)piVar31 + lVar13 * 2 + 0x16) =
                               *(undefined2 *)(pLVar17 + lVar13 * 2 + 0x18);
                          lVar13 = lVar13 + 1;
                          uVar29 = uVar29 - 1;
                        } while (uVar29 != 0);
                      }
                      uVar24 = (ulong)((int)uVar24 + 1);
                      uVar11 = uVar11 + iVar10 + 3 & 0xfffffffc;
                      pDVar22 = pDVar22 + 0x30;
                    } while (pDVar22 != pDVar30);
                    (*DAT_1e1f982d0)();
                    lVar21 = (long)puVar33 - (extraout_x14 & 0xfffffffffffffff0 | 0x10);
                    lVar28 = 0;
                    puVar26 = extraout_x12;
                    do {
                      if (extraout_x8 == lVar28) {
                    /* WARNING: Subroutine does not return */
                        ___assert_rtn("push_back","Array.h",0x45,"_usedCount < _allocCount");
                      }
                      lVar13 = lVar28 + 1;
                      puVar2 = (undefined8 *)(lVar21 + lVar28 * 0x20);
                      puVar27 = puVar26 + 6;
                      uVar35 = *puVar26;
                      uVar37 = puVar26[3];
                      uVar36 = puVar26[2];
                      puVar2[1] = puVar26[1];
                      *puVar2 = uVar35;
                      puVar2[3] = uVar37;
                      puVar2[2] = uVar36;
                      lVar28 = lVar13;
                      puVar26 = puVar27;
                    } while (puVar27 != extraout_x13);
                  }
                  if (((byte)pSVar34[5] & 1) != 0) {
                    *(ulong *)(lVar21 + -0x10) = uVar12;
                    dyld4::console("Setting up kernel page-in linking for subcache %d\n");
                  }
                  iVar10 = ___map_with_linking_np(lVar21,lVar13,puVar33,uVar23);
                  bVar9 = iVar10 == 0;
                  if ((iVar10 != 0) && (((byte)pSVar34[5] & 1) != 0)) {
                    *(ulong *)(lVar21 + -0x10) = uVar12;
                    dyld4::console(
                                  "__map_with_linking_np(subcache %d) failed, falling back to linking in-process\n"
                                  );
                  }
                }
                local_fbe0 = 0;
                if (local_fbd8 != (DyldSharedCache *)0x0) {
                  _vm_deallocate(_mach_task_self_,(mach_vm_address_t)local_fbd8,
                                 (mach_vm_size_t)local_fbd0);
                }
                if (lVar25 == 0) {
                  bVar9 = true;
                }
                if (bVar9) goto LAB_180509570;
              }
              local_fbf0 = local_fbc8[0];
              if (pSVar34[7] == (SharedCacheOptions)0x1) {
                local_fc20 = &__NSConcreteStackBlock;
                local_fc18 = uVar6;
                local_fc10 = 
                ____ZN5dyld3L20mapSplitCachePrivateERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoE_block_invoke
                ;
                puStack_fc08 = &::___block_descriptor_tmp;
                pSStack_fbf8 = local_e840;
                local_fc00 = pSVar34;
                DyldSharedCache::forEachRegion
                          (local_fbc8[0],
                           (_func_void_void_ptr_ulonglong_ulonglong_uint_uint_ulonglong_ulonglong_bool_ptr
                            *)&local_fc20);
              }
              this_00 = (MemoryManager *)lsl::MemoryManager::memoryManager();
              if ((*(ProtectedStack **)(this_00 + 0x30) == (ProtectedStack *)0x0) ||
                 (iVar10 = lsl::ProtectedStack::onStackInAnyFrameInThisThread
                                     (*(ProtectedStack **)(this_00 + 0x30)), iVar10 == 0)) {
                if (this_00[0x20] == (MemoryManager)0x1) {
                  if ((DAT_fffffc10c == 0) || (2 < DAT_fffffc10c - 2)) goto LAB_180509714;
                  if (DAT_fffffc10c - 2 < 2) {
                    uVar32 = UnkSytemRegRead(3,6,0xf,1,5);
                    if ((uVar32 >> 0x24 & 1) != 0) {
LAB_180509294:
                      DyldSharedCache::fixupDataPages
                                ((long)local_fbf0,SUB81(*(undefined8 *)(local_e840 + 8),0));
                      if (local_e678 != '\0') {
                        *(char **)(local_e840 + 0x10) = "error fixing up shared cache";
                        local_fcc0 = (long *)metadata_visitor::ResolvedValue::value
                                                       ((ResolvedValue *)local_e718);
                        dyld4::console("error: cannot fix up shared cache due to %s\n");
                        local_fa01 = 0;
                      }
                      mach_o::Error::~Error((Error *)local_e718);
                      goto LAB_180509514;
                    }
                  }
                  else {
                    if (DAT_fffffc10c != 4) goto LAB_180509714;
                    lVar21 = UnkSytemRegRead(3,3,4,0,3);
                    if (lVar21 == 2) goto LAB_180509294;
                  }
                  if ((DAT_fffffc10c == 0) || (2 < DAT_fffffc10c - 2)) {
LAB_180509714:
                    /* WARNING: Does not return */
                    pcVar8 = (code *)SoftwareBreakpoint(1,0x180509718);
                    (*pcVar8)();
                  }
                  DataMemoryBarrier(2,2);
                  if (DAT_fffffc10c - 2 < 2) {
                    UnkSytemRegWrite(3,6,0xf,1,5,lRam0000000fffffc0d0);
                    InstructionSynchronizationBarrier();
                    lVar21 = UnkSytemRegRead(3,6,0xf,1,5);
                    if (lRam0000000fffffc0d0 != lVar21) goto LAB_180509714;
                  }
                  else {
                    if (DAT_fffffc10c != 4) goto LAB_180509714;
                    lVar21 = UnkSytemRegRead(3,3,4,0,3);
                    if (lVar21 != 2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                  }
                  DyldSharedCache::fixupDataPages
                            ((long)local_fbf0,SUB81(*(undefined8 *)(local_e840 + 8),0));
                  if (local_e678 != '\0') {
                    *(char **)(local_e840 + 0x10) = "error fixing up shared cache";
                    local_fcc0 = (long *)metadata_visitor::ResolvedValue::value
                                                   ((ResolvedValue *)local_e718);
                    dyld4::console("error: cannot fix up shared cache due to %s\n");
                    local_fa01 = 0;
                  }
                  mach_o::Error::~Error((Error *)local_e718);
                  if ((DAT_fffffc10c == 0) || (2 < DAT_fffffc10c - 2)) goto LAB_180509714;
                  DataMemoryBarrier(2,2);
                  if (DAT_fffffc10c - 2 < 2) {
                    UnkSytemRegWrite(3,6,0xf,1,5,lRam0000000fffffc0d8);
                    InstructionSynchronizationBarrier();
                    lVar21 = UnkSytemRegRead(3,6,0xf,1,5);
                    if (lRam0000000fffffc0d8 != lVar21) goto LAB_180509714;
                  }
                  else {
                    if (DAT_fffffc10c != 4) goto LAB_180509714;
                    lVar21 = UnkSytemRegRead(3,3,4,0,3);
                    if (lVar21 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                  }
                }
                else {
                  lsl::MemoryManager::lockGuard();
                  lVar21 = *(long *)(this_00 + 0x18);
                  if (lVar21 == 0) {
                    lsl::MemoryManager::writeProtect(this_00,false);
                    lVar21 = *(long *)(this_00 + 0x18);
                  }
                  *(long *)(this_00 + 0x18) = lVar21 + 1;
                  lsl::Lock::unlock(local_e718[0]);
                  DyldSharedCache::fixupDataPages
                            ((long)local_fbf0,SUB81(*(undefined8 *)(local_e840 + 8),0));
                  if (local_e678 != '\0') {
                    *(char **)(local_e840 + 0x10) = "error fixing up shared cache";
                    local_fcc0 = (long *)metadata_visitor::ResolvedValue::value
                                                   ((ResolvedValue *)local_e718);
                    dyld4::console("error: cannot fix up shared cache due to %s\n");
                    local_fa01 = 0;
                  }
                  mach_o::Error::~Error((Error *)local_e718);
                  lsl::MemoryManager::lockGuard();
                  lVar21 = *(long *)(this_00 + 0x18);
                  *(long *)(this_00 + 0x18) = lVar21 + -1;
                  if (lVar21 + -1 == 0) {
                    lsl::MemoryManager::writeProtect(this_00,true);
                  }
                  lsl::Lock::unlock(local_e718[0]);
                }
              }
              else {
                if ((DAT_fffffc10c == 0) || (2 < DAT_fffffc10c - 2)) goto LAB_180509714;
                DataMemoryBarrier(2,2);
                if (DAT_fffffc10c - 2 < 2) {
                  UnkSytemRegWrite(3,6,0xf,1,5,lRam0000000fffffc0d0);
                  InstructionSynchronizationBarrier();
                  lVar21 = UnkSytemRegRead(3,6,0xf,1,5);
                  if (lRam0000000fffffc0d0 != lVar21) goto LAB_180509714;
                }
                else {
                  if (DAT_fffffc10c != 4) goto LAB_180509714;
                  lVar21 = UnkSytemRegRead(3,3,4,0,3);
                  if (lVar21 != 2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                    halt_baddata();
                  }
                }
                local_e838 = &__NSConcreteStackBlock;
                local_e830 = uVar6;
                local_e828 = 
                ____ZN3lsl13MemoryManager26withWritableMemoryInternalIZN5dyld3L20mapSplitCachePrivateERKNS2_18SharedCacheOptionsEPNS2_19SharedCacheLoadInfoEE3__0EEvT__block_invoke
                ;
                local_e820 = &___block_descriptor_tmp_49;
                local_e818 = &local_e840;
                local_e810 = &local_fbf0;
                local_e808 = &local_fa01;
                lsl::ProtectedStack::withNestedProtectedStack
                          (*(ProtectedStack **)(this_00 + 0x30),(_func_void *)&local_e838);
                if ((DAT_fffffc10c == 0) || (2 < DAT_fffffc10c - 2)) goto LAB_180509714;
                DataMemoryBarrier(2,2);
                if (DAT_fffffc10c - 2 < 2) {
                  UnkSytemRegWrite(3,6,0xf,1,5,lRam0000000fffffc0d8);
                  InstructionSynchronizationBarrier();
                  lVar21 = UnkSytemRegRead(3,6,0xf,1,5);
                  if (lRam0000000fffffc0d8 != lVar21) goto LAB_180509714;
                }
                else {
                  if (DAT_fffffc10c != 4) goto LAB_180509714;
                  lVar21 = UnkSytemRegRead(3,3,4,0,3);
                  if (lVar21 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                    halt_baddata();
                  }
                }
              }
LAB_180509514:
              if (pSVar34[7] == (SharedCacheOptions)0x1) {
                local_fc50 = &__NSConcreteStackBlock;
                local_fc48 = uVar6;
                local_fc40 = 
                ____ZN5dyld3L20mapSplitCachePrivateERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoE_block_invoke_2
                ;
                puStack_fc38 = &___block_descriptor_tmp_9;
                pSStack_fc28 = local_e840;
                local_fc30 = pSVar34;
                DyldSharedCache::forEachRegion
                          (local_fbf0,
                           (_func_void_void_ptr_ulonglong_ulonglong_uint_uint_ulonglong_ulonglong_bool_ptr
                            *)&local_fc50);
              }
            }
          }
LAB_180509570:
          uVar12 = uVar12 + 1;
        } while (uVar12 != local_fc88);
        lVar21 = 0;
        uVar32 = local_fc88;
        do {
          uVar11 = local_e010[lVar21 * 0x70 + 2];
          if (uVar11 != 0xffffffff) {
            uVar11 = _close(uVar11);
          }
          uVar12 = (ulong)uVar11;
          lVar21 = lVar21 + 1;
          uVar32 = uVar32 - 1;
          bVar20 = local_fa01;
        } while (uVar32 != 0);
      }
    }
  }
LAB_1805095f4:
  if (___stack_chk_guard == local_88) {
    return bVar20 & 1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(uVar12);
LAB_180508a30:
  bVar20 = 0;
  goto LAB_1805095f4;
}

