//---------------------------------------------------------------------------

#ifndef ExceptUtilsH
#define ExceptUtilsH

#include <System.hpp>

#define EXCEPTUTILS_MAKE_EXCEPTION_CLASS( name, base ) \
class name : public base \
{ \
	typedef base inherited; \
public: \
	__fastcall name(const System::UnicodeString Msg) : base(Msg) { } \
	__fastcall name(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : base(Msg, Args, Args_Size) { } \
	__fastcall name(int Ident)/* overload */ : base(Ident) { } \
	__fastcall name(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : base(Ident, Args, Args_Size) { } \
	__fastcall name(const System::UnicodeString Msg, int AHelpContext) : base(Msg, AHelpContext) { } \
	__fastcall name(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : base(Msg, Args, Args_Size, AHelpContext) { } \
	__fastcall name(int Ident, int AHelpContext)/* overload */ : base(Ident, AHelpContext) { } \
	__fastcall name(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : base(ResStringRec, Args, Args_Size, AHelpContext) { } \
	__fastcall virtual ~name(void) { } \
};

extern String FormatExceptionErrorMessage( System::TObject* ExceptObject, void * ExceptAddr );

//---------------------------------------------------------------------------
#endif
