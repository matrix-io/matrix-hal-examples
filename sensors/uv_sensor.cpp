/*
 * UV sensor example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// System calls
#include <unistd.h>
// Input/output streams and functions
#include <iostream>

// Interfaces with UV sensor
#include "matrix_hal/uv_sensor.h"
// Holds data from UV sensor
#include "matrix_hal/uv_data.h"
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

  // Create UVData object
  matrix_hal::UVData uv_data;
  // Create UVSensor object
  matrix_hal::UVSensor uv_sensor;
  // Set uv_sensor to use MatrixIOBus bus
  uv_sensor.Setup(&bus);

  // Endless loop
  while (true) {
    // Overwrites UVData object with new data
    uv_sensor.Read(&uv_data);
    // UV output is represented in UV Index
    float UV = uv_data.uv;
    // Clear console
    std::system("clear");
    // Output sensor data to console
    std::cout << " [ UV Sensor Output ]" << std::endl;
    std::cout << " [ UV : " << UV << " ]" << std::endl;

    // Sleep for 20000 microseconds
    usleep(20000);
  }

  return 0;
}