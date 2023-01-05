

void drawCounter() {

  //Filler Text for Counter App
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(8, 23);
  u8g.print("Counter App is left");
  u8g.setPrintPos(8, 43);
  u8g.print("for User to Program");
  
  //Draw Counter Time
  

  //Corner Instructions
  
}


void counter() {

  //Draw counter text to screen
  newScreen(drawCounter);

  //Wait for 3 seconds
  delay(3000);
}
