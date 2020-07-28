#include <Wire.h>

int16_t accelX, accelY, accelZ;
double gForceX, gForceY, gForceZ;
double AccAngleX, AccAngleY, AccAngleZ;
double gForceErrorX=0, gForceErrorY=0;

int16_t gyroX, gyroY, gyroZ;
double rotX, rotY, rotZ;
double GyroAngleX, GyroAngleY, GyroAngleZ;
double GyroErrorX=0, GyroErrorY=0, GyroErrorZ=0;

double Pitch_Angle, Roll_Angle, Yaw_Angle;

double PreviousTime, CurrentTime = 0, ElapsedTime;

int c;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  GyroAngleX = 0;
  GyroAngleY = 0;
  GyroAngleZ = 0;
  CurrentTime = 0;
  setupMPU();
  calculate_IMU_error();
}

void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
  CalculateOrientation();
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = ((int16_t)Wire.read()<<8|Wire.read()); //Store first two bytes into accelX
  accelY = ((int16_t)Wire.read()<<8|Wire.read()); //Store middle two bytes into accelY
  accelZ = ((int16_t)Wire.read()<<8|Wire.read()); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = ((double)(accelX / 16384.0));
  gForceY = ((double)(accelY / 16384.0)); 
  gForceZ = ((double)(accelZ / 16384.0));
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = ((int16_t)Wire.read()<<8|Wire.read()); //Store first two bytes into accelX
  gyroY = ((int16_t)Wire.read()<<8|Wire.read()); //Store middle two bytes into accelY
  gyroZ = ((int16_t)Wire.read()<<8|Wire.read()); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = ((double)((gyroX )/ 131.0));
  rotY = ((double)(gyroY / 131.0)); 
  rotZ = ((double)(gyroZ / 131.0));
}

void CalculateOrientation(){
  AccAngleX = atan(gForceX/(sqrt((gForceY*gForceY)+(gForceZ*gForceZ))))*(180/PI) - gForceErrorX;     // Calculating acceleration Angles
  AccAngleY = atan(((-1)*gForceX)/(sqrt((gForceY*gForceY)+(gForceZ*gForceZ))))*(180/PI) - gForceErrorY;
  
  PreviousTime = CurrentTime;   // Calculating the Execution time for one loop
  CurrentTime = ((double)(millis()));
  ElapsedTime = (CurrentTime - PreviousTime)/1000;

  GyroAngleX = GyroAngleX + ((rotX-GyroErrorX) * ElapsedTime) ;
  GyroAngleY = GyroAngleY + ((rotY-GyroErrorY) * ElapsedTime);
  GyroAngleZ = GyroAngleZ + ((rotZ-GyroErrorZ) * ElapsedTime);
  
  Pitch_Angle = (-1)*(0.9*GyroAngleX + 0.1*AccAngleX); // for my own orintation adjustment
  Roll_Angle = 0.9*GyroAngleY + 0.1*AccAngleY;
  Yaw_Angle = (-1)*GyroAngleZ; // for my own orintation adjustment
}

void printData() {
  Serial.print("  Pitch: ");
  Serial.print(Pitch_Angle);
  Serial.print("    Roll: ");
  Serial.print(Roll_Angle);
  Serial.print("    Yaw: ");
  Serial.print(Yaw_Angle);
  Serial.println();
}

void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  while (c < 500) {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
    accelX = ((double)(((int16_t)(Wire.read() << 8 | Wire.read())) / 16384.0)) ;
    accelY = ((double)(((int16_t)(Wire.read() << 8 | Wire.read())) / 16384.0)) ;
    accelZ = ((double)(((int16_t)(Wire.read() << 8 | Wire.read())) / 16384.0)) ;
    
    // Sum all readings
    gForceErrorX = gForceErrorX + ((atan((accelX) / sqrt(pow((accelY), 2) + pow((accelZ), 2))) * (180 / PI)));
    gForceErrorY = gForceErrorY + ((atan(-1 * (accelY) / sqrt(pow((accelX), 2) + pow((accelZ), 2))) * (180 / PI)));
    c++ ;
  }
  //Divide the sum by 300 to get the error value
  gForceErrorX = gForceErrorX / 500;
  gForceErrorY = gForceErrorY / 500;
  c = 0;
  // Read gyro values 300 times
  while (c < 500) {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);

    gyroX = ((int16_t)(Wire.read() << 8 | Wire.read()));
    gyroY = ((int16_t)(Wire.read() << 8 | Wire.read()));
    gyroZ = ((int16_t)(Wire.read() << 8 | Wire.read()));

    // Sum all readings
    GyroErrorX = GyroErrorX + ((double)(gyroX / 131.0));
    GyroErrorY = GyroErrorY + ((double)(gyroY / 131.0));
    GyroErrorZ = GyroErrorZ + ((double)(gyroZ / 131.0));
    c++;
  }

  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 500;
  GyroErrorY = GyroErrorY / 500;
  GyroErrorZ = GyroErrorZ / 500;
  c=0;
}
