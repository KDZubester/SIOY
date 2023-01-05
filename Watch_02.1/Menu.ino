#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define TURN_OFF 0
#define RETURN_TO_CLOCK 1
#define RESTART_MENU 2

#define APP_SIDE 16
#define MAX_APP_NUM 5
#define CLOCK_APP_NUM 0
#define SET_TIME_NUM 1
#define DODGE_BLOCK_NUM 2
#define STOPWATCH_NUM 3
#define COUNTER_APP_NUM 4
#define CUSTOM_APP_NUM 5

#define BATTERY 0
#define BATTERY_ONE_BAR 1
#define BATTERY_TWO_BARS 2
#define BATTERY_THREE_BARS 3
#define RIGHT_ARROW 4
#define LEFT_ARROW 5
#define UP_ARROW 6
#define DOWN_ARROW 7
#define BOTTOM_ARROW_Y SCREEN_HEIGHT - 8
#define RIGHT_ARROW_X SCREEN_WIDTH - 8

int currentAppNum = 0;

void menuScreen() {

  for (int i = 0; i <= MAX_APP_NUM; i++) {
    struct app app_i = getAppArray()[i];

    //If this iteration is the currently selected app, draw the app icon inverted.
    if (currentAppNum == i) {
      u8g.drawBox(app_i.x, app_i.y, APP_SIDE, APP_SIDE);
      u8g.setColorIndex(0);
      u8g.drawBitmap(app_i.x, app_i.y, 2, 16, app_i.icon);
      u8g.setColorIndex(1);
    }
    else {
      u8g.drawBitmap(app_i.x, app_i.y, 2, 16, app_i.icon);
    }
  }

  //Draw OFF and SEL prompts, along with the arrow icons, in the corners
  u8g.setFont(u8g_font_profont10);
  
  u8g.setPrintPos(RIGHT_X_3, TOP_Y);
  u8g.print("OFF");
  u8g.setPrintPos(LEFT_X, TOP_Y);
  u8g.print("SEL");
  
  u8g.drawBitmap(LEFT_X, BOTTOM_ARROW_Y, 1, 8, getIcon(LEFT_ARROW));
  u8g.drawBitmap(RIGHT_ARROW_X, BOTTOM_ARROW_Y, 1, 8, getIcon(RIGHT_ARROW));
  
}


int menu() {  

  //Begin by drawing the menu screen
  newScreen(menuScreen);

  long unsigned time_0 = millis();
  
  //Stay in menu for 10 seconds, then exit and turn off the screen
  while (millis() - time_0 < 9500) {
    if (digitalRead(BTN_NE) == LOW) {
      break;
    } 
    //Move through apps (Left)
    else if (digitalRead(BTN_SW) == LOW) {

      //Decrement or wrap the current app number
      if (currentAppNum == 0) {
        currentAppNum = MAX_APP_NUM;
      }
      else {
        currentAppNum--;
      }

      delay(100);
      
      //Reset turn off menu counter if the user presses a button
      time_0 = millis();

      //Redraw screen to reflect the current app
      newScreen(menuScreen);
    }
    //Move through apps (Right)
    else if (digitalRead(BTN_SE) == LOW) {
      
      //Increment or wrap the current app number
      if (currentAppNum == MAX_APP_NUM) {
        currentAppNum = 0;
      }
      else {
        currentAppNum++;
      }

      delay(100);
      
      //Reset turn off menu counter if the user presses a button
      time_0 = millis();
      
      //Redraw screen to reflect the current app
      newScreen(menuScreen);
    }
    
    //Enter currently selected App with BTN_NW
    else if (digitalRead(BTN_NW) == LOW) {
      delay(100);

      //Enter app depending on the current app number
      if (currentAppNum == CLOCK_APP_NUM) {
        currentAppNum = 0;
        return RETURN_TO_CLOCK;
      }
      else if (currentAppNum == SET_TIME_NUM) {
        timeSet();
        return RESTART_MENU;
      }
      else if (currentAppNum == DODGE_BLOCK_NUM) {
        dodgeBlock();
        return RESTART_MENU;
      }
      else if (currentAppNum == STOPWATCH_NUM) {
        stopwatch();
        return RESTART_MENU;
      }
      else if (currentAppNum == COUNTER_APP_NUM) {
        counter();
        return RESTART_MENU;
      }
      else if (currentAppNum == CUSTOM_APP_NUM) {
        customApp();
        return RESTART_MENU;
      }
    }
  }

  currentAppNum = 0;
  return TURN_OFF;
}
