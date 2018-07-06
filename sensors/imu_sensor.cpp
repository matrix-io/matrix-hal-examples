/*
 * IMU sensor example
 */

/////////////////////////
// INCLUDE STATEMENTS //
///////////////////////

// System calls
#include <unistd.h>
// Input/output streams and functions
#include <iostream>

// Interfaces with IMU sensor
#include "matrix_hal/imu_sensor.h"
// Holds data from IMU sensor
#include "matrix_hal/imu_data.h"
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

  // Create IMUData object
  matrix_hal::IMUData imu_data;
  // Create IMUSensor object
  matrix_hal::IMUSensor imu_sensor;
  // Set imu_sensor to use MatrixIOBus bus
  imu_sensor.Setup(&bus);

  // Endless loop
  while (true) {
    // Overwrites imu_data with new data from IMU sensor
    imu_sensor.Read(&imu_data);
    // Accelerometer Output
    float accel_X = imu_data.accel_x;
    float accel_Y = imu_data.accel_y;
    float accel_Z = imu_data.accel_z;
    // Gyroscope Output
    float gyro_X = imu_data.gyro_x;
    float gyro_Y = imu_data.gyro_y;
    float gyro_Z = imu_data.gyro_z;
    // Yaw, Pitch, Roll Output
    float yaw = imu_data.yaw;
    float pitch = imu_data.pitch;
    float roll = imu_data.roll;
    // Magnetometer Output
    float mag_X = imu_data.mag_x;
    float mag_Y = imu_data.mag_y;
    float mag_Z = imu_data.mag_z;  // Z-axis points upward
    // Clear console
    std::system("clear");
    // Output sensor data to console
    std::cout << " [ IMU Sensor Output ]" << std::endl;
    std::cout << " [ Acceleration In X : " << accel_X
              << " ] [ Acceleration In Y : " << accel_Y
              << " ] [ Acceleration In Z : " << accel_Z << " ]" << std::endl;
    std::cout << " [ Gyroscope In X : " << gyro_X
              << " ] [ Gyroscope In Y : " << gyro_X
              << " ] [ Gyroscope In Z : " << gyro_Z << " ]" << std::endl;
    std::cout << " [ Yaw : " << yaw << " ] [ Pitch : " << pitch
              << " ] [ Roll : " << roll << " ]" << std::endl;
    std::cout << " [ Magnetometer in X : " << mag_X
              << " ] [ Magnetometer in Y : " << mag_Y
              << " ] [ Magnetometer in Z : " << mag_Z << " ]" << std::endl;

    // Sleep for 20000 microseconds
    usleep(20000);
  }

  return 0;
}