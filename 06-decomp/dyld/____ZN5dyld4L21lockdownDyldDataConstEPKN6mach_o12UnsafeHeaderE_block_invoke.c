
void ____ZN5dyld4L21lockdownDyldDataConstEPKN6mach_o12UnsafeHeaderE_block_invoke
               (long param_1,long param_2)

{
  if ((*(byte *)(param_2 + 0x28) >> 4 & 1) == 0) {
    return;
  }
  dyld4::SyscallDelegate::mprotect
            ((SyscallDelegate *)&dyld4::sSyscallDelegate,
             (void *)(*(long *)(param_1 + 0x20) + *(long *)(param_2 + 0x10)),
             *(ulong *)(param_2 + 0x18),1);
  return;
}

