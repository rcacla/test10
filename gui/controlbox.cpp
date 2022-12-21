
#pragma warning(disable:4800)

#include "gui/controlbox.h"

CGroupBox::CGroupBox(){
}

bool CGroupBox::Create( const CRect &rc , const CStr &Caption , DWORD Style ){
	return CChildObject::Create( "BUTTON" , rc , Caption , Style | WS_CHILD | BS_GROUPBOX , NULL , NULL );
}

//////////////////////////////////////////

CButton::CButton(){
}

bool CButton::Create( const CRect &rc , const CStr &Caption , DWORD Style ){
	return CChildObject::Create( "BUTTON" , rc , Caption , Style | WS_CHILD | BS_PUSHBUTTON , NULL , NULL );
}

bool CButton::IsClicked(){
	return IsCommand( BN_CLICKED );
}

void CButton::SetClick(){
	::SendMessageW( hWnd , BM_CLICK , 0 , 0 );
}

////////////////////////////////////////////////////////

CCheckBox::CCheckBox(){
}

bool CCheckBox::Create( const CRect &rc , const CStr &Caption , DWORD Style ){
	return CChildObject::Create( "BUTTON" , rc , Caption , Style | WS_CHILD | BS_AUTOCHECKBOX , NULL , NULL );
}

bool CCheckBox::IsChecked(){
	return ::SendMessageW( hWnd , BM_GETCHECK , 0 , 0 ) == BST_CHECKED ;
}

void CCheckBox::SetCheck( bool Flag ){
	int bCheck = BST_UNCHECKED;

	if( Flag )
		bCheck = BST_CHECKED;
	::SendMessageW( hWnd , BM_SETCHECK , ( WPARAM ) bCheck , 0 );
}

void CCheckBox::SetCheck(){
	SetCheck( !IsChecked() );
}


/////////////////////////////////////////////////////////////

CRadioButton::CRadioButton(){
}

bool CRadioButton::Create( const CRect &rc , const CStr &Caption , bool Group , DWORD Style ){
	DWORD x = 0;
	if( Group )
		x = WS_GROUP;
	return CChildObject::Create( "BUTTON" , rc , Caption , Style | WS_CHILD | BS_AUTORADIOBUTTON | x , NULL , NULL );
}

bool CRadioButton::IsChecked(){
	return ::SendMessageW( hWnd , BM_GETCHECK , 0 , 0 ) == BST_CHECKED;
}

void CRadioButton::SetCheck( bool Flag ){
	int bCheck = BST_UNCHECKED;

	if( Flag )
		bCheck = BST_CHECKED;
	::SendMessageW( hWnd , BM_SETCHECK , ( WPARAM ) bCheck , 0 );
}

void CRadioButton::SetCheck(){
	SetCheck( !IsChecked() );
}

/////////////////////////////////////////////////////////////

CLabel::CLabel(){
}

bool CLabel::Create( const CRect &rc , const CStr &Caption , DWORD Style ){
	return CChildObject::Create( "STATIC" , rc , Caption , Style | WS_CHILD , NULL , NULL );
}

/////////////////////////////////////////////////////////////

CEdit::CEdit(){
}

bool CEdit::Create( const CRect &rc , const CStr &Caption , DWORD Style ){

	CStr Text;
	::Replace( &Text , Caption , "\n" , "\r\n" );

	return CChildObject::Create( "EDIT" , rc , Text , Style | WS_CHILD , WS_EX_CLIENTEDGE , NULL );
}

void CEdit::DrawText( const CStr &nText ){
	CStr Text;
	::Replace( &Text , nText , "\n" , "\r\n" );

	::SetWindowTextW( hWnd , Text.p );

}

void CEdit::GetText( CStr *nText ){
	int N = ::GetWindowTextLengthW( hWnd );
	nText->Create( N );

	::GetWindowTextW( hWnd , nText->p , N + 1 );
	nText->Replace( "\r\n" , "\n" );
}

