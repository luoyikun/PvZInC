#include "stdafx.h"
#include "resource.h"
#include "config.h"
#include "stdio.h"

__MAPNATURE _MAP[5][9];//植物的格子
__MAPNATURE _MAPZOM[5][3];//僵尸的格子

__CARDNATURE _CARD[8];
__CARDNATURE _CARDZOM[7];
__ZOMBIENATURE _ZOMBIE[ZOMMAX];
__LAWNMOVERNATURE  _LAWNMOVER[5];
__TARGETNATURE   _TARGET[5];
__BULLETNATURE   _BULLET[30];
__BULLETNATURE   _TWOBULLET[30];
int iPeaShooterCnt =0 ;
int iZomCount = 300;
int iZomSum = 0;
int iSunCount = 300;
int iCursorCardIndex = 0;
int iACardTime[8] = {PeaShooterTime,SunFlowerTime,WallNutTime,ChomperTime,
RepeaterTime,SquashTime,JalapenoTime,CherryBombTime
};
int iAMapLife[8]={PeaShooterLife,SunFlowerLife,WallNutLife,ChomperLife,
RepeaterLife,SquashLife,JalapenoLife,CherryBombLife
};

void mapInit() 
{
	int row,col;
	for (row = 0; row < 5; row++ ) {
		for (col = 0; col < 9; col++ ) {
			_MAP[row][col].cName = NO;
			_MAP[row][col].iLife = 0;
			_MAP[row][col].cSun = NO;    
			_MAP[row][col].cChomper = NO;
			_MAP[row][col].cSquash = NO;
			_MAP[row][col].cBomb = NO;
			_MAP[row][col].cCherryBomb = NO;
			_MAP[row][col].ptSite.x = 180+col*80;
			_MAP[row][col].ptSite.y = 76+row*100; 
		}
	}
}

void mapZomInit() 
{
	int row,col;
	for (row = 0; row < 5; row++ ) {
		for (col = 0; col < 3; col++ ) {
			_MAPZOM[row][col].cName = NO;
			_MAPZOM[row][col].iLife = NO;
			_MAPZOM[row][col].cSun = NO;    
			_MAPZOM[row][col].cChomper = NO;
			_MAPZOM[row][col].cSquash = NO;
			_MAPZOM[row][col].cBomb = NO;
			_MAPZOM[row][col].ptSite.x = 660+col*80;
			_MAPZOM[row][col].ptSite.y = 76+row*100; 
			_MAPZOM[row][col].cBeat = NO;
		}
	}
}

void cardInit()
{
	static int iACardMoney[8] = {PeaShooterMoney,SunFlowerMoney,WallNutMoney,ChomperMoney,RepeaterMoney,SquashMoney,JalapenoMoney,CherryBombMoney};

	for ( char cCardIndex = PeaShooter; cCardIndex <= CherryBomb; cCardIndex++ ) {
		_CARD[cCardIndex].cCanFlg = OK;
		_CARD[cCardIndex].ptSite.x = 5;
		_CARD[cCardIndex].ptSite.y = 4+64*cCardIndex;
		_CARD[cCardIndex].iCount = iACardTime[cCardIndex];
		_CARD[cCardIndex].iMoney = iACardMoney[cCardIndex];
	}
}

void cardZomInit ()
{
	static int iACardZomMoney[7] = {TombstoneMoney,ZombieMoney,FlagZombieMoney,ConeheadZombieMoney,BucketheadZombieMoney,NewspaperZombieMoney,PoleVaultingZombieMoney};
	static int iACardZomTime[7] = {TombstoneTime,ZombieTime,FlagZombieTime,ConeheadZombieTime,BucketheadZombieTime,NewspaperZombieTime,PoleVaultingZombieTime};

	for ( char cCardIndex = PeaShooter; cCardIndex < ZombieSum; cCardIndex++ ) {
		_CARDZOM[cCardIndex].cCanFlg = OK;
		_CARDZOM[cCardIndex].ptSite.x = 990;
		_CARDZOM[cCardIndex].ptSite.y = 7+70*cCardIndex;
		_CARDZOM[cCardIndex].iCount = iACardZomTime[cCardIndex];
		_CARDZOM[cCardIndex].iMoney = iACardZomMoney[cCardIndex];
	}
}

