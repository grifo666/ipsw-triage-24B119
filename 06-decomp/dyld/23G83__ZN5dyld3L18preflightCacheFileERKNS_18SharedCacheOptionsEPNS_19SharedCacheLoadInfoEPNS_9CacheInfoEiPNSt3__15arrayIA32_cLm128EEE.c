
/* dyld3::preflightCacheFile(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*,
   dyld3::CacheInfo*, int, std::array<char [32], 128ul>*) */

void dyld3::preflightCacheFile
               (SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2,CacheInfo *param_3,
               int param_4,array *param_5)

{
  long *plVar1;
  ulong *puVar2;
  CacheInfo *pCVar3;
  byte bVar4;
  long lVar5;
  int iVar7;
  int iVar6;
  long lVar8;
  ssize_t sVar9;
  undefined8 uVar10;
  void *pvVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  char *pcVar15;
  long lVar16;
  ulong uVar17;
  long lVar18;
  undefined8 *puVar19;
  ulong uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  ulong uVar24;
  bool bVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined1 auVar28 [16];
  stat sStack_5d38;
  undefined1 auStack_5ca8 [24];
  undefined8 local_5c90 [893];
  ulong local_40a8;
  ulong local_40a0;
  long local_4098;
  long alStack_4090 [3];
  int aiStack_4078 [2];
  ulong local_4070 [2];
  uint local_4060;
  uint local_405c;
  uint auStack_4058 [2];
  long alStack_4050 [9];
  long local_4008;
  int local_3f98;
  byte local_3f93;
  long local_3f90;
  undefined8 uStack_3f88;
  undefined8 local_3f80;
  uint local_3f38;
  int local_3f00;
  uint local_3ee8;
  uint local_3ee4;
  int local_3ea8;
  long local_3e80;
  undefined8 local_3e78;
  long local_70;
  
  uVar17 = (ulong)(uint)param_4;
  auVar28 = (*DAT_1ee63a0d8)();
  lVar12 = auVar28._8_8_;
  lVar8 = auVar28._0_8_;
  local_70 = ___stack_chk_guard;
  iVar7 = (int)uVar17;
  iVar6 = _fstat(iVar7,&sStack_5d38);
  if (iVar6 == 0) {
    FileIdTuple::FileIdTuple((FileIdTuple *)local_4070,&sStack_5d38);
    *(ulong *)(lVar12 + 0x24) = local_4070[1];
    *(ulong *)(lVar12 + 0x1c) = local_4070[0];
    sVar9 = _pread(iVar7,local_4070,0x4000,0);
    if (sVar9 == 0x4000) {
      if (local_4070[0] == 0x2031765f646c7964 && local_4070[1] == 0x6534366d726120) {
        if (0xdf < local_4060) {
          iVar6 = mach_o::Platform::value((Platform *)(lVar8 + 0x10));
          if (local_3f98 == iVar6) {
            if ((local_3f93 >> 1 & 1) != 0) goto LAB_18019b64c;
          }
          else if ((local_3f00 == 0) || (local_3f00 != iVar6)) {
LAB_18019b64c:
            pcVar15 = "shared cache file is for a different platform";
            goto LAB_18019b580;
          }
        }
        if (0xfffffff7 < local_405c - 9) {
          uVar24 = (ulong)local_4060;
          lVar18 = uVar24 - 0x4070;
          lVar5 = (ulong)local_405c * 0x20 + lVar18;
          uVar20 = *(ulong *)((long)local_4070 + uVar24 + 0x10);
          if (uVar20 == 0) {
            if (alStack_4050[2] + alStack_4050[1] != sStack_5d38.st_size) {
              pcVar15 = "shared cache code signature size is invalid";
              goto LAB_18019b698;
            }
            if (local_405c < 2) goto LAB_18019b6b4;
            if (*(int *)((long)aiStack_4078 + lVar5 + 0x4070) != 1) {
              *(char **)(lVar12 + 0x10) = "shared cache linkedit permissions are invalid";
            }
LAB_18019b6a4:
            bVar25 = true;
            uVar23 = *(uint *)((long)auStack_4058 + uVar24) | 4;
          }
          else {
            pcVar15 = "shared cache text file offset is invalid";
LAB_18019b698:
            *(char **)(lVar12 + 0x10) = pcVar15;
            if (1 < local_405c) goto LAB_18019b6a4;
LAB_18019b6b4:
            bVar25 = false;
            uVar23 = *(uint *)((long)auStack_4058 + uVar24);
          }
          if (uVar23 != 5) {
            *(char **)(lVar12 + 0x10) = "shared cache text permissions are invalid";
          }
          if (*(long *)(lVar12 + 0x10) == 0) {
            uVar23 = 1;
LAB_18019b6dc:
            if (local_405c == uVar23) {
              local_40a8 = 0;
              local_40a0 = alStack_4050[1];
              local_4098 = alStack_4050[2];
              iVar6 = _fcntl(iVar7,0x61);
              if (iVar6 == -1) {
                pcVar15 = "code signature registration for shared cache failed";
              }
              else if (local_40a8 < (ulong)alStack_4050[1]) {
                pcVar15 = "code signature does not cover entire shared cache file";
              }
              else {
                pvVar11 = (void *)_mmap(0,0x4000,5,2,uVar17,0);
                if (pvVar11 == (void *)0xffffffffffffffff) {
                  pcVar15 = "first page of shared cache not mmap()able";
                }
                else {
                  iVar6 = __platform_memcmp(pvVar11,local_4070,0x4000);
                  if (iVar6 == 0) {
                    _munmap(pvVar11,0x4000);
                    *(uint *)(param_3 + 0x180) = local_405c;
                    if (local_405c != 0) {
                      lVar16 = 0;
                      lVar18 = 0;
                      bVar4 = *(byte *)(lVar8 + 8);
                      do {
                        uVar23 = *(uint *)((long)auStack_4058 + uVar24);
                        uVar22 = *(uint *)((long)auStack_4058 + uVar24 + 4);
                        if (local_4060 < 0x139) {
                          if (lVar18 == 0x30) {
                            uVar21 = 0x20;
                            lVar13 = alStack_4050[4];
                            lVar14 = alStack_4050[3];
                          }
                          else {
                            lVar13 = 0;
                            lVar14 = 0;
                            uVar21 = 0x20;
                          }
                        }
                        else {
                          lVar13 = (ulong)local_3f38 + lVar16 + -0x4070;
                          uVar17 = *(ulong *)((long)alStack_4050 + lVar13 + 0x4078);
                          uVar21 = 0x60;
                          if ((uVar17 & 1) != 0) {
                            uVar21 = 0x20;
                          }
                          if (((uint)uVar17 >> 2 & 1) != 0) {
                            if ((bVar4 & 1) == 0) {
                              uVar22 = uVar22 | 2;
                            }
                            else {
                              uVar23 = uVar23 | 0x200;
                            }
                          }
                          lVar14 = *(long *)((long)auStack_4058 + lVar13 + 0x4070);
                          lVar13 = *(long *)((long)alStack_4050 + lVar13 + 0x4070);
                          if ((uVar17 & 0x40) != 0) {
                            uVar22 = 3;
                            uVar23 = 3;
                          }
                        }
                        pCVar3 = param_3 + lVar18;
                        uVar10 = *(undefined8 *)((long)local_4070 + uVar24);
                        *(undefined8 *)(pCVar3 + 8) = *(undefined8 *)((long)local_4070 + uVar24 + 8)
                        ;
                        *(undefined8 *)pCVar3 = uVar10;
                        *(undefined8 *)(pCVar3 + 0x10) =
                             *(undefined8 *)((long)local_4070 + uVar24 + 0x10);
                        *(undefined8 *)(pCVar3 + 0x18) = 0;
                        *(undefined8 *)(pCVar3 + 0x20) = 0;
                        *(uint *)(pCVar3 + 0x28) = uVar23;
                        *(uint *)(pCVar3 + 0x2c) = uVar22;
                        if (lVar13 != 0) {
                          if (!bVar25) {
                            *(int *)(param_3 + 0x188) = iVar7;
                    /* WARNING: Subroutine does not return */
                            std::__throw_bad_optional_access_abi_nqn210106_();
                          }
                          *(long *)(pCVar3 + 0x20) =
                               (lVar14 - *(long *)((long)alStack_4090 + lVar5 + 0x4080)) +
                               *(long *)((long)alStack_4090 + lVar5 + 0x4070);
                          *(long *)(pCVar3 + 0x18) = lVar13;
                          *(uint *)(pCVar3 + 0x28) = uVar23 | uVar21;
                          *(uint *)(pCVar3 + 0x2c) = uVar22 | uVar21;
                        }
                        lVar18 = lVar18 + 0x30;
                        lVar16 = lVar16 + 0x38;
                        uVar24 = uVar24 + 0x20;
                      } while ((ulong)local_405c * 0x30 != lVar18);
                      *(int *)(param_3 + 0x188) = iVar7;
                    }
                    if (local_3ee4 < 0x80) {
                      if ((param_5 != (array *)0x0) || (local_3ee4 == 0)) {
                        param_3[0x185] = (CacheInfo)(0x1c8 < local_4060);
                        if (0x1c8 < local_4060) {
                          sVar9 = _pread(iVar7,auStack_5ca8,0x1c00,(ulong)local_3ee8);
                          if (sVar9 != 0x1c00) {
                            pcVar15 = 
                            "shared cache file pread() failed, could not read subcache entries";
                            goto LAB_18019b580;
                          }
                          uVar17 = (ulong)local_3ee4;
                          if (local_3ee4 != 0) {
                            puVar19 = local_5c90;
                            do {
                              uVar10 = *puVar19;
                              uVar27 = puVar19[3];
                              uVar26 = puVar19[2];
                              *(undefined8 *)(param_5 + 8) = puVar19[1];
                              *(undefined8 *)param_5 = uVar10;
                              *(undefined8 *)(param_5 + 0x18) = uVar27;
                              *(undefined8 *)(param_5 + 0x10) = uVar26;
                              puVar19 = puVar19 + 7;
                              uVar17 = uVar17 - 1;
                              param_5 = param_5 + 0x20;
                            } while (uVar17 != 0);
                          }
                        }
                        *(undefined8 *)(param_3 + 0x198) = uStack_3f88;
                        *(long *)(param_3 + 400) = local_3f90;
                        *(undefined8 *)(param_3 + 0x1a0) = local_3f80;
                        param_3[0x184] = *(CacheInfo *)(lVar8 + 0xc);
                        iVar6 = DyldSharedCache::numSubCaches((DyldSharedCache *)local_4070);
                        *(int *)(param_3 + 0x1a8) = iVar6 + 1;
                        *(long *)(param_3 + 0x1b0) = local_3e80 + local_3f90;
                        *(undefined8 *)(param_3 + 0x1b8) = local_3e78;
                        *(bool *)(lVar12 + 0x19) =
                             local_4008 == 0 || local_4008 == 2 && local_3ea8 == 0;
                        uVar10 = 1;
                        goto LAB_18019b590;
                      }
                      pcVar15 = "no shared cache subcache indices";
                    }
                    else {
                      pcVar15 = "shared cache file subcache count exceeds limit";
                    }
                  }
                  else {
                    pcVar15 = "first page of mmap()ed shared cache not valid";
                  }
                }
              }
              goto LAB_18019b580;
            }
            plVar1 = (long *)((long)local_4070 + (ulong)(uVar23 - 1) * 0x20 + lVar18 + 0x4070);
            lVar16 = plVar1[1];
            puVar2 = (ulong *)((long)local_4070 + (ulong)uVar23 * 0x20 + lVar18 + 0x4070);
            if ((ulong)(lVar16 + *plVar1) <= *puVar2) goto code_r0x00018019b708;
            goto LAB_18019b71c;
          }
          goto LAB_18019b584;
        }
        pcVar15 = "shared cache file mappings are invalid";
      }
      else {
        pcVar15 = "shared cache file has wrong magic";
      }
    }
    else {
      pcVar15 = "shared cache file pread() failed";
    }
  }
  else {
    pcVar15 = "shared cache file stat() failed";
  }
  goto LAB_18019b580;
code_r0x00018019b708:
  uVar20 = uVar20 + lVar16;
  uVar23 = uVar23 + 1;
  if (uVar20 != puVar2[2]) goto LAB_18019b71c;
  goto LAB_18019b6dc;
LAB_18019b71c:
  pcVar15 = "shared cache mappings overlap";
LAB_18019b580:
  *(char **)(lVar12 + 0x10) = pcVar15;
LAB_18019b584:
  _close(iVar7);
  uVar10 = 0;
LAB_18019b590:
  if (___stack_chk_guard != local_70) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(uVar10);
  }
  return;
}

