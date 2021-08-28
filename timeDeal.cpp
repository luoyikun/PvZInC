#include "stdafx.h"
#include "resource.h"
#include "config.h"
#include "time.h"

char cSunFlg = NO;
char cRandom =NO;
int iRandomXpos = 0;
int iRandomYpos = 0;
char cWinFlg = NO;
int iZomCnt = 0;
//点了植物和僵尸的卡以后的效果
bool  timeDeal ( DWORD dwTime )
{
	static long int iLastUpdate=0;
	static int iACardZomTime[7] = {TombstoneTime,ZombieTime,FlagZombieTime,ConeheadZombieTime,BucketheadZombieTime,NewspaperZombieTime,PoleVaultingZombieTime};

    if( ( dwTime - iLastUpdate ) >= 1000 )               
    {
        iLastUpdate = dwTime;
		for ( char cCardIndex = PeaShooter; cCardIndex <= CherryBomb; cCardIndex++ ) {
			if ( _CARD[cCardIndex].cCanFlg == NO ) {
				_CARD[cCardIndex].iCount--;
				if (_CARD[cCardIndex].iCount <= 0) {
					_CARD[cCardIndex].iCount = iACardTime[cCardIndex];
					_CARD[cCardIndex].cCanFlg = OK;
				}
			}	
            if ( cCardIndex < ZombieSum ) {
				if ( _CARDZOM[cCardIndex].cCanFlg == NO ) {
					_CARDZOM[cCardIndex].iCount--;
					if (_CARDZOM[cCardIndex].iCount <= 0) {
						_CARDZOM[cCardIndex].iCount = iACardZomTime[cCardIndex];
						_CARDZOM[cCardIndex].cCanFlg = OK;
					}
				}	
			}   
		}
    }
    return true;
}
//向日葵太阳光的出现
bool  sunDeal ( DWORD dwTime )
{
	static long int iLastUpdate=0;
	
    if( ( dwTime - iLastUpdate ) >= 5000 )               
    {
        iLastUpdate = dwTime;
		for (char row = 0; row < 5; row++ ) {
			for (char col = 0; col < 9; col++ ) {
				if ( _MAP[row][col].cName == SunFlower&& _MAP[row][col].cSun == NO ) {
					_MAP[row][col].cSun = OK;
				}
			}
		}
    }
    return true;
}
//僵尸的移动处理
bool  zomDeal ( DWORD dwTime )
{
	static long int iLastUpdate=0;
	
    if( ( dwTime - iLastUpdate ) >= 1000 )               
    {
        iLastUpdate = dwTime;
		for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
			if ( _ZOMBIE[iZomIndex].cAlive == OK && _ZOMBIE[iZomIndex].cPass == OK) {
				if (_ZOMBIE[iZomIndex].cName == NewspaperZombie && _ZOMBIE[iZomIndex].cProtect == NO )
					_ZOMBIE[iZomIndex].ptSite.x -=_ZOMBIE[iZomIndex].iSpeed+10;
				else  if (_ZOMBIE[iZomIndex].cName == PoleVaultingZombie && _ZOMBIE[iZomIndex].cPoleVaulting == NO )
					_ZOMBIE[iZomIndex].ptSite.x -=_ZOMBIE[iZomIndex].iSpeed-10;
				else
					_ZOMBIE[iZomIndex].ptSite.x -=_ZOMBIE[iZomIndex].iSpeed;
			}
		}
    }
    return true;
}
//僵尸的吃植物的间隔处理,就是每隔多少的时间攻击一下。植物就会少一滴血
bool  zomAttackDeal ( DWORD dwTime )
{
	static long int iLastUpdate=0;
	
    if( ( dwTime - iLastUpdate ) >= 1000 )               
    {
        iLastUpdate = dwTime;
		for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
			if ( _ZOMBIE[iZomIndex].cAlive == OK && _ZOMBIE[iZomIndex].cAttack == NO) {
				_ZOMBIE[iZomIndex].cAttack = OK;
			}
		}
    }
    return true;
}
//随机太阳光的出现
bool  sunRandomDeal ( DWORD dwTime )
{
	static long int iLastUpdate=0;
	
    if( ( dwTime - iLastUpdate ) >= 10000 )               
    {
        iLastUpdate = dwTime;
		_MAP[iRandomXpos][iRandomYpos].cSun = OK ;
    }
    return true;
}

bool zomCountDeal (DWORD dwTime)
{
	static long int iLastUpdate=0;
	int iTombstoneSum =1;
    if( ( dwTime - iLastUpdate ) >= 5000 )               
    {
        iLastUpdate = dwTime;
		for ( char cRow = 0; cRow < 5; cRow++ ) {
			for ( char cCol = 0; cCol < 3; cCol++ ) {
			if ( _MAPZOM[cRow][cCol].cName == Tombstone ) 
				iTombstoneSum++;
			}
		}
		iZomCount += iTombstoneSum*25;
    }
    return true;
}

