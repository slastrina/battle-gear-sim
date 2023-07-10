#include <Joystick.h>

int firstButton = 6;
int buttonCount = 8;

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, // hid report type
  JOYSTICK_TYPE_MULTI_AXIS, // joystick type
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

int zAxis_ = 0;
int RxAxis_ = 0;
int RyAxis_ = 0;
int RzAxis_ = 0;
int Throttle_ = 0;

const bool initAutoSendState = true; 

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
  zAxis_ = analogRead(A0);  
  zAxis_ = map(zAxis_,0,1023,0,255);
  Joystick.setZAxis(zAxis_);
  
  RzAxis_ = analogRead(A1);
  RzAxis_ = map(RzAxis_,1023,0,255,0);            
  Joystick.setBrake(RzAxis_);
    
  Throttle_ = analogRead(A2);
  Throttle_ = map(Throttle_,1023,0,255,0);         
  Joystick.setThrottle(Throttle_);                

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
