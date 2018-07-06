/*
 * Pressure sensor example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// System calls
#include <unistd.h>
// Input/output streams and functions
#include <iostream>

// Interfaces with pressure sensor
#include "matrix_hal/pressure_sensor.h"
// Holds data from pressure sensor
#include "matrix_hal/pressure_data.h"
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

  // Create PressureData object
  matrix_hal::PressureData pressure_data;
  // Create PressureSensor object
  matrix_hal::PressureSensor pressure_sensor;
  // Set pressure_sensor to use MatrixIOBus bus
  pressure_sensor.Setup(&bus);

  // Endless loop
  while (true) {
    // Overwrites pressure_data with new data from pressure sensor
    pressure_sensor.Read(&pressure_data);
    // Altitude output is represented in meters
    float altitude = pressure_data.altitude;
    // Pressure output is represented in kPa
    float pressure = pressure_data.pressure;
    // Temperature output is represented in °C
    float temperature = pressure_data.temperature;
    // Clear console
    std::system("clear");
    // Output sensor data to console
    std::cout << " [ Pressure Sensor Output ]" << std::endl;
    std::cout << " [ Altitude (m) : " << altitude
              << " ] [ Pressure (kPa) : " << pressure
              << " ] [ Temperature (°C) : " << temperature << " ]" << std::endl;

    // Sleep for 20000 microseconds
    usleep(20000);
  }

  return 0;
}