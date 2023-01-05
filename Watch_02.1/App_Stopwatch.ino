
#define STOPWATCH_MINUTES 0
#define STOPWATCH_SECONDS 1
#define STOPWATCH_MILLISECONDS 2

int stopwatchValues[3] = { 0, 0, 0 };     // { minutes, seconds, milliseconds }

char timeString[15] = "";

//Set the timeString to what it should be
void formTimeString() {
  sprintf(timeString, "");
  //Handle minutes leading zero
  if (stopwatchValues[STOPWATCH_MINUTES] < 10)    { strncat(timeString, "0", 1); }
  sprintf(timeString, "%s%d:", timeString, stopwatchValues[STOPWATCH_MINUTES]);

  //Handle seconds leading zero
  if (stopwatchValues[STOPWATCH_SECONDS] < 10)    { strncat(timeString, "0", 1); }
  sprintf(timeString, "%s%d.", timeString, stopwatchValues[STOPWATCH_SECONDS]);

  //Handle milliseconds leading zero(s)
  if (stopwatchValues[STOPWATCH_MILLISECONDS] < 10)    { strncat(timeString, "0", 1); }
  if (stopwatchValues[STOPWATCH_MILLISECONDS] < 100)    { strncat(timeString, "0", 1); }
  sprintf(timeString, "%s%d", timeString, stopwatchValues[STOPWATCH_MILLISECONDS]);
}

//Draw the stopwatch display (stopped)
void drawStopped() {
  formTimeString();
  
  //Draw timeString to display
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(33, 37);
  u8g.print(timeString);

  //Corner Instructions
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(RIGHT_X_3, TOP_Y);
  u8g.print("MNU");
  u8g.setPrintPos(RIGHT_X_3, BOTTOM_Y);
  u8g.print("BGN");
  u8g.setPrintPos(LEFT_X, BOTTOM_Y);
  u8g.print("CLR");
}

//Draw the stopwatch display (running)
void drawRunning() {
  formTimeString();
  
  //Draw timeString to display
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(33, 37);
  u8g.print(timeString);

  //Corner Instructions
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(RIGHT_X_3, BOTTOM_Y);
  u8g.print("STP");
}

//All necessary variables for stopwatch
bool stopwatch_running = false;
unsigned long long stopwatch_value = 0;
unsigned long time_1 = 0;

//Handle all stopwatch functions
void stopwatch() {

  int interval = 0;

  //Begin by drawing the stopped stopwatch
  newScreen(drawStopped);

  //Allow user to run stopwatch until pressing Menu button
  while (1) {

    //If the stopwatch should be running, run it
    if (stopwatch_running) {

      //Get the interval since the last update, in milliseconds
      interval = millis() - time_1;
      time_1 = millis();

      //Handle rollover
      if (interval < 0) {
        interval = 300;
      }

      //Add the interval since the last update, in milliseconds, to the stopwatch value
      stopwatch_value += interval;

      //Calculate the minutes, seconds, and milliseconds, depending on the stopwatch value
      stopwatchValues[STOPWATCH_MINUTES] = stopwatch_value / 60000;
      stopwatchValues[STOPWATCH_SECONDS] = (stopwatch_value % 60000) / 1000;
      stopwatchValues[STOPWATCH_MILLISECONDS] = stopwatch_value % 1000;

      //Redraw the new time
      newScreen(drawRunning);

      //Pause the stopwatch if the user presses BTN_SE
      if (digitalRead(BTN_SE) == LOW) {
        stopwatch_running = false;
        newScreen(drawStopped);
        delay(100);
      }
    }
    
    //If the stopwatch should not be running, wait for user input
    else {
      
      //Begin running the stopwatch if the user presses BTN_SE
      if (digitalRead(BTN_SE) == LOW) {
        stopwatch_running = true;
        delay(100);
        time_1 = millis();
      }
      //Exit to menu if the user presses BTN_NE
      else if (digitalRead(BTN_NE) == LOW) {
        break;
      }
      //Reset the stopwatch to 00:00.000 and redraw the screen if the user presses BTN_SW
      else if (digitalRead(BTN_SW) == LOW) {
        stopwatchValues[STOPWATCH_MINUTES] = 0;
        stopwatchValues[STOPWATCH_SECONDS] = 0;
        stopwatchValues[STOPWATCH_MILLISECONDS] = 0;
        stopwatch_value = 0;
        newScreen(drawStopped);
      }
      
    }
    
  }
  
  delay(100);
}
