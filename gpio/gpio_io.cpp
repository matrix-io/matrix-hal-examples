/*
 * GPIO servo output example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// System calls
#include <unistd.h>
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

// Holds desired GPIO pin for output [0-15]
uint16_t pin_out;
// Holds desired output state
uint16_t pin_out_state;
// Holds desired GPIO pin for input [0-15]
uint16_t pin_in;

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
  std::cout << "Select Pin [0-15] For Output: ";
  // Log user input
  std::cin >> pin_out;
  // Prompt user for GPIO state
  std::cout << "Pin Output State [0-1] : ";
  // Log user input
  std::cin >> pin_out_state;
  // Prompt user for GPIO pin
  std::cout << "Select Pin [0-15] For Input: ";
  // Log user input
  std::cin >> pin_in;

  // Set pin_out mode to output
  gpio.SetMode(pin_out, GPIOOutputMode);

  // Set pin_in mode to input
  gpio.SetMode(pin_in, GPIOInputMode);

  // Set pin_out to output pin_out_state
  gpio.SetGPIOValue(pin_out, pin_out_state);

  // Endless loop
  while (true) {
    // Get state of pin_in
    uint16_t pin_in_state = gpio.GetGPIOValue(pin_in);
    // Clear console
    std::system("clear");
    // Output pin_out info to console
    std::cout << "[ Output Pin : " << pin_out << " ]"
              << " [ Output State : " << pin_out_state << " ]" << std::endl;
    // Output pin_in info to console
    std::cout << "[ Input Pin : " << pin_in << " ]"
              << " [ Input State : " << pin_in_state << " ]" << std::endl;
    // Sleep for 10000 microseconds
    usleep(10000);
  }

  return 0;
}
