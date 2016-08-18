#include <LED_7segment_bitbang.h>

// make an alias for accessing elements of LED_7segment_bitbang
LED_7segment_bitbang & led7 = LED_7segment_bitbang::instance;

void setup()
{
	led7.init();
}

void loop()
{
	// Read pin A0, map it to 0 .. 100 %
	
	led7.writed(map(analogRead(A0), 0, 1023, 0, 100));
	delay(100);
}
