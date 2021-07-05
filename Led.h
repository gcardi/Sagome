//---------------------------------------------------------------------------

#ifndef LedH
#define LedH

#include <System.hpp>

#include <vector>

#include "VclGdiplus.h"

class Led {
public:
    Led() {}
    explicit Led( float Size );
    long GetIntensity() const;
    void SetIntensity( long Val );
    void Draw( Gdiplus::Graphics& Canvas,
               Gdiplus::Color Color,
               Gdiplus::PointF Offset = Gdiplus::PointF(),
               Gdiplus::Color RingColor = Gdiplus::Color( 255, 8, 8, 8 ),
               float RingSize = 2.0F ) const;
    float GetSize() const { return size_; }
private:
    typedef  std::vector<Gdiplus::PointF>  GlowCurvePointCont;

    float size_{ 10.0F };
    GlowCurvePointCont glowCurvePoints_;
};

//---------------------------------------------------------------------------
#endif
