
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* dyld4::Loader::mapSegments(Diagnostics&, dyld4::RuntimeState&, char const*, int, unsigned long
   long, dyld4::Loader::CodeSignatureInFile const&, bool, std::span<dyld4::Loader::Region const,
   18446744073709551615ul>, bool, bool, dyld4::Loader::FileValidationInfo const&) */

uint * __thiscall
dyld4::Loader::mapSegments
          (Loader *this,RuntimeState *param_1,char *param_2,undefined8 param_3,vm_size_t param_5_00,
          CodeSignatureInFile *param_5,int param_7,undefined8 param_8,ulong *param_9,long param_10,
          undefined8 param_11,FileValidationInfo *param_12)

{
  ulong *puVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  kern_return_t kVar5;
  uint uVar6;
  int iVar7;
  uint **ppuVar8;
  ulong uVar9;
  long lVar10;
  UnsafeHeader *pUVar11;
  int *piVar12;
  char *pcVar13;
  SyscallDelegate *this_00;
  uint *puVar14;
  ulong uVar15;
  ulong local_560 [2];
  uint local_54c;
  uint *local_548;
  long local_540;
  undefined8 local_538;
  undefined8 uStack_530;
  char *local_528;
  undefined4 local_520 [2];
  undefined8 local_518;
  char *pcStack_510;
  undefined8 local_508;
  undefined8 uStack_500;
  undefined8 local_4f8;
  undefined8 uStack_4f0;
  undefined8 local_4e8;
  undefined8 uStack_4e0;
  undefined8 local_4d8;
  undefined8 uStack_4d0;
  undefined8 local_4c8;
  undefined8 uStack_4c0;
  undefined8 local_4b8;
  char local_4b0 [1024];
  uint *local_b0;
  undefined1 auStack_a8 [8];
  undefined1 auStack_a0 [8];
  undefined1 auStack_98 [40];
  long local_70;
  
  local_70 = ___stack_chk_guard;
  local_520[0] = 0x1f070008;
  local_518 = 0;
  uStack_500 = 0;
  local_508 = 0;
  uStack_4f0 = 0;
  local_4f8 = 0;
  uStack_4e0 = 0;
  local_4e8 = 0;
  uStack_4d0 = 0;
  local_4d8 = 0;
  uStack_4c0 = 0;
  local_4c8 = 0;
  local_4b8 = 0;
  pcStack_510 = param_2;
  dyld3::ScopedTimer::startTimer((ScopedTimer *)local_520);
  iVar7 = (int)param_3;
  ppuVar8 = (uint **)validateFile((Diagnostics *)this,param_1,iVar7,param_2,param_5,param_12);
  uVar9 = Diagnostics::hasError((Diagnostics *)this);
  if ((uVar9 & 1) == 0) {
    if ((param_7 == 0) || (*(int *)(param_5 + 4) == 0)) {
      lVar10 = *(long *)(param_1 + 8);
      if ((*(byte *)(lVar10 + 0x17b) & 1) != 0) goto LAB_1804b0e44;
      getUuidFromFd(param_1,iVar7,(ulonglong)ppuVar8,local_4b0);
      pcVar13 = "missing code signature in <%s> \'%s\'";
    }
    else {
      getUuidFromFd(param_1,iVar7,(ulonglong)ppuVar8,local_4b0);
      iVar4 = SyscallDelegate::registerSignature
                        (*(SyscallDelegate **)(param_1 + 8),(Diagnostics *)this,param_2,local_4b0,
                         iVar7,(ulonglong)ppuVar8,*(uint *)param_5,*(uint *)(param_5 + 4));
      if (iVar4 == 0) goto LAB_1804b11d4;
      lVar10 = *(long *)(param_1 + 8);
LAB_1804b0e44:
      local_4b0[0] = '\0';
      uStack_530 = 0x200;
      local_528 = local_4b0;
      local_538 = ppuVar8;
      iVar4 = SyscallDelegate::fcntl((int)lVar10,iVar7,(void *)0x62);
      if (iVar4 == -1) {
        getUuidFromFd(param_1,iVar7,(ulonglong)ppuVar8,(char *)&local_b0);
        pcVar13 = "code signature in <%s> \'%s\' not valid for use in process: %s";
      }
      else {
        local_540 = 0;
        if (*(char *)(*(long *)(param_1 + 8) + 0x10c) == '\x01') {
          iVar4 = _rosetta_dyld_get_aot_size(param_3,param_2,&local_540,local_4b0,0x400);
          if (iVar4 == 0) {
            param_5_00 = local_540 + param_5_00;
          }
          else {
            local_540 = 0;
            local_4b0[0] = '\0';
          }
        }
        local_548 = (uint *)0x0;
        kVar5 = _vm_allocate(_mach_task_self_,(vm_address_t *)&local_548,param_5_00,1);
        if (kVar5 == 0) {
          if (*(char *)(*(long *)(param_1 + 8) + 0x181) == '\x01') {
            if (ppuVar8 == (uint **)0x0) {
              pcVar13 = "Mapping %s\n";
            }
            else {
              pcVar13 = "Mapping %s (slice offset=0x%llX)\n";
            }
            RuntimeState::log(param_1,pcVar13);
          }
          puVar1 = param_9 + param_10 * 2;
          if (param_10 != 0) {
            iVar4 = 0;
            bVar2 = *(byte *)(*(long *)(param_1 + 8) + 0x110);
            do {
              uVar9 = *param_9;
              if ((((uVar9 >> 0x3e & 1) == 0) && (*(uint *)((long)param_9 + 0xc) != 0)) &&
                 ((uVar9 & 0x7ffffffffffffff) != 0 || iVar4 == 0)) {
                iVar3 = 0x80012;
                if (((long)uVar9 < 0 & bVar2) == 0) {
                  iVar3 = 0x12;
                }
                pUVar11 = (UnsafeHeader *)
                          SyscallDelegate::mmap
                                    (*(SyscallDelegate **)(param_1 + 8),
                                     (void *)((long)local_548 + (uVar9 & 0x7ffffffffffffff)),
                                     (ulong)*(uint *)((long)param_9 + 0xc),(uint)(uVar9 >> 0x3b) & 7
                                     ,iVar3,iVar7,(long)ppuVar8 + (ulong)(uint)param_9[1]);
                piVar12 = ___error();
                if (pUVar11 == (UnsafeHeader *)0xffffffffffffffff) {
                  if (*piVar12 == 1) {
                    iVar7 = SyscallDelegate::sandboxBlockedMmap(*(char **)(param_1 + 8));
                    if (iVar7 == 0) {
                      pcVar13 = "code signing blocked mmap() of \'%s\'";
                    }
                    else {
                      pcVar13 = "file system sandbox blocked mmap() of \'%s\'";
                    }
                  }
                  else {
                    pcVar13 = "mmap(addr=0x%0llX, size=0x%08X) failed with errno=%d for %s";
                  }
                  Diagnostics::error((Diagnostics *)this,pcVar13);
                  goto LAB_1804b11c8;
                }
                if ((iVar4 == 0) &&
                   (lVar10 = mach_o::UnsafeHeader::isMachO
                                       (pUVar11,*(undefined4 *)((long)param_9 + 0xc)), lVar10 == 0))
                {
                  pcVar13 = "not a mach-o file";
                  goto LAB_1804b1188;
                }
                if (*(char *)(*(long *)(param_1 + 8) + 0x181) == '\x01') {
                  uVar6 = (uint)local_548;
                  mach_o::UnsafeHeader::segmentName(uVar6);
                  mach_o::UnsafeHeader::segmentName(uVar6);
                  RuntimeState::log(param_1,"%14.*s (%c%c%c) 0x%012lX->0x%012lX\n");
                }
                iVar4 = iVar4 + 1;
              }
              param_9 = param_9 + 2;
            } while (param_9 != puVar1);
          }
          local_560[0] = local_560[0] & 0xffffffff00000000;
          local_54c = 0;
          iVar7 = mach_o::UnsafeHeader::isFairPlayEncrypted(local_548,(uint *)local_560);
          puVar14 = local_548;
          if (iVar7 != 0) {
            this_00 = *(SyscallDelegate **)(param_1 + 8);
            uVar9 = local_560[0] & 0xffffffff;
            uVar15 = (ulong)local_54c;
            mach_o::UnsafeHeader::arch();
            uVar6 = (uint)local_b0;
            mach_o::UnsafeHeader::arch();
            iVar7 = SyscallDelegate::mremap_encrypted
                              (this_00,(void *)((long)puVar14 + uVar9),uVar15,1,uVar6,
                               local_538._4_4_);
            if (iVar7 != 0) {
              pcVar13 = "could not register fairplay decryption, mremap_encrypted() => %d";
LAB_1804b1188:
              Diagnostics::error((Diagnostics *)this,pcVar13);
LAB_1804b11c8:
              _vm_deallocate(_mach_task_self_,(mach_vm_address_t)local_548,param_5_00);
              goto LAB_1804b11d4;
            }
          }
          puVar14 = local_548;
          if (*(char *)(*(long *)(param_1 + 8) + 0x10c) == '\x01' && local_540 != 0) {
            iVar7 = _rosetta_dyld_map_aot
                              (param_2,local_548,(param_5_00 - local_540) + (long)local_548,
                               auStack_a8,auStack_a0,auStack_98);
            puVar14 = local_548;
            if (iVar7 == 0) {
              local_b0 = local_548;
              uStack_530 = 1;
              local_560[0] = 0;
              local_560[1] = 0;
              local_538 = &local_b0;
              ExternallyViewableState::addRosettaImages
                        (*(ExternallyViewableState **)(param_1 + 0x298),(span *)&local_538,
                         (span *)local_560);
              puVar14 = local_548;
              if (*(char *)(*(long *)(param_1 + 8) + 0x181) == '\x01') {
                RuntimeState::log(param_1,"%14s (r.x) 0x%012llX->0x%012llX\n");
                puVar14 = local_548;
              }
            }
          }
          goto LAB_1804b11d8;
        }
        pcVar13 = "vm_allocate(size=0x%0llX) failed with result=%d";
      }
    }
    Diagnostics::error((Diagnostics *)this,pcVar13);
  }
LAB_1804b11d4:
  puVar14 = (uint *)0x0;
LAB_1804b11d8:
  dyld3::ScopedTimer::endTimer((ScopedTimer *)local_520);
  if (___stack_chk_guard == local_70) {
    return puVar14;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

