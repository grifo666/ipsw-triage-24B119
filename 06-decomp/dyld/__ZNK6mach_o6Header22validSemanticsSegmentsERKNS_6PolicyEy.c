
/* mach_o::Header::validSemanticsSegments(mach_o::Policy const&, unsigned long long) const */

void mach_o::Header::validSemanticsSegments(Policy *param_1,ulonglong param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  ulong *puVar7;
  Policy *pPVar8;
  ulong uVar9;
  long *plVar10;
  char *pcVar11;
  Error *in_x8;
  long lVar12;
  ulong uVar13;
  mach_header *pmVar14;
  ulong *puVar15;
  uint uVar16;
  ulong *puVar17;
  undefined1 auVar18 [16];
  undefined *local_4b8;
  undefined8 local_4b0;
  code *local_4a8;
  undefined *puStack_4a0;
  undefined8 *local_498;
  undefined8 *puStack_490;
  undefined8 *local_488;
  undefined8 *puStack_480;
  undefined8 *local_478;
  Policy *pPStack_470;
  ulonglong local_468;
  undefined8 local_458;
  undefined8 *local_450;
  undefined8 local_448;
  undefined8 local_440;
  undefined8 local_438;
  undefined8 *puStack_430;
  undefined8 local_428;
  undefined1 local_420;
  undefined8 local_418;
  undefined8 *local_410;
  undefined8 local_408;
  undefined1 local_400;
  undefined8 local_3f8;
  undefined8 *local_3f0;
  undefined8 local_3e8;
  code *local_3e0;
  code *local_3d8;
  Error aEStack_3d0 [29];
  undefined1 auStack_3b3 [131];
  undefined1 local_330;
  undefined8 local_328;
  undefined8 *local_320;
  undefined8 local_318;
  code *local_310;
  code *local_308;
  undefined1 *local_300;
  undefined8 local_2f8;
  undefined8 local_2f0;
  mach_vm_address_t local_2e8;
  mach_vm_size_t local_2e0;
  int local_2d8;
  undefined4 local_2d4;
  undefined4 *local_2d0;
  ulong local_2c8;
  byte local_2b9;
  undefined1 local_2b8 [584];
  long local_70;
  
  local_70 = ___stack_chk_guard;
  local_328 = 0;
  local_318 = DAT_1805232c0;
  local_310 = ___Block_byref_object_copy__75;
  local_300 = local_2b8;
  local_308 = ___Block_byref_object_dispose__76;
  local_2f8 = 0xc;
  local_2f0 = 0;
  local_2e8 = 0;
  local_2e0 = 0;
  local_3f8 = 0;
  local_3e8 = DAT_1805232c8;
  local_3e0 = ::___Block_byref_object_copy_;
  local_3d8 = ::___Block_byref_object_dispose_;
  local_3f0 = &local_3f8;
  local_320 = &local_328;
  CStringBuilder::CStringBuilder((CStringBuilder *)&local_3d8,aEStack_3d0,auStack_3b3,0x80,1);
  local_330 = 0;
  local_498 = &local_418;
  local_418 = 0;
  local_408 = DAT_1805232b0;
  local_400 = 0;
  puStack_480 = &local_438;
  local_438 = 0;
  local_428 = DAT_1805232b0;
  local_420 = 0;
  puStack_490 = &local_458;
  local_458 = 0;
  local_448 = DAT_1805232b0;
  local_440 = 0;
  local_4b8 = &__NSConcreteStackBlock;
  local_4b0 = DAT_1805232b8;
  local_4a8 = ____ZNK6mach_o6Header22validSemanticsSegmentsERKNS_6PolicyEy_block_invoke;
  puStack_4a0 = &DAT_1e0188038;
  local_2b9 = 0;
  local_488 = &local_328;
  local_478 = &local_3f8;
  pPStack_470 = param_1;
  local_468 = param_2;
  local_450 = puStack_490;
  puStack_430 = puStack_480;
  local_410 = local_498;
  if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
  uVar2 = (*(int **)param_1)[4];
  if (uVar2 != 0) {
    uVar13 = 0x20;
    if (**(int **)param_1 != -0x1120531) {
      uVar13 = 0x1c;
    }
    uVar16 = 1;
    while (uVar13 + 8 < *(ulong *)(param_1 + 8)) {
      puVar1 = (undefined4 *)(*(long *)param_1 + uVar13);
      uVar3 = puVar1[1];
      uVar9 = uVar13 + uVar3;
      if (((uVar3 < 8 || (uVar3 & 3) != 0) || *(ulong *)(param_1 + 8) < uVar9) || uVar9 < uVar13)
      break;
      local_2d8 = uVar16 - 1;
      local_2d4 = *puVar1;
      local_2d0 = puVar1;
      local_2c8 = (ulong)uVar3;
      (*local_4a8)(&local_4b8,&local_2d8,&local_2b9);
      if ((uVar2 <= uVar16) || (uVar16 = uVar16 + 1, uVar13 = uVar9, (local_2b9 & 1) != 0)) break;
    }
  }
  if (*(char *)(local_3f0 + 0x19) != '\0') {
    Error::Error(in_x8,(Error *)(local_3f0 + 5));
    goto LAB_1804acff0;
  }
  if (0xff < (ulong)local_320[7]) {
    pcVar11 = "too many segments %llu (max 255)";
    goto LAB_1804acfe8;
  }
  if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
  lVar12 = *(long *)param_1;
  iVar5 = *(int *)(lVar12 + 0xc);
  if ((iVar5 == 8 || iVar5 == 6) || ((iVar5 == 2 && ((*(byte *)(lVar12 + 0x18) >> 2 & 1) != 0)))) {
    if (*(char *)(local_410 + 3) == '\x01') {
      if (-1 < *(int *)(lVar12 + 0x18)) {
        lVar12 = dyld3::
                 OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                 ::operator[]((OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                               *)(local_320 + 5),local_450[3]);
        if (*(long *)(lVar12 + 0x10) != 0) {
          pcVar11 = "__TEXT segment fileoffset is not zero";
          goto LAB_1804acfe8;
        }
        if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
      }
      iVar5 = 0x20;
      if (**(int **)param_1 != -0x1120531) {
        iVar5 = 0x1c;
      }
      uVar13 = (ulong)(uint)(iVar5 + (*(int **)param_1)[5]);
      lVar12 = dyld3::
               OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
               ::operator[]((OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                             *)(local_320 + 5),local_450[3]);
      if ((ulong)(*(long *)(lVar12 + 0x18) - *(long *)(lVar12 + 0x10)) < uVar13) {
        pcVar11 = "load commands do not fit in __TEXT segment filesize";
      }
      else {
        plVar10 = (long *)dyld3::
                          OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                          ::operator[]((OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                                        *)(local_320 + 5),local_450[3]);
        if (uVar13 <= (ulong)(plVar10[1] - *plVar10)) {
          if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
          goto LAB_1804ad09c;
        }
        pcVar11 = "load commands do not fit in __TEXT segment vmsize";
      }
    }
    else {
      pcVar11 = "missing __TEXT segment";
    }
LAB_1804acfe8:
    Error::Error(in_x8,pcVar11);
  }
  else {
LAB_1804ad09c:
    iVar5 = *(int *)(*(long *)param_1 + 0xc);
    if ((iVar5 == 8 || iVar5 == 6) ||
       ((iVar5 == 2 && ((*(byte *)(*(long *)param_1 + 0x18) >> 2 & 1) != 0)))) {
      iVar5 = Policy::useProtectedStack((Policy *)param_2);
    }
    else {
      iVar5 = 0;
    }
    puVar15 = (ulong *)local_320[5];
    lVar12 = local_320[7];
    puVar7 = puVar15;
    puVar17 = puVar15;
    if (lVar12 != 0) {
      do {
        if (puVar7 != puVar17) {
          if ((*puVar7 < puVar17[1]) && (*puVar17 < puVar7[1])) {
            pcVar11 = "vm range of segment \'%s\' overlaps segment \'%s\'";
            goto LAB_1804acfe8;
          }
          if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
          if (((-1 < *(int *)(*(long *)param_1 + 0x18)) && (puVar7[2] < puVar17[3])) &&
             (puVar17[2] < puVar7[3])) {
            pcVar11 = "file range of segment \'%s\' overlaps segment \'%s\'";
            goto LAB_1804acfe8;
          }
          if (((iVar5 != 0) && (puVar17[5] == puVar7[5])) &&
             (iVar6 = __platform_memcmp((void *)puVar17[4],(void *)puVar7[4],puVar17[5]), iVar6 == 0
             )) {
            pcVar11 = "duplicate segment name \'%s\'";
            goto LAB_1804acfe8;
          }
        }
        puVar7 = puVar7 + 6;
      } while ((puVar7 != puVar15 + lVar12 * 6) ||
              (puVar17 = puVar17 + 6, puVar7 = puVar15, puVar17 != puVar15 + lVar12 * 6));
    }
    iVar5 = Policy::enforceSegmentOrderMatchesLoadCmds((Policy *)param_2);
    if (iVar5 != 0) {
      if (*(ulong *)(param_1 + 8) < 0x1c) {
LAB_1804ad3b0:
                    /* WARNING: Does not return */
        pcVar4 = (code *)SoftwareBreakpoint(1,0x1804ad3b4);
        (*pcVar4)();
      }
      if ((-1 < *(int *)(*(long *)param_1 + 0x18)) && (2 < (ulong)local_320[7])) {
        uVar13 = 1;
        do {
          puVar7 = (ulong *)dyld3::
                            OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                            ::operator[]((OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                                          *)(local_320 + 5),uVar13 - 1);
          auVar18 = dyld3::
                    OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                    ::operator[]((OverflowSafeArray<mach_o::UnsafeHeader::validSemanticsSegments(mach_o::Policy_const&,unsigned_long_long)const::SegRange,4294967295ull>
                                  *)(local_320 + 5),uVar13);
          pPVar8 = auVar18._0_8_;
          if ((*(ulong *)(pPVar8 + 0x10) < puVar7[2]) &&
             (*(ulong *)(pPVar8 + 0x10) != *(ulong *)(pPVar8 + 0x18))) {
            pcVar11 = "segment \'%s\' file offset out of order";
            goto LAB_1804acfe8;
          }
          if (*(ulong *)pPVar8 < *puVar7) {
            if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
            pmVar14 = *(mach_header **)param_1;
            if ((pmVar14->filetype != 0xc) ||
               (uVar9 = validSemanticsSegments(pPVar8,auVar18._8_8_), (uVar9 & 1) != 0)) {
              Architecture::Architecture((Architecture *)&local_2d8,pmVar14);
              iVar5 = Architecture::usesx86_64Instructions((Architecture *)&local_2d8);
              if ((iVar5 != 0) && (iVar5 = isDynamicExecutable((Header *)param_1), iVar5 != 0)) {
                if (*(ulong *)(param_1 + 8) < 0x1c) goto LAB_1804ad3b0;
                if ((*(uint *)(*(long *)param_1 + 0x18) >> 0x15 & 1) == 0) goto LAB_1804ad25c;
              }
              uVar9 = validSemanticsSegments(param_1,(ulonglong)pPVar8);
              if ((uVar9 & 1) == 0) goto LAB_1804acff0;
            }
          }
LAB_1804ad25c:
          uVar13 = uVar13 + 1;
        } while (uVar13 < local_320[7] - 1);
      }
    }
    validMachOHeader();
  }
LAB_1804acff0:
  __Block_object_dispose(&local_458,8);
  __Block_object_dispose(&local_438,8);
  __Block_object_dispose(&local_418,8);
  __Block_object_dispose(&local_3f8,8);
  Error::~Error(aEStack_3d0);
  __Block_object_dispose(&local_328,8);
  local_2f0 = 0;
  if (local_2e8 != 0) {
    _vm_deallocate(_mach_task_self_,local_2e8,local_2e0);
  }
  if (___stack_chk_guard == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

