
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
__ZN5dyld3L18preflightCacheFileERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoEPNS_9CacheInfoEiPNSt3__15arrayIA32_cLm128EEEPKS3_
          (undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,long param_5,
          long param_6,undefined8 param_7,undefined8 param_8)

{
  long *plVar1;
  long *plVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  long lVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  undefined8 uVar11;
  long lVar12;
  long lVar13;
  int *piVar14;
  long lVar15;
  uint uVar16;
  char *pcVar17;
  uint uVar18;
  ulong uVar19;
  long lVar20;
  long lVar21;
  byte bVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined1 auVar25 [16];
  ulong *puVar26;
  undefined1 auStack_5d38 [96];
  long lStack_5cd8;
  undefined1 auStack_5ca8 [24];
  undefined8 auStack_5c90 [893];
  ulong uStack_40a8;
  ulong uStack_40a0;
  long lStack_4098;
  ulong auStack_4070 [2];
  uint uStack_4060;
  uint uStack_405c;
  uint auStack_4058 [2];
  long alStack_4050 [9];
  long lStack_4008;
  int iStack_3f98;
  byte bStack_3f93;
  long lStack_3f90;
  undefined8 uStack_3f88;
  undefined8 uStack_3f80;
  uint uStack_3f38;
  int iStack_3f00;
  undefined4 uStack_3ee8;
  uint uStack_3ee4;
  int iStack_3ea8;
  long lStack_3e80;
  undefined8 uStack_3e78;
  long lStack_70;
  
  auVar25 = (*pcRam00000001e1f982d0)();
  lVar15 = auVar25._8_8_;
  lVar13 = auVar25._0_8_;
  lStack_70 = ____stack_chk_guard;
  iVar7 = func_0x0001804b1704(param_4,auStack_5d38);
  if (iVar7 == 0) {
    func_0x0001804dde34(auStack_4070,auStack_5d38);
    *(ulong *)(lVar15 + 0x24) = auStack_4070[1];
    *(ulong *)(lVar15 + 0x1c) = auStack_4070[0];
    lVar9 = func_0x0001804b187c(param_4,auStack_4070,0x4000,0);
    if (lVar9 != 0x4000) {
      pcVar17 = "shared cache file pread() failed";
      goto LAB_18050a234;
    }
    uVar10 = func_0x00018049d25c(auStack_4070);
    if ((uVar10 & 1) == 0) {
      pcVar17 = "shared cache file has wrong magic";
      goto LAB_18050a234;
    }
    iVar7 = func_0x000180484230(lVar13 + 0x10);
    if (iStack_3f98 == iVar7) {
      if ((bStack_3f93 >> 1 & 1) != 0) {
LAB_18050a22c:
        pcVar17 = "shared cache file is for a different platform";
        goto LAB_18050a234;
      }
    }
    else if ((iStack_3f00 == 0) || (iStack_3f00 != iVar7)) goto LAB_18050a22c;
    if (uStack_405c - 9 < 0xfffffff8) {
      pcVar17 = "shared cache file mappings are invalid";
      goto LAB_18050a234;
    }
    uVar19 = (ulong)uStack_4060;
    lVar9 = uVar19 - 0x4070;
    plVar1 = (long *)((long)auStack_4070 + (ulong)(uStack_405c - 1) * 0x20 + lVar9 + 0x4070);
    uVar10 = *(ulong *)((long)&uStack_4060 + uVar19);
    if (uVar10 == 0) {
      if (alStack_4050[2] + alStack_4050[1] != lStack_5cd8) {
        pcVar17 = "shared cache code signature size is invalid";
        goto LAB_18050a2ec;
      }
      if (uStack_405c < 2) goto LAB_18050a308;
      if ((int)plVar1[3] != 1) {
        *(char **)(lVar15 + 0x10) = "shared cache linkedit permissions are invalid";
      }
LAB_18050a2f8:
      bVar6 = true;
      uVar8 = *(uint *)((long)auStack_4058 + uVar19) | 4;
    }
    else {
      pcVar17 = "shared cache text file offset is invalid";
LAB_18050a2ec:
      *(char **)(lVar15 + 0x10) = pcVar17;
      if (1 < uStack_405c) goto LAB_18050a2f8;
LAB_18050a308:
      bVar6 = false;
      uVar8 = *(uint *)((long)auStack_4058 + uVar19);
    }
    if (uVar8 != 5) {
      *(char **)(lVar15 + 0x10) = "shared cache text permissions are invalid";
    }
    if (*(long *)(lVar15 + 0x10) == 0) {
      if (uStack_405c - 1 != 0) {
        uVar8 = 1;
        do {
          plVar2 = (long *)((long)auStack_4070 + (ulong)(uVar8 - 1) * 0x20 + lVar9 + 0x4070);
          lVar12 = plVar2[1];
          puVar26 = (ulong *)((long)auStack_4070 + (ulong)uVar8 * 0x20 + lVar9 + 0x4070);
          if ((*puVar26 < (ulong)(lVar12 + *plVar2)) ||
             (uVar10 = uVar10 + lVar12, uVar10 != puVar26[2])) {
            pcVar17 = "shared cache mappings overlap";
            goto LAB_18050a234;
          }
          uVar8 = uVar8 + 1;
        } while (uStack_405c != uVar8);
      }
      uStack_40a8 = 0;
      uStack_40a0 = alStack_4050[1];
      lStack_4098 = alStack_4050[2];
      puVar26 = &uStack_40a8;
      iVar7 = func_0x00018048e47c(param_4,0x61);
      if (iVar7 == -1) {
        pcVar17 = "code signature registration for shared cache failed";
      }
      else if (uStack_40a8 < (ulong)alStack_4050[1]) {
        pcVar17 = "code signature does not cover entire shared cache file";
      }
      else {
        lVar12 = func_0x000180497674(0,0x4000,5,2,param_4,0,param_7,param_8,puVar26);
        if (lVar12 == -1) {
          pcVar17 = "first page of shared cache not mmap()able";
        }
        else {
          iVar7 = func_0x00018048bd90(lVar12,auStack_4070,0x4000);
          if (iVar7 == 0) {
            func_0x00018048e658(lVar12,0x4000);
            *(undefined8 *)(param_3 + 0x198) = uStack_3f88;
            *(long *)(param_3 + 400) = lStack_3f90;
            *(undefined8 *)(param_3 + 0x1a0) = uStack_3f80;
            *(undefined1 *)(param_3 + 0x184) = *(undefined1 *)(lVar13 + 0xb);
            iVar7 = func_0x0001804dc498(auStack_4070);
            *(int *)(param_3 + 0x1a8) = iVar7 + 1;
            *(long *)(param_3 + 0x1b0) = lStack_3e80 + lStack_3f90;
            *(undefined8 *)(param_3 + 0x1b8) = uStack_3e78;
            bVar22 = lStack_4008 == 0 || lStack_4008 == 2 && iStack_3ea8 == 0;
            *(byte *)(lVar15 + 0x19) = bVar22;
            if (param_6 != 0) {
              bVar22 = *(byte *)(param_6 + 0x19);
            }
            if (uStack_405c == 0) {
              iVar7 = 0;
            }
            else {
              uVar10 = 0;
              iVar7 = 0;
              do {
                puVar4 = (undefined8 *)((long)auStack_4070 + uVar10 * 0x20 + lVar9 + 0x4070);
                uVar18 = *(uint *)(puVar4 + 3);
                uVar16 = *(uint *)((long)puVar4 + 0x1c);
                lVar12 = uVar10 * 0x38 + ((ulong)uStack_3f38 - 0x4070);
                uVar19 = *(ulong *)((long)alStack_4050 + lVar12 + 0x4078);
                uVar8 = 0x60;
                if ((uVar19 & 1) != 0) {
                  uVar8 = 0x20;
                }
                if (((uint)uVar19 >> 2 & 1) != 0) {
                  if ((*(byte *)(lVar13 + 7) & 1) == 0) {
                    uVar16 = uVar16 | 2;
                  }
                  else {
                    uVar18 = uVar18 | 0x200;
                  }
                }
                lVar5 = *(long *)((long)auStack_4058 + lVar12 + 0x4070);
                lVar12 = *(long *)((long)alStack_4050 + lVar12 + 0x4070);
                if ((uVar19 & 0x40) != 0) {
                  uVar18 = 3;
                  uVar16 = 3;
                }
                if (((uint)uVar19 >> 7 & 1) == 0) {
LAB_18050a544:
                  *(int *)(param_3 + 0x188) = (int)param_4;
                  puVar3 = (undefined8 *)(param_3 + (long)iVar7 * 0x30);
                  uVar11 = *puVar4;
                  puVar3[1] = puVar4[1];
                  *puVar3 = uVar11;
                  uVar11 = puVar4[2];
                  puVar3[3] = 0;
                  puVar3[4] = 0;
                  puVar3[2] = uVar11;
                  *(uint *)(puVar3 + 5) = uVar18;
                  *(uint *)((long)puVar3 + 0x2c) = uVar16;
                  if (lVar12 != 0) {
                    if (!bVar6) goto LAB_18050a6dc;
                    lVar20 = plVar1[2];
                    lVar21 = *plVar1;
                    puVar3[3] = lVar12;
                    puVar3[4] = (lVar5 - lVar20) + lVar21;
                    *(uint *)(puVar3 + 5) = uVar18 | uVar8;
                    *(uint *)((long)puVar3 + 0x2c) = uVar16 | uVar8;
                  }
                  iVar7 = iVar7 + 1;
                }
                else {
                  if ((bVar22 & 1) != 0) {
                    if (*(char *)(lVar13 + 5) != '\0') {
                      func_0x0001804e9ff0("  including auth GOT mapping\n");
                    }
                    goto LAB_18050a544;
                  }
                  if (*(char *)(lVar13 + 5) != '\0') {
                    func_0x0001804e9ff0("  skipping auth GOT mapping\n");
                  }
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 < uStack_405c);
            }
            *(int *)(param_3 + 0x180) = iVar7;
            if (uStack_3ee4 < 0x80) {
              if ((param_5 != 0) || (uStack_3ee4 == 0)) {
                if (uStack_3ee4 != 0) {
                  lVar13 = func_0x0001804b187c(param_4,auStack_5ca8,0x1c00,uStack_3ee8);
                  if (lVar13 != 0x1c00) {
                    pcVar17 = "shared cache file pread() failed, could not read subcache entries";
                    goto LAB_18050a234;
                  }
                  uVar10 = (ulong)uStack_3ee4;
                  if (uStack_3ee4 != 0) {
                    lVar13 = 0;
                    do {
                      puVar4 = (undefined8 *)(param_5 + lVar13 * 0x20);
                      uVar11 = auStack_5c90[lVar13 * 7];
                      uVar24 = auStack_5c90[lVar13 * 7 + 3];
                      uVar23 = auStack_5c90[lVar13 * 7 + 2];
                      puVar4[1] = auStack_5c90[lVar13 * 7 + 1];
                      *puVar4 = uVar11;
                      puVar4[3] = uVar24;
                      puVar4[2] = uVar23;
                      lVar13 = lVar13 + 1;
                      uVar10 = uVar10 - 1;
                    } while (uVar10 != 0);
                  }
                }
                uVar11 = 1;
                goto LAB_18050a244;
              }
              pcVar17 = "no shared cache subcache indices";
            }
            else {
              pcVar17 = "shared cache file subcache count exceeds limit";
            }
          }
          else {
            pcVar17 = "first page of mmap()ed shared cache not valid";
          }
        }
      }
      goto LAB_18050a234;
    }
  }
  else {
    pcVar17 = "shared cache file stat() failed";
LAB_18050a234:
    *(char **)(lVar15 + 0x10) = pcVar17;
  }
  func_0x00018048e06c(param_4);
  uVar11 = 0;
LAB_18050a244:
  if (____stack_chk_guard == lStack_70) {
    return uVar11;
  }
  func_0x0001804d4680(uVar11);
LAB_18050a6dc:
  auVar25 = func_0x0001804e0960();
  do {
    uVar11 = func_0x00018049c9a8(auVar25._0_8_,auVar25._8_8_,0);
    if ((int)uVar11 != -1) {
      return uVar11;
    }
    piVar14 = (int *)func_0x00018049c320();
  } while ((*piVar14 == 0x23) || (piVar14 = (int *)func_0x00018049c320(), *piVar14 == 4));
  return 0xffffffff;
}

