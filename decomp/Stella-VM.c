// Stella VM and associated values
void * init_StellaVM(int start)
{
  void *code;
  void *slice;
  SceSize size;
  void *temp;
  
  if (StellaVM_heap == (void *)0x0) {
    size = 0x10000; // this looks like it's just for debug stuff since game is always true otherwise
    if (true) {
      if (StellaVM_base_size_pointer == 0) { // base size is 0x5400 at address pointed to
        return (void *)0xffffffff;
      }
      size = StellaVM_base_size_pointer << 10; // converts base to real size
      if (size == 0) goto allocate_StellaVM_from_slice;
    }
    StellaVM_block_id = sceKernelAllocPartitionMemory(2,"UserSbrk",3,size,(void *)4096);
    if (0 < StellaVM_block_id) {
      StellaVM_block_start = sceKernelGetBlockHeadAddr(StellaVM_block_id);
      StellaVM_block_end = (void *)((int)StellaVM_block_start + size);
      StellaVM_heap = StellaVM_block_start;
    }
  }
allocate_StellaVM_from_slice:
  temp = StellaVM_block_start;
  if (StellaVM_heap == (void *)0x0) {
    code = (void *)0xffffffff;
  }
  else {
    slice = (void *)((int)StellaVM_block_start + start);
    code = (void *)0xffffffff;
    if ((StellaVM_heap <= slice) &&
       (code = StellaVM_block_start, temp = slice, StellaVM_block_end < slice)) {
      return (void *)0xffffffff;
    }
  }
  StellaVM_block_start = temp;
  return code;
}

// instead of booting like a normal PSP game, bypass the bootloader and run full game code inside of StellaVM's memory space
void bootstrap_StellaVM_binary(int thread)
{
  code *StellaVM_binary;
  int *temp;
  int *cursor;
  int slice;

  // The way the StellaVM_binary implementation works is currently not fully understood; it can go a few ways
  temp = *(int **)(StellaVM_binary_pointer + 0x148);
  if (temp == (int *)0x0) {
    StellaVM_binary = *(code **)(StellaVM_binary_pointer + 0x3c);
  }
  else {
    slice = temp[1];
    while( true ) {
      slice = slice + -1;
      if (-1 < slice) {
        cursor = temp + slice;
        do {
          (*(code *)cursor[2])();
          slice = slice + -1;
          cursor = cursor + -1;
        } while (-1 < slice);
      }
      temp = (int *)*temp;
      if (temp == (int *)0x0) break;
      slice = temp[1];
    }
    StellaVM_binary = *(code **)(StellaVM_binary_pointer + 0x3c);
  }
  if (StellaVM_binary != 0) {
    (*StellaVM_binary)(); // Possibly running the ELF header (what PSP usually boots with) as both the PSP boot and StellaVM bootloading mechanism
  }
  check_module_sanity(thread);
  return;
}

// Check if everything is running correctly
void check_StellaVM_sanity(int *heap,int start)
{
  void *code;

  StellaVM_error_thrown = 0;
  code = init_StellaVM(start);
  if ((code == (void *)0xffffffff) && (StellaVM_error_thrown != 0)) {
    *heap = StellaVM_error_thrown;
  }
  return;
}

// This is just debug code left in that is currently mostly dead due to 	`if (false)` code
void check_module_sanity(int thread)
{
  int *heap;
  int *pointer;
  int id;
  int kmod_id;
  int status [4];

  if (false) {
    heap = (int *)func_0xf77fc000(); // ignore these since this function probably only exists in their Debug / Dev Tools
    pointer = (int *)get_StellaVM_binary_pointer();
    if (heap != pointer) {
      sceKernelPrintf();
      sceKernelExitThread(thread);
    }
    debug_main_thread(heap); // this code goes pretty far down the stack; until debug is able to get enabled, this probably won't be of much interest yet
    id = func_0xf77fc000(heap);
    kmod_id = sceKernelGetModuleId();
    if (kmod_id != id) {
      sceKernelStopModule(id,0,(void *)0x0,status,(SceKernelSMOption *)0x0);
      sceKernelUnloadModule(id);
      sceKernelExitThread(thread);
    }
  }
  status[0] = sceKernelStopUnloadSelfModuleWithStatus();
  sceKernelPrintf();
  trap(0);
  return;
}

