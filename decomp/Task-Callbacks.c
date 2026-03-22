// Implementations related to Task Management through Callbacks
void populate_task_callback_queue(int heap)
{
  int clean;
  int tcp;

  tcp = task_callback_pointer;
  if (task_callback_pointer == heap) {
    *(undefined4 *)(heap + 0x44) = 0;
    *(undefined4 *)(heap + 0x40) = 0;
  }
  else {
    if (*(ushort *)(heap + 0x10) < *(ushort *)(task_callback_pointer + 0x10)) {
      clean = heap;
      *(int *)(heap + 0x44) = task_callback_pointer;
      task_callback_pointer = clean;
      *(undefined4 *)(heap + 0x40) = 0;
      *(int *)(tcp + 0x40) = heap;
      return;
    }
    clean = *(int *)(task_callback_pointer + 0x44);
    while( true ) {
      if (clean == 0) {
        *(int *)(tcp + 0x44) = heap;
        *(int *)(heap + 0x40) = tcp;
        return;
      }
      if (*(ushort *)(heap + 0x10) < *(ushort *)(clean + 0x10)) break;
      tcp = clean;
      clean = *(int *)(clean + 0x44);
    }
    *(int *)(heap + 0x44) = clean;
    *(int *)(heap + 0x40) = tcp;
    *(int *)(tcp + 0x44) = heap;
    if (*(int *)(heap + 0x44) != 0) {
      *(int *)(*(int *)(heap + 0x44) + 0x40) = heap;
      return;
    }
  }
  return;
}

int * run_task_function_callback
                (int start,undefined4 context,undefined2 id,int address,int pointer,
                undefined4 subcontext1,undefined4 subcontext2)
{
  int *heap;
  undefined4 clean;
  int completed;
  int continue;
  int *heap2;
  
  clean = task_callback_heap;
  task_callback_heap = (int *)0x0;
  heap = (int *)allocate_heap_stage1(0x58,0x8969a00,0x8969a00,0);
  if (heap == (int *)0x0) {
    return (int *)0x0;
  }
  allocate_heap_stage2((undefined1 *)heap,0,0x58);
  heap[6] = address;
  *(undefined2 *)(heap + 2) = 0x1801;
  *(undefined2 *)((int)heap + 10) = 0;
  *(undefined2 *)(heap + 3) = 0x1801;
  *(undefined2 *)((int)heap + 0xe) = 0x1801;
  heap[7] = pointer;
  *(undefined2 *)(heap + 4) = id;
  heap[0x12] = start;
  heap[0x13] = 0;
  heap[0x14] = 0;
  continue = task_callback_queue_continue;
  completed = task_callback_queue_completed;
  *(ushort *)((int)heap + 0x12) = *(ushort *)((int)heap + 0x12) | 1;
  *(ushort *)((int)heap + 0x12) = *(ushort *)((int)heap + 0x12) | 2;
  *(ushort *)((int)heap + 0x12) = *(ushort *)((int)heap + 0x12) & 0xfffb;
  heap[1] = continue;
  *heap = completed;
  *(ushort *)((int)heap + 0x12) = *(ushort *)((int)heap + 0x12) & 0xfff7;
  *(ushort *)((int)heap + 0x12) = *(ushort *)((int)heap + 0x12) | 0x10;
  *(ushort *)((int)heap + 0x12) = *(ushort *)((int)heap + 0x12) & 0xffdf;
  task_callback_queue_completed = task_callback_queue_completed + 1;
  task_callback_queue_continue =
       (uint)(task_callback_queue_completed == 0) + task_callback_queue_continue;
  if (start != 0) {
    completed = *(int *)(start + 0x4c);
    if (completed == 0) {
      *(int **)(start + 0x4c) = heap;
    }
    else {
      for (continue = *(int *)(completed + 0x50); continue != 0;
          continue = *(int *)(continue + 0x50)) {
        completed = continue;
      }
      *(int **)(completed + 0x50) = heap;
    }
  }
  task_callback_heap = heap;
  set_tbl_data(heap);
  (*(code *)heap[6])(heap,0,subcontext1,subcontext2);
  task_callback_global_queue = task_callback_global_queue + 1;
  heap2 = heap;
  task_callback_heap = (int *)clean;
  if (task_callback_global_queue != 1) {
    populate_task_callback_queue((int)heap);
    heap2 = task_callback_pointer;
  }
  task_callback_pointer = heap2;
  return heap;
}

