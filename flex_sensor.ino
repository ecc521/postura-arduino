const int flexSensorPin = A3;

int getFlexSensor1() {
    int flexSensorReading = analogRead(flexSensorPin); 
    int flexDegrees = map(flexSensorReading, 670, 787, 90, 180);
    return flexDegrees;
}
