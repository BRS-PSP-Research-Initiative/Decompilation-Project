/* 0x88106ec - System.VOL_data - Copy of System.VOL on heap */
/* Heap allocation implementation is completely broken; 
 * devs most likely used undocumented, custom Assembly code or other hacks */
undefined4 * allocate_System.VOL_copy_on_heap_var1
          (char *string,undefined4 *pointer,short mask,undefined4 unknown,int negative)

{
  undefined4 *heap;
  int normal;
  uint flags;
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  heap = (undefined4 *)allocate_heap_stage1(0x120,0x8969ae4,0x8969ae4,0);
  allocate_heap_stage2((undefined1 *)heap,0,0x120);
  strcpy((char *)(heap + 3),"disc0:/PSP_GAME/USRDIR/");
  normal = str_remove_null(string);
  remove_non_alphabet_chars_from_string(string,normal);
  strcpy((char *)(heap + 3),string);
  *heap = 0;
  if (negative < 1) {
    negative = -0x1;
  }
  heap[0x43] = negative;
  if (mask != 0) {
    *pointer = 0;
  }
  *(byte *)(heap + 1) = *(byte *)(heap + 1) & 0xfe | (byte)mask & 1;
  *(byte *)(heap + 1) = *(byte *)(heap + 1) & 0xfd;
  heap[0x44] = pointer;
  heap[0x45] = unknown;
  heap[0x46] = 0;
  heap[0x47] = 0;
  flags = sceKernelCpuSuspendIntr();
  puVar1 = heap;
  if (System.VOL_data != (undefined4 *)0x0) {
    puVar1 = System.VOL_data;
    for (puVar2 = (undefined4 *)System.VOL_data[0x47]; puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)puVar2[0x47]) {
      puVar1 = puVar2;
    }
    puVar1[0x47] = heap;
    heap[0x47] = 0;
    heap[0x46] = puVar1;
    puVar1 = System.VOL_data;
  }
  System.VOL_data = puVar1;
  sceKernelCpuResumeIntr(flags);
  return heap;
}

undefined4 * allocate_System.VOL_copy_on_heap_var2
          (char *string,undefined4 *pointer,short mask,undefined4 unknown,int negative)

{
  undefined4 *heap;
  int not_disc0;
  uint flags;
  undefined4 *stage2;
  undefined4 *stage1;
  
  heap = (undefined4 *)allocate_heap_stage1(0x120,0x8969ae4,0x8969ae4,0);
  allocate_heap_stage2((undefined1 *)heap,0,0x120);
  not_disc0 = strstr((byte *)string,(byte *)"disc0:",5);
  if (not_disc0 != 0) {
    strcpy((char *)(heap + 3),"disc0:/PSP_GAME/USRDIR/");
  }
  not_disc0 = str_remove_null(string);
  remove_non_alphabet_chars_from_string(string,not_disc0);
  strcpy((char *)(heap + 3),string);
  *heap = 0;
  if (negative < 1) {
    negative = -1;
  }
  heap[0x43] = negative;
  if (mask != 0) {
    *pointer = 0;
  }
  heap[2] = 0xffffffff;
  *(byte *)(heap + 1) = *(byte *)(heap + 1) & 0xfe | (byte)mask & 1;
  *(byte *)(heap + 1) = *(byte *)(heap + 1) & 0xfd;
  heap[0x44] = pointer;
  heap[0x45] = unknown;
  heap[0x46] = 0;
  heap[0x47] = 0;
  flags = sceKernelCpuSuspendIntr();
  stage2 = heap;
  if (System.VOL_data != (undefined4 *)0x0) {
    stage2 = System.VOL_data;
    for (stage1 = (undefined4 *)System.VOL_data[0x47]; stage1 != (undefined4 *)0x0;
        stage1 = (undefined4 *)stage1[0x47]) {
      stage2 = stage1;
    }
    stage2[0x47] = heap;
    heap[0x47] = 0;
    heap[0x46] = stage2;
    stage2 = System.VOL_data;
  }
  System.VOL_data = stage2;
  sceKernelCpuResumeIntr(flags);
  return heap;
}

