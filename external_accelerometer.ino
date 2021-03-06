int xpin = A0;                
int ypin = A1;                
int zpin = A2; 

void getExternalAccelerometer(float axes[3]) {
  int xReading = analogRead(xpin);
  int yReading = analogRead(ypin);
  int zReading = analogRead(zpin);

  //Map the calibrated analog values. 
  int x = map(xReading, 411, 610, -100, 100);
  int y = map(yReading, 413, 615, -100, 100);
  int z = map(zReading, 422, 574, -100, 100);

  //Convert to g's
  float xg = (float)x/(-100.00);
  float yg = (float)y/(-100.00);
  float zg = (float)z/(100.00);

  axes[0] = xg;
  axes[1] = yg;
  axes[2] = zg;
}
