#include <ArduinoBLE.h>

const int vibrationMotor = 3;


//Postura Bluetooth Service. 
BLEService posturaService("0cfbadd9-2593-4b4e-9bb6-1a459c706000");

//Accelerometer and Gyroscope Characteristics. 
//12 bytes: x, y, z, little endian (TODO: CURRENTLY USES DEVICE ENDIANNESS - should convert in case program run on big endian devices)
union {
  float axes[3];
  byte bytes[12];
} accReading1;

union {
  float axes[3];
  byte bytes[12];
} accReading2;

union {
  float axes[3];
  byte bytes[12];
} gyroReading1;
  
BLECharacteristic accelerometer1("0cfbadd9-2593-4b4e-9bb6-1a459c706010", BLERead | BLENotify, 12, true);
BLECharacteristic accelerometer2("0cfbadd9-2593-4b4e-9bb6-1a459c706011", BLERead | BLENotify, 12, true);
BLECharacteristic gyroscope1("0cfbadd9-2593-4b4e-9bb6-1a459c706020", BLERead | BLENotify, 12, true);

//Flex sensor characteristics. Degrees bend, integer. 
BLEByteCharacteristic flexSensor1("0cfbadd9-2593-4b4e-9bb6-1a459c706030", BLERead | BLENotify);

//Vibration motor. Off is 0, anything else is on. 
BLEByteCharacteristic vibration("0cfbadd9-2593-4b4e-9bb6-1a459c706040", BLERead | BLEWrite);

void setupBLE() {
    if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Postura");
  BLE.setAdvertisedService(posturaService);
  
  posturaService.addCharacteristic(accelerometer1);
  posturaService.addCharacteristic(accelerometer2);
  posturaService.addCharacteristic(gyroscope1);

  posturaService.addCharacteristic(flexSensor1);

  posturaService.addCharacteristic(vibration);

  BLE.addService(posturaService);

  BLE.advertise();

  Serial.println("starting Bluetooth® advertising!");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

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

  getAccelerometer(accReading1.axes);
  getGyroscope(gyroReading1.axes);
  getExternalAccelerometer(accReading2.axes);

  accelerometer1.writeValue(accReading1.bytes, 12);
  gyroscope1.writeValue(gyroReading1.bytes, 12);
  accelerometer2.writeValue(accReading2.bytes, 12);

  flexSensor1.writeValue(getFlexSensor1());
}
