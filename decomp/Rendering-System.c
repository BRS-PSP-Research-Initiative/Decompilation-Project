// The Rendering System Stack code (minus Proprietary implementations)

void sceDisplaySetMode_&_FrameBuf
               (int pixel_format,int display_width,int display_height,int frame_buffer_width,
               int depth_buffer_width)
{
  if (sceDisplaySetMode_callback? != (code *)0x0) {
    (*sceDisplaySetMode_callback?)();
  }
  temp_frame_buffer_pixel_format_data = pixel_format;
  depth_buffer_width_data = depth_buffer_width;
  temp_frame_buffer_width_data = frame_buffer_width;
  display_width_data = display_width;
  display_height_data = display_height;
  sceDisplaySetMode(0,display_width,display_height);
  if (frame_buffer_data == 1) {
    sceDisplaySetFrameBuf
              ((void *)(sceGeEdramAddr_data + temp_frame_buffer_width_data),depth_buffer_width,
               pixel_format,1);
  }
  return;
}

void populate_render_buffer1
               (int display_width,int display_height,int frame_buffer_width,int depth_buffer_width)
{
  undefined4 *render_buffer1;
  int slice;
  undefined4 height;
  undefined4 width;
  
  sceDisplaySetMode_&_FrameBuf
            (temp_frame_buffer_pixel_format_data,display_width,display_height,frame_buffer_width,
             depth_buffer_width);
  render_buffer1 = &::render_buffer1;
  slice = 4;
  do {
    height = display_height_data;
    width = display_width_data;
    slice = slice + -1;
    render_buffer1[0x27] = temp_frame_buffer_pixel_format_data;
    render_buffer1[0x28] = width;
    render_buffer1[0x29] = height;
    render_buffer1 = render_buffer1 + 0x3f;
  } while (-1 < slice);
  return;
}

