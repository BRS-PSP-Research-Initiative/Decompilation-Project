// decompression isn't just the normal kind; there's some customization done to it

// reads string data from Archive and formats it correctly depending on character width and encoding
byte * format_text_from_Archive
                 (int heap,ushort *wide_char,byte *byte_heap1,byte *byte_heap2,
                 int *are_wide_chars_returned)
{
  int enc;
  byte *idx;
  char *start;
  byte *clean1;
  byte *clean2;
  undefined4 cursor;
  int offset;
  ushort char_width [2];
  byte byte_clean1;
  byte byte_heap1[1];
  byte *clean3;
  
  if (wide_char == (ushort *)0x0) {
    wide_char = char_width;
  }
  if (byte_heap1 == (byte *)0x0) {
    start = *(char **)(heap + 0x34);
  }
  else {
    if (byte_heap2 == (byte *)0x0) {
      return (byte *)0xffffffff;
    }
    start = *(char **)(heap + 0x34);
  }
  if ((start != (char *)0x0) && (enc = strstrip_whitespace(start), 1 < enc)) {
    enc = strstrip_encoding(*(byte **)(heap + 0x34),(byte *)"C-SJIS");
    if (enc == 0) {
      byte_clean1 = *byte_heap1;
      if (byte_heap1 == (byte *)0x0) {
        return (byte *)0x0;
      }
      if (((0x80 < byte_clean1) && (byte_clean1 < 0xa0)) ||
         ((0xdf < byte_clean1 && (byte_clean1 < 0xf0)))) {
        byte_heap1[1] = byte_heap1[1];
        if (byte_heap2 < (byte *)0x2) {
          return (byte *)0xffffffff;
        }
        if (((byte_heap1[1] < 0x40) || (0x7e < byte_heap1[1])) &&
           ((byte_heap1[1] < 0x80 || (0xfc < byte_heap1[1])))) {
          return (byte *)0xffffffff;
        }
        *wide_char = (ushort)byte_clean1 * 0x100 + (ushort)byte_heap1[1];
        return (byte *)0x2;
      }
    }
    else {
      enc = strstrip_encoding(*(byte **)(heap + 0x34),(byte *)"C-EUCJP");
      if (enc == 0) {
        byte_clean1 = *byte_heap1;
        if (byte_heap1 == (byte *)0x0) {
          return (byte *)0x0;
        }
        if ((0xa0 < byte_clean1) && (byte_clean1 != 0xff)) {
          byte_heap1[1] = byte_heap1[1];
          if (byte_heap2 < (byte *)0x2) {
            return (byte *)0xffffffff;
          }
          if ((0xa0 < byte_heap1[1]) && (byte_heap1[1] != 0xff)) {
            *wide_char = (ushort)byte_clean1 * 0x100 + (ushort)byte_heap1[1];
            return (byte *)0x2;
          }
          return (byte *)0xffffffff;
        }
      }
      else {
        enc = strstrip_encoding(*(byte **)(heap + 0x34),(byte *)"C-JIS");
        if (enc == 0) {
          if (byte_heap1 == (byte *)0x0) {
            *are_wide_chars_returned = 0;
            return (byte *)0x1;
          }
          enc = 3;
          if (*are_wide_chars_returned == 0) {
            enc = 0;
          }
          idx = (byte *)0x0;
          clean1 = byte_heap1;
          clean2 = byte_heap1;
          clean3 = byte_heap1;
          if (byte_heap2 != (byte *)0x0) {
            do {
              byte_clean1 = *clean2;
              enc = enc * 0x24;
              if (byte_clean1 == 0x4a) {
                cursor = *(undefined4 *)(enc + 0x8977944);
                enc = *(int *)(enc + 0x8977794);
              }
              else if (byte_clean1 == 0x42) {
                cursor = *(undefined4 *)(enc + 0x8977940);
                enc = *(int *)(enc + 0x8977790);
              }
              else if (byte_clean1 == 0x40) {
                cursor = *(undefined4 *)(enc + 0x897793c);
                enc = *(int *)(enc + 0x897778c);
              }
              else if (byte_clean1 == 0x28) {
                cursor = *(undefined4 *)(enc + 0x8977938);
                enc = *(int *)(enc + 0x8977788);
              }
              else if (byte_clean1 == 0x24) {
                cursor = *(undefined4 *)(enc + 0x8977934);
                enc = *(int *)(enc + 0x8977784);
              }
              else if (byte_clean1 == 0x1b) {
                cursor = *(undefined4 *)(enc + 0x8977930);
                enc = *(int *)(enc + 0x8977780);
              }
              else if (byte_clean1 == 0) {
                cursor = *(undefined4 *)(enc + 0x8977948);
                enc = *(int *)(enc + 0x8977798);
              }
              else {
                offset = 8;
                if (byte_clean1 < 0x21) {
LAB_0895988c:
                  offset = offset << 2;
                }
                else {
                  offset = 0x20;
                  if (byte_clean1 < 0x7f) {
                    offset = 7;
                    goto LAB_0895988c;
                  }
                }
                cursor = *(undefined4 *)(enc + offset + 0x8977930);
                enc = *(int *)(enc + offset + 0x8977780);
              }
              switch(cursor) {
              case 0:
                *are_wide_chars_returned = 0;
                *wide_char = (ushort)*clean1;
                return idx + 1;
              case 1:
                *are_wide_chars_returned = 0;
                *wide_char = (ushort)*clean1 * 0x100 + (ushort)clean1[1];
                return idx + 1;
              case 2:
                *are_wide_chars_returned = 1;
                *wide_char = (ushort)*clean1 * 0x100 + (ushort)clean1[1];
                return clean1 + (2 - (int)byte_heap1);
              case 3:
              case 4:
                clean1 = clean3 + 1;
                break;
              case 5:
                break;
              case 6:
                *are_wide_chars_returned = 0;
                *wide_char = 0;
                return idx;
              default:
                return (byte *)0xffffffff;
              }
              idx = idx + 1;
              clean2 = clean2 + 1;
              clean3 = clean3 + 1;
            } while (idx < byte_heap2);
          }
          return (byte *)0xffffffff;
        }
      }
    }
  }
  if (byte_heap1 == (byte *)0x0) {
    return (byte *)0x0;
  }
  *wide_char = (ushort)*byte_heap1;
  return (byte *)(uint)(*byte_heap1 != 0);
}
