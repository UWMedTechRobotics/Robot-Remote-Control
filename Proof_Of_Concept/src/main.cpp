
#include <Arduino.h>
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"
#include <RemoteXY.h>

// RemoteXY GUI configuration
#pragma pack(push, 1)
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] = // 53 bytes V19
    {255, 3, 0, 0, 0, 46, 0, 19, 0, 0, 0, 0, 31, 1, 106, 200, 1, 1, 3, 0,
     4, 15, 50, 74, 25, 128, 2, 26, 4, 15, 128, 74, 25, 128, 2, 26, 2, 39, 91, 44,
     22, 0, 2, 26, 31, 31, 79, 78, 0, 79, 70, 70, 0};

// this structure defines all the variables and events of your control interface
struct
{

  // input variables
  int8_t LEFT_MOTOR;  // from 0 to 100
  int8_t RIGHT_MOTOR; // from 0 to 100
  uint8_t ON_SWITCH;  // =1 if switch ON and =0 if OFF, from 0 to 1

  // other variable
  uint8_t connect_flag; // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <Servo.h>

#define LED_BUILTIN 2
#define LEFT_MOTOR_PWM_PIN 32
#define RIGHT_MOTOR_PWM_PIN 33

#define ESC_SIGNAL_PIN 10
#define THRUSTER_CALIBRATION_DELAY 5000  // Delay necessary for thruster calibration in milli-seconds.
#define STALL_US 1500                    // Duty cycle for stalling thruster in micro-seconds.
#define DUTY_CYCLE_MIN 1350
#define DUTY_CYCLE_MAX 1650

void setMotor(int left, int right);

Servo thruster_left;
Servo thruster_right;

void setup()
{
  RemoteXY_Init();

  pinMode(LED_BUILTIN, OUTPUT);

  thruster_left.attach(LEFT_MOTOR_PWM_PIN, 1000, 2000);
  thruster_right.attach(RIGHT_MOTOR_PWM_PIN, 1000, 2000);

  thruster_left.writeMicroseconds(STALL_US);
  thruster_right.writeMicroseconds(STALL_US);

  RemoteXYEngine.delay(THRUSTER_CALIBRATION_DELAY);
}

void loop()
{
  RemoteXYEngine.handler();

  if(RemoteXY.ON_SWITCH == 0)
  {
    digitalWrite(LED_BUILTIN, LOW);
    setMotor(0, 0);
    return;
  }

  setMotor(RemoteXY.LEFT_MOTOR, RemoteXY.RIGHT_MOTOR);
}

void setMotor(int left, int right) {
  // map(value, fromLow, fromHigh, toLow, toHigh)
  int left_duty_cycle = map(left, 0, 100, DUTY_CYCLE_MIN, DUTY_CYCLE_MAX);
  int right_duty_cycle = map(right, 0, 100, DUTY_CYCLE_MIN, DUTY_CYCLE_MAX);

  thruster_left.writeMicroseconds(left_duty_cycle);
  thruster_right.writeMicroseconds(right_duty_cycle);
}