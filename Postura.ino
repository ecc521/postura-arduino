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
  accelerometer.writeValue(accReading.bytes, 12);

  getGyroscope(gyroReading.axes);
  gyroscope.writeValue(gyroReading.bytes, 12);

  flexSensor1.writeValue();
}
