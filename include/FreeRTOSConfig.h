
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* In most cases, configCPU_CLOCK_HZ must be set to the frequency of the clock
 * that drives the peripheral used to generate the kernels periodic tick
 * interrupt. The default value is set to 20MHz and matches the QEMU demo
 * settings.  Your application will certainly need a different value so set this
 * correctly. This is very often, but not always, equal to the main system clock
 * frequency. */
#define configCPU_CLOCK_HZ ((unsigned long)16000000)

/* configTICK_RATE_HZ sets frequency of the tick interrupt in Hz, normally
 * calculated from the configCPU_CLOCK_HZ value. */
#define configTICK_RATE_HZ 100

/* Sets the total size of the FreeRTOS heap, in bytes, when heap_1.c, heap_2.c
 * or heap_4.c are included in the build.  This value is defaulted to 4096 bytes
 * but it must be tailored to each application.  Note the heap will appear in
 * the .bss section.  See https://www.freertos.org/a00111.html. */
#define configTOTAL_HEAP_SIZE 4096

/* Time is measured in 'ticks' - which is the number of times the tick interrupt
 * has executed since the RTOS kernel was started.
 * The tick count is held in a variable of type TickType_t.
 *
 * configTICK_TYPE_WIDTH_IN_BITS controls the type (and therefore bit-width) of
 * TickType_t:
 *
 * Defining configTICK_TYPE_WIDTH_IN_BITS as TICK_TYPE_WIDTH_16_BITS causes
 * TickType_t to be defined (typedef'ed) as an unsigned 16-bit type.
 *
 * Defining configTICK_TYPE_WIDTH_IN_BITS as TICK_TYPE_WIDTH_32_BITS causes
 * TickType_t to be defined (typedef'ed) as an unsigned 32-bit type.
 *
 * Defining configTICK_TYPE_WIDTH_IN_BITS as TICK_TYPE_WIDTH_64_BITS causes
 * TickType_t to be defined (typedef'ed) as an unsigned 64-bit type. */
#define configTICK_TYPE_WIDTH_IN_BITS TICK_TYPE_WIDTH_32_BITS

/* configMINIMAL_STACK_SIZE defines the size of the stack used by the Idle task
 * (in words, not in bytes!).  The kernel does not use this constant for any
 * other purpose.  Demo applications use the constant to make the demos somewhat
 * portable across hardware architectures. */
#define configMINIMAL_STACK_SIZE 128

/* configMAX_PRIORITIES Sets the number of available task priorities.  Tasks can
 * be assigned priorities of 0 to (configMAX_PRIORITIES - 1).  Zero is the
 * lowest priority. */
#define configMAX_PRIORITIES 5

/* Set configUSE_PREEMPTION to 1 to use pre-emptive scheduling.  Set
 * configUSE_PREEMPTION to 0 to use co-operative scheduling.
 * See https://www.freertos.org/single-core-amp-smp-rtos-scheduling.html. */
#define configUSE_PREEMPTION 1

/* Set the following configUSE_* constants to 1 to include the named hook
 * functionality in the build.  Set to 0 to exclude the hook functionality from
 * the build.  The application writer is responsible for providing the hook
 * function for any set to 1.  See https://www.freertos.org/a00016.html. */
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0

/* configMAX_SYSCALL_INTERRUPT_PRIORITY sets the interrupt priority above which
 * FreeRTOS API calls must not be made.  Interrupts above this priority are
 * never disabled, so never delayed by RTOS activity.  The default value is set
 * to the highest interrupt priority (0).  Not supported by all FreeRTOS ports.
 * See https://www.freertos.org/RTOS-Cortex-M3-M4.html for information specific
 * to ARM Cortex-M devices. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 0


/******************************************************************************/
/* Debugging assistance. ******************************************************/
/******************************************************************************/

/* configASSERT() has the same semantics as the standard C assert().  It can
 * either be defined to take an action when the assertion fails, or not defined
 * at all (i.e. comment out or delete the definitions) to completely remove
 * assertions.  configASSERT() can be defined to anything you want, for example
 * you can call a function if an assert fails that passes the filename and line
 * number of the failing assert (for example, "vAssertCalled( __FILE__, __LINE__
 * )" or it can simple disable interrupts and sit in a loop to halt all
 * execution on the failing line for viewing in a debugger. */

/* *INDENT-OFF* */
#define configASSERT(x)                                                        \
  if ((x) == 0) {                                                              \
    taskDISABLE_INTERRUPTS();                                                  \
    for (;;)                                                                   \
      ;                                                                        \
  }
/* *INDENT-ON* */



#endif /* FREERTOS_CONFIG_H */
