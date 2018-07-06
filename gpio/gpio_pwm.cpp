/*
 * GPIO PWM output example
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
  // Prompt user for PWM frequency
  std::cout << "Select Frequency (in Hz) : ";
  // Log user input
  std::cin >> frequency;
  // Prompt user for PWM duty percentage
  std::cout << "Select Duty Percentage : ";
  // Log user input
  std::cin >> percentage;

  // Set pin mode to output
  gpio.SetMode(pin, GPIOOutputMode);
  // Set pin function to PWM
  gpio.SetFunction(pin, PWMFunction);

  // If setting PWM returns an error, log it
  // SetPWM function carries out PWM logic and outputs PWM signal
  if (!gpio.SetPWM(frequency, percentage, pin))
    // Output error to console
    std::cerr << "ERROR: invalid input" << std::endl;
  else
    // Else output GPIO PWM info to console
    std::cout << "[ Pin : " << pin << " ] [ Frequency : " << frequency
              << " ] [ Duty Percentage : " << percentage << " ]" << std::endl;

  return 0;
}