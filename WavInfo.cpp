//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

#include <memory>

#include "WavInfo.h"

using std::make_unique;

//---------------------------------------------------------------------------
#pragma package(smart_init)

WavInfo::WavInfo( String FileName )
{
    auto FS = make_unique<TFileStream>( FileName, fmOpenRead, fmShareDenyNone );
    if ( FS->Read( &wh_, sizeof wh_ ) < sizeof wh_ ) {
        RaiseInvalidFileFormat( FileName );
    }
    if ( wh_.AudioFormat != 1 ) {
        RaiseInvalidFileFormat( FileName );
    }
//    fileSize_ = FS->Size;
}
//---------------------------------------------------------------------------

void WavInfo::RaiseInvalidFileFormat( String FileName )
{
    throw Exception( _T( "Invalid file format (%s)" ), ARRAYOFCONST( ( FileName ) ) );
}
//---------------------------------------------------------------------------

double WavInfo::GetDuration() const
{
    return static_cast<double>( wh_.Subchunk2Size ) * 8 /
           wh_.bitsPerSample / wh_.NumOfChan / wh_.SamplesPerSec;

}
//---------------------------------------------------------------------------
