
#pragma warning(disable:4800)

#include "gui/object.h"

HWND CObject::hWnd_Proc;
UINT CObject::Msg_Proc;
WPARAM CObject::Wp_Proc;
LPARAM CObject::Lp_Proc;
HINSTANCE CObject::hInstance;
HWND CObject::hWndParent = NULL;
int CObject::gID = 0;

void CObject::SetHWND( const CObject &Parent ){
	hWndParent = Parent.hWnd;
}

void CObject::SetHWND(){
	hWndParent = NULL;
}

CObject::CObject(){
	hWnd = NULL;
}

bool CObject::IsOk() const{
	return hWnd != NULL;
}

bool CObject::Create( const CStr &ClassName , const CRect &rc , const CStr &Caption , DWORD Style , DWORD ExStyle , int ID , LPVOID lpParam ){

	if( IsOk() )
		return false;

	if( hWndParent == NULL ){
		hWnd = ::CreateWindowExW( ExStyle , ClassName.p , Caption.p , Style , rc.left , rc.top , rc.right - rc.left , rc.bottom - rc.top , NULL , ( HMENU ) ID , hInstance , lpParam );
	}else{
		hWnd = ::CreateWindowExW( ExStyle , ClassName.p , Caption.p , Style , rc.left , rc.top , rc.right - rc.left , rc.bottom - rc.top , hWndParent , ( HMENU ) ID , hInstance , lpParam );
	}

	return hWnd != NULL;
}

void CObject::SetCaption( const CStr &Caption ){
	::SetWindowTextW( hWnd , Caption.p );
}

void CObject::GetCaption( CStr *Caption ){
	wchar_t c[ 256 ];

	::GetWindowTextW( hWnd , &c[ 0 ] , 256 );
	*Caption = c;
}

bool CObject::SetVisible( bool bVisible ){
	int CmdShow;
	if( bVisible ){
		CmdShow = SW_SHOW;
	}else{
		CmdShow = SW_HIDE;
	}
	return ::ShowWindow( hWnd , CmdShow );
}

bool CObject::SetEnable( bool bEnable ){
	return ::EnableWindow( hWnd , bEnable );
}

bool CObject::SetVisible(){
	return SetVisible( !IsVisible() );
}

bool CObject::SetEnable(){
	return SetEnable( !IsEnable() );
}

bool CObject::IsVisible(){
	return ::IsWindowVisible( hWnd );
}

bool CObject::IsEnable(){
	return ::IsWindowEnabled( hWnd );
}

void CObject::SetFocus(){
	::SetFocus( hWnd );
}

bool CObject::IsActive(){
	WINDOWINFO Info;

	::GetWindowInfo( hWnd , &Info );

	return Info.dwWindowStatus == 1;
}

void CObject::SetRect( const CRect &rc ){
	::SetWindowPos( hWnd , HWND_TOP , rc.left , rc.top , rc.right - rc.left , rc.bottom - rc.top , SWP_ASYNCWINDOWPOS );
}

CRect CObject::GetRect(){
	RECT RC;
	::GetWindowRect( hWnd , &RC );
	return CRect( RC );
}

CRect CObject::GetClientRect(){
	RECT RC;
	::GetClientRect( hWnd , &RC );
	return CRect( RC );
}

CSize CObject::GetSize(){
	RECT RC;
	CSize sz;

	::GetClientRect( hWnd , &RC );
	sz.Set( RC.right , RC.bottom );

	return sz;
}

// Event

bool CObject::IsMsg( UINT Msg ){
	return ( hWnd_Proc == hWnd ) && ( Msg_Proc == Msg );
}

bool CObject::IsDrag( CStr *pFileName ){

	if( !IsMsg( WM_DROPFILES ) ){ return false; }

	HDROP hDrop = (HDROP) Wp_Proc;
	if( 1 != DragQueryFile( hDrop, 0xFFFFFFFF, NULL, 0 ) ){ return false; }

	char acFileName[256];
	DragQueryFileA( hDrop, 0, acFileName, sizeof( acFileName ) );

	*pFileName = acFileName;
	return true;
}

///////////////////////////////////////

CDialog::CDialog(){

}

CDialog::~CDialog(){
}

bool CDialog::Create( const CStr &ClassName , const CRect &rc , const CStr &Caption , DWORD Style , DWORD ExStyle ){
	return CObject::Create( ClassName , rc , Caption , Style , ExStyle , NULL , NULL );
}

