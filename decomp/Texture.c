// Renderer Texture Stack
void init_Renderer_texture_stack(void)
{
  byte *stack;
  
  scePspGu::sceGuOffset(0x710,0x778);
  scePspGu::sceGuViewport(0x800,0x800,0x1e0,0x110);
  scePspGu::sceGuDepthRange(50000,10000);
  scePspGu::sceGuScissor(0,0,0x1e0,0x110);
  scePspGu::sceGuEnable(10);
  scePspGu::sceGuEnable(0xb);
  scePspGu::sceGuEnable(0xc);
  scePspGu::sceGuEnable(0xd);
  scePspGu::sceGuEnable(0xe);
  scePspGu::sceGuLight(0);
  scePspGu::sceGuAmbientColorABGR(0,0xffffffff,0xffffffff,0xffffffff);
  scePspGu::sceGuColorMaterial(1);
  scePspGu::sceGuShadeModel(1);
  scePspGu::sceGuEnable(0x15);
  scePspGu::sceGuTexFunc(0,1);
  scePspGu::sceGuEnable(0);
  scePspGu::sceGuEnable(4);
  scePspGu::sceGuBlendFunc(0,2,3,0,0);
  scePspGu::sceGuEnable(1);
  scePspGu::sceGuEnable(0x12);
  scePspGu::sceGuFrontFace(1);
  scePspGu::sceGmoModelGetVertexOffset?((int *)0x0);
  scePspGu::sceGuEnable(7);
  scePspGu::sceGuEnable(5);
  scePspGu::sceGuTexOffset(0,0);
  scePspGu::sceGuEnable(6);
  scePspGu::sceGuTexFilter(1,1);
  scePspGu::sceGuEnable(2);
  scePspGu::sceGuLightMode(0xffffffff);
  scePspGu::sceGumOrtho(0,0x43f00000,0x43880000,0,0xc3fa0000,0x43fa0000);
  scePspGu::sceGuSetMatrix(0,(int)&stack);
  scePspGu::sceGuSetMatrix(1,0x166710);
  scePspGu::sceGuSetMatrix(2,0x166710);
  scePspGu::sceGuSetMatrix(3,0x166710);
  scePspGu::sceGuTexWrap(0,0);
  return;
}

// Texture index
uint decrypt_Texture_idx(undefined4 idx,int y,int x)
{
  uint mask;
  
  mask = x * y;
  switch(idx) {
  case 0:
  case 1:
  case 2:
  case 6:
    return mask * 2;
  case 3:
  case 7:
    return mask * 4;
  case 4:
    mask = mask >> 1;
  case 5:
    return mask;
  case 8:
    return mask >> 1;
  case 9:
  case 10:
    mask = 0;
  default:
    return mask;
  }
}

