/*
  Asynchrony.h - Library that allows you to schedule tasks in the future without blocking your loop.
  Created by littleBitsman, December 8, 2023.
  Licensed under the GNU General Public License v3.0.
*/
// Asynchrony.cpp
#include "Asynchrony.h"

// Initialize the array of scheduled tasks
Asynchrony::ScheduledTask Asynchrony::scheduledTasks[20];

/* Method to schedule a function with a time delay without blocking your loop.
 * In order for this to work, you must call `Asynchrony::runEventLoop` in your loop function to update
 * the event loop.
 * DO NOT pass a function that yields using `delay()`. It will still stop execution.
 */
void Asynchrony::schedule(unsigned long delay, void (*func)(...))
{
  unsigned long executionTime = millis() + delay;

  // Find an empty slot in the array to store the task
  for (int i = 0; i < sizeof(scheduledTasks) / sizeof(scheduledTasks[0]); ++i)
  {
    if (scheduledTasks[i].func == nullptr)
    {
      scheduledTasks[i] = {func, executionTime};
      break;
    }
  }
}

// Run the event loop and execute scheduled tasks.
void Asynchrony::runEventLoop()
{
  unsigned long currentTime = millis();

  // Iterate through the array and execute tasks if their time has come
  for (int i = 0; i < sizeof(scheduledTasks) / sizeof(scheduledTasks[0]); ++i)
  {
    if (scheduledTasks[i].func != nullptr && currentTime >= scheduledTasks[i].executionTime)
    {
      scheduledTasks[i].func(millis());
      // Clear the task after execution
      scheduledTasks[i] = {nullptr, 0};
    }
  }
}
