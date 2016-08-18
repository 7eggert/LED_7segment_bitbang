Driver code for a LED 7-segment-block A-403G-3A 2½ Segment LED block

Uses timer 2 for a 1 kHz flicker-free display

The fritzing file LED_7segment_bitbang.fzz shows my wiring on the PCB.
Please ignore the breadboard view, it's useless.


How to connect the LED block to the pins:

1) The ground pins have 470 ohm resistors for driving the LED, this will
   give about 10 mA. For most chips (except e.g. C-403H-3A), you can use up
   to 20 mA, but 10 mA is OK. Remember to check weather your Atmel chip can
   drain the amount of current you're planning to drain.
   
2) The Pins 2, 10, 5 are connected using a NPN transistor, C=5V, E=Pin,
   B=Arduino (via 1000 ohm resistors).

I'm using a different naming scheme than in the data sheet:

_AAA_
B   C
B   C
_DDD_
E   F
E   F
_GGG_


The bottom left pin of the block is Pin 1, top left is 10.

The pins are connrcted like this: (that's how it happened to fit)
LED	Arduino
 1	 7
 2	 4
 3	 5
 4	 3
 5	 6
 6	10
 7	12
 8	11
 9	 9
10	 8
