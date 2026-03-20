// Pointer Tools implementation

// Typical use case: copying from Data on disc copy to a pointer region that Production data uses
// origin - original memory region
// target - memory region being copied into
// slice - max size of allocation region
undefined1 * pointer_copy(undefined1 *origin,undefined1 *target,int slice)
{
  undefined1 uVar1;
  undefined1 *result;
  
  result = origin;
  for (; slice != 0; slice = slice + -1) {
    heap = *origin;
    origin = origin + 1;
    *target = heap;
    target = target + 1;
  }
  return result;
}

int get_value_based_on_pointer_index(int *pointer,undefined4 idx)
{
  int result;
  
  result = 0;
  switch(idx) {
  case 0:
    return *pointer;
  case 1:
    return pointer[1];
  case 2:
    return pointer[2];
  case 3:
    return pointer[3];
  case 4:
    return pointer[4];
  case 5:
    return pointer[5];
  case 6:
    return pointer[6];
  case 7:
    return pointer[7];
  case 8:
    return pointer[8];
  case 9:
    return pointer[10];
  case 10:
    return pointer[0xb];
  case 0xb:
    return pointer[0xc];
  case 0xc:
    return pointer[0xd];
  case 0xd:
    return pointer[0xe];
  case 0xe:
    return pointer[0xf];
  case 0xf:
    return pointer[0x10];
  case 0x10:
    return (int)(char)pointer[0x11];
  case 0x11:
    return (int)*(char *)((int)pointer + 0x45);
  case 0x12:
    return pointer[0x12];
  case 0x13:
    return pointer[0x13];
  case 0x14:
    return pointer[0x14];
  case 0x15:
    return pointer[0x15];
  case 0x16:
    return pointer[0x16];
  case 0x17:
    return pointer[0x17];
  case 0x18:
    result = pointer[0x18];
  }
  return result;
}

void set_value_based_on_pointer_index(undefined4 *pointer,undefined4 index,undefined4 value)
{
  switch(index) {
  case 0:
    *pointer = value;
    return;
  case 1:
    pointer[1] = value;
    return;
  case 2:
    pointer[2] = value;
    return;
  case 3:
    pointer[3] = value;
    return;
  case 4:
    pointer[4] = value;
    return;
  case 5:
    pointer[5] = value;
    return;
  case 6:
    pointer[6] = value;
    return;
  case 7:
    pointer[7] = value;
    return;
  case 8:
    pointer[8] = value;
    return;
  case 9:
    pointer[10] = value;
    return;
  case 10:
    pointer[0xb] = value;
    return;
  case 0xb:
    pointer[0xc] = value;
    return;
  case 0xc:
    pointer[0xd] = value;
    return;
  case 0xd:
    pointer[0xe] = value;
    return;
  case 0xe:
    pointer[0xf] = value;
    return;
  case 0xf:
    pointer[0x10] = value;
    return;
  case 0x10:
    *(char *)(pointer + 0x11) = (char)value;
    return;
  case 0x11:
    *(char *)((int)pointer + 0x45) = (char)value;
    return;
  case 0x12:
    pointer[0x12] = value;
    return;
  case 0x13:
    pointer[0x13] = value;
    return;
  case 0x14:
    pointer[0x14] = value;
    return;
  case 0x15:
    pointer[0x15] = value;
    return;
  case 0x16:
    pointer[0x16] = value;
    return;
  case 0x17:
    pointer[0x17] = value;
    return;
  case 0x18:
    pointer[0x18] = value;
  }
  return;
}

