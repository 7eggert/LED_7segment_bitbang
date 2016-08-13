#include <LED_7segment_bitbang.h>

// make an alias for accessing elements of LED_7segment_bitbang
LED_7segment_bitbang &led7 = LED_7segment_bitbang::instance;

void setup() {
  // put your setup code here, to run once:
  led7.init();  
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for (i=0; i<200; i++){
    led7.writed(i);
  delay(100);
  }
  for (i=0; i<0x200; i++){
    led7.writeh(i);
  delay(100);
  }
}

