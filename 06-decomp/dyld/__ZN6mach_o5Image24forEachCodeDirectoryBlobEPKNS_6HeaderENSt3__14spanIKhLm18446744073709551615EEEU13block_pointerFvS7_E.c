
/* mach_o::Image::forEachCodeDirectoryBlob(mach_o::Header const*, std::span<unsigned char const,
   18446744073709551615ul>, void ( block_pointer)(std::span<unsigned char const,
   18446744073709551615ul>)) */

void __thiscall
mach_o::Image::forEachCodeDirectoryBlob(Image *this,int *param_1,ulong param_3,long param_4)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  bool bVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  ulong uVar9;
  ulong uVar10;
  undefined8 uVar11;
  undefined8 extraout_x13;
  undefined8 extraout_x13_00;
  undefined8 uVar12;
  undefined8 extraout_x14;
  undefined8 extraout_x14_00;
  ulong uVar13;
  ulong extraout_x15;
  ulong extraout_x15_00;
  ulong uVar14;
  int *piVar15;
  long lVar16;
  ulong uVar17;
  undefined8 local_70;
  undefined4 local_68;
  
  if ((0xb < param_3) && (*param_1 == -0x3ff32106)) {
    uVar8 = param_1[2];
    uVar6 = (uVar8 & 0xff00ff00) >> 8 | (uVar8 & 0xff00ff) << 8;
    uVar17 = (ulong)(uVar6 >> 0x10 | uVar6 << 0x10);
    if (uVar17 <= param_3 - 0xc >> 3) {
      local_70 = Platform::watchOS;
      local_68 = DAT_1e018bb80;
      uVar6 = Header::builtForPlatform((Header *)this,&local_70,0);
      uVar7 = Header::isMainExecutable((Header *)this);
      pcVar3 = hash_rank_watchOS_dylibs;
      if (uVar6 == 0) {
        pcVar3 = hash_rank;
      }
      if (uVar8 != 0) {
        lVar16 = 0;
        uVar14 = 0;
        piVar15 = (int *)0x0;
        uVar11 = 0x5000000;
        uVar12 = 0x20cdefa;
        uVar13 = (ulong)(uVar6 & uVar7);
        do {
          iVar2 = param_1[lVar16 * 2 + 3];
          uVar8 = iVar2 - 0x100000;
          bVar4 = false;
          bVar5 = false;
          if (iVar2 != 0) {
            bVar5 = (uint)uVar11 <= uVar8;
            bVar4 = uVar8 == (uint)uVar11;
          }
          if ((!bVar5 || bVar4) &&
             (uVar8 = (param_1 + lVar16 * 2 + 3)[1],
             uVar8 = (uVar8 & 0xff00ff00) >> 8 | (uVar8 & 0xff00ff) << 8,
             uVar10 = (ulong)(uVar8 >> 0x10 | uVar8 << 0x10), uVar10 <= param_3 - 0x58)) {
            uVar9 = param_3 - uVar10;
            piVar1 = (int *)((long)param_1 + uVar10);
            if (uVar9 < 4) {
LAB_1804c5a80:
                    /* WARNING: Does not return */
              pcVar3 = (code *)SoftwareBreakpoint(1,0x1804c5a84);
              (*pcVar3)();
            }
            if (*piVar1 == (int)uVar12) {
              if (uVar9 < 0x58) goto LAB_1804c5a80;
              uVar8 = (piVar1[1] & 0xff00ff00U) >> 8 | (piVar1[1] & 0xff00ffU) << 8;
              uVar10 = (ulong)(uVar8 >> 0x10 | uVar8 << 0x10);
              if (uVar10 <= uVar9) {
                if ((int)uVar13 == 1) {
                  (**(code **)(param_4 + 0x10))(param_4,piVar1);
                  _OUTLINED_FUNCTION_2();
                  uVar11 = extraout_x13_00;
                  uVar12 = extraout_x14_00;
                  uVar13 = extraout_x15_00;
                }
                else {
                  if (uVar14 != 0) {
                    uVar8 = (*pcVar3)(piVar1,uVar10);
                    (*pcVar3)(piVar15,uVar14);
                    uVar6 = _OUTLINED_FUNCTION_2();
                    uVar11 = extraout_x13;
                    uVar12 = extraout_x14;
                    uVar13 = extraout_x15;
                    if (uVar8 <= uVar6) goto LAB_1804c5994;
                  }
                  uVar14 = uVar10;
                  piVar15 = piVar1;
                }
              }
            }
          }
LAB_1804c5994:
          lVar16 = lVar16 + 1;
          uVar17 = uVar17 - 1;
        } while (uVar17 != 0);
        if (uVar14 != 0) {
          (**(code **)(param_4 + 0x10))(param_4,piVar15,uVar14);
        }
      }
    }
  }
  return;
}

