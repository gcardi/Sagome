//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>
#include <vector>

#include "GdiPlusUtils.h"

#include "VclGdiplus.h"

using std::auto_ptr;
using std::vector;
using std::make_unique;

using Gdiplus::GdiplusStartup;
using Gdiplus::GdiplusShutdown;
using Gdiplus::Status;
using Gdiplus::StringAlignment;
using Gdiplus::StringAlignmentNear;
using Gdiplus::StringAlignmentCenter;
using Gdiplus::StringAlignmentFar;
using Gdiplus::Image;
using Gdiplus::RectF;
using Gdiplus::ColorMatrixFlagsDefault;
using Gdiplus::ColorAdjustTypeDefault;
using Gdiplus::ColorMatrix;
using Gdiplus::ImageAttributes;
using Gdiplus::GetImageEncodersSize;
using Gdiplus::ImageCodecInfo;

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
namespace GdiplusUtils {
//---------------------------------------------------------------------------

GdiPlusSessionManager::GdiPlusSessionManager()
{
    GdiplusStartup( &gdiplusToken_, &gdiplusStartupInput_, NULL );
}
//---------------------------------------------------------------------------

GdiPlusSessionManager::~GdiPlusSessionManager() /* throw() */
{
    try {
        GdiplusShutdown( gdiplusToken_ );
    }
    catch ( ... ) {
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall EGdiplusException::EGdiplusException( String Msg )
    : inherited( _T( "GDI+ error: " ) + Msg )
{
}
//---------------------------------------------------------------------------

__fastcall EGdiplusException::EGdiplusException( Gdiplus::Status Code )
    : inherited( _T( "GDI+ error: " ) + GetGdiplusStatusStrings( Code ) )
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

static String FormatOSErrorMessage( DWORD ErrCode );

void GdiplusCheck( Gdiplus::Status Code )
{
    switch ( Code ) {
        case Status::Ok:
            return;
        case Status::Win32Error:
            throw EGdiplusException(
                GetGdiplusStatusStrings( Code ) + _T( ": " ) +
                FormatOSErrorMessage( GetLastError() )
            );
        default:
            throw EGdiplusException( Code );
    }
}
//---------------------------------------------------------------------------

String GetGdiplusStatusStrings( Gdiplus::Status Code ) {
    static PCTSTR const Strs[] = {
      _T( "Ok" ),
      _T( "Generic Error" ),
      _T( "Invalid Parameter" ),
      _T( "Out Of Memory" ),
      _T( "Object Busy" ),
      _T( "Insufficient Buffer" ),
      _T( "Not Implemented" ),
      _T( "Win32 Error" ),
      _T( "Wrong State" ),
      _T( "Aborted" ),
      _T( "File Not Found" ),
      _T( "Value Overflow" ),
      _T( "Access Denied" ),
      _T( "Unknown Image Format" ),
      _T( "Font Family Not Found" ),
      _T( "Font Style Not Found" ),
      _T( "Not TrueType Font" ),
      _T( "Unsupported Gdi+ Version" ),
      _T( "Gdi+ Not Initialized" ),
      _T( "Property Not Found" ),
      _T( "Property Not Supported" ),
      _T( "Profile Not Found" ),
    };

    if ( Code < static_cast<int>( sizeof Strs / sizeof *Strs ) )
        return Strs[Code];
    else
        return String( _T( "Unknown (code " ) ) + Code + _T( ")" );
}
//---------------------------------------------------------------------------

class TEOSErrorLocalFree {
public:
    explicit TEOSErrorLocalFree( PVOID Buffer )
        : Buffer_( Buffer ) {}
    ~TEOSErrorLocalFree() { LocalFree( Buffer_ ); }
    TEOSErrorLocalFree( TEOSErrorLocalFree const & ) = delete;
    TEOSErrorLocalFree& operator=( TEOSErrorLocalFree const & ) = delete;
private:
    PVOID Buffer_;
};

String FormatOSErrorMessage( DWORD ErrCode )
{
    PVOID Buffer;

    DWORD Ret = FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                0, ErrCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<PTCHAR>( &Buffer ), 0,
                0
          );
    if ( !Ret )
        return String( _T ( "FormatOSErrorMessage failed!" ) );

    TEOSErrorLocalFree LocalFreeObj( Buffer );

    return String( static_cast<PTCHAR>( Buffer ) );
}
//---------------------------------------------------------------------------

Gdiplus::Image* LoadImage( String FileName )
{
    if ( FileExists( FileName ) ) {
        auto_ptr<Gdiplus::Image> NewImage( new Gdiplus::Image( FileName.c_str() ) );
        if ( NewImage.get() )
            GdiplusCheck( NewImage->GetLastStatus() );
/*
String Msg = String( TEXT( __FUNC__ ": " ) ) +
    ExtractFileName( FileName ) +
    String( TEXT( " - " ) ) +
    NewImage->GetWidth() + String( TEXT( "w, " ) ) +
    NewImage->GetHeight() + String( TEXT( "h" ) );
OutDebugString( Msg.c_str() );
*/
        return NewImage.release();
    }
    else
        throw EGdiplusException( String( _T( "Can't load the image \"" ) ) + FileName + _T( "\"" ) );
}
//---------------------------------------------------------------------------

Gdiplus::Color TColorToGdiplusColor( TColor Val )
{
    return Gdiplus::Color(
        ( Val >> 24 ) & 0xFF, Val & 0xFF, ( Val >> 8 ) & 0xFF, ( Val >> 16 ) & 0xFF
    );
}
//---------------------------------------------------------------------------

Gdiplus::Color TColorToGdiplusColor( TColor Val, BYTE Alpha )
{
    return Gdiplus::Color(
        Alpha, Val & 0xFF, ( Val >> 8 ) & 0xFF, ( Val >> 16 ) & 0xFF
    );
}
//---------------------------------------------------------------------------

StringAlignment AlignmentToGdiplusStringAlignment( TAlignment Val )
{
    switch ( Val ) {
        case taLeftJustify:
            return StringAlignmentNear;
        case taRightJustify:
            return StringAlignmentFar;
        case taCenter:
            return StringAlignmentCenter;
    }
    return StringAlignmentCenter;
}
//---------------------------------------------------------------------------

StringAlignment VerticalAlignmentToGdiplusStringAlignment( TVerticalAlignment Val )
{
    switch ( Val ) {
        case taAlignTop:
            return StringAlignmentNear;
        case taAlignBottom:
            return StringAlignmentFar;
        case taVerticalCenter:
            return StringAlignmentCenter;
    }
    return StringAlignmentCenter;
}
//---------------------------------------------------------------------------

void DrawImage( Gdiplus::Graphics& g, Gdiplus::Image& Img, Gdiplus::RectF const & DstRect,
                BYTE AlphaBlend, bool Stretched, bool MantainAspectRatio )
{
    ImageAttributes imgAttrs;

    ImageAttributes* pImgAttrs = 0; //&imgAttrs;

    // Con GDI+ 1.0, quelle di XP per intenderci, se si applicano
    // gli attributi ad una immagine (Gdiplus::ImageAttributes), il metodo
    // Graphics::DrawImage se ne sbatte dell'ultima chiamata al metodo
    // Image::SelectActiveFrame ed usa sempre il frame 0. Quindi, se si
    // vogliono far funzionare - ad esempio - le multigif, si deve evitare
    // di applicare i suddetti attributi, passando pImgAttrs == null al metodo
    // Graphics::DrawImage utilizzato pi� in basso. Siccome gli attributi -
    // in questa applicazione - si usano solo per generare la traslucenza
    // (alphablend), se quest'ultima non � necessaria, si passa null come
    // pImgAttrs. Con GDI+ 1.1 questo problema sembra non esistere (su seven,
    // ad esempio, che come Vista ha le 1.1, funziona a dovere).
    // Morale: se si vogliono vedere le gif animate su XP non si deve dare
    // la trasparenza alle immagini

    if ( AlphaBlend < 255 ) {
        static ColorMatrix const UnityColMat = {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        ColorMatrix ColMat( UnityColMat );

        ColMat.m[3][3] = (float)AlphaBlend / 255.0;

        imgAttrs.SetColorMatrix( &ColMat, ColorMatrixFlagsDefault, ColorAdjustTypeDefault );

        pImgAttrs = &imgAttrs;

    }

    float ImgWidth = Img.GetWidth();
    float ImgHeight = Img.GetHeight();

    if ( Stretched || MantainAspectRatio ) {
        float DstWidth = DstRect.Width;
        float DstHeight = DstRect.Height;
        if ( MantainAspectRatio && ImgWidth > 0 && ImgHeight > 0 && DstWidth > 0 && DstHeight > 0 ) {
            float const Rs = ImgWidth / ImgHeight;
            float const Rd = DstWidth / DstHeight;

            String Msg;

            float NewDstWidth;
            float NewDstHeight;
            float DX = DstRect.GetLeft();
            float DY = DstRect.GetTop();
            float k = Rs / Rd;

            if ( Rs > Rd ) {
                NewDstWidth = DstWidth;
                NewDstHeight = DstHeight / k;

                DY += ( DstHeight - NewDstHeight ) / 2.0F;
            }
            else if ( Rs < Rd ) {
                NewDstWidth = DstWidth * k;
                NewDstHeight = DstHeight;

                DX += ( DstWidth - NewDstWidth ) / 2.0F;

            }
            else {
                NewDstWidth = DstWidth;
                NewDstHeight = DstHeight;
            }

            Gdiplus::RectF DRect( DX, DY, NewDstWidth, NewDstHeight );

            g.DrawImage(
                &Img, DRect, 0.0F, 0.0F, ImgWidth, ImgHeight,
                Gdiplus::UnitPixel, pImgAttrs, 0, 0
            );

        }
        else
            g.DrawImage(
                &Img, DstRect, 0.0F, 0.0F, ImgWidth, ImgHeight,
                Gdiplus::UnitPixel, pImgAttrs, 0, 0
            );
    }
    else {
        Gdiplus::RectF DRect( DstRect.GetLeft(), DstRect.GetTop(), ImgWidth, ImgHeight );
        g.DrawImage(
            &Img, DRect, 0.0F, 0.0F, ImgWidth, ImgHeight,
            Gdiplus::UnitPixel, pImgAttrs, 0, 0
        );
    }
}
//---------------------------------------------------------------------------

Gdiplus::RectF VCLRectToGdiPlusRectF( TRect const & Rect )
{
    return Gdiplus::RectF(
        static_cast<float>( Rect.Left ),
        static_cast<float>( Rect.Top ),
        static_cast<float>( Rect.Width() ),
        static_cast<float>( Rect.Height() )
    );
/*
    return RectF(
        static_cast<float>( Rect.Left ),
        static_cast<float>( Rect.Top ),
        static_cast<float>( Rect.Width() - 1 ),
        static_cast<float>( Rect.Height() - 1 )
    );
*/
}
//---------------------------------------------------------------------------

void GetEncoderClsid( WCHAR const * Format, CLSID* Clsid )
{
    UINT Num = 0;
    UINT Size = 0;

    GdiplusCheck( GetImageEncodersSize( &Num, &Size ) );

    if ( Size == 0 )
        throw Exception( "GetImageEncodersSize() failure!" );

    vector<char> ImageCodecInfoBuffer( Size );

    ImageCodecInfo* const ImgCodecInfo =
        reinterpret_cast<ImageCodecInfo*>( &ImageCodecInfoBuffer[0] );

    GdiplusCheck( GetImageEncoders( Num, Size, ImgCodecInfo ) );

    for ( UINT j = 0 ; j < Num ; ++j )
       if ( !wcscmp( ImgCodecInfo[j].MimeType, Format ) ) {
           *Clsid = ImgCodecInfo[j].Clsid;
           break;
       }
}
//---------------------------------------------------------------------------

Gdiplus::Image* LoadImageFromStream( TStream* Stream, String MimeType )
{
    // Se non si memorizza la stream l'immagine si perde
    TStreamAdapter* const SA = new TStreamAdapter( Stream, soReference );

    //TRaii<TStreamAdapter,&TStreamAdapter::_AddRef,&TStreamAdapter::_Release>
    //const RefCountManager( *SA );
    struct TRefCountManager {
        TRefCountManager( TStreamAdapter& SA )
           : sa_{ SA } { sa_._AddRef(); }
        ~TRefCountManager() {
            try {
                sa_._Release();
            }
            catch ( ... ) {
            }
        }
        TStreamAdapter& sa_;
    }
    RefCountManager( *SA );

    CLSID ClassID;
    GetEncoderClsid( MimeType.c_str(), &ClassID );
    _di_IStream istream = SA->operator _di_IStream();

    auto i = make_unique<Gdiplus::Image>( istream );
    Gdiplus::SizeF Size;
    i->GetPhysicalDimension( &Size );
    auto_ptr<Gdiplus::Bitmap> Bmp( new Gdiplus::Bitmap( Size.Width, Size.Height ) );
    Gdiplus::Graphics g( Bmp.get() );
    g.DrawImage( i.get(), 0, 0 );
    return Bmp.release();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
} // End of namespace GdiplusUtils
//---------------------------------------------------------------------------




