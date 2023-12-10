#include "Asynchrony.h"

/*
 * Asynchrony - An asynchronous scheduling library for Arduino.
 * Created December 8, 2023.
 * Modified December 9, 2023.
 * Copyright (C) 2023 littleBitsman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// Initialize the array of scheduled tasks
Asynchrony::ScheduledTask Asynchrony::scheduledTasks[20];

/* Method to schedule a function with a time delay without blocking your loop.
 * In order for this to work, you must call `Asynchrony::runEventLoop` in your loop function to update
 * the event loop.
 * DO NOT pass a function that yields using `delay()`. It will still stop execution.
 */
int Asynchrony::schedule(unsigned long delay, void (*func)(...))
{
  unsigned long executeAt = millis() + delay;

  for (int i = 0; i < sizeof(scheduledTasks) / sizeof(scheduledTasks[0]); ++i)
  {
    if (scheduledTasks[i].func == nullptr)
    {
      scheduledTasks[i] = {func, executeAt};
      break;
    }
  }

  return executeAt;
}

// Run the event loop and execute scheduled tasks.
void Asynchrony::runEventLoop()
{
  unsigned long currentTime = millis();

  for (int i = 0; i < sizeof(scheduledTasks) / sizeof(scheduledTasks[0]); i++)
  {
    if (scheduledTasks[i].func != nullptr && currentTime >= scheduledTasks[i].executeAt)
    {
      scheduledTasks[i].func(millis());

      scheduledTasks[i] = {nullptr, 0};
    }
  }
}
