// Projection Matrix data implementations
void copy_projection_matrix_data_to_production_data(void)
{
  int data;

  data = get_production_data_blob();
  pointer_copy((undefined1 *)(data + 0x21a10),(undefined1 *)(data + 0x21538),100);
  return;
}

void allocate_heap_stage2_production_projection_matrix_data(void)
{
  int data;

  data = get_production_data_blob();
  allocate_heap_stage2((undefined1 *)(data + 0x21538),0,100);
  return;
}

int get_production_projection_matrix_data(void)
{
  int data;

  data = get_production_data_blob();
  return data + 0x21538;
}

int get_value_of_production_projection_matrix_data_by_switch(uint switch)
{
  int result;
  int *pmd;
  
  result = 0;
  switch(switch) {
  case 0:
    result = get_value_of_production_projection_matrix_data[0x08]();
    break;
  case 1:
    result = get_value_of_production_projection_matrix_data[0x10]();
    break;
  case 2:
    result = get_value_of_production_projection_matrix_data[0x0f]();
    break;
  case 3:
    result = get_value_of_production_projection_matrix_data[0x15]();
    break;
  case 4:
    result = get_value_of_production_projection_matrix_data[0x13]();
    break;
  case 5:
    result = get_value_of_production_projection_matrix_data[0x11]_times_[0x14]();
    break;
  case 6:
    result = get_value_of_production_projection_matrix_data[0x11]();
    break;
  case 7:
    result = get_value_of_production_projection_matrix_data[0x14]();
    break;
  default:
    if ((0xc < switch) && (switch < 0x11)) {
      pmd = (int *)get_production_projection_matrix_data();
      result = get_value_based_on_pointer_index(pmd,switch - 2);
    }
    break;
  case 9:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,1);
    break;
  case 10:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,2);
    break;
  case 0xb:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,9);
    break;
  case 0xc:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,10);
    break;
  case 0x12:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,5);
    break;
  case 0x13:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,6);
    break;
  case 0x14:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,4);
    break;
  case 0x15:
    pmd = (int *)get_production_projection_matrix_data();
    result = get_value_based_on_pointer_index(pmd,7);
    break;
  case 0x16:
    result = 0x32;
  }
  return result;
}
