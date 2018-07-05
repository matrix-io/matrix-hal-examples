/*
 * Everloop yellow/purple example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// System calls
#include <unistd.h>
// Input/output streams and functions
#include <iostream>

// Interfaces with Everloop
#include "matrix_hal/everloop.h"
// Holds data for Everloop
#include "matrix_hal/everloop_image.h"
// Communicates with MATRIX device
#include "matrix_hal/matrixio_bus.h"

int main() {
  ////////////////////
  // INITIAL SETUP //
  //////////////////

  // Create MatrixIOBus object for hardware communication
  matrix_hal::MatrixIOBus bus;
  // Initialize bus and exit program if error occurs
  if (!bus.Init()) return false;

  /////////////////
  // MAIN SETUP //
  ///////////////

  // Holds the number of LEDs on MATRIX device
  int ledCount = bus.MatrixLeds();
  // Create EverloopImage object, with size of ledCount
  matrix_hal::EverloopImage everloop_image(ledCount);
  // Create Everloop object
  matrix_hal::Everloop everloop;
  // Set everloop to use MatrixIOBus bus
  everloop.Setup(&bus);

  // For each led in everloop_image.leds, set led value
  for (int i = 0; i < everloop_image.leds.size(); i++) {
    // When remainder is zero set led to purple
    if (i % 2 == 0) {
      // Blending blue and red to make purple
      everloop_image.leds[i].blue = 40;
      everloop_image.leds[i].red = 40;
    }
    // Else set led to yellow
    else {
      // Blending green and red to make yellow
      everloop_image.leds[i].green = 40;
      everloop_image.leds[i].red = 60;
    }
  }

  // Updates the Everloop on the MATRIX device
  everloop.Write(&everloop_image);

  // Output everloop status to console
  std::cout << "Everloop set to yellow and purple for 10 seconds." << std::endl;

  for (int i = 0; i <= 10; i++) {
    // Output time remaining to console
    std::cout << "Time remaining (s) : " << 10 - i << std::endl;
    // Sleep for 1 second
    usleep(1000000);
  }

  // For each led in everloop_image.leds, set led value to 0
  for (matrix_hal::LedValue &led : everloop_image.leds) {
    // Turn off Everloop
    led.red = 0;
    led.green = 0;
    led.blue = 0;
    led.white = 0;
  }

  // Updates the Everloop on the MATRIX device
  everloop.Write(&everloop_image);

  return 0;
}
