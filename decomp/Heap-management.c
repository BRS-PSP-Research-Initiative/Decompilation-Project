// Heap management implementations - deals with allocating memory in two different stages
// Stage1 - Memory for Data that must be available from the start of the game
// Stage2 - Memory for Data that applies to the Game itself; can be used for production or Pointers to copies of Data from the disc

// Stage1 Allocation is partially lost data; it will probably need to be fully reimplemented from scratch

// heap - current memory being allocated
// value - default value; usually 0 but may be allocated with another value
// slice - max size of allocation region
undefined1 * allocate_heap_stage2(undefined1 *heap,undefined1 value,int slice)
{
  undefined1 *pointer;
  
  pointer = heap;
  for (; slice != 0; slice = slice + -1) {
    *pointer = value;
    pointer = pointer + 1;
  }
  return heap;
}

