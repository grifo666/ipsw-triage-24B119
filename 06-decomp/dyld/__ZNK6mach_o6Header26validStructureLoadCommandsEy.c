
/* mach_o::Header::validStructureLoadCommands(unsigned long long) const */

void mach_o::Header::validStructureLoadCommands(ulonglong param_1)

{
  code *pcVar1;
  ulong in_x1;
  char *pcVar2;
  int iVar3;
  Error *in_x8;
  undefined *local_388;
  undefined8 local_380;
  code *local_378;
  undefined *puStack_370;
  undefined8 *local_368;
  undefined8 *puStack_360;
  undefined8 *local_358;
  undefined8 *puStack_350;
  undefined8 *local_348;
  undefined8 *puStack_340;
  undefined8 *local_338;
  undefined8 *puStack_330;
  undefined8 *local_328;
  undefined8 *puStack_320;
  undefined8 *local_318;
  undefined8 *puStack_310;
  undefined8 *local_308;
  undefined8 *puStack_300;
  undefined8 *local_2f8;
  undefined8 *local_2f0;
  ulonglong uStack_2e8;
  undefined8 local_2e0;
  undefined8 *local_2d8;
  undefined8 local_2d0;
  undefined4 local_2c8;
  undefined8 local_2c0;
  undefined8 *local_2b8;
  undefined8 local_2b0;
  undefined4 local_2a8;
  undefined8 local_2a0;
  undefined8 *local_298;
  undefined8 local_290;
  undefined4 local_288;
  undefined8 local_280;
  undefined8 *local_278;
  undefined8 local_270;
  undefined4 local_268;
  undefined8 local_260;
  undefined8 *local_258;
  undefined8 local_250;
  undefined4 local_248;
  undefined8 local_240;
  undefined8 *local_238;
  undefined8 local_230;
  undefined4 local_228;
  undefined8 local_220;
  undefined8 *local_218;
  undefined8 local_210;
  undefined4 local_208;
  undefined8 local_200;
  undefined8 *local_1f8;
  undefined8 local_1f0;
  undefined4 local_1e8;
  undefined8 local_1e0;
  undefined8 *local_1d8;
  undefined8 local_1d0;
  undefined4 local_1c8;
  undefined8 local_1c0;
  undefined8 *local_1b8;
  undefined8 local_1b0;
  undefined4 local_1a8;
  undefined8 local_1a0;
  undefined8 *local_198;
  undefined8 local_190;
  undefined4 local_188;
  undefined8 local_180;
  undefined8 *local_178;
  undefined8 local_170;
  undefined4 local_168;
  undefined8 local_160;
  undefined8 *local_158;
  undefined8 local_150;
  undefined4 local_148;
  undefined8 local_140;
  undefined8 *local_138;
  undefined8 local_130;
  undefined4 local_128;
  undefined8 local_120;
  undefined8 *local_118;
  undefined8 local_110;
  undefined4 local_108;
  undefined8 local_100;
  undefined8 *local_f8;
  undefined8 local_f0;
  code *local_e8;
  code *local_e0;
  Error aEStack_d8 [29];
  undefined1 auStack_bb [131];
  undefined1 local_38;
  
  if (*(ulong *)(param_1 + 8) < 0x1c) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x1804997e8);
    (*pcVar1)();
  }
  iVar3 = 0x20;
  if (**(int **)param_1 != -0x1120531) {
    iVar3 = 0x1c;
  }
  if (in_x1 < (uint)(iVar3 + (*(int **)param_1)[5])) {
    Error::Error(in_x8,"load commands length (%llu) exceeds length of file (%llu)");
    return;
  }
  local_100 = 0;
  local_f0 = DAT_1805232c8;
  local_e8 = ::___Block_byref_object_copy_;
  local_e0 = ::___Block_byref_object_dispose_;
  local_f8 = &local_100;
  CStringBuilder::CStringBuilder((CStringBuilder *)&local_e0,aEStack_d8,auStack_bb,0x80,1);
  local_38 = 0;
  puStack_350 = &local_120;
  local_120 = 0;
  local_110 = DAT_1805232b0;
  local_108 = 0;
  local_348 = &local_140;
  local_140 = 0;
  local_130 = DAT_1805232b0;
  local_128 = 0;
  puStack_340 = &local_160;
  local_160 = 0;
  local_150 = DAT_1805232b0;
  local_148 = 0;
  local_338 = &local_180;
  local_180 = 0;
  local_170 = DAT_1805232b0;
  local_168 = 0;
  puStack_330 = &local_1a0;
  local_1a0 = 0;
  local_190 = DAT_1805232b0;
  local_188 = 0;
  local_328 = &local_1c0;
  local_1c0 = 0;
  local_1b0 = DAT_1805232b0;
  local_1a8 = 0;
  puStack_320 = &local_1e0;
  local_1e0 = 0;
  local_1d0 = DAT_1805232b0;
  local_1c8 = 0;
  local_318 = &local_200;
  local_200 = 0;
  local_1f0 = DAT_1805232b0;
  local_1e8 = 0;
  puStack_310 = &local_220;
  local_220 = 0;
  local_210 = DAT_1805232b0;
  local_208 = 0;
  local_358 = &local_240;
  local_240 = 0;
  local_230 = DAT_1805232b0;
  local_228 = 0;
  local_368 = &local_260;
  local_260 = 0;
  local_250 = DAT_1805232b0;
  local_248 = 0;
  local_308 = &local_280;
  local_280 = 0;
  local_270 = DAT_1805232b0;
  local_268 = 0;
  puStack_300 = &local_2a0;
  local_2a0 = 0;
  local_290 = DAT_1805232b0;
  local_288 = 0;
  local_2f8 = &local_2c0;
  local_2c0 = 0;
  local_2b0 = DAT_1805232b0;
  local_2a8 = 0;
  local_2f0 = &local_2e0;
  local_2e0 = 0;
  local_2d0 = DAT_1805232b0;
  local_2c8 = 0;
  local_388 = &__NSConcreteStackBlock;
  local_380 = DAT_1805232b8;
  local_378 = ____ZNK6mach_o6Header26validStructureLoadCommandsEy_block_invoke;
  puStack_370 = &DAT_1e0189298;
  puStack_360 = &local_100;
  uStack_2e8 = param_1;
  local_2d8 = local_2f0;
  local_2b8 = local_2f8;
  local_298 = puStack_300;
  local_278 = local_308;
  local_258 = local_368;
  local_238 = local_358;
  local_218 = puStack_310;
  local_1f8 = local_318;
  local_1d8 = puStack_320;
  local_1b8 = local_328;
  local_198 = puStack_330;
  local_178 = local_338;
  local_158 = puStack_340;
  local_138 = local_348;
  local_118 = puStack_350;
  forEachLoadCommand((Header *)param_1,(_func_void_LoadCommandInfo_ptr_bool_ptr *)&local_388,
                     (Error *)(local_f8 + 5));
  if (*(char *)(local_f8 + 0x19) == '\0') {
    if (*(int *)(local_118 + 3) < 2) {
      if (*(int *)(local_138 + 3) < 2) {
        if (*(int *)(local_158 + 3) < 2) {
          if (*(int *)(local_178 + 3) < 2) {
            if (*(int *)(local_198 + 3) < 2) {
              if (*(int *)(local_1b8 + 3) < 2) {
                if (*(int *)(local_1d8 + 3) < 2) {
                  if (*(int *)(local_1f8 + 3) < 2) {
                    if (*(int *)(local_218 + 3) < 2) {
                      if (*(int *)(local_238 + 3) < 2) {
                        if (*(int *)(local_258 + 3) < 2) {
                          if (*(int *)(local_278 + 3) < 2) {
                            if (*(int *)(local_298 + 3) < 2) {
                              if (*(int *)(local_2b8 + 3) < 2) {
                                if (*(int *)(local_2d8 + 3) < 2) {
                                  validMachOHeader();
                                  goto LAB_180499538;
                                }
                                pcVar2 = "multiple LC_ROUTINES[_64] load commands found";
                              }
                              else {
                                pcVar2 = "multiple LC_MAIN or LC_UNIXTHREAD load commands found";
                              }
                            }
                            else {
                              pcVar2 = "multiple LC_DYLD_INFO load commands found";
                            }
                          }
                          else {
                            pcVar2 = "multiple LC_ENCRYPTION_INFO_64 load commands found";
                          }
                        }
                        else {
                          pcVar2 = "multiple LC_ID_DYLIB load commands found";
                        }
                      }
                      else {
                        pcVar2 = "multiple LC_TARGET_TRIPLE load commands found";
                      }
                    }
                    else {
                      pcVar2 = "multiple LC_FUNCTION_VARIANT_FIXUPS load commands found";
                    }
                  }
                  else {
                    pcVar2 = "multiple LC_FUNCTION_VARIANTS load commands found";
                  }
                }
                else {
                  pcVar2 = "multiple LC_DYLD_CHAINED_FIXUPS load commands found";
                }
              }
              else {
                pcVar2 = "multiple LC_DYLD_EXPORTS_TRIE load commands found";
              }
            }
            else {
              pcVar2 = "multiple LC_FUNCTION_STARTS load commands found";
            }
          }
          else {
            pcVar2 = "multiple LC_ATOM_INFO load commands found";
          }
        }
        else {
          pcVar2 = "multiple LC_SEGMENT_SPLIT_INFO load commands found";
        }
      }
      else {
        pcVar2 = "multiple LC_DYSYMTAB load commands found";
      }
    }
    else {
      pcVar2 = "multiple LC_SYMTAB load commands found";
    }
    Error::Error(in_x8,pcVar2);
  }
  else {
    Error::Error(in_x8,(Error *)(local_f8 + 5));
  }
LAB_180499538:
  __Block_object_dispose(&local_2e0,8);
  __Block_object_dispose(&local_2c0,8);
  __Block_object_dispose(&local_2a0,8);
  __Block_object_dispose(&local_280,8);
  __Block_object_dispose(&local_260,8);
  __Block_object_dispose(&local_240,8);
  __Block_object_dispose(&local_220,8);
  __Block_object_dispose(&local_200,8);
  __Block_object_dispose(&local_1e0,8);
  __Block_object_dispose(&local_1c0,8);
  __Block_object_dispose(&local_1a0,8);
  __Block_object_dispose(&local_180,8);
  __Block_object_dispose(&local_160,8);
  __Block_object_dispose(&local_140,8);
  __Block_object_dispose(&local_120,8);
  __Block_object_dispose(&local_100,8);
  Error::~Error(aEStack_d8);
  return;
}

