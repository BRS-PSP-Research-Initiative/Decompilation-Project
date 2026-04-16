// The Rendering System Stack code (minus Proprietary implementations)

// Renderer Base Address init
int check_Renderer_init_sanity(void)
{
  int error;
  
  if (((Renderer_base_address_state != 0) || (*(int *)(Renderer_base_address_heap + 0x10) != 0)) ||
     (error = sceGeListUpdateStallAddr
                         ((int)sceGeDraw_base_ptr,*(void **)(Renderer_base_address_heap + 8)),
     -1 < error)) {
    error = 0;
  }
  return error;
}

void init_Renderer_base_address(uint mask,uint base,uint arg,uint flag,char *array)
{
  uint *VTYPE;
  undefined *ptr;

  ptr = Renderer_base_address_heap;
  if (base != 0) {
    VTYPE = *(uint **)(Renderer_base_address_heap + 8);
    *VTYPE = base & 0xffffff | 0x12000000;
    *(uint **)(ptr + 8) = VTYPE + 1;
  }
  if (flag != 0) {
    VTYPE = *(uint **)(ptr + 8);
    *VTYPE = ((flag << 4) >> 0x1c) << 0x10 | 0x10000000;
    *(uint **)(ptr + 8) = VTYPE + 2;
    VTYPE[1] = flag & 0xffffff | 0x2000000;
  }
  if (array != (char *)0x0) {
    VTYPE = *(uint **)(ptr + 8);
    *VTYPE = ((uint)((int)array << 4) >> 0x1c) << 0x10 | 0x10000000;
    *(uint **)(ptr + 8) = VTYPE + 2;
    VTYPE[1] = (uint)array & 0xffffff | 0x1000000;
  }
  VTYPE = *(uint **)(ptr + 8);
  *VTYPE = (mask & 7) << 0x10 | arg | 0x4000000;
  *(uint **)(ptr + 8) = VTYPE + 1;
  check_Renderer_init_sanity();
  return;
}

