#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#define mainDELAY_LOOP_COUNT 10000

void vTask1(void *pvParameters) {

  UNUSED(pvParameters);
  /* ulCount is declared volatile to ensure it is not optimized out. */
  volatile unsigned long ulCount;
  for (;;) {
    /* Print out the name of the current task task. */
    printf("Task 1 is running");
    /* Delay for a period. */
    for (ulCount = 0; ulCount < mainDELAY_LOOP_COUNT; ulCount++) {
      /*
       * This loop is just a very crude delay implementation. There is
       * nothing to do in here. Later examples will replace this crude
       *loop with a proper delay / sleep function. */
    }
  }
}


void vTask2(void *pvParameters) {

  UNUSED(pvParameters);
  /* ulCount is declared volatile to ensure it is not optimized out. */
  volatile unsigned long ulCount;
  for (;;) {
    /* Print out the name of the current task task. */
    printf("Task 2 is running");
    /* Delay for a period. */
    for (ulCount = 0; ulCount < mainDELAY_LOOP_COUNT; ulCount++) {
      /*
       * This loop is just a very crude delay implementation. There is
       * nothing to do in here. Later examples will replace this crude
       *loop with a proper delay / sleep function. */
    }
  }
}

int main(void) {
  /*
   * Variables declared here may no longer exist after starting the FreeRTOS
   * scheduler. Do not attempt to access variables declared on the stack used
   * by main() from tasks.
   */
  /*
   * Create one of the two tasks. Note that a real application should check
   * the return value of the xTaskCreate() call to ensure the task was
   * created successfully.
   */
  xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
  xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
  /* Start the created tasks running. */
  vTaskStartScheduler();
  /* Execution will only reach here if there was insufficient heap to
         start the scheduler. */
  for (;;)
    ;
  return 0;
}
