/*
 * Humidity sensor example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// System calls
#include <unistd.h>
// Input/output streams and functions
#include <iostream>

// Interfaces with humidity sensor
#include "matrix_hal/humidity_sensor.h"
// Holds data from humidity sensor
#include "matrix_hal/humidity_data.h"
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

  // Create HumidityData object
  matrix_hal::HumidityData humidity_data;
  // Create HumiditySensor object
  matrix_hal::HumiditySensor humidity_sensor;
  // Set humidity_sensor to use MatrixIOBus bus
  humidity_sensor.Setup(&bus);

  // Endless loop
  while (true) {
    // Overwrites humidity_data with new data from humidity sensor
    humidity_sensor.Read(&humidity_data);
    // Humidity output is represented in %
    float humidity = humidity_data.humidity;
    // Temperature output is represented in °C
    float temperature = humidity_data.temperature;
    // Clear console
    std::system("clear");
    // Output sensor data to console
    std::cout << " [ Humidity Sensor Output ]" << std::endl;
    std::cout << " [ Humidity (%) : " << humidity
              << " ] [ Temperature (°C) : " << temperature << "]" << std::endl;

    // Sleep for 20000 microseconds
    usleep(20000);
  }

  return 0;
}