#include "U8glib.h"
#include "LowPower.h"
#include "RTClib.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RIGHT_X_3 112
#define TOP_Y 6
#define LEFT_X 0
#define BOTTOM_Y 62

#define TURN_OFF 0
#define RETURN_TO_CLOCK 1

#define UP_ARROW 6
#define DOWN_ARROW 7
#define BOTTOM_ARROW_Y SCREEN_HEIGHT - 8
#define RIGHT_ARROW_X SCREEN_WIDTH - 8

#define ONE_SECOND 1000

//Global display object
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

//Clock object
RTC_DS3231 rtc;


const int BTN_NE = 2;
const int BTN_SE = 3;
const int BTN_NW = 4;
const int BTN_SW = 5;


//Declaration of printTime Function
void printTime(DateTime now);

//Draw clock, all button prompts, and battery
void wakeScreen(void) {

  u8g.setColorIndex(1);

  printTime(rtc.now());

  //Draw OFF and MENU prompts at the corners
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(RIGHT_X_3, TOP_Y);
  u8g.print("OFF");
  u8g.setPrintPos(LEFT_X, BOTTOM_Y);
  u8g.print("MENU");

  drawBattery(1,1);
  
}

//Erase the screen (write nothing to the screen);
void clearDisplay(void) {
  u8g.setPrintPos(0, 10);
  u8g.print("");
}

//Pass all drawing functions to this function to draw a new screen
void newScreen( void (*f) (void) ) {
  u8g.firstPage();
  do {
    (*f)();
  } while (u8g.nextPage() );
}

//Wake up function: passed into the "attachInterrupt" Function
void wakeUp() {}

//Set up function for buttons, interrupts, and RTC module. This is called at startup
void setup(void) {
  pinMode(BTN_NE, INPUT);//_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_NE), wakeUp, FALLING);

  pinMode(BTN_SE, INPUT);
  pinMode(BTN_NW, INPUT);
  pinMode(BTN_SW, INPUT);

  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    while (1) delay(10);
  }

  //Uncomment this line to get the reset time to current
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

bool enterMenu = false;
bool reenterClock = true;

//This function is called as soon as it returns -- Think of it as being called inside a while loop in main
void loop(void) {

  //Shut off the board if user did not request to reenter the clock
  if (!reenterClock) {
    //Shut off Board and Sleep
    newScreen(clearDisplay);
    delay(200);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    delay(20);
  }

  //Do not keep reentering Clock
  reenterClock = false;
  
  //Draw start up screen (clock, menu button, off button)
  newScreen(wakeScreen);

  delay(200);

  long unsigned time_0 = millis();
  long unsigned time_1 = millis();

  //Keep screen on for 5 seconds, unless user goes to menu or turns the screen off
  while ((millis() - time_0) < 4800) {
    //If user presses power button, turn off
    if (digitalRead(BTN_NE) == LOW) {
      break;
    } 
    else if (digitalRead(BTN_SW) == LOW) {
      enterMenu = true;
      break;
    }
    else if ((millis() - time_1) >= ONE_SECOND) {
      //Redraw screen every 1 second, to show if battery is fluctuating
      time_1 = millis();
      newScreen(wakeScreen);
    }
  }

  //Enter menu if the user presses the menu button
  if (enterMenu) {
    delay(200);
    enterMenu = false;
    //Keep running menu, unless the user selects the clock app, or turns off the watch
    while (1) {
      int menuReturnVal = menu();

      //Check menuReturnVal --> Turn off or return to clock accordingly.
      if (menuReturnVal == TURN_OFF) {
        break;
      }
      if (menuReturnVal == RETURN_TO_CLOCK) {
        reenterClock = true;
        break;
      }
    }
  }

}
