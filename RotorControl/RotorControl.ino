#include <Servo.h>

// This array contains the PID Constant Value
const double YawPIDConstants = [3.5,0.005,2.05];
const double PitchPIDConstants = [3.5,0.005,2.05];
const double RollPIDConstants = [3.5,0.005,2.05];

double YawPID = [0,0,0];
double PitchPID = [0,0,0];
double RollPID = [0,0,0];

double YawAdjust, RollAdjust, PitchAdjust;

// The values are respectivly as: [PID_Proportional, PID_Integral, PID_Derivative]

double PitchError, RollError, YawError;
double PrevPitchError = 0, PrevRollError = 0, PrevYawError = 0;

double M1Adjust, M2Adjust, M3Adjust, M4Adjust;

Servo M1, M2, M3, M4;

void setup(){
  
  M1.attach(14,1000,2000);
  M2.attach(12,1000,2000);
  M3.attach(13,1000,2000);
  M4.attach(15,1000,2000);

  M1.writeMicroseconds(1000);
  M2.writeMicroseconds(1000);
  M3.writeMicroseconds(1000);
  M4.writeMicroseconds(1000); 
  
}

void loop(){
  CalculatePIDAdjusts();
  WriteToESCs();
  
}

void CalculatePIDAdjusts(){
  CalculateYawAdjust();
  CalculateRollAdjust();
  CalculatePitchAdjust();
}

void CalculateYawAdjust(){
  YawPID[0] = YawPIDConstants[0]*YawError;
  if(-3<YawError<3){
    YawPID[1] += YawPIDConstants[1]*YawError;
  }
  YawPID[2] = YawPIDConstants[2]*((YawError-PrevYawError)/ElapsedTime);
  YawAdjust = YawPID[0] + YawPID[1] + YawPID[2];
}

void CalculatePitchAdjust(){
  PitchPID[0] = PitchPIDConstants[0]*PitchError;
  if(-5<PitchError<5){
    PitchPID[1] += PitchPIDConstants[1]*PitchError;
  }
  PitchPID[2] = PitchPIDConstants[2]*((PitchError-PrevPitchError)/ElapsedTime);
  PitchAdjust = PitchPID[0] + PitchPID[1] + PitchPID[2];
}

void CalculateRollAdjust(){
  RollPID[0] = RollPIDConstants[0]*RollError;
  if(-6<RollError<6){
    RollPID[1] += RollPIDConstants[1]*RollError;
  }
  RollPID[2] = RollPIDConstants[2]*((RollError-PrevRollError)/ElapsedTime);
  RollAdjust = RollPID[0] + RollPID[1] + RollPID[2];
}

void WriteToESCs()
{
  M1Adjust = throttle_Val + PitchAdjust - RollAdjust - YawAdjust;
  M2Adjust = throttle_Val + PitchAdjust + RollAdjust + YawAdjust;
  M3Adjust = throttle_Val - PitchAdjust + RollAdjust + YawAdjust;
  M4Adjust = throttle_Val - PitchAdjust - RollAdjust - YawAdjust;

  if (M1Adjust > 2000)
    M1Adjust = 2000;
  if (M1Adjust < 1000)
    M1Adjust = 1000;

  if (M2Adjust > 2000)
    M2Adjust = 2000;
  if (M2Adjust < 1000)
    M2Adjust = 1000;
    
  if (M3Adjust > 2000)
    M3Adjust = 2000;
  if (M3Adjust < 1000)
    M3Adjust = 1000;

  if (M4Adjust > 2000)
    M4Adjust = 2000;
  if (M4Adjust < 1000)
    M4Adjust = 1000;
  M1.writeMicroseconds(M1Adjust);
  M2.writeMicroseconds(M2Adjust);
  M3.writeMicroseconds(M3Adjust);
  M4.writeMicroseconds(M4Adjust);    
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
