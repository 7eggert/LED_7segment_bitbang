#include <LED_7segment_bitbang.h>

// make an alias for accessing elements of LED_7segment_bitbang
LED_7segment_bitbang & led7 = LED_7segment_bitbang::instance;

void setup()
{
	led7.init();
}

void loop()
{
	int i;
	// write dcimal integer values
	for (i = 0; i < 200; i++) {
		led7.writed(i);
		delay(100);
	}
	// write hexadecimal values
	for (i = 0; i < 0x200; i++) {
		led7.writeh(i);
		delay(100);
	}
}
