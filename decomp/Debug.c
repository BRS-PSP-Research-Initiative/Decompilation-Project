// Debug code related to tracking Memory Usage
// Max Memory is 32MB (32768)
// divisor is just how it can be divided into equal chunks
undefined4 debug_Memory_usage_by_divisor(int heap,int divisor)
{
  uint flags;
  
  if (delimiter_data == '\0') {
    flags = sceKernelCpuSuspendIntr();
    if (divisor < 1) {
      *(undefined4 *)(heap + 0x12090) = 32768;
    }
    else {
      if (256 < divisor) {
        divisor = 256;
      }
      *(int *)(heap + 0x12090) = 32768 / divisor;
    }
    sceKernelCpuResumeIntr(flags);
    return 1;
  }
  return 0;
}

void run_Memory_usage_debugger(int code)
{
  char temp;

  if (code < 1) {
    debug_Memory_usage_by_divisor(*(int *)(Assets_heap + 0x80),0);
    temp = *Assets_heap;
  }
  else {
    debug_Memory_usage_by_divisor(*(int *)(Assets_heap + 0x80),code);
    temp = *Assets_heap;
  }
  if (temp != '\0') {
    *Assets_heap = '\0';
  }
  return;
}
