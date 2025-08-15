#include <BleGamepad.h>

#define LATCH_PIN 35
#define CLOCK_PIN 21

#define DATA_PIN 36

#define LATCH_PERIOD 1
#define CLOCK_PERIOD 1

#define BTN_RIGHT 1 << 0
#define BTN_LEFT 1 << 1
#define BTN_DOWN 1 << 2
#define BTN_UP 1 << 3
#define BTN_START 1 << 4
#define BTN_SELECT 1 << 5
#define BTN_B 1 << 6
#define BTN_A 1 << 7

#define ANALOG_MIN 0x0
#define ANALOG_MAX 0x7FFF

BleGamepad gamepad("NES Bluetooth Adapter", "linterloper", 100);
BleGamepadConfiguration gamepadConfig;

void emitPulse(int pin, int lengthMs) {
  digitalWrite(pin, HIGH);
  delay(lengthMs);
  digitalWrite(pin, LOW);
}

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  pinMode(DATA_PIN, INPUT);

  gamepadConfig.setAutoReport(false);

  gamepadConfig.setModelNumber("1.0");
  gamepadConfig.setSoftwareRevision("Software Rev 1");
  gamepadConfig.setFirmwareRevision("1.0");
  gamepadConfig.setHardwareRevision("1.0");

  gamepad.begin(&gamepadConfig);

  gamepad.setAxes(
    INT16_MAX / 2, 
    INT16_MAX / 2,
    INT16_MAX / 2, 
    INT16_MAX / 2,
    INT16_MAX / 2, 
    INT16_MAX / 2,
    INT16_MAX / 2, 
    INT16_MAX / 2
  );

  gamepad.setLeftThumb(
    INT16_MAX / 2, 
    INT16_MAX / 2
  );
}


int lastGamepadState = 0;

void loop() {
  if(!gamepad.isConnected()) {
    return;
  }

  emitPulse(LATCH_PIN, LATCH_PERIOD);

  int gamepadState = 0;
  
  for(int i = 0; i < 8; i++) {
    gamepadState |= !digitalRead(DATA_PIN);

    if(i != 7) {
      gamepadState = gamepadState << 1;
    }

    emitPulse(CLOCK_PIN, CLOCK_PERIOD);
  }

  int16_t xAxis = (gamepadState & BTN_LEFT) != 0 ? 0 : (gamepadState & BTN_RIGHT) != 0 ? INT16_MAX : INT16_MAX / 2;
  int16_t yAxis = (gamepadState & BTN_UP) != 0 ? 0 : (gamepadState & BTN_DOWN) != 0 ? INT16_MAX : INT16_MAX / 2;

  if(gamepadState == lastGamepadState) {
    return;
  }

  gamepad.setLeftThumb(xAxis, yAxis);

  for (int i = 0; i < 4; i++) {
    if((gamepadState & (1 << (i + 4))) != 0) {
      gamepad.press(i + 1);
    } else {
      gamepad.release(i + 1);
    }
  }

  lastGamepadState = gamepadState;
  gamepad.sendReport();
}