bool CEdit::IsChange(){
	return IsCommand( EN_CHANGE );
}

bool CEdit::IsUpdate(){
	return IsCommand( EN_UPDATE );
}

/////////////////////////////////////////////////////////////

CListBox::CListBox(){
}

bool CListBox::Create( const CRect &rc , DWORD Style ){
	return CChildObject::Create( "LISTBOX" , rc , "" , Style | WS_CHILD  | WS_VSCROLL | LBS_NOTIFY , WS_EX_CLIENTEDGE , NULL );
}

void CListBox::Clear(){
	::SendMessageW( hWnd , LB_RESETCONTENT , 0 , 0 );
}

void CListBox::Delete(){
	::SendMessageW( hWnd , LB_DELETESTRING , ( WPARAM ) GetIndex() , 0 );
}

bool CListBox::SetIndex( int Index ){
	return ::SendMessageW( hWnd , LB_SETCURSEL , ( WPARAM ) Index , 0 ) != LB_ERR;
}

bool CListBox::SetIndex_ItemNo( int ItemNo ){
	int i , sz = GetCount();

	for( i = 0; i < sz; i++ ){
		if( ItemNo == ( int ) ::SendMessageW( hWnd , LB_GETITEMDATA , ( WPARAM ) i , 0 ) ){
			SetIndex( i );
			return true;
		}
	}
	return false;
}

void CListBox::Set( int ItemNo , const CStr &nString ){
	int Index = GetCount();
	::SendMessageW( hWnd , LB_INSERTSTRING , ( WPARAM ) Index , ( LPARAM ) nString.p );
	::SendMessageW( hWnd , LB_SETITEMDATA , ( WPARAM ) Index , ( LPARAM ) ItemNo );
}

bool CListBox::Insert( int ItemNo , const CStr &nString ){
	int Index = GetIndex();

	::SendMessageW( hWnd , LB_INSERTSTRING , ( WPARAM ) Index , ( LPARAM ) nString.p );
	::SendMessageW( hWnd , LB_SETITEMDATA , ( WPARAM ) Index , ( LPARAM ) ItemNo );
	return true;
}

void CListBox::SetReDraw( bool Flag ){
	::SendMessageW( hWnd , WM_SETREDRAW , ( WPARAM ) Flag , 0 );
}

int CListBox::GetCount(){
	return ( int ) ::SendMessageW( hWnd , LB_GETCOUNT , 0 , 0 );
}

int CListBox::GetIndex(){
	return ( int ) ::SendMessageW( hWnd , LB_GETCURSEL , 0 , 0 );
}

bool CListBox::GetItem( int *ItemNo ){
	int Index = GetIndex();
	if( Index == -1 )
		return false;
	*ItemNo = ( int ) ::SendMessageW( hWnd , LB_GETITEMDATA , ( WPARAM ) Index , 0 );
	return true;
}

bool CListBox::GetItem( CStr *nString ){
	int Index = GetIndex();
	if( Index == -1 )
		return false;
	nString->Create( SendMessageW( hWnd , LB_GETTEXTLEN  , 0 , 0 ) );
	SendMessageW( hWnd , LB_GETTEXT , ( WPARAM ) Index , ( LPARAM ) nString->p );

	return true;
}

void CListBox::operator += ( const CStr &nString ){
	::SendMessageW( hWnd , LB_INSERTSTRING , GetCount() , ( LPARAM ) nString.p );
}

void CListBox::operator = ( const CVector< CStr > &vString ){
	int i , sz = vString.GetSize();
	
	Clear();
	for( i = 0; i < sz; i++ ){
		::SendMessageW( hWnd , LB_INSERTSTRING , i , ( LPARAM ) vString.p[ i ].p );
	}
}

