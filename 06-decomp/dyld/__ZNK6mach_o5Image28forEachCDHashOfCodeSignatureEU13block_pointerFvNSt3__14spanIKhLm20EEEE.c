
/* mach_o::Image::forEachCDHashOfCodeSignature(void ( block_pointer)(std::span<unsigned char const,
   20ul>)) const */

void __thiscall mach_o::Image::forEachCDHashOfCodeSignature(Image *this,_func_void_span *param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  undefined8 local_38;
  undefined8 uStack_30;
  undefined1 local_28;
  
  codeSignature();
  if (local_28 != '\x01') {
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x180519d40);
    (*pcVar1)();
  }
  forEachCDHashOfCodeSignature(this,local_38,uStack_30,param_1);
  return;
}