// heap here is a reference to a pointer to a table that seems to not be loaded by the game but instead at boot up; my guess - the jump table in the last section of the binary
undefined4 parse_StellaVM_library_table(undefined4 heap)
{
  undefined4 *cursor;
  int pos;
  undefined *bin;
  
  bin = StellaVM_binary_pointer;
  cursor = *(undefined4 **)(StellaVM_binary_pointer + 0x148);
  if (cursor == (undefined4 *)0x0) {
    cursor = (undefined4 *)(StellaVM_binary_pointer + 0x14c);
    *(undefined4 **)(StellaVM_binary_pointer + 0x148) = cursor;
    pos = *(int *)(bin + 0x150);
  }
  else {
    pos = cursor[1];
  }
  if (0x1f < pos) {
    cursor = (undefined4 *)parse_StellaVM_binary_pointer_offset_0x88(0x88);
    if (cursor == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    cursor[1] = 0;
    *cursor = *(undefined4 *)(StellaVM_binary_pointer + 0x148);
    *(undefined4 **)(StellaVM_binary_pointer + 0x148) = cursor;
  }
  pos = cursor[1];
  cursor[1] = pos + 1;
  cursor[pos + 2] = heap;
  return 0;
}

// majority of these `variables` that say local or auStack don't do anything
// the function name is partially a community joke with the BRS fan Discord server and what the main StellaVM thread is labeled in the code
SceKernelThreadEntry samuel_jackson_thread(int size,char *xtext)
{
  int main;
  int data;
  undefined1 *stream;
  uint cursor;
  char *heap;
  char **p2p;
  int in_k0;
  char *text [24];
  undefined4 local_3a0;
  undefined1 *stack;
  undefined1 *local_398;
  undefined1 *local_394;
  undefined4 local_390;
  undefined1 clean2 [28];
  undefined4 local_370;
  undefined1 *sj;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  undefined1 local_340;
  undefined1 pos [36];
  undefined4 local_300;
  undefined4 local_2f8;
  undefined4 local_2f4;
  undefined2 local_2f0;
  undefined2 local_2ee;
  undefined2 local_2ec;
  undefined2 local_2ea;
  undefined2 local_2e8;
  undefined2 local_2e6;
  undefined2 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined1 local_2c8;
  undefined1 local_2c0;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_1cc;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined1 temp_stack [92];
  undefined1 auStack_dc [92];
  undefined1 auStack_80 [92];
  undefined4 local_24;
  char *clean_text;
  
  p2p = text;
  if ((true) || (_flush_global_game_data == 0)) {
    init_StellaVM(0);
  }
  main = 0;
  heap = xtext;
  clean_text = xtext;
  if (0 < size) {
    while( true ) {
      text[0] = clean_text;
      main = main + 1;
      data = strstrip_whitespace(heap);
      heap = heap + data + 1;
      p2p = p2p + 1;
      if ((0x13 < main) || (size <= (int)heap - (int)xtext)) break;
      *p2p = heap;
      clean_text = text[0];
    }
  }
  text[main] = (char *)0x0;
  if (true) {
    stack = temp_stack;
    local_398 = auStack_dc;
    local_394 = auStack_80;
    stream = clean2;
    main = 0x18;
    local_3a0 = 0;
    local_390 = 0;
    do {
      main = main + -1;
      *stream = 0;
      stream = stream + 1;
    } while (-1 < main);
    sj = &Sam_Jackson;
    cursor = 0;
    local_370 = 0;
    local_368 = 0;
    local_364 = 0;
    local_360 = 0;
    local_35c = 0;
    local_358 = 0;
    local_354 = 0;
    local_350 = 0;
    local_34c = 0;
    local_348 = 0;
    local_344 = 0;
    local_340 = 0;
    do {
      stream = pos + cursor;
      cursor = cursor + 1;
      *stream = 0;
    } while (cursor < 0x24);
    local_2f8 = 1;
    local_2f4 = 0;
    local_2f0 = 0x330e;
    local_2ee = 0xabcd;
    local_2ec = 0x1234;
    local_2ea = 0xe66d;
    local_2e8 = 0xdeec;
    local_2e6 = 5;
    local_2e4 = 0xb;
    local_300 = 0;
    local_2e0 = 0;
    local_2dc = 0;
    local_2d8 = 0;
    local_2d4 = 0;
    local_2d0 = 0;
    local_2cc = 0;
    local_2a4 = 0;
    local_2a0 = 0;
    local_29c = 0;
    local_298 = 0;
    local_294 = 0;
    local_290 = 0;
    local_28c = 0;
    local_288 = 0;
    local_284 = 0;
    local_280 = 0;
    local_2c8 = 0;
    local_2c0 = 0;
    local_2a8 = 0;
    local_258 = 0;
    local_254 = 0;
    local_250 = 0;
    local_24c = 0;
    local_14c = 0;
    local_1cc = 0;
    local_148 = 0;
    local_144 = 0;
    local_140 = 0;
    local_13c = 0;
    allocate_heap_stage2(stack,0,0x114);
    local_24 = 0;
  }
  else {
    func_0xf77fc000(&local_3a0);
    main = sceKernelGetModuleIdByAddress(module_start);
    main = func_0xf77fc000(main,&local_3a0);
    if (main < 0) {
      sceKernelExitThread(1);
      return flush_global_game_data;
    }
  }
  *(undefined4 **)(in_k0 + 4) = &local_3a0;
  parse_StellaVM_library_table(&StellaVM_library_table);
  unknown_StellaVM_function();
  if ((false) && (false)) {
    parse_StellaVM_library_table(0);
    func_0xf77fc000();
  }
  main = sceKernelStart_main_thread();
  if ((false) && (data = main, _flush_global_game_data != 0)) goto flush_StellaVM_binary;
  do {
    data = bootstrap_StellaVM_binary(main);
flush_StellaVM_binary:
    sceKernelExitDeleteThread(data);
  } while( true );
}

// Where the `module` starts after the PSP boots up the game
bool module_start(SceSize size,void *args)
{
  SceUID suid;
  char *name;
  uint priority;
  int stack_size;
  SceUInt attr;
  
  sceKernelSetCompiledSdkVersion603_605();
  sceKernelSetCompilerVersion();
  if (false) {
    _flush_global_game_data = sceKernelGetSystemTimeLow();
    _flush_global_game_data = _flush_global_game_data ^ _flush_global_game_data << 0xb;
    priority = sceKernelGetThreadId();
    _flush_global_game_data = _flush_global_game_data ^ priority;
  }
  name = s_mfrpg_main; // Samuel mfing rpg main; recently rewatch Snakes on a Plane
  if (false) {
    name = "user_main";
  }
  priority = 0x20;
  if (false) {
    priority = _flush_global_game_data;
  }
  stack_size = 0x40000;
  if (true) {
    stack_size = StackSize << 10;
  }
  attr = 0x80000000;
  if (false) {
    attr = _flush_global_game_data | 0x80000000;
  }
  suid = sceKernelCreateThread
                   (name,samuel_jackson_thread,priority,stack_size,attr,
                    (SceKernelThreadOptParam *)0x0);
  if (suid >= 0) {
    sceKernelStartThread(suid,size,args);
  }
  return suid < 0;
}

// Production Debug
void StellaVM_binary_Memory_debugger(int code)
{
  run_Memory_usage_debugger(code);
  *fevt_&_minigame_data = *fevt_&_minigame_data & 0xffffffef;
  return;
}

void StellaVM_binary_Memory_debugger(int heap)
{
  int data;
  
  data = get_Production_bootstrap(heap,0);
  StellaVM_binary_Memory_debugger(data);
  return;
}


