/***************************************************************
   Motor driver function definitions - by Jere Leman
***************************************************************/

#ifdef A100_MOTOR_DRIVER
  // 1 - Motor
  #define RIGHT_MOTOR_BACKWARD 5
  #define RIGHT_MOTOR_FORWARD  6
  #define RIGHT_PWM 3

  // 2 - Motor
  #define LEFT_MOTOR_FORWARD   9
  #define LEFT_MOTOR_BACKWARD  10
  #define LEFT_PWM 11

  // Current & Voltage Output
  #define CURRENT_PIN A0
  #define VOLTAGE_PIN A1
#endif

// Function declarations
void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
float readCurrent();
float readVoltage();
void monitorMotorParameters();
