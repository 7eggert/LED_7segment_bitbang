#ifndef __LED_7segment_bitbang_included__
#define __LED_7segment_bitbang_included__
#define private public

class LED_7segment_bitbang final {
  public:
  // Singleton instance;
  // use "LED_7segment_bitbang &myname = LED_7segment_bitbang::instance"
  // to access the functions more easily
  static LED_7segment_bitbang instance; // Singleton instance

  // start timer, blank the display
  void init();

  // stop timer, blank the display
  static void done();

  // output bitmasks
  // be _very_ careful while addressing these, 
  // only assign l_, la ... lg
  // or use l_ as a bitmask
  static uint16_t volatile bits[3]; // only set la..lg

  // constants for turning on LEDs
  // negative logic, since these pins drive grounding pins
  // (lb & lc 
  static const uint16_t l_ = 0x1ea8; // blank
  static const uint16_t la=l_ & ~(B00010000 << 8); // top
  static const uint16_t lb=l_ & ~(B00001000 << 8); // top left
  static const uint16_t lc=l_ & ~(B00000100 << 8); // top right
  static const uint16_t ld=l_ & ~(B00000010 << 8); // middle
  static const uint16_t le=l_ & ~(B00100000);      // bottm left
  static const uint16_t lf=l_ & ~(B00001000);      // bottom right
  static const uint16_t lg=l_ & ~(B10000000);      // bottom

  // digits 0..9, a..f, blank, "r", "-"
  // 0..f are fixed, the other values may still change for the
  // next version of the library
  static const uint16_t v[];

  // blank display
  void blank(){
    bits[0] = bits[1] = bits[2] = v[16];
  }
  
  // write decimal or error if n>199
  void writede(int n){
  	if (n > 199) {
  		write_err();
  		return;
	}
	writed(n);
  }
  
  // write decimal
  void writed(int n){
    byte c = n%10;
    n/=10;
    bits[2] = v[c];
    if (!n) goto blank1;
    bits[1] = v[n%10];
    n/=10;    
    if (!n) goto blank2;
    bits[0] = v[n & 0x0f]; // prevent access of outside array, faster than %10
    return;
    blank1:
    bits[1] = v[16];
    blank2:
    bits[0] = v[16];
  }
  
  // write hex values
  void writeh(int n){
    byte c=n&0x0f; n>>=4;
    bits[2] = v[c];
    if (!n) goto blank1;
    bits[1] = v[n&0x0f];
    n>>=4;
    if (!n) goto blank2;
    bits[0] = v[n & 0x0f]; // prevent access of outside array
    return;
    blank1:
    bits[1] = v[16];
    blank2:
    bits[0] = v[16];
  }
  
  // write "Er"
  void write_err(){
    bits[0] = v[16]; //blank
    bits[1] = v[0xe]; //"e"
    bits[2] = v[17]; //"r"
  }
  
  // write "--"
  void write_minus(){
    bits[0] = v[16]; //blank
    bits[1] = v[18]; //"-"
    bits[2] = v[18]; //"-"
  }
  
  // write -9 .. 199
  void writei(int i){
    if (i < -9) {
    	write_err();
    	return;
    }
    if (i < 0) {
        bits[0] = v[16]; //blank
        bits[1] = v[18]; //"-"
        bits[2] = v[-i]; //digit
    }
    writede(i);
  }
  
  // alias for blank()
  void write_blank(){
  	blank();
  }
  // display next digit; internal function, but it expects to be called from
  // interrupt so it has to be public
  void LED_7segment_bitbang::next();

  private:
  LED_7segment_bitbang(); // Singleton constructor
  static volatile char current_d; // current digit
  static const char digit_pin[];  // pins corresponding to digits
  static const byte PD=B11111000; // GPIO-register D mask
  static const byte PB=B00011111; // GPIO-register B mask
  static const byte PD_blank=B10101000; // value for blank output
  static const byte PB_blank=B00011110; // dito
  static void set_blank_voltages();
};
#endif //__LED_7segment_bitbang_included__
