/*
  Basic.ino

  A basic example of how to use Asynchrony.

  No circuit is required.

  Created 9 December, 2023
  By littleBitsman
  Modified 9 December, 2023
  By littleBitsman

  https://github.com/littleBitsman/Asynchrony
*/

#include <Asynchrony.h>

void exampleTask() {
  Serial.println(millis());
}

void setup() {
  // Begin serial logging.
  Serial.begin(9600);

  // Schedules exampleTask to be ran in 1000 milliseconds, or 1 second.
  Asynchrony::schedule(1000, exampleTask);
}

void loop() {
  // Runs the event loop, which checks all the functions that need to be ran.
  Asynchrony::runEventLoop();
}