
/* DyldSharedCache::isSubCachePath(char const*) */

undefined8 DyldSharedCache::isSubCachePath(char *param_1)

{
  int iVar1;
  char *pcVar2;
  undefined8 uVar3;
  
  pcVar2 = __platform_strchr(param_1,0x2e);
  if ((pcVar2 == (char *)0x0) || (iVar1 = __platform_strcmp(pcVar2,".development"), iVar1 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

