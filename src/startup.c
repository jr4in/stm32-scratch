/**
 * file: startup.c
 * brief: All the initialisation functions and Vector Table
 */
typedef void (*TABLE_ENTRIES)(void);
extern char __STACK_TOP;
void Reset_Handler(void);
int main(void);

TABLE_ENTRIES VECTOR_TABLE[100] __attribute__((section(".vectors"))) = {
    (TABLE_ENTRIES)&__STACK_TOP,
    Reset_Handler,

};

/**
 * brief: The first function that executes on initialisation
 *
 */
void Reset_Handler(void) {
  extern char __data_start_lma__;
  extern char __data_start_vma__;
  extern char __data_end_vma__;
  extern char __bss_start__;
  extern char __bss_end__;
  char *data_copy_loop, *data_source_loop, *bss_zero_loop;

  /* Copy data from ROM to RAM */
  data_source_loop = &__data_start_lma__;
  for (data_copy_loop = &__data_start_vma__; data_copy_loop < &__data_end_vma__;
       data_copy_loop++) {
    *data_copy_loop = *data_source_loop;
    data_source_loop++;
  }

  for (bss_zero_loop = &__bss_start__; bss_zero_loop < &__bss_end__;
       bss_zero_loop++) {
    *bss_zero_loop = 0;
  }

  main();
  while (1)
    ;
}
