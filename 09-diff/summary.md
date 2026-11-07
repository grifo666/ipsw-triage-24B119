   • using diff cache at /Users/operador/Library/Caches/ipsw/diffs/23G83_iPhone18_2_26.6.1_3c8534373e0c3f95__24B119_iPhone18_2_27.2_c11f66006014315e.db
   • Diffing KERNELCACHES     
   • Diffing DYLD_SHARED_CACHES
   • Diffing MachOs           
      • Scanning filesystem volume
   • System 'aea' binary failed, falling back to pure Go implementation error=failed to decrypt using '/usr/bin/aea' (bad key?) exit status 1: Decryption failed
Authentication failed
Error 0xba00a000
byte stream write error
reading segment data
loading segment
worker proc reported an error
worker proc reported an error
SharedBufferWrite
consumer proc reported an error
consumer proc reported an error
consumer proc reported an error
consumer proc reported an error
Threads reported errors
Stream processing cancelled

   ⨯ failed to process filesystem volume error=failed to mount New fs volume: failed to parse AEA encrypted DMG: failed to decrypt clusters: failed to decrypt cluster #22: failed to write uncompressed decrypted data to file: write /var/folders/yb/hx1g2v390cb8zzhs_93zqx340000gn/T/ipsw-diff627744337/ipsw-session/new/141-10103-215.dmg: no space left on device
      • Scanning SystemOS volume 
      • Scanning AppOS volume    
      • Scanning ExclaveOS volume

- [26.6.1 (23G83) .vs 27.2 (24B119)](#2661-23g83-vs-272-24b119)
	- [Inputs](#inputs)
	- [Kernel](#kernel)
		- [Version](#version)
		- [Kexts](#kexts)
			- [🆕 NEW (4)](#-new)
			- [❌ Removed (1)](#-removed)
			- [⬆️ Updated (297)](#️-updated)
	- [Machos](#machos)
	- [DSC](#dsc)
		- [WebKit](#webkit)
		- [Dylibs](#dylibs)
		  - [🆕 NEW (533)](#-new-2)
		  - [❌ Removed (78)](#️-removed-2)
		  - [⬆️ Updated (4176)](#️-updated-2)


# 26.6.1 (23G83) .vs 27.2 (24B119)

## Inputs

- `iPhone18,2_26.6.1_23G83_Restore.ipsw`
- `iPhone18,2_27.2_24B119_Restore.ipsw`

## Kernel

### Version

| iOS                                     | Version                                 | Build                                | Date                                  |
| :-------------------------------------- | :-------------------------------------- | :----------------------------------- | :------------------------------------ |
| 26.6.1 *(23G83)* | 25.6.0 | 12377.162.14~4 | Thu, 30Jul2026 12:43:49 PDT |
| 27.2 *(24B119)* | 27.2.0 | 13432.42.3~28 | Tue, 13Oct2026 21:26:58 PDT |

### Kexts
## DSC


### WebKit

| iOS                                     | Version           |
| :-------------------------------------- | :---------------- |
| 26.6.1 *(23G83)* | 624.5.1.10.3 |
| 27.2 *(24B119)* | 625.2.8.10.7 |

### Dylibs

##### `dyld`
> `/usr/lib/dyld`
```diff

-1387.0.0.0.0
-  __TEXT.__text: 0x9195c
-  __TEXT.__const: 0x20d8
-  __TEXT.__cstring: 0x10072
-  __TEXT.__info_plist: 0x4e5
-  __TEXT.__unwind_info: 0x4f0
-  __DATA_CONST.__const: 0x4c08
-  __AUTH_CONST.__auth_ptr: 0x90
-  __AUTH_CONST.__const: 0x24a0
-  __DATA.__data: 0x1b0
+27104.0.0.0.0
+  __TEXT.__text: 0x9ee60
+  __TEXT.__const: 0x1998
+  __TEXT.__cstring: 0x1263d
+  __TEXT.__info_plist: 0x4eb
+  __TEXT.__unwind_info: 0x35b8
+  __DATA_CONST.__const: 0x5618
+  __AUTH_CONST.__const: 0x2760
+  __AUTH_CONST.__auth_ptr: 0x98
+  __DATA.__data: 0x1c0
   __DATA.__crash_info: 0x148
-  __DATA.__common: 0x930
+  __DATA.__common: 0x8f0
   __DATA.__bss: 0x508
   __DATA_DIRTY.__all_image_info: 0x170
   __DATA_DIRTY.__data: 0x64
-  __DATA_DIRTY.__bss: 0x1bb8
-  __DATA_DIRTY.__common: 0x1120
+  __DATA_DIRTY.__common: 0x1160
