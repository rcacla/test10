

#define PREFIX 
#include "global.h"



void Get( int *pDest ){

	char *p0 = (char*) pDest;
	int x = *pDest;
	char *p1 = (char*) &x;

	p0[0] = p1[3];
	p0[1] = p1[2];
	p0[2] = p1[1];
	p0[3] = p1[0];

}

void GetCText( char *pText, int sz ){
	for( int i = sz-1; i >= 0; i-- ){ 
	//for( int i = sz-1; i >= sz-2; i-- ){ 
		if( pText[i] == (char)0x20 ){
			pText[i] = '\0';
		}else{
			break;
		}
	}
}

int CMain( const CVector< CStr > &vArg, const CMap< CStr, CStr > &mArg ){

	CStr InputDir = "sbin/tmp/vb";
	CStr OutputDir = "sbin/tmp/vb_out";

	CVector<CAbl> vAbl;
	CVector<CItem> vItem;
	CVector<CSkill> vSkill;
	CVector<CEq> vEq[3];
	CVector<CMagicStone> vMagicStone;

	CMap<int, char*> mapAbl;
	CMap<int, char*> mapItem;
	CMap<int, char*> mapSkill;

	CMap<int, CStr> mapEl;
	CMap<int, CStr> mapType0;
	CMap<int, CStr> mapType1;
	CMap<int, CStr> mapPat;
	CMap<int, CStr> mapReg;

	{
		CMap<int, CStr> *p = &mapEl;

		p->Set( 0, "無属性" );
		p->Set( 1, "火属性" );
		p->Set( 2, "氷属性" );
		p->Set( 3, "雷属性" );
		p->Set( 4, "風属性" );
		p->Set( 5, "光属性" );
		p->Set( 6, "闇属性" );
	}

	{
		CMap<int, CStr> *p = &mapType0;

		p->Set( 0, "物理攻撃" );
		p->Set( 1, "攻撃魔法" );
		p->Set( 2, "回復魔法" );
		p->Set( 3, "状態付加" );
		p->Set( 4, "状態回復" );
		p->Set( 5, "ステータス補助[敵]" );
		p->Set( 6, "ステータス補助[未]" );
		p->Set( 7, "効果魔法" );
		p->Set( 8, "復活" );
		p->Set( 9, "盗む" );
		p->Set( 10, "次のターンまで" );
		p->Set( 11, "初期化" );
		p->Set( 12, "ブレス" );
		p->Set( 13, "固定ダメージ" );
		p->Set( 14, "吸収" );
		p->Set( 15, "確認" );
		p->Set( 16, "脱出" );
		p->Set( 17, "パラメータUP" );
		p->Set( 18, "特殊能力を覚える" );
		p->Set( 19, "エンカウント率変化" );
		p->Set( 20, "アイテム発見率変化" );
		p->Set( 21, "地図" );
		p->Set( 22, "鍵" );
		p->Set( 23, "トラップ解除" );
		p->Set( 24, "合成素材" );
		p->Set( 25, "大事なもの" );
		p->Set( 26, "召喚" );
	}

	{
		CMap<int, CStr> *p = &mapPat;

		p->Set( 0, "単体" );
		p->Set( 1, "全体" );
		p->Set( 2, "自分" );
		p->Set( 3, "ランダム" );
		p->Set( 4, "ランダム×２" );
		p->Set( 5, "ランダム×３" );
		p->Set( 6, "ランダム×４" );
		p->Set( 7, "ランダム×５" );
		p->Set( 8, "ランダム×６" );
		p->Set( 9, "ランダム×７" );
		p->Set( 10, "ランダム×８" );
		p->Set( 11, "ランダム[未・敵]" );
		p->Set( 12, "ランダム[未・敵]×２" );
		p->Set( 13, "ランダム[未・敵]×３" );
		p->Set( 14, "ランダム[未・敵]×４" );
		p->Set( 15, "ランダム[未・敵]×５" );
		p->Set( 16, "ランダム[未・敵]×６" );
		p->Set( 17, "ランダム[未・敵]×７" );
		p->Set( 18, "ランダム[未・敵]×８" );
		p->Set( 19, "全体[未・敵]" );

	}

	{
		CMap<int, CStr> *p = &mapReg;

		p->Set( 0, "E" );
		p->Set( 1, "D" );
		p->Set( 2, "C" );
		p->Set( 3, "B" );
		p->Set( 4, "A" );
	}

	////////////////////////////////////////

	{
		CFile cf;
		{
			CStr tmp;
			tmp.Set( "%S/アビリティ.dat", InputDir.p );
			if( !cf.Open( tmp, true ) ){ return 0; }
		}

		CAbl obj;
		int x = 0;
		CStr o;

		strcpy( obj.Name, "" );
		strcpy( obj.Ex, "" );
		vAbl += obj;
		while( 1 ){

			if( !cf.Read( (void*) obj.Name, sizeof(obj.Name) ) ){ break; }
			GetCText( obj.Name, sizeof(obj.Name) );
			o.Add( "%s\t", obj.Name );

			if( !cf.Read( (void*) obj.Ex, sizeof(obj.Ex) ) ){ break; }
			GetCText( obj.Ex, sizeof(obj.Ex) );
			o.Add( "%s\t", obj.Ex );

			o.Add( "\n" );

			vAbl += obj;
			x++;
		}

		{
			CStr tmp;
			tmp.Set( "%S/アビリティ.txt", OutputDir.p );
			FILE *fpOut = _wfopen( tmp.p, L"w" );

			fprintf( fpOut, "%S", o.p );
			fclose( fpOut );
		}

		int sz = vAbl.GetSize();
		for( int i = 0; i < sz; i++ ){
			mapAbl.Set( i, vAbl[i].Name );
		}

	}

	////////////////////////////////////////////////

	{
		CFile cf;
		{
			CStr tmp;
			tmp.Set( "%S/アイテム.dat", InputDir.p );
			if( !cf.Open( tmp, true ) ){ return 0; }
		}

		CItem obj;
		int x = 0;
		CStr o;

		strcpy( obj.Name, "" );

		vItem += obj;
		while( 1 ){
			
			if( !cf.Read( (void*) obj.Use, sizeof(obj.Use) ) ){ break; }
			
			if( !cf.Read( (void*) obj.Name, sizeof(obj.Name) ) ){ break; }
			GetCText( obj.Name, sizeof(obj.Name) );
			o.Add( "%s\t", obj.Name );
			for( int i = 0; i < 3; i++ ){ o.Add( "%d\t", obj.Use[i]); }

			if( !cf.Read( (void*) &obj.Prace, sizeof(obj.Prace) ) ){ break; }
			o.Add( "%d\t", obj.Prace);
			if( !cf.Read( (void*) &obj.Pow, sizeof(obj.Pow) ) ){ break; }
			o.Add( "%d\t", obj.Pow);
			if( !cf.Read( (void*) &obj.Hit, sizeof(obj.Hit) ) ){ break; }
			o.Add( "%d\t", obj.Hit);
			if( !cf.Read( (void*) &obj.El, sizeof(obj.El) ) ){ break; }
			
			o.Add( "%S\t", mapEl[obj.El].p);
			if( !cf.Read( (void*) obj.Kind, sizeof(obj.Kind) ) ){ break; }

			o.Add( "%S\t", mapType0[obj.Kind[0]].p);
			o.Add( "%d\t", obj.Kind[1]);
			if( !cf.Read( (void*) &obj.Pat, sizeof(obj.Pat) ) ){ break; }
			
			o.Add( "%S\t", mapPat[obj.Pat].p);
			if( !cf.Read( (void*) obj.Effect, sizeof(obj.Effect) ) ){ break; }
			GetCText( obj.Effect, sizeof(obj.Effect) );
			o.Add( "%s\t", obj.Effect );

			if( !cf.Read( (void*) &obj.Ref, sizeof(obj.Ref) ) ){ break; }
			o.Add( "%d\t", obj.Ref);

			o.Add( "\n" );

			vItem += obj;
			x++;
		}

		{
			CStr tmp;
			tmp.Set( "%S/アイテム.txt", OutputDir.p );
			FILE *fpOut = _wfopen( tmp.p, L"w" );

			fprintf( fpOut, "%S", o.p );
			fclose( fpOut );
		}

	}

	////////////////////////////////////////////////
	for( int k = 0; k < 3; k++ ){
		CFile cf;
		{
			CStr tmp;
			tmp.Set( "%S/装備%d.dat", InputDir.p, k );
			if( !cf.Open( tmp, true ) ){ return 0; }
		}

		CEq obj;
		int x = 0;
		CStr o;

		strcpy( obj.Name, "" );

		vEq[k] += obj;
		while( 1 ){
			if( x >= 150 ){ break; }
			if( !cf.Read( (void*) obj.Name, sizeof(obj.Name) ) ){ break; }
			GetCText( obj.Name, sizeof(obj.Name) );
			o.Add( "%s\t", obj.Name );

			if( !cf.Read( (void*) &obj.Prace, sizeof(obj.Prace) ) ){ break; }
			o.Add( "%d\t", obj.Prace);

			if( !cf.Read( (void*) obj.Data, sizeof(obj.Data) ) ){ break; }
			for( int i = 0; i < 15; i++ ){ o.Add( "%d\t", obj.Data[i]); }

			if( !cf.Read( (void*) obj.Kind, sizeof(obj.Kind) ) ){ break; }
			for( int i = 0; i < 2; i++ ){ o.Add( "%s\t", mapAbl[obj.Kind[i]]); }

			if( !cf.Read( (void*) obj.Resistor, sizeof(obj.Resistor) ) ){ break; }
			for( int i = 0; i < 13; i++ ){ o.Add( "%d\t", obj.Resistor[i]); }


			o.Add( "\n" );

			vEq[k] += obj;
			x++;
		}

		{
			CStr tmp;
			tmp.Set( "%S/Eq%d.txt", OutputDir.p, k );
			FILE *fpOut = _wfopen( tmp.p, L"w" );

			fprintf( fpOut, "%S", o.p );
			fclose( fpOut );
		}

	}
	////////////////////////////////////////////////

	{
		CFile cf;
		{
			CStr tmp;
			tmp.Set( "%S/特殊.dat", InputDir.p );
			if( !cf.Open( tmp, true ) ){ return 0; }
		}

		CSkill obj;
		int x = 0;
		CStr o;

		strcpy( obj.Name, "" );

		vSkill += obj;
		while( 1 ){
			if( x >= 300 ){ break; }
			if( !cf.Read( (void*) obj.Use, sizeof(obj.Use) ) ){ break; }
			
			if( !cf.Read( (void*) obj.Name, sizeof(obj.Name) ) ){ break; }
			GetCText( obj.Name, sizeof(obj.Name) );
			o.Add( "%s\t", obj.Name );
			for( int i = 0; i < 3; i++ ){ o.Add( "%d\t", obj.Use[i]); }

			if( !cf.Read( (void*) &obj.Mp, sizeof(obj.Mp) ) ){ break; }
			o.Add( "%d\t", obj.Mp);

			if( !cf.Read( (void*) &obj.Pow, sizeof(obj.Pow) ) ){ break; }
			o.Add( "%d\t", obj.Pow);
			if( !cf.Read( (void*) &obj.Hit, sizeof(obj.Hit) ) ){ break; }
			o.Add( "%d\t", obj.Hit);
			if( !cf.Read( (void*) &obj.El, sizeof(obj.El) ) ){ break; }
			
			o.Add( "%S\t", mapEl[obj.El].p);
			if( !cf.Read( (void*) obj.Kind, sizeof(obj.Kind) ) ){ break; }

			o.Add( "%S\t", mapType0[obj.Kind[0]].p);
			o.Add( "%d\t", obj.Kind[1]);
			if( !cf.Read( (void*) &obj.Pat, sizeof(obj.Pat) ) ){ break; }
			
			o.Add( "%S\t", mapPat[obj.Pat].p);
			if( !cf.Read( (void*) obj.Effect, sizeof(obj.Effect) ) ){ break; }
			GetCText( obj.Effect, sizeof(obj.Effect) );
			o.Add( "%s\t", obj.Effect );

			if( !cf.Read( (void*) &obj.Ref, sizeof(obj.Ref) ) ){ break; }
			o.Add( "%d\t", obj.Ref);

			o.Add( "\n" );

			vSkill += obj;
			x++;
		}

		{
			CStr tmp;
			tmp.Set( "%S/スキル.txt", OutputDir.p );
			FILE *fpOut = _wfopen( tmp.p, L"w" );

			fprintf( fpOut, "%S", o.p );
			fclose( fpOut );
		}

		int sz = vSkill.GetSize();
		for( int i = 0; i < sz; i++ ){
			mapSkill.Set( i, vSkill[i].Name );
		}

		sz = vAbl.GetSize();
		for( int i = 1; i < sz; i++ ){
			mapSkill.Set( 300+i, vAbl[i].Name );
		}
	}

	////////////////////////////////////////////////
	{
		CFile cf;
		{
			CStr tmp;
			tmp.Set( "%S/マテリア.dat", InputDir.p );
			if( !cf.Open( tmp, true ) ){ return 0; }
		}

		CMagicStone obj;
		int x = 0;
		CStr o;

		strcpy( obj.Name, "" );

		vMagicStone += obj;
		while( 1 ){
			
			if( !cf.Read( (void*) obj.Name, sizeof(obj.Name) ) ){ break; }
			GetCText( obj.Name, sizeof(obj.Name) );
			o.Add( "%s\t", obj.Name );

			if( !cf.Read( (void*) &obj.Prace, sizeof(obj.Prace) ) ){ break; }
			o.Add( "%d\t", obj.Prace);

			if( !cf.Read( (void*) obj.Data0, sizeof(obj.Data0) ) ){ break; }

			if( !cf.Read( (void*) obj.Data1, sizeof(obj.Data1) ) ){ break; }
			for( int i = 0; i < 5; i++ ){
				o.Add( "%d\t", obj.Data0[i]);
				o.Add( "%s\t", mapSkill[obj.Data1[i]]);
			}

			o.Add( "\n" );

			vMagicStone += obj;
			x++;
		}

		{
			CStr tmp;
			tmp.Set( "%S/MagicStone.txt", OutputDir.p );
			FILE *fpOut = _wfopen( tmp.p, L"w" );

			fprintf( fpOut, "%S", o.p );
			fclose( fpOut );
		}

	}

	////////////////////////////////////////////////

	{
		int cnt = 0;
		int sz = vItem.GetSize();
		for( int i = 0; i < sz; i++ ){
			mapItem.Set( cnt, vItem[i].Name );
			cnt++;
		}
		for( int k = 0; k < 3; k++ ){
			sz = vEq[k].GetSize();
			for( int i = 1; i < sz; i++ ){
				mapItem.Set( cnt, vEq[k][i].Name );
				cnt++;
			}
		}
		sz = vMagicStone.GetSize();
		for( int i = 1; i < sz; i++ ){
			mapItem.Set( cnt, vMagicStone[i].Name );
			cnt++;
		}
	}

	{
		CFile cf;
		{
			CStr tmp;
			tmp.Set( "%S/モンスター.dat", InputDir.p );
			if( !cf.Open( tmp, true ) ){ return 0; }
		}

		CEnemy obj;
		int x = 0;
		CStr o;
		while( 1 ){

			if( !cf.Read( (void*) obj.Name, sizeof(obj.Name) ) ){ break; }
			GetCText( obj.Name, sizeof(obj.Name) );
			o.Add( "%s\t", obj.Name );

			if( !cf.Read( (void*) obj.HMP, sizeof(obj.HMP) ) ){ break; }
			for( int i = 0; i < 2; i++ ){ o.Add( "%d\t", obj.HMP[i]); }

			if( !cf.Read( (void*) obj.Para, sizeof(obj.Para) ) ){ break; }
			for( int i = 0; i < 16; i++ ){ o.Add( "%d\t", obj.Para[i]); }

			if( !cf.Read( (void*) obj.GetPoint, sizeof(obj.GetPoint) ) ){ break; }

			if( !cf.Read( (void*) obj.Probability, sizeof(obj.Probability) ) ){ break; }

			if( !cf.Read( (void*) obj.ItemData, sizeof(obj.ItemData) ) ){ break; }

			if( !cf.Read( (void*) obj.Resistor, sizeof(obj.Resistor) ) ){ break; }
			for( int i = 0; i < 20; i++ ){ o.Add( "%S\t", mapReg[obj.Resistor[i]].p); }

			if( !cf.Read( (void*) obj.Work, sizeof(obj.Work) ) ){ break; }

			for( int i = 0; i < 3; i++ ){ 
				o.Add( "%d\t", obj.GetPoint[i]);
				o.Add( "%s\t", mapItem[obj.ItemData[i]] );
			}
			for( int i = 0; i < 9; i++ ){
				o.Add( "%d\t", obj.Probability[i]);
				o.Add( "%s\t", mapSkill[obj.Work[i]]);
			}

			if( !cf.Read( (void*) obj.Ability, sizeof(obj.Ability) ) ){ break; }
			for( int i = 0; i < 6; i++ ){ o.Add( "%s\t", mapAbl[obj.Ability[i]]);}

			o.Add( "\n" );
			x++;
		}

		{
			CStr tmp;
			tmp.Set( "%S/モンスター.txt", OutputDir.p );
			FILE *fpOut = _wfopen( tmp.p, L"w" );

			fprintf( fpOut, "%S", o.p );
			fclose( fpOut );
		}

	}


	return 1;

}


