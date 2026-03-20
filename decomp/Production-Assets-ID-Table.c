// Projection Assets ID Table implementations
int get_production_assets_id_table(void)
{
  int iVar1;
  
  iVar1 = get_production_data_blob();
  return iVar1 + 0x2199c;
}

void allocate_heap_stage2_production_assets_id_table(void)
{
  int data;

  data = get_production_data_blob();
  allocate_heap_stage2((undefined1 *)(data + 0x2199c),0,0x70);
  zero_production_assets_id_table_offset_0x20(0);
  return;
}
