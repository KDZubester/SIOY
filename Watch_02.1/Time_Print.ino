
void printTime(DateTime now) 
{
  //Put the current time in timeString, including any zeros ("0")
  char timeString[12] = "";
  if (now.hour() < 10)    { strncat(timeString, "0", 1); }
  sprintf(timeString, "%s%d:", timeString, now.hour());
  if (now.minute() < 10)    { strncat(timeString, "0", 1); }
  sprintf(timeString, "%s%d", timeString, now.minute());

  //Draw timeString to display
  u8g.setFont(u8g_font_profont17);
  u8g.setPrintPos(30, 40);
  u8g.print(timeString);
}
