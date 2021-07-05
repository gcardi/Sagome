//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>

#include "ColorCvt.h"

#include "cmath"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
namespace ColorCvt {
//---------------------------------------------------------------------------

TRGB HSVToRGB( THSV hsv )
{
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    if ( hsv.GetS() == 0.0 ) {
        r = hsv.GetV();
        g = hsv.GetV();
        b = hsv.GetV();
    }
    else {
        int i;
        double f, p, q, t, h;

        h = std::fmod( std::abs( hsv.GetH() ), 360.0 ) / 60.0;

        i = (int)std::floor( h );

        //f = std::fmod( h, 1.0 );
        f = h - i;


        p = hsv.GetV() * ( 1.0 - hsv.GetS() );
        q = hsv.GetV() * ( 1.0 - ( hsv.GetS() * f ) );
        t = hsv.GetV() * ( 1.0 - ( hsv.GetS() * ( 1.0 - f ) ) );

        switch (i)
        {
        case 0:
            r = hsv.GetV();
            g = t;
            b = p;
            break;

        case 1:
            r = q;
            g = hsv.GetV();
            b = p;
            break;

        case 2:
            r = p;
            g = hsv.GetV();
            b = t;
            break;

        case 3:
            r = p;
            g = q;
            b = hsv.GetV();
            break;

        case 4:
            r = t;
            g = p;
            b = hsv.GetV();
            break;

        default:
            r = hsv.GetV();
            g = p;
            b = q;
            break;
        }
    }

    return TRGB(
        static_cast<uint8_t>( std::min( r * 255.0, 255.0 ) ),
        static_cast<uint8_t>( std::min( g * 255.0, 255.0 ) ),
        static_cast<uint8_t>( std::min( b * 255.0, 255.0 ) )
    );
}
//---------------------------------------------------------------------------

RGBTRIPLE TRGB::ToRGBTRIPLE() const
{
    RGBTRIPLE triple;
    triple.rgbtBlue = b_;;
    triple.rgbtGreen = g_;
    triple.rgbtRed = r_;
    return triple;
}
//---------------------------------------------------------------------------

static double HueToRGB( double v1, double v2, double vH )
{
	if ( vH < 0 ) {
		vH += 1;
    }

	if ( vH > 1 ) {
		vH -= 1;
    }

	if ( ( 6.0 * vH ) < 1 ) {
		return ( v1 + ( v2 - v1 ) * 6.0 * vH );
    }

	if ( ( 2.0 * vH ) < 1.0 ) {
		return v2;
    }

	if ( ( 3 * vH ) < 2.0 ) {
		return ( v1 + ( v2 - v1 ) * ( ( 2.0 / 3.0 ) - vH ) * 6.0 );
    }

	return v1;
}

TRGB HSLToRGB( THSL hsl )
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

	if ( hsl.GetS() == 0 )	{
		r = g = b = static_cast<uint8_t>( hsl.GetL() * 255.0 );
	}
	else	{
		float v1, v2;
		float hue = static_cast<double>( hsl.GetH() ) / 360.0;

		v2 =
            ( hsl.GetL() < 0.5 ) ?
              ( hsl.GetL() * ( 1 + hsl.GetS() ) )
            :
              ( (hsl.GetL() + hsl.GetS() ) - ( hsl.GetL() * hsl.GetS() ) );
		v1 = 2 * hsl.GetL() - v2;
		r = static_cast<uint8_t>( 255.0 * HueToRGB( v1, v2, hue + ( 1.0 / 3 ) ) );
		g = static_cast<uint8_t>( 255.0 * HueToRGB( v1, v2, hue ) );
		b = static_cast<uint8_t>( 255.0 * HueToRGB( v1, v2, hue - ( 1.0 / 3 ) ) );
	}
	return TRGB( r, g, b );
}
//---------------------------------------------------------------------------
} // End of namespace ColorCvt
//---------------------------------------------------------------------------

