#ifndef __LED_7segment_bitbang_included__
#define __LED_7segment_bitbang_included__
#define private public

class LED_7segment_bitbang final {
  public:
  static uint16_t volatile bits[3]; // only set la..lg
  static void init();
  static void done();
  static const uint16_t v[];
  static const uint16_t la=B00010000 << 8;
  static const uint16_t lb=B00001000 << 8;
  static const uint16_t lc=B00000100 << 8;
  static const uint16_t ld=B00000010 << 8;
  static const uint16_t le=B00100000;
  static const uint16_t lf=B00001000;
  static const uint16_t lg=B10000000;
  static LED_7segment_bitbang instance;
  void LED_7segment_bitbang::next();
  void blank(){
    bits[0] = bits[1] = bits[2] = v[16];
  }
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
  void write_err(int n){
    bits[0] = v[16]; //blank
    bits[1] = v[0xe]; //"e"
    bits[2] = v[17]; //"r"
  }
  private:
  LED_7segment_bitbang();
  static volatile char current_d;
  static const char d[];
  static const byte PD=B11111000;
  static const byte PB=B00011111;
  static const byte PD_blank=B10101000;
  static const byte PB_blank=B00011110;
};
#endif //__LED_7segment_bitbang_included__