void bulletTime (DWORD dwTime)
{
	static long int iLastUpdate=0;
	if( ( dwTime - iLastUpdate ) >= 2500 )               
    {
        iLastUpdate = dwTime;
		//fireActive(1,_qBULLET);
		for ( int index = 0;index < 30; index++ ) {
 			//if ( _BULLET[index].cAlive == NO ) {
 				_BULLET[index].cAlive = OK;
				_BULLET[index].ptNew = _BULLET[index].ptSite;
				_TWOBULLET[index].cAlive = OK;
				_TWOBULLET[index].ptNew = _TWOBULLET[index].ptSite;
			//}		
		}
	}
}

void bulletDeal ( DWORD dwTime )
{   

	static long int iLastUpdate=0;
	
	if( ( dwTime - iLastUpdate ) >= 10 ) {
        iLastUpdate = dwTime;
		for ( int index = 0;index < 30; index++ ) {
			if ( _BULLET[index].cOpen == OK ) 
				_BULLET[index].ptNew.x += 7; 
			if ( _TWOBULLET[index].cOpen == OK )
				_TWOBULLET[index].ptNew.x += 7;
		}
	}
}
//子弹散了后的消失的处理
void peaBulletHit(DWORD dwTime)
{
	static long int iLastUpdate=0;
	
	if( ( dwTime - iLastUpdate ) >= 500) {
        iLastUpdate = dwTime;
		for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
			if ( _ZOMBIE[iZomIndex].cBeat == OK ) {
				_ZOMBIE[iZomIndex].cBeat = NO;
			}
		}
		for ( int row = 0; row < 5; row++ ) {
			for (int col = 0; col < 3;col ++) {
				if ( _MAPZOM[row][col].cName == Tombstone && _MAPZOM[row][col].cBeat == OK )
					_MAPZOM[row][col].cBeat = NO;
			}
		}
		for (int iTargetIndex = 0; iTargetIndex < 5; iTargetIndex++ ) {
			if ( _TARGET[iTargetIndex].cBeat == OK )
				_TARGET[iTargetIndex].cBeat = NO;
		}
	}
}

// 进入动画帧的框架
bool cartoonDeal(int *nCurFrame , int *iTime , int *oldUpdate , DWORD dwTime,char iType )
{
    if( *nCurFrame == -1 )
        return false;
	
    if( ( dwTime - *oldUpdate )>=150 )               //当时间大于100时播放下一个动画
    {
        *oldUpdate = dwTime;
        (*nCurFrame)++;
		
        if(  *nCurFrame>=*iTime )           //爆炸类型nType为1，将播放完7个图片，时间长，一般是击中目标
        { 
            *nCurFrame = -1;
			if ( iType == CChompertKill &&iChomperTmp != -1 ) {
				_MAP[ (_ZOMBIE[iChomperTmp].ptSite.y-36)/100][(_ZOMBIE[iChomperTmp].ptSite.x-100)/80].cChomper = NO;
				iChomperTmp = -1;
			}	
			if ( iType ==CSquashKill&&iSquashTmp != -1 )
				iSquashTmp = -1;
			if (iType == CBoomKill) {
				for (char row = 0; row < 5; row++ ) {
					for (char col = 0; col < 9; col++ ) {
						if ( _MAP[row][col].cBomb == OK ) {
							_MAP[row][col].cBomb = NO;
						}
					}
				}
			}
			if (iType == CPoleVaulting) {
				_ZOMBIE[iPoleVaultingTmp].cPoleVaulting = NO;
				_ZOMBIE[iPoleVaultingTmp].ptSite.x -= 40;
			}
        }
 		if ( iType == CChompertKill && *nCurFrame == *iTime-2 && iChomperTmp != -1 && _ZOMBIE[iChomperTmp].cAlive == OK ) {
 			_ZOMBIE[iChomperTmp].cAlive = NO;
 		}
		if (  iType ==CSquashKill&&*nCurFrame == *iTime-2 && iSquashTmp != -1 && _ZOMBIE[iSquashTmp].cAlive == OK ) {
			_ZOMBIE[iSquashTmp].cAlive = NO;
 		}
    }
    return true;
}

//植物的子弹杀死僵尸的处理
void killDeal(DWORD dwTime, __CARTOON *_qKill,int iType)
{
	int  i;
	struct __CARTOON *e;
	e=_qKill;
	// 爆炸处理
	for( i=0; i<SameTime; i++ )
	{   		
		cartoonDeal(&e->iCurFrame , &e->iType , &e->iUpdate , dwTime ,iType);
		e=e->next;		
	}
}