void CListBox::operator = ( const CVector< CPair< int , CStr > > &v ){
	int i , sz = v.GetSize();
	
	Clear();
	for( i = 0; i < sz; i++ ){
		::SendMessageW( hWnd , LB_INSERTSTRING , i , ( LPARAM ) v.p[ i ].y.p );
		::SendMessageW( hWnd , LB_SETITEMDATA ,i , ( LPARAM ) v.p[ i ].x );
	}
}

////////////////////////////////////////

CComboBox::CComboBox(){
}

bool CComboBox::Create( const CRect &rc , DWORD Style ){
	return CChildObject::Create( "COMBOBOX" , rc , "" , Style | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL , NULL , NULL );
}

void CComboBox::Clear(){
	::SendMessageW( hWnd , CB_RESETCONTENT , 0 , 0 );
}

void CComboBox::Delete(){
	::SendMessageW( hWnd , CB_DELETESTRING , ( WPARAM ) GetIndex() , 0 );
}

bool CComboBox::SetIndex( int Index ){
	return ::SendMessageW( hWnd , CB_SETCURSEL , ( WPARAM ) Index , 0 ) != LB_ERR;
}

bool CComboBox::SetIndex_ItemNo( int ItemNo ){
	int i , sz = GetCount();

	for( i = 0; i < sz; i++ ){
		if( ItemNo == ( int ) ::SendMessageW( hWnd , CB_GETITEMDATA , ( WPARAM ) i , 0 ) ){
			SetIndex( i );
			return true;
		}
	}
	return false;
}

void CComboBox::Set( int ItemNo , const CStr &nString ){
	int Index = GetCount();
	::SendMessageW( hWnd , CB_ADDSTRING , ( WPARAM ) Index , ( LPARAM ) nString.p );
	::SendMessageW( hWnd , CB_SETITEMDATA , ( WPARAM ) Index , ( LPARAM ) ItemNo );
}

bool CComboBox::Insert( int ItemNo , const CStr &nString ){
	int Index = GetIndex();
	if( Index == -1 )
		return false;
	::SendMessageW( hWnd , CB_INSERTSTRING , ( WPARAM ) Index , ( LPARAM ) nString.p );
	::SendMessageW( hWnd , CB_SETITEMDATA , ( WPARAM ) Index , ( LPARAM ) ItemNo );

	return true;
}

int CComboBox::GetCount(){
	return ( int ) ::SendMessageW( hWnd , CB_GETCOUNT , 0 , 0 );
}

int CComboBox::GetIndex(){
	return ( int ) ::SendMessageW( hWnd , CB_GETCURSEL , 0 , 0 );
}

bool CComboBox::GetItem( int *ItemNo ){
	int Index = GetIndex();
	if( Index == -1 )
		return false;
	*ItemNo = ( int ) ::SendMessageW( hWnd , CB_GETITEMDATA , ( WPARAM ) Index , 0 );
	return true;
}

bool CComboBox::GetItem( CStr *nString ){
	int Index = GetIndex();
	if( Index == -1 )
		return false;

	nString->Create( SendMessageW( hWnd , CB_GETLBTEXTLEN , 0 , 0 ) );
	SendMessageW( hWnd , CB_GETLBTEXT , ( WPARAM ) Index , ( LPARAM ) nString->p );

	return true;
}

void CComboBox::operator += ( const CStr &nString ){
	::SendMessageW( hWnd , CB_ADDSTRING , GetCount() , ( LPARAM ) nString.p );
}

void CComboBox::operator = ( const CVector< CStr > &vString ){
	int i , sz = vString.GetSize();
	
	Clear();
	for( i = 0; i < sz; i++ ){
		::SendMessageW( hWnd , CB_ADDSTRING , i , ( LPARAM ) vString.p[ i ].p );
	}
}

void CComboBox::operator = ( const CVector< CPair< int , CStr > > &v ){
	int i , sz = v.GetSize();
	
	Clear();
	for( i = 0; i < sz; i++ ){
		::SendMessageW( hWnd , CB_ADDSTRING , i , ( LPARAM ) v.p[ i ].y.p );
		::SendMessageW( hWnd , CB_SETITEMDATA ,i , ( LPARAM ) v.p[ i ].x );
	}
}

