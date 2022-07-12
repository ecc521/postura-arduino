const int vibrationMotor = 3;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(ledPin, OUTPUT);
  pinMode(vibrationMotor, OUTPUT);

  setupIMU();
  setupBLE();
  
  digitalWrite(LED_BUILTIN, HIGH); //Everything started successfully. 
}



void loop() {
  BLE.poll();

  if (vibration.value()) {
    //Turn vibration on. 
    digitalWrite(vibrationMotor, HIGH);
  }
  else {
    //Turn vibration off. 
    digitalWrite(vibrationMotor, LOW);
  }

  getAccelerometer(accReading.axes);
  accelerometer1.writeValue(accReading1.bytes, 12);

  getGyroscope(gyroReading.axes);
  gyroscope1.writeValue(gyroReading1.bytes, 12);

  getExternalAccelerometer(accReading2.axes);
  accelerometer2.writeValue(accReading2.bytes, 12);

  flexSensor1.writeValue(getFlexSensor1());
}