// CLUT parsing
void decrypt_CLUT(int heap)
{
  uint start;
  uint range;
  int shifter;
  uint key;
  int idx;
  uint size;
  uint mask;
  uint cursor;
  uint code;
  int encryption_key;
  
  start = heap + 0x10;
  code = (uint)*(byte *)(heap + 8);
  mask = *(byte *)(heap + 9) & 0xf;
  shifter = 1;
  range = *(ushort *)(heap + 6) & 0xfff;
  key = (int)(uint)*(byte *)(heap + 9) >> 4;
  size = heap + *(int *)(heap + 0xc);
  encryption_key = 1 << ((int)(uint)*(ushort *)(heap + 6) >> 0xc);
  cursor = 0;
  if (1 < range) {
    for (shifter = 2; shifter < (int)range; shifter = shifter << 1) {
    }
  }
  scePspGu::sceGuEnable(9);
  switch(*(undefined1 *)(heap + 8)) {
  case 0:
  case 1:
  case 2:
    cursor = 1;
    if ((encryption_key < 8) || (range < 8)) {
      cursor = 0;
    }
    break;
  case 3:
    code = 3;
    cursor = 1;
    if ((encryption_key < 4) || (range < 8)) {
      cursor = 0;
    }
    break;
  case 4:
    code = 4;
    cursor = 1;
    if ((encryption_key < 0x20) || (range < 8)) {
      cursor = 0;
    }
    if (key < 2) {
      if (true) {
        if (key == 0) {
          scePspGu::sceGuClutMode(0,0,0xff,0);
          scePspGu::sceGuClutLoad(1,size);
        }
        else {
          scePspGu::sceGuClutMode(1,0,0xff,0);
          scePspGu::sceGuClutLoad(1,size);
        }
      }
    }
    else if (key < 3) {
      scePspGu::sceGuClutMode(2,0,0xff,0);
      scePspGu::sceGuClutLoad(1,size);
    }
    else if (key < 4) {
      scePspGu::sceGuClutMode(3,0,0xff,0);
      scePspGu::sceGuClutLoad(2,size);
    }
    break;
  case 5:
    code = 5;
    cursor = 1;
    if ((encryption_key < 0x10) || (range < 8)) {
      cursor = 0;
    }
    if (key < 2) {
      if (true) {
        if (key == 0) {
          scePspGu::sceGuClutMode(0,0,0xff,0);
          scePspGu::sceGuClutLoad(0x10,size);
        }
        else {
          scePspGu::sceGuClutMode(1,0,0xff,0);
          scePspGu::sceGuClutLoad(0x10,size);
        }
      }
      break;
    }
    if (2 < key) {
      if (key < 4) {
        scePspGu::sceGuClutMode(3,0,0xff,0);
        scePspGu::sceGuClutLoad(0x20,size);
      }
      break;
    }
    scePspGu::sceGuClutMode(2,0,0xff,0);
    scePspGu::sceGuClutLoad(0x10,size);
  case 6:
  case 7:
    break;
  case 8:
    code = 8;
  case 9:
  case 10:
    cursor = 0;
  }
  scePspGu::sceGuTexMode(code,mask,0,cursor);
  idx = 0;
  if (mask != 0xffffffff) {
    do {
      scePspGu::sceGuTexImage(idx,encryption_key,shifter,encryption_key,start);
      range = decrypt_Texture_idx((uint)*(byte *)(heap + 8),encryption_key,shifter);
      idx = idx + 1;
      start = start + range;
      encryption_key = encryption_key / 2;
      shifter = shifter / 2;
    } while (idx < (int)(mask + 1));
  }
  return;
}

// Decrypt Texture Data
void decrypt_Texture_data(uint *xmask)
{
  uint data;
  uint mask;
  ScePspFMatrix4 matrix;
  
  data = get_texture_data();
  if ((0 < (int)xmask[7]) || ((int)xmask[7] < 0)) {
    scePspGu::sceGuEnable(0x15);
    scePspGu::sceGuTexFunc(0,0);
    scePspGu::sceGuEnable(1);
    scePspGu::sceGuEnable(0);
    scePspGu::sceGuBlendFunc(0,2,3,0,0);
    scePspGu::sceGuBlendFunc(0,10,10,0xffffff,0);
    scePspGu::sceGuColorMaterial(0xffffffff);
    scePspGu::sceGuTexFilter(1,1);
    scePspGu::sceGuEnable(4);
    scePspGu::sceGuTexMode(1,0,0,0);
    scePspGu::sceGuTexImage(0,0x200,0x200,0x200,data);
    scePspGu::sceGuEnable(9);
    scePspGu::sceGuLightMode(0x80ffffff);
    scePspGu::sceGuAmbient(0xff333333);
    init_Renderer_texture_stack();
    scePspGu::sceGuEnable(9);
    scePspGu::sceGuEnable(5);
    libpspmath::vfpu_ortho_matrix(&matrix);
    matrix.x.x = 960.0;
    matrix.y.y = 544.0;
    scePspGu::sceGuSetMatrix(2,(int)&matrix);
    libpspmath::vfpu_ortho_matrix(&matrix);
    if ((*xmask & 1) == 0) {
      mask = (int)((xmask[3] - xmask[5]) * 0xff) / (int)xmask[3];
    }
    else {
      mask = 0xff;
    }
    scePspGu::sceGuColorMaterial
              (mask << 8 | mask |
               (int)((xmask[2] - xmask[4]) * 0xff) / (int)xmask[2] << 0x18 | mask << 0x10);
    scePspGu::sceGuTexFunc(0,0);
    scePspGu::sceGuBlendFunc(0,2,3,0,0);
    scePspGu::sceGuEnable(4);
    scePspGu::sceGuTexMode(1,0,0,0);
    scePspGu::sceGuTexImage(0,0x200,0x200,0x200,data);
    scePspGu::sceGuEnable(9);
    scePspGu::sceGuTexScale(0x3f700000,0x3f080000);
    init_Renderer_base_address(4,0x81,0x13,0,&Renderer_base_address_buffer);
    scePspGu::sceGuTexScale(0x3f800000,0x3f800000);
  }
  return;
}