//////////////////////////////////////////////////

CScrollBar::CScrollBar(){
	Label = NULL;
}

bool CScrollBar::Create( const CRect &rc , bool HFlag , DWORD Style ){
	DWORD x = 0;
	if( HFlag )
		x = SBS_HORZ;
	else
		x = SBS_VERT;

	if( !CChildObject::Create( "SCROLLBAR" , rc , "" , Style | WS_CHILD | x , NULL , NULL ) )
		return false;

	Info.cbSize = sizeof( SCROLLINFO );
	Info.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	Info.nMin = 0;
	Info.nMax = 100;
	Info.nPage = 1;
	Info.nPos = 0;

	::SetScrollInfo( hWnd , SB_CTL , &Info , TRUE );
	return true;
}

int CScrollBar::GetValue(){
	return Info.nPos;
}

CRange CScrollBar::GetRange(){
	return CRange( Info.nMin , Info.nMax );
}

int CScrollBar::GetPage(){
	return Info.nPage;
}

void CScrollBar::SetValue( int x ){
	x = ::GetValue( x , CRange( Info.nMin , Info.nMax ) );
	Info.nPos = x;
	::SetScrollInfo( hWnd , SB_CTL , &Info , TRUE );
	if( Label != NULL ){
		CStr Text;
		Text.Set( "%d" , x );
		Label->SetCaption( Text );
	}
}

void CScrollBar::SetRange( const CRange &Rn ){
	Info.nMin = Rn.Min;
	Info.nMax = Rn.Max;
	SetValue( Rn.Min );
}

void CScrollBar::SetPage( int x ){
	Info.nPage = x;
	::SetScrollInfo( hWnd , SB_CTL , &Info , TRUE );
}

void CScrollBar::SetLabel( CLabel *Label ){
	this->Label = Label;
}

bool CScrollBar::IsScroll(){
	return ( hWnd == ( HWND ) Lp_Proc ) && ( Msg_Proc == WM_VSCROLL || Msg_Proc == WM_HSCROLL );
}

bool CScrollBar::Execute(){
	if( !IsScroll() )
		return false;
	int Msg = LOWORD( Wp_Proc );
	int x = GetValue();

	if( Msg == SB_LINELEFT ){
		x--;
	}else if( Msg == SB_LINERIGHT ){
		x++;
	}else if( Msg == SB_LEFT ){
		x = Info.nMin;
	}else if( Msg == SB_RIGHT ){
		x = Info.nMax;
	}else if( Msg == SB_PAGELEFT ){
		x -= Info.nPage;
	}else if( Msg == SB_PAGERIGHT ){
		x += Info.nPage;
	}else if( Msg == SB_THUMBPOSITION ){
		x = HIWORD( Wp_Proc );
	}else if( Msg == SB_THUMBTRACK ){
		x = HIWORD( Wp_Proc );
	}else{
		return false;
	}

	SetValue( x );

	return true;
}

////////////////////////////////////////////////////////////

CTrackBar::CTrackBar(){
	Label = NULL;
}

bool CTrackBar::Create( const CRect &rc , DWORD Style ){
	if( !CChildObject::Create( "msctls_trackbar32" , rc , "" , Style | WS_CHILD , NULL , NULL ) )
		return false;
	::SendMessageW( hWnd , 0x400 + 23 , 0 , (LPARAM) 1 );
	SetRange( CRange( 0 , 100 ) );
	SetPage( 1 );
	return true;
}

int CTrackBar::GetValue(){
	return ( int ) SendMessage( hWnd , 0x400 , 0 , 0 );
}

void CTrackBar::SetValue( int x ){
	x = ::GetValue( x , Rn );
	::SendMessageW( hWnd , 0x400 + 5 , ( WPARAM ) 1, ( LPARAM ) x );
	if( Label != NULL ){
		CStr Text;
		Text.Set( "%d" , x );
		Label->SetCaption( Text );
	}
}

