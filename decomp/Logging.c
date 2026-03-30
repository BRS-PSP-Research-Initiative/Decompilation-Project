// Debug logging implementation
int get_log(int fd,void *data,SceSize size)
{
  int log;
  
  if (fd == 1) {
    fd = sceKernelStdout();
  }
  else if (fd < 2) {
    if (fd == 0) {
      fd = sceKernelStdin();
    }
  }
  else if (fd == 2) {
    fd = sceKernelStderr();
  }
  log = -9;
  if (-1 < fd) {
    log = sceIoWrite(fd,data,size);
  }
  return log;
}

uint read_&_write_debug_log(int fd,undefined1 *heap,uint range,int action)
{
  uint log;
  int temp;
  undefined1 *data;
  
  if (action == 1) {
    log = get_log(fd,&temp_log,Log_size);
    Log_size = 0;
    Log_heap_ptr = &temp_log;
    return log;
  }
  log = 0;
  data = heap;
  if (range != 0) {
    do {
      *Log_heap_ptr = *data;
      Log_heap_ptr = Log_heap_ptr + 1;
      Log_size = Log_size + 1;
      if (0x7f < (int)Log_size) {
        temp = get_log(fd,&temp_log,Log_size);
        Log_heap_ptr = &temp_log;
        Log_size = 0;
        if (temp == 0) {
          return 0;
        }
      }
      log = log + 1;
      data = heap + log;
    } while (log < range);
  }
  return log;
}

int strstrip_whitespace(char *heap)
{
  char *clean;
  char cursor;

  cursor = *heap;
  clean = heap;
  while (cursor != '\0') {
    clean = clean + 1;
    cursor = *clean;
  }
  return (int)clean - (int)heap;
}
