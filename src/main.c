#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
int main(void) { /* Start the created tasks running. */
  vTaskStartScheduler();
  /* Execution will only reach here if there was insufficient heap to
         start the scheduler. */
  for (;;)
    ;
  return 0;
}
