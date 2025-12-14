/*
 *if base and bounds were arrays (with one entry per segment),
 *the hardware would be doing something like this to obtain the desired
 *physical address: 
 *Base and Bounds Segmentation
 * Hardware address translation using segmented memory with base and bounds.
 */

#include <stdint.h>
#include <stdlib.h>

#define SEG_MASK 0xC000    // Top 2 bits for segment
#define SEG_SHIFT 14
#define OFFSET_MASK 0x3FFF // Lower 14 bits for offset
#define PROTECTION_FAULT 1

typedef struct {
  uint32_t base[4];
  uint32_t bounds[4];
} SegmentTable;

uint32_t translate_virtual_address(uint32_t vaddr, SegmentTable *seg_table) {
  int segment = (vaddr & SEG_MASK) >> SEG_SHIFT;
  uint32_t offset = vaddr & OFFSET_MASK;
  
  if (offset >= seg_table->bounds[segment]) {
    raise_exception(PROTECTION_FAULT);
    return 0;
  }
  
  return seg_table->base[segment] + offset;
}

void raise_exception(int fault_type) {
  // Handle exception
  exit(EXIT_FAILURE);
}

uint32_t access_memory(uint32_t phys_addr) {
  // Access memory at physical address
  return *(uint32_t *)phys_addr;
}