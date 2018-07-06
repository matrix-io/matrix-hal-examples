/*
 * Microphone array record to file example
 * Channel 8 is beamforming output
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

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
// Grabs duration input from user
DEFINE_int32(duration, 5,
             "Interrupt after N seconds");  // Argument example: "--duration 10"
// Grabs gain input from user
DEFINE_int32(gain, -1, "Microphone Gain");  // Argument example: "--gain 5"

int main(int argc, char *agrv[]) {
  ////////////////////
  // INITIAL SETUP //
  //////////////////

  // Parse command line flags with gflags utility
  // (https://gflags.github.io/gflags/)
  google::ParseCommandLineFlags(&argc, &agrv, true);

  // Create MatrixIOBus object for hardware communication
  matrix_hal::MatrixIOBus bus;
  // Initialize bus and exit program if error occurs
  if (!bus.Init()) return false;

  // Set user flags from gflags as variables
  int sampling_rate = FLAGS_sampling_frequency;
  int seconds_to_record = FLAGS_duration;
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
  // Log recording duration variable
  std::cout << "Duration : " << seconds_to_record << "s" << std::endl;

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

  // Create an array of streams to write microphone data to files
  std::ofstream os[microphone_array.Channels() + 1];

  // For each microphone channel (+1 for beamforming), make a file and open it
  for (uint16_t c = 0; c < microphone_array.Channels() + 1; c++) {
    // Set filename for microphone output
    std::string filename = "mic_" +
                           std::to_string(microphone_array.SamplingRate()) +
                           "_s16le_channel_" + std::to_string(c) + ".raw";
    // Create and open file
    os[c].open(filename, std::ofstream::binary);
  }

  // Counter variable for tracking recording time
  uint32_t samples = 0;
  // For recording duration
  for (int s = 0; s < seconds_to_record; s++) {
    // Endless loop
    while (true) {
      // Read microphone stream data
      microphone_array.Read();

      // For number of samples
      for (uint32_t s = 0; s < microphone_array.NumberOfSamples(); s++) {
        // For each microphone
        for (uint16_t c = 0; c < microphone_array.Channels(); c++) {
          // Send microphone data to buffer
          buffer[c][samples] = microphone_array.At(s, c);
        }
        // Writes beamformed microphone data into buffer
        buffer[microphone_array.Channels()][samples] = microphone_array.Beam(s);
        // Increment samples for buffer write
        samples++;
      }

      // Once number of samples is >= sampling rate
      if (samples >= microphone_array.SamplingRate()) {
        // For each microphone channel
        for (uint16_t c = 0; c < microphone_array.Channels() + 1; c++) {
          // Write to recording file
          os[c].write((const char *)buffer[c], samples * sizeof(int16_t));
        }
        // Set samples to zero for loop to fill buffer
        samples = 0;
        break;
      }
    }
  }

  return 0;
}
