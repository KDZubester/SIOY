
#define BATTERY_HEIGHT   8
#define BATTERY_WIDTH    16

void drawBattery(int x, int y) {

  //FIND AVERAGE ADC OVER 50 CYCLES
  ADMUX = _BV(REFS0)    // ref = Vcc
    | 14;           // channel 14 is the bandgap reference
  ADCSRA |= _BV(ADSC);   // start conversion
  loop_until_bit_is_clear(ADCSRA, ADSC);  // wait until complete
  int adc_int = (int) ADC;

  for (int i = 0; i < 50; i++) {
    ADMUX = _BV(REFS0)    // ref = Vcc
      | 14;           // channel 14 is the bandgap reference
    ADCSRA |= _BV(ADSC);   // start conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);  // wait until complete
    adc_int = (adc_int + ADC) / 2;
  }
  //END 10 CYCLES

  int percentage = (390 - adc_int) * 2;

  if (adc_int < 310) {
    u8g.drawBitmap(x, y, 2, 8, getIcon(0));
    u8g.setFont(u8g_font_profont10);
    u8g.setPrintPos(x+5, y+7);
    u8g.print("?");
  }
  else if (percentage > 65) {
    u8g.drawBitmap(x, y, 2, 8, getIcon(3));
  }
  else if (percentage > 31) {
    u8g.drawBitmap(x, y, 2, 8, getIcon(2));
  }
  else if (percentage > 10) {
    u8g.drawBitmap(x, y, 2, 8, getIcon(1));
  }
  else {
    u8g.drawBitmap(x, y, 2, 8, getIcon(0));
  }
  
}
