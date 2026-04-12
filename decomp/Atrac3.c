// Atrac3 (at3) is a proprietary Sony Wav format
void init_Atrac3_data(char *name)
{
  int at3;
  
  at3 = strstrip_whitespace(name);
  if (at3 != 0) {
    Assets_heap[1] = '\0';
    at3 = flush_Atrac3_data_mask();
    if ((at3 == 0) && (at3 = get_delimiter_data(), at3 == 0)) {
      if (*Assets_heap == '\0') {
        populate_Atrac3_data(name,0,*(int *)(Assets_heap + 0x80),(int)*(short *)(Assets_heap + 2));
        *Assets_heap = '\0';
      }
      else {
        at3 = flush_Atrac3_data_mask();
        if (at3 == 0) {
          populate_Atrac3_data(name,0,*(int *)(Assets_heap + 0x80),(int)*(short *)(Assets_heap + 2))
          ;
          *Assets_heap = '\0';
        }
        else {
          run_Memory_usage_debugger(0);
          parse_string(Assets_heap + 4,name,0x40);
        }
      }
    }
    else {
      run_Memory_usage_debugger(0);
      parse_string(Assets_heap + 4,name,0x40);
      *Assets_heap = '\x01';
    }
  }
  return;
}