void CTrackBar::SetRange( const CRange &Rn ){
	this->Rn = Rn;
	::SendMessageW( hWnd , 0x400 + 6 , ( WPARAM ) 1 , MAKELONG( Rn.Min , Rn.Max ) );
	SetValue( Rn.Min );
}

void CTrackBar::SetPage( int x ){
	::SendMessageW( hWnd , 0x400 + 21 , 0 , ( LPARAM ) x );
}

void CTrackBar::SetLabel( CLabel *Label ){
	this->Label = Label;
}

bool CTrackBar::IsScroll(){
	return hWnd == ( HWND ) Lp_Proc && Msg_Proc == WM_HSCROLL;
}

bool CTrackBar::Execute(){
	if( !IsScroll() )
		return false;
	if( Label != NULL ){
		CStr Text;
		Text.Set( "%d" , GetValue() );
		Label->SetCaption( Text );
	}
	return true;
}

/////////////////////////////////////////////////////////////

CTabControl::CTabControl(){
	Index = 0;
}

bool CTabControl::Create( const CRect &rc , DWORD Style ){
	return CChildObject::Create( "SysTabControl32" , rc , "" , Style | WS_CHILD , NULL , NULL );
}

int CTabControl::GetIndex(){
	return TabCtrl_GetCurSel( hWnd );
}

bool CTabControl::IsSelect(){
	if( !( LOWORD( Wp_Proc ) == ID && Msg_Proc == WM_NOTIFY ) )
		return false;
	return ( ( NMHDR * ) Lp_Proc )->code == TCN_SELCHANGE;
}

void CTabControl::operator += ( const CStr &nString ){
	char *tp;
	int N = ::WideCharToMultiByte( CP_ACP , 0 , nString.p , -1 , NULL , 0 , NULL , 0 );

	tp = ( char * ) malloc( N );
	::WideCharToMultiByte( CP_ACP , 0 , nString.p , -1 , tp , N , NULL , 0 );

	TCITEM tc_item;
	tc_item.mask = TCIF_TEXT;
	tc_item.pszText = tp;

	TabCtrl_InsertItem( hWnd , Index , &tc_item );
	Index++;
	free( tp );
}

//////////////////////////////////////////////////

CPicture::CPicture(){
}

bool CPicture::Create( const CRect &rc , DWORD Style ){
	return CChildObject::Create( "STATIC" , rc , "" , Style | WS_CHILD | SS_BITMAP , NULL , NULL );
}

bool CPicture::DrawImage( const CBmp &nBmp ){
	if( !nBmp.IsOk() ) return false;
	::SendMessage( hWnd , STM_SETIMAGE , ( WPARAM ) IMAGE_BITMAP, ( LPARAM ) nBmp.hBmp );
	return true;
}

//////////////////////////////////////////////////

CTreeControl::CTreeControl(){
}

bool CTreeControl::Create( const CRect &rc , DWORD Style ){
	return CChildObject::Create( WC_TREEVIEW , rc , "" , Style | WS_CHILD | WS_BORDER | WS_VSCROLL | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT , WS_EX_CLIENTEDGE , NULL );
}

HTREEITEM CTreeControl::SetItem( HTREEITEM hTree , const CStr &Item , HTREEITEM InsertFlag ){
	char *p;
	HTREEITEM hItem;
	TVINSERTSTRUCT tvi;

	int N = ::WideCharToMultiByte( CP_ACP , 0 , Item.p , -1 , NULL , 0 , NULL , 0 );
	p = ( char * ) malloc( N );
	::WideCharToMultiByte( CP_ACP , 0 , Item.p , -1 , p , N , NULL , 0 );

	tvi.hInsertAfter = InsertFlag;
	tvi.item.mask = TVIF_TEXT;
	tvi.item.pszText = p;

	if( hTree == NULL ){
		tvi.hParent = TVI_ROOT;
	}else{
		tvi.hParent = hTree;
	}
	hItem = TreeView_InsertItem( hWnd , &tvi );
	::free( p );

	return hItem;
}

