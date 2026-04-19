
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

#define LED_BUILTIN 2

void setMotor(int left, int right);

void setup()
{
  RemoteXY_Init(); // initialization by macros

  // TODO you setup code
  pinMode(LED_BUILTIN, OUTPUT);
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


  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXYEngine.delay()
}

void setMotor(int left, int right) {

}