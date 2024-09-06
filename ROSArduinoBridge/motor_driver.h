/***************************************************************
   Motor driver function definitions - modified by Jere Leman
***************************************************************/

#ifdef A100_MOTOR_DRIVER
  // 1 - Motor
  #define RIGHT_MOTOR_BACKWARD 5
  #define RIGHT_MOTOR_FORWARD  6
  #define RIGHT_PWM 9

  // 2 - Motor
  #define LEFT_MOTOR_FORWARD   7
  #define LEFT_MOTOR_BACKWARD  8
  #define LEFT_PWM 10

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
