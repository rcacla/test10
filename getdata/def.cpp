


#include "main.h"

int CMain( const CVector< CStr > &vArg, const CMap< CStr, CStr > &mArg );

int CMainPre( HINSTANCE hInstance, const CVector< CStr > &vArg ){

	CVector< CStr > vTmpArg, vTmp;
	CMap< CStr, CStr > mArg;

	locale::global( locale( "japanese" ) );

	CTable::Init();
	Init_Random();
	Init_Angle();
	::srand( ( unsigned int ) time( NULL ) );

	int szArg = vArg.GetSize();
	int stArg = 0;
	
	if( szArg >= 1 ){
		if( Load( &mArg, vArg[0] ) ){
			stArg = 1;
		}
	}
	
	CRgz Rgz = "^-{.+?}:{.*}";

	for( int i = stArg; i < szArg; i++ ){
		
		if( ::IsString( NULL, &vTmp, vArg[i], Rgz ) ){
			mArg.Set( vTmp[0], vTmp[1] );
		}else{
			vTmpArg += vArg[i];
		}

	}

	return CMain( vTmpArg, mArg );

}


int main( int Argc, char **Argv ){

	CVector< CStr > vArg;

	for( int i = 1; i < Argc; i++ ){
		vArg += Argv[i];
	}

	HINSTANCE hInstance = ( HINSTANCE ) GetModuleHandle( NULL );

	return CMainPre( hInstance, vArg );
	
}

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow ){

	// コンソールの引数と同様の形にする
	
	CStr Text = lpCmdLine;

	{
		wchar_t c_space = L' ';
		wchar_t c_tab = L'\t';
		wchar_t c_str = L'"';
		wchar_t c_rep = L'ж';

		int sz = Text.GetSize();
		bool strFlag = false;
		bool spFlag = false;
		wchar_t *p = Text.p;

		CVector< CPair< int , int > > vIndex;

		for( int i = 0; i < sz; i++ ){

			if( *p == c_str ){
				vIndex += CPair< int, int >( i, i );
				strFlag = !strFlag;
			}
			if( *p != c_space ){ spFlag = false; }

			if( !strFlag ){
				if( *p == c_tab ){
					*p = c_space;
				}
				if( spFlag ){
					if( *p == c_space ){
						vIndex += CPair< int, int >( i, i );
					}
				}else{
					if( *p == c_space ){
						*p = c_rep;
					}
				}
			}

			if( *p == c_rep ){ spFlag = true; }

			p++;
		}

		Text.Erase( vIndex );

	}

	CVector< CStr > vArg;
	CRgz Rgz = "({.+?}ж)*{.+}";

	if( !::IsString( NULL, &vArg, Text, Rgz ) ){
	}

	return CMainPre( hInstance, vArg );
}



