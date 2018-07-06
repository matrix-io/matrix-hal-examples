/*
 * GPIO servo output example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// Input/output streams and functions
#include <iostream>

// Interfaces with GPIO
#include "matrix_hal/gpio_control.h"
// Communicates with MATRIX device
#include "matrix_hal/matrixio_bus.h"

////////////////////////
// INITIAL VARIABLES //
//////////////////////

// GPIOOutputMode is 1
const uint16_t GPIOOutputMode = 1;
// GPIOInputMode is 0
const uint16_t GPIOInputMode = 0;

// PWMFunction is 1
const uint16_t PWMFunction = 1;

// Holds desired PWM frequency
float frequency;
// Holds desired PWM duty percentage
float percentage;
// Holds desired GPIO pin [0-15]
uint16_t pin;
// Holds desired servo angle
float angle;
// Holds servo minimum pulse length (for calibration)
float min_pulse_ms;

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

  // Create GPIOControl object
  matrix_hal::GPIOControl gpio;
  // Set gpio to use MatrixIOBus bus
  gpio.Setup(&bus);

  // Prompt user for GPIO pin
  std::cout << "Select Pin [0-15] : ";
  // Log user input
  std::cin >> pin;
  // Prompt user for servo angle
  std::cout << "Servo Angle : ";
  // Log user input
  std::cin >> angle;
  // Prompt user for servo minimum pulse length in ms (for calibration)
  std::cout << "Servo Min Pulse (ms) : ";
  // Log user input
  std::cin >> min_pulse_ms;

  // Set pin mode to output
  gpio.SetMode(pin, GPIOOutputMode);
  // Set pin function to PWM
  gpio.SetFunction(pin, PWMFunction);

  // If setting servo angle returns an error, log it
  // SetServoAngle function sets a servo angle based on the min_pulse_ms
  if (!gpio.SetServoAngle(angle, min_pulse_ms, pin))
    // Output error to console
    std::cerr << "ERROR: invalid input" << std::endl;
  else
    // Else output servo control info to console
    std::cout << "[ Pin : " << pin << " ]"
              << " [ Servo Angle : " << angle
              << " ] [ Servo Min Pulse (ms) : " << min_pulse_ms << " ] "
              << std::endl;

  return 0;
}