void CTreeControl::Delete( HTREEITEM hTree ){
	::SendMessage( hWnd , TVM_DELETEITEM , 0 , ( LPARAM ) hTree );
}

bool CTreeControl::SetString( HTREEITEM hTree , const CStr &nText ){
	char *p;

	int N = ::WideCharToMultiByte( CP_ACP , 0 , nText.p , -1 , NULL , 0 , NULL , 0 );
	p = ( char * ) malloc( N );
	::WideCharToMultiByte( CP_ACP , 0 , nText.p , -1 , p , N , NULL , 0 );
	TVITEMA Item;

	Item.hItem = hTree;
	Item.mask = TVIF_TEXT;
	Item.pszText = p;

	bool Flag = ( bool ) ::SendMessage( hWnd , TVM_SETITEM , 0 , ( LPARAM ) &Item );
	::free( p );
	return Flag;
}

int CTreeControl::GetCount(){
	return ( int ) ::SendMessage( hWnd , TVM_GETCOUNT , 0 , 0 );
}

bool CTreeControl::GetString( CStr *nText , HTREEITEM hTree ){
	TVITEMA Item;
	char p[ 256 ];

	Item.hItem = hTree;
	Item.mask = TVIF_TEXT;
	Item.pszText = p;
	Item.cchTextMax = 256;
	if( ( bool ) ::SendMessage( hWnd , TVM_GETITEM , 0 , ( LPARAM ) &Item ) == false ) return false;
	*nText = p;
	return true;
}

HTREEITEM CTreeControl::GetItemSelect(){
	return ( HTREEITEM ) ::SendMessage( hWnd , TVM_GETNEXTITEM , ( WPARAM ) TVGN_CARET , 0 );
}

HTREEITEM CTreeControl::GetItemParent( HTREEITEM hTree ){
	return ( HTREEITEM ) ::SendMessage( hWnd , TVM_GETNEXTITEM , ( WPARAM ) TVGN_PARENT , ( LPARAM ) hTree );
}

//////////////////////////////////////////////////

CFileControl::CFileControl(){
	ofn.lStructSize = sizeof( OPENFILENAME );
	ofn.hwndOwner = NULL;
	ofn.nFilterIndex = 0;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = strFile;
	ofn.lpstrFilter = L"All files {*.*}\0*.*\0";
}

void CFileControl::SetOwner(){
	ofn.hwndOwner = NULL;
}

void CFileControl::SetOwner( const CDialog &nDlg ){
	ofn.hwndOwner = nDlg.hWnd;
}

void CFileControl::SetFilter( const CVector< CPair< CStr , CStr > > &vFilter ){
	int i , sz;
	FilterFile = "";
	sz = vFilter.GetSize();

	for( i = 0; i < sz; i++ ){
		FilterFile += vFilter[ i ].x;
		FilterFile += "^";
		FilterFile += vFilter[ i ].y;
		FilterFile += "^";
	}

	sz = FilterFile.GetSize();
	wchar_t *p;
	p = FilterFile.p;
	for( i = 0; i < sz; i++ ){
		if( p[ i ] == L'^' ) p[ i ] = L'\0'; 
	}
	ofn.lpstrFilter = FilterFile.p;
}

bool CFileControl::GetOpen( CStr *nDest ){
	ofn.Flags = OFN_FILEMUSTEXIST;
	if( !GetOpenFileNameW( &ofn ) ) return false;
	*nDest = &strFile[ 0 ];
	return true;
}

bool CFileControl::GetSave( CStr *nDest ){
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	if( !GetSaveFileNameW( &ofn ) ) return false;
	*nDest = &strFile[ 0 ];
	return true;
}

