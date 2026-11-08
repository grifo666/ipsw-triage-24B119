
/* dyld3::validMagic(dyld3::SharedCacheOptions const&, DyldSharedCache const*) */

undefined8 dyld3::validMagic(SharedCacheOptions *param_1,DyldSharedCache *param_2)

{
  int iVar1;
  size_t sVar2;
  long lVar3;
  long lVar4;
  
  sVar2 = __platform_strlen((char *)param_1);
  lVar3 = 0;
  lVar4 = 0x20;
  while ((*(size_t *)((long)&DAT_1e018c508 + lVar3) != sVar2 ||
         (iVar1 = __platform_memcmp(*(void **)((long)&archCacheMagic + lVar3),param_1,sVar2),
         iVar1 != 0))) {
    lVar3 = lVar3 + 0x10;
    lVar4 = lVar4 + -0x10;
    if (lVar4 == 0) {
      return 0;
    }
  }
  return 1;
}

