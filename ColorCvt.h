//---------------------------------------------------------------------------

#ifndef ColorCvtH
#define ColorCvtH

#include <windows.h>

#include <cstdint>

//---------------------------------------------------------------------------
namespace ColorCvt {
//---------------------------------------------------------------------------

class TRGB {
public:
    TRGB( uint8_t r, uint8_t g, uint8_t b )
      : r_{ r }, g_{ g }, b_{ b } {}

    uint8_t GetR() const { return r_; }
    uint8_t GetG() const { return g_; }
    uint8_t GetB() const { return b_; }
    RGBTRIPLE ToRGBTRIPLE() const;
private:
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};

class THSV {
public:
    THSV( double h, double s, double v )
      : h_{ h }, s_{ s },v_{ v } {}
    THSV( THSV const & ) = default;
    double GetH() const { return h_; }
    double GetS() const { return s_; }
    double GetV() const { return v_; }
private:
    double h_;
    double s_;
    double v_;

};

class THSL {
public:
	THSL( int h, float s, float l )
      : h_{ h }, s_{ s }, l_{ l } {}
    double GetH() const { return h_; }
    double GetS() const { return s_; }
    double GetL() const { return l_; }
private:
	int h_;
	float s_;
	float l_;
};


extern TRGB HSVToRGB( THSV hsv );
extern TRGB HSLToRGB( THSL hsl );

//---------------------------------------------------------------------------
} // End of namespace ColorCvt
//---------------------------------------------------------------------------
#endif
