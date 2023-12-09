/*
  Asynchrony.h - Library that allows you to schedule tasks in the future without blocking your loop.
  Created by littleBitsman, December 8, 2023.
  Licensed under the GNU General Public License v3.0.
*/
#ifndef Asynchrony_h
#define Asynchrony_h

#include <Arduino.h>

class Asynchrony
{
private:
  // Structure to store scheduled tasks
  struct ScheduledTask
  {
    void (*func)(...); // Function pointer
    unsigned long executionTime;
  };

  // Array to store scheduled tasks
  static ScheduledTask scheduledTasks[20]; // Adjust the size as needed

public:
  /* Method to schedule a function with a time delay without blocking your loop.
   * In order for this to work, you must call `Asynchrony::runEventLoop` in your loop function to update
   * the event loop.
   */
  static void schedule(unsigned long delay, void (*func)(...));

  // Run the event loop and execute scheduled tasks.
  static void runEventLoop();
};

#endif
