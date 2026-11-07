
/* dyld3::preflightCacheFile(dyld3::SharedCacheOptions const&, dyld3::SharedCacheLoadInfo*,
   dyld3::CacheInfo*, int, std::array<char [32], 128ul>*, dyld3::SharedCacheLoadInfo const*) */

void dyld3::preflightCacheFile
               (SharedCacheOptions *param_1,SharedCacheLoadInfo *param_2,CacheInfo *param_3,
               int param_4,array *param_5,SharedCacheLoadInfo *param_6)

{
  long *plVar1;
  long *plVar2;
  undefined8 *puVar3;
  CacheInfo *pCVar4;
  array *paVar5;
  long lVar6;
  long lVar7;
  bool bVar8;
  long lVar9;
  int iVar10;
  uint uVar12;
  ssize_t sVar13;
  ulong uVar14;
  undefined8 uVar15;
  void *pvVar16;
  long lVar17;
  DyldSharedCache *extraout_x1;
  undefined8 in_x6;
  undefined8 in_x7;
  uint uVar18;
  char *pcVar19;
  uint uVar20;
  ulong uVar21;
  long lVar22;
  long lVar23;
  long lVar24;
  SharedCacheLoadInfo SVar25;
  ulong uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined1 auVar29 [16];
  ulong *puVar30;
  stat sStack_5d38;
  undefined1 auStack_5ca8 [24];
  undefined8 local_5c90 [893];
  ulong local_40a8;
  ulong local_40a0;
  long local_4098;
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
  int iVar11;
  
  uVar26 = (ulong)(uint)param_4;
  auVar29 = (*DAT_1e1f982d0)();
  lVar17 = auVar29._8_8_;
  lVar23 = auVar29._0_8_;
  local_70 = ___stack_chk_guard;
  iVar11 = (int)uVar26;
  iVar10 = _fstat(iVar11,&sStack_5d38);
  if (iVar10 == 0) {
    FileIdTuple::FileIdTuple((FileIdTuple *)local_4070,&sStack_5d38);
    *(ulong *)(lVar17 + 0x24) = local_4070[1];
    *(ulong *)(lVar17 + 0x1c) = local_4070[0];
    sVar13 = _pread(iVar11,local_4070,0x4000,0);
    if (sVar13 != 0x4000) {
      pcVar19 = "shared cache file pread() failed";
      goto LAB_18050a234;
    }
    uVar14 = validMagic((SharedCacheOptions *)local_4070,extraout_x1);
    if ((uVar14 & 1) == 0) {
      pcVar19 = "shared cache file has wrong magic";
      goto LAB_18050a234;
    }
    iVar10 = mach_o::Platform::value((Platform *)(lVar23 + 0x10));
    if (local_3f98 == iVar10) {
      if ((local_3f93 >> 1 & 1) != 0) {
LAB_18050a22c:
        pcVar19 = "shared cache file is for a different platform";
        goto LAB_18050a234;
      }
    }
    else if ((local_3f00 == 0) || (local_3f00 != iVar10)) goto LAB_18050a22c;
    if (local_405c - 9 < 0xfffffff8) {
      pcVar19 = "shared cache file mappings are invalid";
      goto LAB_18050a234;
    }
    uVar21 = (ulong)local_4060;
    lVar9 = uVar21 - 0x4070;
    plVar1 = (long *)((long)local_4070 + (ulong)(local_405c - 1) * 0x20 + lVar9 + 0x4070);
    uVar14 = *(ulong *)((long)&local_4060 + uVar21);
    if (uVar14 == 0) {
      if (alStack_4050[2] + alStack_4050[1] != sStack_5d38.st_size) {
        pcVar19 = "shared cache code signature size is invalid";
        goto LAB_18050a2ec;
      }
      if (1 < local_405c) {
        if ((int)plVar1[3] != 1) {
          *(char **)(lVar17 + 0x10) = "shared cache linkedit permissions are invalid";
        }
        goto LAB_18050a2f8;
      }
LAB_18050a308:
      bVar8 = false;
      uVar12 = *(uint *)((long)auStack_4058 + uVar21);
    }
    else {
      pcVar19 = "shared cache text file offset is invalid";
LAB_18050a2ec:
      *(char **)(lVar17 + 0x10) = pcVar19;
      if (local_405c < 2) goto LAB_18050a308;
LAB_18050a2f8:
      bVar8 = true;
      uVar12 = *(uint *)((long)auStack_4058 + uVar21) | 4;
    }
    if (uVar12 != 5) {
      *(char **)(lVar17 + 0x10) = "shared cache text permissions are invalid";
    }
    if (*(long *)(lVar17 + 0x10) == 0) {
      if (local_405c - 1 != 0) {
        uVar12 = 1;
        do {
          plVar2 = (long *)((long)local_4070 + (ulong)(uVar12 - 1) * 0x20 + lVar9 + 0x4070);
          lVar7 = plVar2[1];
          puVar30 = (ulong *)((long)local_4070 + (ulong)uVar12 * 0x20 + lVar9 + 0x4070);
          if ((*puVar30 < (ulong)(lVar7 + *plVar2)) ||
             (uVar14 = uVar14 + lVar7, uVar14 != puVar30[2])) {
            pcVar19 = "shared cache mappings overlap";
            goto LAB_18050a234;
          }
          uVar12 = uVar12 + 1;
        } while (local_405c != uVar12);
      }
      local_40a8 = 0;
      local_40a0 = alStack_4050[1];
      local_4098 = alStack_4050[2];
      puVar30 = &local_40a8;
      iVar10 = _fcntl(iVar11,0x61);
      if (iVar10 == -1) {
        pcVar19 = "code signature registration for shared cache failed";
      }
      else if (local_40a8 < (ulong)alStack_4050[1]) {
        pcVar19 = "code signature does not cover entire shared cache file";
      }
      else {
        pvVar16 = (void *)_mmap(0,0x4000,5,2,uVar26,0,in_x6,in_x7,puVar30);
        if (pvVar16 == (void *)0xffffffffffffffff) {
          pcVar19 = "first page of shared cache not mmap()able";
        }
        else {
          iVar10 = __platform_memcmp(pvVar16,local_4070,0x4000);
          if (iVar10 == 0) {
            _munmap(pvVar16,0x4000);
            *(undefined8 *)(param_3 + 0x198) = uStack_3f88;
            *(long *)(param_3 + 400) = local_3f90;
            *(undefined8 *)(param_3 + 0x1a0) = local_3f80;
            param_3[0x184] = *(CacheInfo *)(lVar23 + 0xb);
            iVar10 = DyldSharedCache::numSubCaches((DyldSharedCache *)local_4070);
            *(int *)(param_3 + 0x1a8) = iVar10 + 1;
            *(long *)(param_3 + 0x1b0) = local_3e80 + local_3f90;
            *(undefined8 *)(param_3 + 0x1b8) = local_3e78;
            SVar25 = (SharedCacheLoadInfo)(local_4008 == 0 || local_4008 == 2 && local_3ea8 == 0);
            *(SharedCacheLoadInfo *)(lVar17 + 0x19) = SVar25;
            if (param_6 != (SharedCacheLoadInfo *)0x0) {
              SVar25 = param_6[0x19];
            }
            if (local_405c == 0) {
              iVar10 = 0;
            }
            else {
              uVar26 = 0;
              iVar10 = 0;
              do {
                puVar3 = (undefined8 *)((long)local_4070 + uVar26 * 0x20 + lVar9 + 0x4070);
                uVar20 = *(uint *)(puVar3 + 3);
                uVar18 = *(uint *)((long)puVar3 + 0x1c);
                lVar7 = uVar26 * 0x38 + ((ulong)local_3f38 - 0x4070);
                uVar14 = *(ulong *)((long)alStack_4050 + lVar7 + 0x4078);
                uVar12 = 0x60;
                if ((uVar14 & 1) != 0) {
                  uVar12 = 0x20;
                }
                if (((uint)uVar14 >> 2 & 1) != 0) {
                  if ((*(byte *)(lVar23 + 7) & 1) == 0) {
                    uVar18 = uVar18 | 2;
                  }
                  else {
                    uVar20 = uVar20 | 0x200;
                  }
                }
                lVar6 = *(long *)((long)auStack_4058 + lVar7 + 0x4070);
                lVar7 = *(long *)((long)alStack_4050 + lVar7 + 0x4070);
                if ((uVar14 & 0x40) != 0) {
                  uVar20 = 3;
                  uVar18 = 3;
                }
                if (((uint)uVar14 >> 7 & 1) == 0) {
LAB_18050a544:
                  *(int *)(param_3 + 0x188) = iVar11;
                  pCVar4 = param_3 + (long)iVar10 * 0x30;
                  uVar15 = *puVar3;
                  *(undefined8 *)(pCVar4 + 8) = puVar3[1];
                  *(undefined8 *)pCVar4 = uVar15;
                  uVar15 = puVar3[2];
                  *(undefined8 *)(pCVar4 + 0x18) = 0;
                  *(undefined8 *)(pCVar4 + 0x20) = 0;
                  *(undefined8 *)(pCVar4 + 0x10) = uVar15;
                  *(uint *)(pCVar4 + 0x28) = uVar20;
                  *(uint *)(pCVar4 + 0x2c) = uVar18;
                  if (lVar7 != 0) {
                    if (!bVar8) {
                    /* WARNING: Subroutine does not return */
                      std::__throw_bad_optional_access_abi_nqn220106_();
                    }
                    lVar22 = plVar1[2];
                    lVar24 = *plVar1;
                    *(long *)(pCVar4 + 0x18) = lVar7;
                    *(long *)(pCVar4 + 0x20) = (lVar6 - lVar22) + lVar24;
                    *(uint *)(pCVar4 + 0x28) = uVar20 | uVar12;
                    *(uint *)(pCVar4 + 0x2c) = uVar18 | uVar12;
                  }
                  iVar10 = iVar10 + 1;
                }
                else {
                  if (((byte)SVar25 & 1) != 0) {
                    if (*(char *)(lVar23 + 5) != '\0') {
                      dyld4::console("  including auth GOT mapping\n");
                    }
                    goto LAB_18050a544;
                  }
                  if (*(char *)(lVar23 + 5) != '\0') {
                    dyld4::console("  skipping auth GOT mapping\n");
                  }
                }
                uVar26 = uVar26 + 1;
              } while (uVar26 < local_405c);
            }
            *(int *)(param_3 + 0x180) = iVar10;
            if (local_3ee4 < 0x80) {
              if ((param_5 != (array *)0x0) || (local_3ee4 == 0)) {
                if (local_3ee4 != 0) {
                  sVar13 = _pread(iVar11,auStack_5ca8,0x1c00,(ulong)local_3ee8);
                  if (sVar13 != 0x1c00) {
                    pcVar19 = "shared cache file pread() failed, could not read subcache entries";
                    goto LAB_18050a234;
                  }
                  uVar26 = (ulong)local_3ee4;
                  if (local_3ee4 != 0) {
                    lVar23 = 0;
                    do {
                      paVar5 = param_5 + lVar23 * 0x20;
                      uVar15 = local_5c90[lVar23 * 7];
                      uVar28 = local_5c90[lVar23 * 7 + 3];
                      uVar27 = local_5c90[lVar23 * 7 + 2];
                      *(undefined8 *)(paVar5 + 8) = local_5c90[lVar23 * 7 + 1];
                      *(undefined8 *)paVar5 = uVar15;
                      *(undefined8 *)(paVar5 + 0x18) = uVar28;
                      *(undefined8 *)(paVar5 + 0x10) = uVar27;
                      lVar23 = lVar23 + 1;
                      uVar26 = uVar26 - 1;
                    } while (uVar26 != 0);
                  }
                }
                uVar15 = 1;
                goto LAB_18050a244;
              }
              pcVar19 = "no shared cache subcache indices";
            }
            else {
              pcVar19 = "shared cache file subcache count exceeds limit";
            }
          }
          else {
            pcVar19 = "first page of mmap()ed shared cache not valid";
          }
        }
      }
      goto LAB_18050a234;
    }
  }
  else {
    pcVar19 = "shared cache file stat() failed";
LAB_18050a234:
    *(char **)(lVar17 + 0x10) = pcVar19;
  }
  _close(iVar11);
  uVar15 = 0;
LAB_18050a244:
  if (___stack_chk_guard != local_70) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(uVar15);
  }
  return;
}

