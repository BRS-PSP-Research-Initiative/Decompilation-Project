// All of the data flushing mechanisms (how to set data buffers and heap to default / 0 state)

// SHARED
uint flush_data_mask(int heap)
{
  if (heap != 0) {
    return (*(uint *)(heap + 0x12074) & 0x100) >> 8;
  }
  return 0;
}

// AUDIO
undefined4 flush_sceAudio_Data(void)
{
  int reserve;
  int offset;
  int channel;
  
  if (is_sceAudioCh_populated == 0) {
    sceKernel_Data3 = &sceKernel_Data5;
    sceKernel_Data7 = &sceKernel_Data6;
    sceKernelMemset();
    sceKernelMemset();
    sceAudio_Data = sceAudioChReserve(-1,0x1c0,0);
    if (-1 < sceAudio_Data) {
      channel = 0;
      offset = 0;
      while( true ) {
        reserve = sceAudioChReserve(-1,0x100,0);
        *(int *)((int)&sceAudioCh_Data + offset) = reserve;
        if (reserve < 0) break;
        channel = channel + 1;
        offset = channel * 4;
        if (2 < channel) {
          is_sceAudioCh_populated = 1;
          return 0;
        }
      }
      while (channel = channel + -1, -1 < channel) {
        sceAudioChRelease(channel);
      }
      sceAudioChRelease(sceAudio_Data);
    }
  }
  return 0x80440001;
}

int flush_audio_config(uint channel,int format)
{
  int cfg;
  cfg = -0x7fbbfff0;
  if (channel < 4) {
    cfg = sceAudioChangeChannelConfig((&sceAudioCh_Data)[channel],format);
  }
  return cfg;
}

int flush_audio_channel_buffer_length(uint channel,uint length)
{
  int result;
  
  result = -0x7fbbfff0;
  if (channel < 4) {
    result = -0x7fbbffef;
    if (length - 0x40 < 0xff81) {
      result = -0x7fbbffef;
      if ((length & 0x3f) == 0) {
        result = sceAudioSetChannelDataLen((&sceAudioCh_Data)[channel],length);
      }
    }
  }
  return result;
}

void flush_Atrac3_data_mask(void)
{
  flush_data_mask(*(int *)(Assets_heap + 0x80));
  return;
}

// Global Game Data loaded at Start
void flush_global_game_data(void)
{
  int offset;
  int idx;
  undefined1 *heap;
  
  production_data = (undefined1 *)allocate_heap_stage1(0x21ea0,0x89695c0,0x89695c0,0);
  allocate_heap_stage2(production_data,0,0x21ea0);
  *(undefined4 *)(production_data + 0x20018) = 0xffffffff;
  *(undefined4 *)(production_data + 0x2001c) = 0xffffffff;
  *(undefined4 *)(production_data + 0x20020) = 0xffffffff;
  *(undefined4 *)(production_data + 0x20024) = 0xffffffff;
  *(undefined4 *)(production_data + 0x20028) = 0xffffffff;
  idx = 0;
  offset = 0;
  do {
    heap = production_data;
    idx = idx + 1;
    *(undefined4 *)(production_data + offset + 0x206c0) = 0xffffffff;
    *(undefined4 *)(heap + offset + 0x206c4) = 0;
    *(undefined4 *)(heap + offset + 0x206cc) = 0;
    offset = offset + 0x10;
  } while (idx < 6);
  flush_production_data_0x2076c(); // not fully sure what this is yet
  set_FLD_loader_flag(1);
  Fld_data = allocate_heap_stage1(0x300000,0x40,0x89695c0,0x89695c0);
  IF_data = allocate_heap_stage1(0x180000,0x40,0x89695c0,0x89695c0); // Possibly wrong
  return;
}

// Misc
undefined4 flush_Controller_data(void)
{
  SceUID pad;
  
  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(1);
  Controller_data = (undefined1 *)allocate_heap_stage1(0xb0,0x8969fe0,0x8969fe0,0);
  *(undefined4 *)(Controller_data + 0xa0) = 0;
  *(undefined4 *)(Controller_data + 0xa4) = 0x2000;
  *(undefined4 *)(Controller_data + 0xa8) = 0x4000;
  *(undefined4 *)(Controller_data + 0xac) = 0xffffffff;
  allocate_heap_stage2(Controller_data,0,0xa0);
  pad = zero_sceKernelSema_data("Pad");
  *(SceUID *)(Controller_data + 0xac) = pad;
  return 1;
}

undefined4 ExitGame_function_callback(void)
{
  sceKernelExitGame();
  return 0;
}

void flush_real_time_clock(undefined4 tick,undefined4 rtc)
{
  RtcAccumulativeTimeForDriver_data = rtc;
  render_data_update_tick = tick;
  return;
}

void flush_umd_data(void)
{
  sceUmdActivate(1,"disc0:");
  return;
}


void flush_umd_data(void)
{
  sceUmdActivate(1,"disc0:");
  return;
}
