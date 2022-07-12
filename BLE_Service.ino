#include <ArduinoBLE.h>

//Postura Bluetooth Service. 
BLEService posturaService("0cfbadd9-2593-4b4e-9bb6-1a459c706e0b");

//Accelerometer and Gyroscope Characteristics. 
//12 bytes: x, y, z, little endian (TODO: CURRENTLY USES DEVICE ENDIANNESS - should convert in case program run on big endian devices)
union {
  float axes[3];
  byte bytes[12];
} accReading;

union {
  float axes[3];
  byte bytes[12];
} gyroReading;
  
BLECharacteristic accelerometer("0cfbadd9-2593-4b4e-9bb6-1a459c706e0c", BLERead | BLENotify, 12, true);
BLECharacteristic gyroscope("0cfbadd9-2593-4b4e-9bb6-1a459c706e0d", BLERead | BLENotify, 12, true);

//Flex sensor characteristics. Degrees bend, integer. 
BLEByteCharacteristic flexSensor1("0cfbadd9-2593-4b4e-9bb6-1a459c706e0f", BLERead | BLENotify);

//Vibration motor. Actually a boolean (0 for off, 1 for on). 
BLEByteCharacteristic vibration("0cfbadd9-2593-4b4e-9bb6-1a459c706e0e", BLERead | BLEWrite);

void setupBLE() {
    if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Postura");
  BLE.setAdvertisedService(posturaService);

  posturaService.addCharacteristic(vibration);
  
  posturaService.addCharacteristic(accelerometer);
  posturaService.addCharacteristic(gyroscope);

  BLE.addService(posturaService);

  BLE.advertise();

  Serial.println("starting Bluetooth® advertising!");
}