//推土机的位移处理
void moverDeal (DWORD dwTime) 
{
	static long int iLastUpdate=0;
	
	if( ( dwTime - iLastUpdate ) >= 10) {
        iLastUpdate = dwTime;
		for (int iMoverIndex = 0; iMoverIndex < 5; iMoverIndex++ ) {
			if ( _LAWNMOVER[iMoverIndex].cActive == OK ) {
				_LAWNMOVER[iMoverIndex].ptSite.x += 10;
				if ( _LAWNMOVER[iMoverIndex].ptSite.x >= 900 ) {
					_LAWNMOVER[iMoverIndex].cAlive = NO;
				}
			} 
		}
	}
}
//食人花的消化时间的处理
void chomperDigestDeal(DWORD dwTime) 
{
	static long int iLastUpdate=0;
	if( ( dwTime - iLastUpdate ) >= 100000) {
		iLastUpdate = dwTime;
		for (char row = 0; row < 5; row++ ) {
			for (char col = 0; col < 9; col++ ) {
				if ( _MAP[row][col].cName == Chomper&& _MAP[row][col].cChomper == NO ) {
					_MAP[row][col].cChomper = OK;
				}
			}
		}
	}
}
//樱桃的炸弹
void cherryBombDeal(DWORD dwTime) 
{
	static long int iLastUpdate=0;
	if( ( dwTime - iLastUpdate ) >= 1000) {
		iLastUpdate = dwTime;
		for (char row = 0; row < 5; row++ ) {
			for (char col = 0; col < 9; col++ ) {
				if ( _MAP[row][col].cName ==  CherryBomb ) {
					_MAP[row][col].cName = NO;
					_MAP[row][col].cCherryBomb = NO;
				}
			}
		}
	}	
}

void cherryDieDeal(DWORD dwTime)
{
	static long int iLastUpdate=0;
	if( ( dwTime - iLastUpdate ) >= 2000) {
		iLastUpdate = dwTime;
		for (char row = 0; row < 5; row++ ) {
			for (char col = 0; col < 9; col++ ) {
				if (  _MAP[row][col].cName == NO && _MAP[row][col].cBomb == OK) {
					_MAP[row][col].cCherryBomb = NO;
					_MAP[row][col].cBomb = NO;
					if (col <= 5)
						_MAP[row][col+1].cBomb = NO;
					if (col >=1)
						_MAP[row][col-1].cBomb = NO;
					if(row <= 3)
						_MAP[row+1][col].cBomb = NO;
					if(row >= 1)
						_MAP[row-1][col].cBomb = NO;
				}
			}
		}
	}
}

void jalapenoDeal (DWORD dwTime)
{
	static long int iLastUpdate=0;
	if( ( dwTime - iLastUpdate ) >= 10) {
		iLastUpdate = dwTime;
		for (char row = 0; row < 5; row++ ) {
			for (char col = 0; col < 9; col++ ) {
				if ( _MAP[row][col].cName == Jalapeno  ) {
					_MAP[row][col].cName = NO;
					killActivate(_MAP[row][col].ptSite.x,_MAP[row][col].ptSite.y,8,_qJalapenoKill);
				}
			}
		}
	}	
}

void gameoverDeal()
{
	int iTragetCnt = 0;
	for (int iTargetIndex = 0; iTargetIndex < 5; iTargetIndex++ ) {
		if ( _TARGET[iTargetIndex].iLife < 0 ) {
 			iTragetCnt++;
 			if(iTragetCnt >= 3)
				cWinFlg = PlantWin;
			else
				cWinFlg = NO;
		}
	}
	for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
		if ( _ZOMBIE[iZomIndex].ptSite.x <=  0) {
			cWinFlg = ZomWin;
		}
	}
}
bool gameProgress( DWORD dwTime )
{
	zomCountDeal (dwTime);
	sunRandomDeal(dwTime);
	timeDeal(dwTime);
	sunDeal(dwTime);
    zomDeal(dwTime);
	bulletTime (dwTime);
	bulletDeal (dwTime);
	peaBulletHit(dwTime);
	hitDeal();

	killDeal(dwTime,_qBulletKill,CBulletKill);
	killDeal(dwTime,_qSquashKill,CSquashKill);
	killDeal(dwTime,_qChompertKill,CChompertKill);
	killDeal(dwTime,_qJalapenoKill,CJalapenoKill);
	killDeal(dwTime,_qBoomKill,CBoomKill);
	killDeal(dwTime,_qPoleVaultingZombieDie,CBoomKill);
	killDeal(dwTime,_qPoleVaultingZombieJump,CPoleVaulting);
	killDeal(dwTime,_qNewspaperZombieDie,CPoleVaulting);

	moverDeal(dwTime);
	chomperDigestDeal(dwTime);
	jalapenoDeal(dwTime);
	zomAttackDeal(dwTime);
	cherryBombDeal(dwTime);
	cherryDieDeal(dwTime);
	gameoverDeal();
	return true;
}

// 进入游戏帧
bool frameInto(HINSTANCE hinstance,DWORD dwTime)
{
	bool bRet = false;
    switch( cWinFlg)
    {
	case NO:			
		{
			gameProgress(dwTime);
			gameInterface();
		}
		break;
    default:
		{
			gameOver();
		}
		break;
    }     
	return true;
// 	return gameProgress( dwTime );
}
