

void drawCustomApp() {

  //Filler Text for Counter App
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(9, 23);
  u8g.print("Custom App is left");
  u8g.setPrintPos(7, 43);
  u8g.print("for User to Program");
  
  //Draw Counter Time
  

  //Corner Instructions
  
}


void customApp() {

  //Draw counter text to screen
  newScreen(drawCustomApp);

  //Wait for 3 seconds
  delay(3000);
}
