/*
 * Microphone array record to FIFO pipe example
 * Channel 8 is beamforming output
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// Imports FIFO pipe support (https://en.wikipedia.org/wiki/Named_pipe)
#include <sys/stat.h>
// Linux file control options
#include <fcntl.h>
// System calls
#include <unistd.h>
// Google gflags parser
#include <gflags/gflags.h>
// Input/output stream class to operate on files
#include <fstream>
// Input/output streams and functions
#include <iostream>
// Use strings
#include <string>
// Arrays for math operations
#include <valarray>

// Communicates with MATRIX device
#include "matrix_hal/matrixio_bus.h"
// Interfaces with microphone array
#include "matrix_hal/microphone_array.h"
// Enables using FIR filter with microphone array
#include "matrix_hal/microphone_core.h"

////////////////////////
// INITIAL VARIABLES //
//////////////////////

// Defines variables from user arguments using gflags utility
// (https://gflags.github.io/gflags/)

// Grabs sampling frequency input from user
DEFINE_int32(
    sampling_frequency, 16000,
    "Sampling Frequency");  // Argument example: "--sampling_frequency 48000"
// Grabs gain input from user
DEFINE_int32(gain, -1, "Microphone Gain");  // Argument example: "--gain 5"

int main(int argc, char *agrv[]) {
  // Parse command line flags with gflags utility
  // (https://gflags.github.io/gflags/)
  google::ParseCommandLineFlags(&argc, &agrv, true);

  ////////////////////
  // INITIAL SETUP //
  //////////////////

  // Create MatrixIOBus object for hardware communication
  matrix_hal::MatrixIOBus bus;
  // Initialize bus and exit program if error occurs
  if (!bus.Init()) return false;

  // Set user flags from gflags as variables
  int sampling_rate = FLAGS_sampling_frequency;
  int gain = FLAGS_gain;

  /////////////////
  // MAIN SETUP //
  ///////////////

  // Create MicrophoneArray object
  matrix_hal::MicrophoneArray microphone_array;
  // Set microphone_array to use MatrixIOBus bus
  microphone_array.Setup(&bus);
  // Set microphone sampling rate
  microphone_array.SetSamplingRate(sampling_rate);

  // If gain is positive, set the gain
  if (gain > 0) microphone_array.SetGain(gain);

  // Log gain_ and sampling_frequency_ variables
  microphone_array.ShowConfiguration();

  // Calculate and set up beamforming delays for beamforming
  microphone_array.CalculateDelays(0, 0, 1000,
                                   320 * 1000);  // These are default values

  ///////////////////////
  // FIR FILTER SETUP //
  /////////////////////

  // Create MicrophoneCore object
  matrix_hal::MicrophoneCore microphone_core(microphone_array);
  // Set microphone_core to use MatrixIOBus bus
  microphone_core.Setup(&bus);

  ///////////////////////
  // MICROPHONE INPUT //
  /////////////////////

  // Create a buffer array for microphone input
  int16_t buffer[microphone_array.Channels() + 1]
                [microphone_array.SamplingRate() +
                 microphone_array.NumberOfSamples()];

  // For each channel plus the beamforming channel
  for (uint16_t c = 0; c < microphone_array.Channels() + 1; c++) {
    // Name for the FIFO pipe
    std::string name = "/tmp/matrix_micarray_channel_" + std::to_string(c);

    // Create the FIFO pipe
    if (mkfifo(name.c_str(), 0666) != 0) {
      // Output error if mkfifo fails
      std::cerr << "unable to create " << name << " FIFO." << std::endl;
    }
  }

  // For pipe operations
  int named_pipe_handle;
  // Endless loop
  while (true) {
    // Read microphone stream data
    microphone_array.Read();

    // Bool to flag when beamformed written
    bool beam_write = false;

    // For each microphone
    for (uint16_t c = 0; c < microphone_array.Channels() + 1; c++) {
      // Open pipe
      std::string name = "/tmp/matrix_micarray_channel_" + std::to_string(c);
      named_pipe_handle = open(name.c_str(), O_WRONLY | O_NONBLOCK);

      // For number of samples
      for (uint32_t s = 0; s < microphone_array.NumberOfSamples(); s++) {
        buffer[c][s] = microphone_array.At(s, c);
        // If beamformed data was not sent to buffer, send it
        if (!beam_write) {
          // Send beamformed data to buffer
          buffer[microphone_array.Channels()][s] = microphone_array.Beam(s);
        }
      }
      // Flag that beamforming data is in buffer
      beam_write = true;

      // Write to each pipe
      write(named_pipe_handle, &buffer[c][0],
            sizeof(int16_t) * microphone_array.NumberOfSamples());
      // Close pipe after write
      close(named_pipe_handle);
    }
  }

  return 0;
}