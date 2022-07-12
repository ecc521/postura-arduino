#include <Arduino_LSM9DS1.h>

void setupIMU() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

//Replaces axes[0] with x, axes[1] with y, axes[2] with z
void getAccelerometer(float axes[3]) {
  if (IMU.accelerationAvailable()) {
    //Acceleration in G's
    IMU.readAcceleration(axes[0], axes[1], axes[2]);
  }
}

//Replaces axes[0] with x, axes[1] with y, axes[2] with z
void getGyroscope(float axes[3]) {
    if (IMU.gyroscopeAvailable()) {
    //Gyroscope in degrees/second
    IMU.readGyroscope(axes[0], axes[1], axes[2]);
  }
}

//Replaces axes[0] with x, axes[1] with y, axes[2] with z
void getMagnetometer(float axes[3]) {
  if (IMU.magneticFieldAvailable()) {
    //Magnetic Field in uT
    IMU.readMagneticField(axes[0], axes[1], axes[2]);
  }
}

//Replaces first subarray with accelerometer (x, y, z), second with gyroscope (x, y, z) and third with magnetometer (x, y, z)
void getIMUReadings(float readings[3][3]) {
  getAccelerometer(readings[0]);
  getGyroscope(readings[1]);
  getMagnetometer(readings[2]);
}
