
/* WARNING: Type propagation algorithm not settling */
/* dyld3::mapSplitCacheSystemWide(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*) */

void dyld3::mapSplitCacheSystemWide(SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2)

{
  uint *puVar1;
  undefined8 *puVar2;
  CacheInfo *pCVar3;
  ulong *puVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  SharedCacheOptions *pSVar9;
  undefined8 uVar10;
  ulong uVar11;
  DynamicRegion *this;
  ssize_t sVar12;
  SharedCacheLoadInfo *pSVar13;
  long lVar14;
  long extraout_x8;
  long extraout_x8_00;
  long lVar15;
  long lVar16;
  uint uVar17;
  ulong uVar18;
  uint uVar19;
  ulong *puVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  ulong uVar24;
  undefined1 auVar25 [16];
  ulong auStack_f9a0 [2];
  undefined8 local_f990;
  undefined8 uStack_f988;
  undefined1 *local_f980;
  array aaStack_f978 [8];
  ulong auStack_f970 [511];
  CacheInfo aCStack_e978 [392];
  undefined4 local_e7f0;
  uint local_e7d0;
  ulong local_e7c8;
  dyld_cache_header adStack_e7b8 [568];
  undefined8 local_e580;
  undefined8 local_e578;
  undefined8 local_e570;
  undefined2 local_e568;
  undefined8 local_e564;
  undefined8 local_e55c;
  undefined8 local_e550;
  undefined8 uStack_e548;
  CacheInfo local_e180 [8];
  CacheInfo aCStack_e178 [8];
  CacheInfo aCStack_e170 [8];
  CacheInfo aCStack_e168 [8];
  CacheInfo local_e160 [8];
  CacheInfo aCStack_e158 [344];
  uint local_e000 [8];
  uint local_dfe0;
  char local_180 [264];
  long local_78;
  
  auVar25 = (*DAT_1e1f982d0)();
  pSVar13 = auVar25._8_8_;
  pSVar9 = auVar25._0_8_;
  local_78 = ___stack_chk_guard;
  local_e7f0 = 0;
  local_180[0xe8] = '\0';
  local_180[0xe9] = '\0';
  local_180[0xea] = '\0';
  local_180[0xeb] = '\0';
  local_180[0xec] = '\0';
  local_180[0xed] = '\0';
  local_180[0xee] = '\0';
  local_180[0xef] = '\0';
  local_180[0xe0] = '\0';
  local_180[0xe1] = '\0';
  local_180[0xe2] = '\0';
  local_180[0xe3] = '\0';
  local_180[0xe4] = '\0';
  local_180[0xe5] = '\0';
  local_180[0xe6] = '\0';
  local_180[0xe7] = '\0';
  local_180[0xf8] = '\0';
  local_180[0xf9] = '\0';
  local_180[0xfa] = '\0';
  local_180[0xfb] = '\0';
  local_180[0xfc] = '\0';
  local_180[0xfd] = '\0';
  local_180[0xfe] = '\0';
  local_180[0xff] = '\0';
  local_180[0xf0] = '\0';
  local_180[0xf1] = '\0';
  local_180[0xf2] = '\0';
  local_180[0xf3] = '\0';
  local_180[0xf4] = '\0';
  local_180[0xf5] = '\0';
  local_180[0xf6] = '\0';
  local_180[0xf7] = '\0';
  local_180[200] = '\0';
  local_180[0xc9] = '\0';
  local_180[0xca] = '\0';
  local_180[0xcb] = '\0';
  local_180[0xcc] = '\0';
  local_180[0xcd] = '\0';
  local_180[0xce] = '\0';
  local_180[0xcf] = '\0';
  local_180[0xc0] = '\0';
  local_180[0xc1] = '\0';
  local_180[0xc2] = '\0';
  local_180[0xc3] = '\0';
  local_180[0xc4] = '\0';
  local_180[0xc5] = '\0';
  local_180[0xc6] = '\0';
  local_180[199] = '\0';
  local_180[0xd8] = '\0';
  local_180[0xd9] = '\0';
  local_180[0xda] = '\0';
  local_180[0xdb] = '\0';
  local_180[0xdc] = '\0';
  local_180[0xdd] = '\0';
  local_180[0xde] = '\0';
  local_180[0xdf] = '\0';
  local_180[0xd0] = '\0';
  local_180[0xd1] = '\0';
  local_180[0xd2] = '\0';
  local_180[0xd3] = '\0';
  local_180[0xd4] = '\0';
  local_180[0xd5] = '\0';
  local_180[0xd6] = '\0';
  local_180[0xd7] = '\0';
  local_180[0xa8] = '\0';
  local_180[0xa9] = '\0';
  local_180[0xaa] = '\0';
  local_180[0xab] = '\0';
  local_180[0xac] = '\0';
  local_180[0xad] = '\0';
  local_180[0xae] = '\0';
  local_180[0xaf] = '\0';
  local_180[0xa0] = '\0';
  local_180[0xa1] = '\0';
  local_180[0xa2] = '\0';
  local_180[0xa3] = '\0';
  local_180[0xa4] = '\0';
  local_180[0xa5] = '\0';
  local_180[0xa6] = '\0';
  local_180[0xa7] = '\0';
  local_180[0xb8] = '\0';
  local_180[0xb9] = '\0';
  local_180[0xba] = '\0';
  local_180[0xbb] = '\0';
  local_180[0xbc] = '\0';
  local_180[0xbd] = '\0';
  local_180[0xbe] = '\0';
  local_180[0xbf] = '\0';
  local_180[0xb0] = '\0';
  local_180[0xb1] = '\0';
  local_180[0xb2] = '\0';
  local_180[0xb3] = '\0';
  local_180[0xb4] = '\0';
  local_180[0xb5] = '\0';
  local_180[0xb6] = '\0';
  local_180[0xb7] = '\0';
  local_180[0x88] = '\0';
  local_180[0x89] = '\0';
  local_180[0x8a] = '\0';
  local_180[0x8b] = '\0';
  local_180[0x8c] = '\0';
  local_180[0x8d] = '\0';
  local_180[0x8e] = '\0';
  local_180[0x8f] = '\0';
  local_180[0x80] = '\0';
  local_180[0x81] = '\0';
  local_180[0x82] = '\0';
  local_180[0x83] = '\0';
  local_180[0x84] = '\0';
  local_180[0x85] = '\0';
  local_180[0x86] = '\0';
  local_180[0x87] = '\0';
  local_180[0x98] = '\0';
  local_180[0x99] = '\0';
  local_180[0x9a] = '\0';
  local_180[0x9b] = '\0';
  local_180[0x9c] = '\0';
  local_180[0x9d] = '\0';
  local_180[0x9e] = '\0';
  local_180[0x9f] = '\0';
  local_180[0x90] = '\0';
  local_180[0x91] = '\0';
  local_180[0x92] = '\0';
  local_180[0x93] = '\0';
  local_180[0x94] = '\0';
  local_180[0x95] = '\0';
  local_180[0x96] = '\0';
  local_180[0x97] = '\0';
  local_180[0x68] = '\0';
  local_180[0x69] = '\0';
  local_180[0x6a] = '\0';
  local_180[0x6b] = '\0';
  local_180[0x6c] = '\0';
  local_180[0x6d] = '\0';
  local_180[0x6e] = '\0';
  local_180[0x6f] = '\0';
  local_180[0x60] = '\0';
  local_180[0x61] = '\0';
  local_180[0x62] = '\0';
  local_180[99] = '\0';
  local_180[100] = '\0';
  local_180[0x65] = '\0';
  local_180[0x66] = '\0';
  local_180[0x67] = '\0';
  local_180[0x78] = '\0';
  local_180[0x79] = '\0';
  local_180[0x7a] = '\0';
  local_180[0x7b] = '\0';
  local_180[0x7c] = '\0';
  local_180[0x7d] = '\0';
  local_180[0x7e] = '\0';
  local_180[0x7f] = '\0';
  local_180[0x70] = '\0';
  local_180[0x71] = '\0';
  local_180[0x72] = '\0';
  local_180[0x73] = '\0';
  local_180[0x74] = '\0';
  local_180[0x75] = '\0';
  local_180[0x76] = '\0';
  local_180[0x77] = '\0';
  local_180[0x48] = '\0';
  local_180[0x49] = '\0';
  local_180[0x4a] = '\0';
  local_180[0x4b] = '\0';
  local_180[0x4c] = '\0';
  local_180[0x4d] = '\0';
  local_180[0x4e] = '\0';
  local_180[0x4f] = '\0';
  local_180[0x40] = '\0';
  local_180[0x41] = '\0';
  local_180[0x42] = '\0';
  local_180[0x43] = '\0';
  local_180[0x44] = '\0';
  local_180[0x45] = '\0';
  local_180[0x46] = '\0';
  local_180[0x47] = '\0';
  local_180[0x58] = '\0';
  local_180[0x59] = '\0';
  local_180[0x5a] = '\0';
  local_180[0x5b] = '\0';
  local_180[0x5c] = '\0';
  local_180[0x5d] = '\0';
  local_180[0x5e] = '\0';
  local_180[0x5f] = '\0';
  local_180[0x50] = '\0';
  local_180[0x51] = '\0';
  local_180[0x52] = '\0';
  local_180[0x53] = '\0';
  local_180[0x54] = '\0';
  local_180[0x55] = '\0';
  local_180[0x56] = '\0';
  local_180[0x57] = '\0';
  local_180[0x28] = '\0';
  local_180[0x29] = '\0';
  local_180[0x2a] = '\0';
  local_180[0x2b] = '\0';
  local_180[0x2c] = '\0';
  local_180[0x2d] = '\0';
  local_180[0x2e] = '\0';
  local_180[0x2f] = '\0';
  local_180[0x20] = '\0';
  local_180[0x21] = '\0';
  local_180[0x22] = '\0';
  local_180[0x23] = '\0';
  local_180[0x24] = '\0';
  local_180[0x25] = '\0';
  local_180[0x26] = '\0';
  local_180[0x27] = '\0';
  local_180[0x38] = '\0';
  local_180[0x39] = '\0';
  local_180[0x3a] = '\0';
  local_180[0x3b] = '\0';
  local_180[0x3c] = '\0';
  local_180[0x3d] = '\0';
  local_180[0x3e] = '\0';
  local_180[0x3f] = '\0';
  local_180[0x30] = '\0';
  local_180[0x31] = '\0';
  local_180[0x32] = '\0';
  local_180[0x33] = '\0';
  local_180[0x34] = '\0';
  local_180[0x35] = '\0';
  local_180[0x36] = '\0';
  local_180[0x37] = '\0';
  local_180[8] = '\0';
  local_180[9] = '\0';
  local_180[10] = '\0';
  local_180[0xb] = '\0';
  local_180[0xc] = '\0';
  local_180[0xd] = '\0';
  local_180[0xe] = '\0';
  local_180[0xf] = '\0';
  local_180[0] = '\0';
  local_180[1] = '\0';
  local_180[2] = '\0';
  local_180[3] = '\0';
  local_180[4] = '\0';
  local_180[5] = '\0';
  local_180[6] = '\0';
  local_180[7] = '\0';
  local_180[0x18] = '\0';
  local_180[0x19] = '\0';
  local_180[0x1a] = '\0';
  local_180[0x1b] = '\0';
  local_180[0x1c] = '\0';
  local_180[0x1d] = '\0';
  local_180[0x1e] = '\0';
  local_180[0x1f] = '\0';
  local_180[0x10] = '\0';
  local_180[0x11] = '\0';
  local_180[0x12] = '\0';
  local_180[0x13] = '\0';
  local_180[0x14] = '\0';
  local_180[0x15] = '\0';
  local_180[0x16] = '\0';
  local_180[0x17] = '\0';
  iVar7 = preflightMainCacheFile(pSVar9,pSVar13,aCStack_e978,local_180,aaStack_f978);
  uVar10 = 0;
  if (iVar7 != 0) {
    lVar14 = 0;
    uVar21 = (ulong)local_e7d0;
    lVar16 = 0xe000;
    do {
      *(undefined4 *)((long)local_e000 + lVar14 + 8) = 0;
      lVar14 = lVar14 + 0x1c0;
      lVar16 = lVar16 + -0x1c0;
    } while (lVar16 != 0);
    if (1 < local_e7d0) {
      lVar16 = uVar21 - 1;
      lVar14 = 1;
      do {
        local_e55c = 0;
        local_e564 = 0;
        local_e570 = 0;
        local_e580 = 0;
        local_e578 = 0;
        local_e568 = 0;
        local_e550 = 0;
        uStack_e548 = 0;
        uVar11 = preflightSubCacheFile
                           (pSVar9,(SharedCacheLoadInfo *)&local_e580,local_e180 + lVar14 * 0x1c0,
                            local_180,(char *)(auStack_f9a0 + lVar14 * 4U + 1),pSVar13);
        if ((uVar11 & 1) == 0) {
          uVar10 = 0;
          goto LAB_180509c60;
        }
        lVar14 = lVar14 + 1;
        lVar16 = lVar16 + -1;
      } while (lVar16 != 0);
    }
    this = (DynamicRegion *)DyldSharedCache::DynamicRegion::make(0);
    if (this == (DynamicRegion *)0x0) {
      *(char **)(pSVar13 + 0x10) = "Could not vm_allocate dynamic config memory";
      uVar10 = 0;
    }
    else {
      ___bzero(&local_e580,0x400);
      FileIdTuple::getPath((FileIdTuple *)(pSVar13 + 0x1c),(char *)&local_e580);
      DyldSharedCache::DynamicRegion::setDyldCacheFileID
                (this,*(undefined8 *)(pSVar13 + 0x1c),*(undefined8 *)(pSVar13 + 0x24));
      dyld4::ProcessConfig::evaluateProcessorSpecificFunctionVariantFlags
                (*(ProcessConfig **)(pSVar9 + 0x20));
      DyldSharedCache::DynamicRegion::setProcessorFlags((uint)this);
      dyld4::ProcessConfig::evaluateSystemWideFunctionVariantFlags
                (*(ProcessConfig **)(pSVar9 + 0x20));
      DyldSharedCache::DynamicRegion::setSystemWideFlags((uint)this);
      DyldSharedCache::DynamicRegion::setCachePath(this,(char *)&local_e580);
      __platform_memmove(local_e180,aCStack_e978,0x1c0);
      sVar12 = _pread(local_e000[2],adStack_e7b8,0x238,0);
      if (sVar12 == 0x238) {
        buildRootsBitmaps(*(ProcessConfig **)(pSVar9 + 0x20),this,local_e000[2],adStack_e7b8,
                          (bool)pSVar13[0x19],(bool)(*(ProcessConfig **)(pSVar9 + 0x20))[0x151]);
      }
      uStack_f988._4_4_ = local_e7d0 + 1;
      local_f980 = (undefined1 *)&local_f990;
      (*DAT_1e1f982d0)((ulong)uStack_f988._4_4_ * 0xc + 0xf & 0x1ffffffff0);
      lVar14 = (long)&local_f990 - extraout_x8;
      if (local_e7d0 == 0) {
        uVar21 = 0;
        uVar8 = 0;
      }
      else {
        uVar11 = 0;
        uVar8 = 0;
        do {
          puVar1 = (uint *)(lVar14 + uVar11 * 0xc);
          uVar19 = local_e000[uVar11 * 0x70];
          *puVar1 = local_e000[uVar11 * 0x70 + 2];
          puVar1[1] = uVar19;
          uVar8 = uVar19 + uVar8;
          uVar19 = local_dfe0;
          if (uVar11 != 0) {
            uVar19 = 0;
          }
          puVar1[2] = uVar19;
          uVar11 = uVar11 + 1;
        } while (uVar21 != uVar11);
      }
      puVar2 = (undefined8 *)(lVar14 + uVar21 * 0xc);
      *puVar2 = DAT_180523eb0;
      *(undefined4 *)(puVar2 + 1) = 0;
      local_f990 = (ulong)(uVar8 + 1);
      (*DAT_1e1f982d0)(local_f990 * 3);
      puVar20 = (ulong *)(lVar14 + extraout_x8_00 * -0x10);
      if (((byte)pSVar9[5] & 1) != 0) {
        dyld4::console("Mapping the shared cache system wide\n");
      }
      if (local_e7d0 != 0) {
        uVar11 = 0;
        uVar19 = 0;
        do {
          uVar18 = (ulong)local_e000[uVar11 * 0x70];
          if (local_e000[uVar11 * 0x70] != 0) {
            lVar16 = 0;
            uVar17 = uVar19;
            do {
              pCVar3 = local_e180 + lVar16 * 0x30 + uVar11 * 0x1c0;
              uVar19 = uVar17 + 1;
              puVar4 = puVar20 + (ulong)uVar17 * 6;
              uVar22 = *(ulong *)pCVar3;
              uVar24 = *(ulong *)(pCVar3 + 0x18);
              uVar23 = *(ulong *)(pCVar3 + 0x10);
              puVar4[1] = *(ulong *)(pCVar3 + 8);
              *puVar4 = uVar22;
              puVar4[3] = uVar24;
              puVar4[2] = uVar23;
              uVar22 = *(ulong *)(pCVar3 + 0x20);
              puVar4[5] = *(ulong *)(pCVar3 + 0x28);
              puVar4[4] = uVar22;
              lVar16 = lVar16 + 1;
              uVar18 = uVar18 - 1;
              uVar17 = uVar19;
            } while (uVar18 != 0);
          }
          uVar11 = uVar11 + 1;
        } while (uVar11 != uVar21);
      }
      uVar18 = DyldSharedCache::DynamicRegion::size();
      puVar4 = puVar20 + (ulong)uVar8 * 6;
      *puVar4 = local_e7c8;
      uVar11 = local_f990;
      puVar4[1] = uVar18;
      puVar4[3] = 0;
      puVar4[4] = 0;
      puVar4[2] = (ulong)this;
      puVar4[5] = 0x100000001;
      lVar16 = *(ulong *)(pSVar13 + 0x30) - *puVar20;
      if ((*puVar20 <= *(ulong *)(pSVar13 + 0x30) && lVar16 != 0) && ((int)local_f990 != 0)) {
        lVar15 = 0;
        uVar18 = local_f990;
        do {
          puVar4 = puVar20 + lVar15 * 6;
          *puVar4 = *puVar4 + lVar16;
          if (puVar4[3] != 0) {
            puVar4[4] = puVar4[4] + lVar16;
          }
          lVar15 = lVar15 + 1;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      iVar7 = ___shared_region_map_and_slide_2_np(uStack_f988._4_4_,lVar14,uVar11,puVar20);
      DyldSharedCache::DynamicRegion::free(this);
      if (local_e7d0 != 0) {
        lVar14 = 0;
        do {
          if (local_e000[lVar14 * 0x70 + 2] != 0xffffffff) {
            _close(local_e000[lVar14 * 0x70 + 2]);
          }
          lVar14 = lVar14 + 1;
          uVar21 = uVar21 - 1;
        } while (uVar21 != 0);
      }
      uVar8 = reuseExistingCache(pSVar9,pSVar13);
      if (iVar7 == 0) {
        if (uVar8 == 0) {
          if (pSVar9[5] == (SharedCacheOptions)0x1) {
            dyld4::console("mapped dyld cache file system wide\n");
          }
        }
        else if ((*(long *)(pSVar9 + 0x20) != 0) &&
                (*(int *)(*(long *)(pSVar9 + 0x20) + 0x108) == 1)) {
          pcVar5 = "development";
          if (pSVar13[0x19] == (SharedCacheLoadInfo)0x0) {
            pcVar5 = "customer";
          }
          pcVar6 = "mapped";
          if (pSVar13[0x19] == (SharedCacheLoadInfo)0x0) {
            pcVar6 = "unmapped";
          }
          puVar20[-2] = (ulong)pcVar5;
          puVar20[-1] = (ulong)pcVar6;
          dyld4::console("dyld cache mapped system-wide: %s, auth GOTs: %s\n");
        }
      }
      else if ((uVar8 & 1) == 0) {
        if (*(long *)(pSVar13 + 0x10) == 0) {
          uVar10 = 0;
          *(char **)(pSVar13 + 0x10) = "syscall to map cache into shared region failed";
        }
        else {
          uVar10 = 0;
        }
        goto LAB_180509c60;
      }
      uVar10 = 1;
    }
  }
LAB_180509c60:
  if (___stack_chk_guard != local_78) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(uVar10);
  }
  return;
}

