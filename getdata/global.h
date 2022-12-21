
#pragma once

#include "main.h"

struct CAbl{
    char Name[30];
	char Ex[100];
};

struct CSkill{
    char Use[3];
    char Name[30];
	short Mp;
    short Pow;
    short Hit;
    short El;
    short Kind[2];
    short Pat;
	char Effect[30];
    char Ref;
};


struct CItem{
    char Use[3];
    char Name[30];
    int Prace;
    short Pow;
    short Hit;
    short El;
    short Kind[2];
    short Pat;
	char Effect[30];
    char Ref;
};

struct CEq{
    char Name[30];
    int Prace;
    short Data[15];
    char Kind[2];
    short Resistor[13];
};

struct CMagicStone{
    char Name[30];
    int Prace;
    int Data0[5];
	short Data1[5];
};

struct CEnemy{
    char Name[30];
	int HMP[2];
    short Para[16];
    int GetPoint[3];
    short Probability[9];
    short ItemData[3];
    short Resistor[20];
    short Work[9];
    short Ability[6];

};