void zombieInit () 
{
	for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
		_ZOMBIE[iZomIndex].cAlive = NO;
		_ZOMBIE[iZomIndex].cBeat = NO;
		_ZOMBIE[iZomIndex].cPass = OK;
		_ZOMBIE[iZomIndex].cAttack = OK;
		_ZOMBIE[iZomIndex].cProtect = OK;
		_ZOMBIE[iZomIndex].cPoleVaulting = NO;
		_ZOMBIE[iZomIndex].ptSite.x = 200;
	} 
}

void lawnMowerInit()
{
	for (char cMoverindex = 0; cMoverindex < 5; cMoverindex++ ) {
		_LAWNMOVER[cMoverindex].cAlive = OK;
		_LAWNMOVER[cMoverindex].cActive = NO;
		_LAWNMOVER[cMoverindex].ptSite.x = 100;
		_LAWNMOVER[cMoverindex].ptSite.y = 120+cMoverindex*90;
	}
}

void tragetInit() 
{
	for (char cMoverindex = 0; cMoverindex < 5; cMoverindex++ ) {
		_TARGET[cMoverindex].iLife = TargetLife ;
		_TARGET[cMoverindex].ptSite.x = 920;
		_TARGET[cMoverindex].ptSite.y = 76+cMoverindex*100;
		_TARGET[cMoverindex].cBeat = NO;
	}
}

void bulletInit () 
{
	for ( char index = 0; index < 30; index++ ) {
		_BULLET[index].cAlive = NO;
		_BULLET[index].cOpen = NO;
		if ( index <= 5) {
			_BULLET[index].ptSite.x = _MAP[0][index].ptSite.x+50;
			_BULLET[index].ptSite.y = _MAP[0][index].ptSite.y;
		}
		if ( index > 5 && index <=11){
			_BULLET[index].ptSite.x = _MAP[1][index-6].ptSite.x+50;
			_BULLET[index].ptSite.y = _MAP[1][index-6].ptSite.y+10;
		}
		if ( index >=12 && index <=17){
			_BULLET[index].ptSite.x = _MAP[2][index-12].ptSite.x+50;
			_BULLET[index].ptSite.y = _MAP[2][index-12].ptSite.y+10;
		}
		if ( index >=18 && index <=23){
			_BULLET[index].ptSite.x = _MAP[3][index-18].ptSite.x+50;
			_BULLET[index].ptSite.y = _MAP[3][index-18].ptSite.y+10;
		}
		if ( index >=24 && index <=29){
			_BULLET[index].ptSite.x = _MAP[4][index-24].ptSite.x+50;
			_BULLET[index].ptSite.y = _MAP[4][index-24].ptSite.y+10;
		}

		_BULLET[index].ptNew.x=_BULLET[index].ptSite.x;
		_BULLET[index].ptNew.y=_BULLET[index].ptSite.y;
	}

	for ( index = 0; index < 30; index++ ) {
		_TWOBULLET[index].cAlive = _BULLET[index].cAlive;
		_TWOBULLET[index].cOpen = _BULLET[index].cOpen;
		_TWOBULLET[index].ptSite.x = _BULLET[index].ptSite.x-25;
		_TWOBULLET[index].ptSite.y = _BULLET[index].ptSite.y;
		_TWOBULLET[index].ptNew.x = _BULLET[index].ptNew.x-25;
		_TWOBULLET[index].ptNew.y = _BULLET[index].ptNew.y;
	}
}

void allInit () 
{
	mapInit();
	mapZomInit();
	cardInit();
	cardZomInit ();
	zombieInit ();
	bulletInit () ;
	lawnMowerInit();
	tragetInit();
	bulletInit ();
	dieInit();
	cMenuSelecte=0;
	iZomCnt=0;	
	iPeaShooterCnt =0 ;
	iZomCount = 300;
	iZomSum = 0;
	iSunCount = 300;
}


