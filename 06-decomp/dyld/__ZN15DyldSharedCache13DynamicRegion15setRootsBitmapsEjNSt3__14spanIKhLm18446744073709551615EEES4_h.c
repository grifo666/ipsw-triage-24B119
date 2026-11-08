
/* DyldSharedCache::DynamicRegion::setRootsBitmaps(unsigned int, std::span<unsigned char const,
   18446744073709551615ul>, std::span<unsigned char const, 18446744073709551615ul>, unsigned char)
    */

void DyldSharedCache::DynamicRegion::setRootsBitmaps
               (DynamicRegion *param_1,uint param_2,char *param_3,size_t param_4,char *param_5,
               size_t param_6,DynamicRegion param_7)

{
  ulong uVar1;
  long lVar2;
  char *pcVar3;
  char *pcVar4;
  
  if (*(int *)(param_1 + 100) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0x6c) == 0) &&
     (param_4 == (ulong)param_2 + 7 >> 3 && param_6 == (ulong)param_2 + 7 >> 3)) {
    lVar2 = firstFreeOffset(param_1);
    uVar1 = lVar2 + param_6;
    if ((uVar1 >> 0x20 == 0) && (uVar1 + param_6 < 0x4001)) {
      pcVar4 = param_3;
      if (param_4 != 0) {
        do {
          pcVar3 = pcVar4 + 1;
          if (*pcVar4 != '\0') {
            param_7 = (DynamicRegion)((byte)param_7 | 4);
            break;
          }
          pcVar4 = pcVar3;
        } while (pcVar3 != param_3 + param_4);
      }
      pcVar4 = param_5;
      if (param_6 != 0) {
        do {
          pcVar3 = pcVar4 + 1;
          if (*pcVar4 != '\0') {
            param_7 = (DynamicRegion)((byte)param_7 | 8);
            break;
          }
          pcVar4 = pcVar3;
        } while (pcVar3 != param_5 + param_6);
      }
      __platform_memmove(param_1 + lVar2,param_3,param_4);
      __platform_memmove(param_1 + uVar1,param_5,param_6);
      *(int *)(param_1 + 0x60) = (int)lVar2;
      *(int *)(param_1 + 100) = (int)param_6;
      *(int *)(param_1 + 0x68) = (int)uVar1;
      *(int *)(param_1 + 0x6c) = (int)param_6;
      *(uint *)(param_1 + 0x50) = param_2;
      param_1[0x54] = param_7;
    }
  }
  return;
}

