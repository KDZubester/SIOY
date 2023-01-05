
//Hour and minute array positions
#define HOURS 0
#define MINUTES 1

//Time array
int setTimeValue[2] = { 12, 30 };     // { hours, minutes }

bool blinkOn = true;
int currentTimeUnit = HOURS;


//Draw editable time in its current state
void drawTimeSet() {
  //Put the current time in timeString, including any zeros ("0")
  char timeString[12] = "";

  //Include any leading zeros - hours
  if (!blinkOn &&  currentTimeUnit == HOURS) {
    sprintf(timeString, "%s  :", timeString);
  }
  else {
    if (setTimeValue[HOURS] < 10)    { strncat(timeString, "0", 1); }
    sprintf(timeString, "%s%d:", timeString, setTimeValue[HOURS]);
  }

  //Include any leading zeros - minutes
  if (!blinkOn &&  currentTimeUnit == MINUTES) {
    sprintf(timeString, "%s  ", timeString);
  }
  else {
    if (setTimeValue[MINUTES] < 10)    { strncat(timeString, "0", 1); }
    sprintf(timeString, "%s%d", timeString, setTimeValue[MINUTES]);
  }
  
  //Draw timeString to display
  u8g.setFont(u8g_font_profont17);
  u8g.setPrintPos(30, 40);
  u8g.print(timeString);

  //Corner Instructions
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(RIGHT_X_3, TOP_Y);
  u8g.print("SET");
  u8g.setPrintPos(RIGHT_X_3, BOTTOM_Y);
  u8g.print("NXT");

  u8g.drawBitmap(LEFT_X, BOTTOM_ARROW_Y, 1, 8, getIcon(DOWN_ARROW));
  u8g.drawBitmap(LEFT_X, TOP_Y, 1, 8, getIcon(UP_ARROW));
}

//Handle the timeSet App
void timeSet() {

  setTimeValue[HOURS] = rtc.now().hour();
  setTimeValue[MINUTES] = rtc.now().minute();

  currentTimeUnit = HOURS;

  delay(100);

  //Run App until user exits
  while (1) {
    bool exitToMenu = false;

    //Blink every 0.25 seconds. While we wait to blink, check if user increments or decrements a time unit
    long unsigned time_0 = millis();
    while ((millis() - time_0) < 250) {
      //Change which value is blinking if BTN_SE is pressed
      if (digitalRead(BTN_SE) == LOW) {
        if (currentTimeUnit == MINUTES) { currentTimeUnit = HOURS; }
        else { currentTimeUnit++; }
        delay(100);
        break;
      }
      //Increment the currently blinking time unit
      else if (digitalRead(BTN_NW) == LOW) {
        (setTimeValue[currentTimeUnit])++;  //Increment the time value at array position (currentBlink)
        if (currentTimeUnit == HOURS && setTimeValue[currentTimeUnit] == 24) { setTimeValue[currentTimeUnit] = 0; }
        if (currentTimeUnit == MINUTES && setTimeValue[currentTimeUnit] == 60) { setTimeValue[currentTimeUnit] = 0; }
        delay(100);
        break;
      }
      //Decrement the currently blinking time unit
      else if (digitalRead(BTN_SW) == LOW) {
        (setTimeValue[currentTimeUnit])--;  // Decrement the time value at array position (currentBlink)
        if (currentTimeUnit == HOURS && setTimeValue[currentTimeUnit] == -1) { setTimeValue[currentTimeUnit] = 23; }
        if (currentTimeUnit == MINUTES && setTimeValue[currentTimeUnit] == -1) { setTimeValue[currentTimeUnit] = 59; }
        delay(100);
        break;
      }
      //Break out of both while loops if user presses BTN_NE: Set the current time as the user input time
      else if (digitalRead(BTN_NE) == LOW) {
        exitToMenu = true;
        break;
      }
      
    }

    //Break out of both while loops if user presses BTN_NE, reset exitToMenu to false;
    if (exitToMenu == true) {
      break;
    }

    //Only Blink if neither the up nor the down button is pressed
    if (digitalRead(BTN_NW) != LOW && digitalRead(BTN_SW) != LOW) {
      blinkOn = !blinkOn;
    }
    else {
      blinkOn = true;
    }

    //Update screen with the latest time value
    newScreen(drawTimeSet);
  }
  delay(100);

  //Adjust time based on user input
  // rtc.adjust(DateTime(year, month, day, hour, minute, second));
  rtc.adjust(DateTime(2022, 12, 19, setTimeValue[0], setTimeValue[1], 0));

}
