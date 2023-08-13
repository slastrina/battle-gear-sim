#include <Joystick.h>

int firstButton = 6;
int buttonCount = 8;

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, // hid report type
  JOYSTICK_TYPE_JOYSTICK, // joystick type
  8, // button count
  0, // hatswitch count
  false, // includeXAxis
  false, // includeYAxis
  true, // includeZAxis
  false, // includeRxAxis
  false, // includeRyAxis
  false, // includeRzAxis
  false, // includeRudder
  true, // includeThrottle
  false,  // includeAccelerator
  true,  // includeBrake
  false); // includeSteering

int Clutch_ = 0;
int Brake_ = 0;
int Throttle_ = 0;

const bool initAutoSendState = true; 

const int DEADZONE = 20; // Size of the deadzone around the center

// Flags to check if previous value was outside the deadzone
bool wasOutsideDeadzone_Clutch = false;
bool wasOutsideDeadzone_Brake = false;
bool wasOutsideDeadzone_Throttle = false;

void setup()
{
  // Init Analog
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);

  // Init digital (buttons)
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  
  Joystick.begin();

}

// Constant that maps the phyical pin to the joystick button.
// Start Pin Index
const int pinToButtonMap = firstButton;

// Last state of the button - we are
int lastButtonState[8] = {0,0,0,0,0,0,0,0};

void loop(){
  Clutch_ = analogRead(A0);
  Clutch_ = map(Clutch_, 15, 560, 0, 1023);

  if (Clutch_ > DEADZONE) {
    Joystick.setZAxis(Clutch_);
    wasOutsideDeadzone_Clutch = true;
  } else if (wasOutsideDeadzone_Clutch) {
    Joystick.setZAxis(0);
    wasOutsideDeadzone_Clutch = false;
  }

  Brake_ = analogRead(A1);
  Brake_ = map(Brake_, 340, 650, 0, 1023);

  if (Brake_ > DEADZONE) {
    Joystick.setBrake(Brake_);
    wasOutsideDeadzone_Brake = true;
  } else if (wasOutsideDeadzone_Brake) {
    Joystick.setBrake(0);
    wasOutsideDeadzone_Brake = false;
  }

  Throttle_ = analogRead(A2);
  Throttle_ = map(Throttle_, 40, 480, 0, 1023);

  if (Throttle_ > DEADZONE) {
    Joystick.setThrottle(Throttle_);
    wasOutsideDeadzone_Throttle = true;
  } else if (wasOutsideDeadzone_Throttle) {
    Joystick.setThrottle(0);
    wasOutsideDeadzone_Throttle = false;
  }
  
  // Read pin values
  for (int index = 0; index < buttonCount; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
   
  delay (50);
}
