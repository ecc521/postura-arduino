#include <ArduinoBLE.h>
#include <vector>

const int vibrationMotor = 3;

//DataItem - Sensor sample groups. 
struct DataItem {
  //Accelerometer and gyroscope characteristics are 12 bytes: x, y, z, little endian 
  //TODO: PROGRAM CURRENTLY USES DEVICE ENDIANNESS - should convert in case program run on big endian devices
  union {
    float axes[3];
    byte bytes[12];
  } acc1;
  
  union {
    float axes[3];
    byte bytes[12];
  } gyro1;
  
  union {
    float axes[3];
    byte bytes[12];
  } acc2;

  //Flex sensor characteristics. Degrees bend, integer. 
  byte flex1;
};


DataItem getLatestReading() {
  DataItem reading;
  
  getAccelerometer(reading.acc1.axes);
  getGyroscope(reading.gyro1.axes);
  getExternalAccelerometer(reading.acc2.axes);
  reading.flex1 = getFlexSensor1();
  return reading;
}

BLEService posturaService("0cfbadd9-2593-4b4e-9bb6-1a459c706000");
BLECharacteristic accelerometer1("0cfbadd9-2593-4b4e-9bb6-1a459c706010", BLERead | BLENotify, 12, true);
BLECharacteristic accelerometer2("0cfbadd9-2593-4b4e-9bb6-1a459c706011", BLERead | BLENotify, 12, true);
BLECharacteristic gyroscope1("0cfbadd9-2593-4b4e-9bb6-1a459c706020", BLERead | BLENotify, 12, true);
BLEByteCharacteristic flexSensor1("0cfbadd9-2593-4b4e-9bb6-1a459c706030", BLERead | BLENotify);

//Vibration motor. Off is 0, anything else is on. 
BLEByteCharacteristic vibration("0cfbadd9-2593-4b4e-9bb6-1a459c706040", BLERead | BLEWrite);


void updateCharacteristics(DataItem reading) {
  accelerometer1.writeValue(reading.acc1.bytes, 12);
  gyroscope1.writeValue(reading.gyro1.bytes, 12);
  accelerometer2.writeValue(reading.acc2.bytes, 12);
  flexSensor1.writeValue(reading.flex1);
}


void setupBLE() {
  if (!BLE.begin()) {while (1);}

  BLE.setLocalName("Postura");
  BLE.setAdvertisedService(posturaService);
  
  posturaService.addCharacteristic(accelerometer1);
  posturaService.addCharacteristic(accelerometer2);
  posturaService.addCharacteristic(gyroscope1);
  posturaService.addCharacteristic(flexSensor1);

  posturaService.addCharacteristic(vibration);

  BLE.addService(posturaService);
  BLE.advertise();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(vibrationMotor, OUTPUT);

  setupIMU();
  setupBLE();
  
  digitalWrite(LED_BUILTIN, HIGH); //Everything started successfully. 
}


void loop() {
  BLE.poll();

  if (vibration.value() == 0) {
    //Turn vibration off. 
    digitalWrite(vibrationMotor, LOW);
  }
  else {
    //Turn vibration on. 
    digitalWrite(vibrationMotor, HIGH);
  }
  
  DataItem latestReading = getLatestReading();
  updateCharacteristics(latestReading);
}