HDC CDialog::BeginPaint(){
	PaintFlag = true;
	return ::BeginPaint( hWnd , &ps );
}

HDC CDialog::GetHDC(){
	PaintFlag = false;
	hdc = ::GetDC( hWnd );
	return hdc;
}

void CDialog::EndPaint(){
	if( PaintFlag ){
		::EndPaint( hWnd , &ps );
	}else{
		ReleaseDC( hWnd , hdc );
	}
}

bool CDialog::SetMenu( const CStr &ClassName ){
	return ( bool ) ::SetMenu( hWnd , ::LoadMenuW( CObject::hInstance , ClassName.p ) );
}

bool CDialog::SetPopUp( const CStr &ClassName , int No ){
	POINT pt;
	pt.x = LOWORD( Lp_Proc );
	pt.y = HIWORD( Lp_Proc );
	::ClientToScreen( hWnd , &pt );
	if( !::TrackPopupMenu( ::GetSubMenu( ::LoadMenuW( hInstance , ClassName.p ) , No ) , TPM_LEFTALIGN | TPM_TOPALIGN , pt.x , pt.y , 0 , hWnd , NULL ) )
		return false;
	return true;
}

// Event

bool CDialog::IsMenu( int ID ){
	return ( hWnd_Proc == hWnd ) && ( Msg_Proc == WM_COMMAND ) && ( LOWORD( Wp_Proc ) == ID );
}

bool CDialog::IsLButtonDown( CPoint *pt ){
	if( !IsMsg( WM_LBUTTONDOWN ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsRButtonDown( CPoint *pt ){
	if( !IsMsg( WM_RBUTTONDOWN ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsMButtonDown( CPoint *pt ){
	if( !IsMsg( WM_MBUTTONDOWN ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsLButtonUp( CPoint *pt ){
	if( !IsMsg( WM_LBUTTONUP ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsRButtonUp( CPoint *pt ){
	if( !IsMsg( WM_RBUTTONUP ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsMButtonUp( CPoint *pt ){
	if( !IsMsg( WM_MBUTTONUP ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsLButton( CPoint *pt ){
	if( hWnd_Proc != hWnd )
		return false;
	if( Wp_Proc!= MK_LBUTTON )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsRButton( CPoint *pt ){
	if( hWnd_Proc != hWnd )
		return false;
	if( Wp_Proc != MK_RBUTTON )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsMButton( CPoint *pt ){
	if( hWnd_Proc != hWnd )
		return false;
	if( Wp_Proc != MK_MBUTTON )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsMove( CPoint *pt ){
	if( !IsMsg( WM_MOUSEMOVE ) )
		return false;
	if( pt != NULL ){
		pt->Set( LOWORD( Lp_Proc ) , HIWORD( Lp_Proc ) );
	}
	return true;
}

bool CDialog::IsDestroy(){
	return IsMsg( WM_DESTROY );
}

bool CDialog::IsPaint(){
	return IsMsg( WM_PAINT );
}

bool CDialog::IsSizeChange(){
	return IsMsg( WM_SIZE );
}



///////////////////////////////////////////////////////////////

CChildObject::CChildObject(){

}

bool CChildObject::Create( const CStr &ClassName , const CRect &rc , const CStr &Caption , DWORD Style , DWORD ExStyle , LPVOID lpParam ){
	gID++;
	ID = gID;
	return CObject::Create( ClassName , rc , Caption , Style , ExStyle , ID , NULL );
}

bool CChildObject::IsCommand(){
	return LOWORD( Wp_Proc ) == ID && Msg_Proc == WM_COMMAND;
}

bool CChildObject::IsCommand( int CommandID ){
	return LOWORD( Wp_Proc ) == ID && Msg_Proc == WM_COMMAND && HIWORD( Wp_Proc ) == CommandID;
}

CRect CChildObject::GetRect(){
	WINDOWINFO Info;
	HWND hWnd_Parent = ::GetParent( hWnd );
	CRect rc;
	RECT RC0 , RC1;
	int w , h;

	::GetWindowInfo( hWnd_Parent , &Info );
	::GetWindowRect( hWnd_Parent , &RC0 );
	::GetWindowRect( hWnd , &RC1 );

	w = RC0.left + Info.cxWindowBorders;
	h = RC0.top + ::GetSystemMetrics( SM_CYMENU ) + Info.cyWindowBorders;

	rc.Set( RC1.left - w , RC1.top - h , RC1.right - w , RC1.bottom - h );

	return rc;
}

//////////////////////////////////////////

