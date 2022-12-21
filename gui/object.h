
#pragma once

#include "common/geometry.h"
#include "common/str.h"


class CObject{
protected:

public:

	static HWND hWnd_Proc;
	static UINT Msg_Proc;
	static WPARAM Wp_Proc;
	static LPARAM Lp_Proc;
	static HINSTANCE hInstance;
	static HWND hWndParent;
	static int gID;

	HWND hWnd;
	int ID;

	static void SetHWND( const CObject &Parent );
	static void SetHWND();

	CObject();
	bool IsOk() const;
	bool Create( const CStr &ClassName , const CRect &rc , const CStr &Caption , DWORD Style , DWORD ExStyle , int ID , LPVOID lpParam );

	void SetCaption( const CStr &Caption );
	void GetCaption( CStr *Caption );

	bool SetVisible( bool bVisible );
	bool SetEnable( bool bEnable );
	bool SetVisible();
	bool SetEnable();
	bool IsVisible();
	bool IsEnable();

	void SetFocus();
	bool IsActive();

	void SetRect( const CRect &rc );
	CRect GetRect();
	CRect GetClientRect();
	CSize GetSize();

	// Event
	bool IsMsg( UINT Msg );
	bool IsDrag( CStr *pFileName );
};

////////////////////////////////////

class CDialog :public CObject{
private:
	PAINTSTRUCT ps;
	bool PaintFlag;
	HDC hdc;
public:
	CDialog();
	~CDialog();
	bool Create( const CStr &ClassName , const CRect &rc , const CStr &Caption , DWORD Style , DWORD ExStyle );

	HDC BeginPaint();
	HDC GetHDC();
	void EndPaint();

	bool SetMenu( const CStr &ClassName );
	bool SetPopUp( const CStr &ClassName , int No = 0 );
	// Event
	bool IsMenu( int ID );

	bool IsLButtonDown( CPoint *pt = NULL );
	bool IsRButtonDown( CPoint *pt = NULL );
	bool IsMButtonDown( CPoint *pt = NULL );
	bool IsLButtonUp( CPoint *pt = NULL );
	bool IsRButtonUp( CPoint *pt = NULL );
	bool IsMButtonUp( CPoint *pt = NULL );
	bool IsLButton( CPoint *pt = NULL );
	bool IsRButton( CPoint *pt = NULL );
	bool IsMButton( CPoint *pt = NULL );
	bool IsMove( CPoint *pt = NULL );
	bool IsDestroy();
	bool IsPaint();
	bool IsSizeChange();
	
};

//////////////////////////////////////////

class CChildObject :public CObject{
protected:

public:
	CChildObject();

	bool Create( const CStr &ClassName , const CRect &rc , const CStr &Caption , DWORD Style , DWORD ExStyle , LPVOID lpParam );
	bool IsCommand();
	bool IsCommand( int CommandID );

	CRect GetRect();
};


//////////////////////////////////////////



