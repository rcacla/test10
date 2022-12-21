

#pragma once

#pragma comment(lib,"comctl32.lib")

#include "gui/object.h"
#include <commctrl.h>    //コモンコントロールのため必要
#include "common\bmp.h"

class CGroupBox :public CChildObject{
private:

public:
	CGroupBox();
	bool Create( const CRect &rc , const CStr &Caption , DWORD Style = WS_VISIBLE );

};

//////////////////////////////////////////
class CButton :public CChildObject{
private:

public:
	CButton();
	bool Create( const CRect &rc , const CStr &Caption , DWORD Style = WS_VISIBLE );

	bool IsClicked();
	void SetClick();
};

//////////////////////////////////////////

class CCheckBox :public CChildObject{
private:

public:
	CCheckBox();
	bool Create( const CRect &rc , const CStr &Caption , DWORD Style = WS_VISIBLE );
	
	bool IsChecked();
	void SetCheck( bool Flag );
	void SetCheck();
};

///////////////////////////////////////////////////////

class CRadioButton :public CChildObject{
private:

public:
	CRadioButton();
	bool Create( const CRect &rc , const CStr &Caption , bool Group = false , DWORD Style = WS_VISIBLE );

	bool IsChecked();
	void SetCheck( bool Flag );
	void SetCheck();
};

////////////////////////////////////////////////////////////

class CLabel :public CChildObject{
private:

public:
	CLabel();
	bool Create( const CRect &rc , const CStr &Caption , DWORD Style = WS_VISIBLE );

};

////////////////////////////////////////////////////////////

class CEdit :public CChildObject{
private:

public:
	CEdit();
	bool Create( const CRect &rc , const CStr &Caption , DWORD Style = WS_VISIBLE );

	void DrawText( const CStr &nText );
	void GetText( CStr *nText );

	bool IsChange();
	bool IsUpdate();
	
};

////////////////////////////////////////////////////////////

class CListBox :public CChildObject{
private:

public:
	CListBox();
	bool Create( const CRect &rc , DWORD Style = WS_VISIBLE );

	void Clear();
	void Delete();

	bool SetIndex( int Index );
	bool SetIndex_ItemNo( int ItemNo );
	void Set( int ItemNo , const CStr &nString );
	bool Insert( int ItemNo , const CStr &nString );
	void SetReDraw( bool Flag );

	int GetCount();
	int GetIndex();
	bool GetItem( int *ItemNo );
	bool GetItem( CStr *nString );

	void operator += ( const CStr &nString );
	void operator = ( const CVector< CStr > &vString );
	void operator = ( const CVector< CPair< int , CStr > > &v );
};

////////////////////////////////////////////////////////////

class CComboBox :public CChildObject{
private:

public:
	CComboBox();
	bool Create( const CRect &rc , DWORD Style = WS_VISIBLE );

	void Clear();
	void Delete();

	bool SetIndex( int Index );
	bool SetIndex_ItemNo( int ItemNo );
	void Set( int ItemNo , const CStr &nString );
	bool Insert( int ItemNo , const CStr &nString );

	int GetCount();
	int GetIndex();
	bool GetItem( int *ItemNo );
	bool GetItem( CStr *nString );

	void operator += ( const CStr &nString );
	void operator = ( const CVector< CStr > &vString );
	void operator = ( const CVector< CPair< int , CStr > > &v );
};

////////////////////////////////////////////////////////////

class CScrollBar :public CChildObject{
private:
	SCROLLINFO Info;
	CLabel *Label;
public:
	CScrollBar();
	bool Create( const CRect &rc , bool HFlag = true , DWORD Style = WS_VISIBLE );

	int GetValue();
	CRange GetRange();
	int GetPage();

	void SetValue( int x );
	void SetRange( const CRange &Rn );
	void SetPage( int x );
	void SetLabel( CLabel *Label );

	bool IsScroll();
	bool Execute();
};

////////////////////////////////////////////////////////////

class CTrackBar :public CChildObject{
private:
	CRange Rn;
	CLabel *Label;
public:
	CTrackBar();
	bool Create( const CRect &rc , DWORD Style = WS_VISIBLE );

	int GetValue();
	void SetValue( int x );
	void SetRange( const CRange &Rn );
	void SetPage( int x );
	void SetLabel( CLabel *Label );

	bool IsScroll();
	bool Execute();

};

////////////////////////////////////////////////////////////

class CTabControl :public CChildObject{
private:
	int Index;
public:
	CTabControl();
	bool Create( const CRect &rc , DWORD Style = WS_VISIBLE );
	int GetIndex();
	bool IsSelect();
	void operator += ( const CStr &nString );
};

////////////////////////////////////////////////////////////

class CPicture :public CChildObject{
private:
public:
	CPicture();
	bool Create( const CRect &rc , DWORD Style = WS_VISIBLE );
	bool DrawImage( const CBmp &nBmp );
};

//////////////////////////////////////////////////////////////

class CTreeControl :public CChildObject{
private:
public:
	CTreeControl();
	bool Create( const CRect &rc , DWORD Style = WS_VISIBLE );

	// TVI_FIRST  TVI_LAST  TVI_SORT
	HTREEITEM SetItem( HTREEITEM hTree , const CStr &Item , HTREEITEM InsertFlag = TVI_LAST );
	void Delete( HTREEITEM hTree );
	bool SetString( HTREEITEM hTree , const CStr &nText );

	int GetCount();
	bool GetString( CStr *nText , HTREEITEM hTree );
	HTREEITEM GetItemSelect();
	HTREEITEM GetItemParent( HTREEITEM hTree );
};

/////////////////////////////////////////////////////////////

class CFileControl{
private:
	OPENFILENAMEW ofn;
	CStr FilterFile;
	wchar_t strFile[ MAX_PATH ];
public:
	CFileControl();
	void SetOwner();
	void SetOwner( const CDialog &nDlg );
	void SetFilter( const CVector< CPair< CStr , CStr > > &vFilter );
	bool GetOpen( CStr *nDest );
	bool GetSave( CStr *nDest );
};


