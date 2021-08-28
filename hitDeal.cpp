#include "stdafx.h"
#include "resource.h"
#include "config.h"

int iChomperTmp = -1;
int iSquashTmp = -1;
int iPoleVaultingTmp = -1;
//×Óµ¯Åöµ½½©Ê¬
void bulletHit( __BULLETNATURE _BULLET[])
{
	for ( int iBulletIndex =0; iBulletIndex < 30; iBulletIndex++ ) {
		if ( _BULLET[iBulletIndex].cOpen == OK && _BULLET[iBulletIndex].cAlive == OK ) {
			for ( int iZomIndex = 0; iZomIndex < iZomSum; iZomIndex++ ) {
				if ( _ZOMBIE[iZomIndex].cAlive == OK ) {
					if ( _BULLET[iBulletIndex].ptNew.x >= _ZOMBIE[iZomIndex].ptSite.x-10 &&_BULLET[iBulletIndex].ptNew.x <= _ZOMBIE[iZomIndex].ptSite.x +80&& _BULLET[iBulletIndex].ptNew.y >= _ZOMBIE[iZomIndex].ptSite.y && _BULLET[iBulletIndex].ptNew.y <= _ZOMBIE[iZomIndex].ptSite.y+100) {
						_BULLET[iBulletIndex].cAlive =NO;
						_ZOMBIE[iZomIndex].cBeat = OK;
						_ZOMBIE[iZomIndex].iLife--; 
						if ( _ZOMBIE[iZomIndex].iLife <= 5 && _ZOMBIE[iZomIndex].iLife > 0 && (_ZOMBIE[iZomIndex].cName == ConeheadZombie||_ZOMBIE[iZomIndex].cName == BucketheadZombie||_ZOMBIE[iZomIndex].cName == NewspaperZombie)) {
							_ZOMBIE[iZomIndex].cProtect = NO;
						}
						if (_ZOMBIE[iZomIndex].iLife <= 0) {
							_ZOMBIE[iZomIndex].cAlive = NO;
							if ( _ZOMBIE[iZomIndex].cName == PoleVaultingZombie)
								killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,9,_qPoleVaultingZombieDie);
							else if ( _ZOMBIE[iZomIndex].cName == NewspaperZombie)
								killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,9,_qNewspaperZombieDie);
							else
								killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,10,_qBulletKill);
						}
					}
				}
			}
			for ( int row = 0; row < 5; row++ ) {
				for (int col = 0; col < 3;col ++) {
					if ( _MAPZOM[row][col].cName == Tombstone && _BULLET[iBulletIndex].ptNew.x >= _MAPZOM[row][col].ptSite.x && _BULLET[iBulletIndex].ptNew.x <= _MAPZOM[row][col].ptSite.x+70 && _BULLET[iBulletIndex].ptNew.y >= _MAPZOM[row][col].ptSite.y && _BULLET[iBulletIndex].ptNew.y <= _MAPZOM[row][col].ptSite.y+100) {
						_MAPZOM[row][col].iLife--;
						_MAPZOM[row][col].cBeat = OK;
						_BULLET[iBulletIndex].cAlive =NO;
						if ( _MAPZOM[row][col].iLife <= 0 ) {
							_MAPZOM[row][col].cName = NO;
						}
					}
				}
			}
			for (int iTargetIndex = 0; iTargetIndex < 5; iTargetIndex++ ) {
				if ( _TARGET[iTargetIndex].iLife >= 0 && _BULLET[iBulletIndex].ptNew.x >=  _TARGET[iTargetIndex].ptSite.x && _BULLET[iBulletIndex].ptNew.x <=  _TARGET[iTargetIndex].ptSite.x+70 && _BULLET[iBulletIndex].ptNew.y >=  _TARGET[iTargetIndex].ptSite.y && _BULLET[iBulletIndex].ptNew.y <=  _TARGET[iTargetIndex].ptSite.y+100) {
					_TARGET[iTargetIndex].iLife--;
					_TARGET[iTargetIndex].cBeat = OK;
					_BULLET[iBulletIndex].cAlive =NO;
				}
			}
		}
	}
}

void bulletHitZombie ()
{
	bulletHit( _BULLET);
	bulletHit( _TWOBULLET);
}
//½©Ê¬Åöµ½Ö²Îï
void zomHitPlant ()
{
	for ( int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
		if ( _ZOMBIE[iZomIndex].cAlive == OK ) {
			if ( _ZOMBIE[iZomIndex].cPoleVaulting == NO &&_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != NO &&_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cChomper == NO &&_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != Squash)	{
				 _ZOMBIE[iZomIndex].cPass =NO;
				 if(_ZOMBIE[iZomIndex].cAttack ==OK)	{
					_ZOMBIE[iZomIndex].cAttack = NO;
					_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].iLife--;
				 }
			}

			if( _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].iLife <= 0 ) {
				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName =NO;
				_BULLET[(_ZOMBIE[iZomIndex].ptSite.y-36)/100*6+(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cOpen = NO;
				_BULLET[(_ZOMBIE[iZomIndex].ptSite.y-36)/100*6+(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cAlive = NO;
				_TWOBULLET[(_ZOMBIE[iZomIndex].ptSite.y-36)/100*6+(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cOpen = NO;
				_TWOBULLET[(_ZOMBIE[iZomIndex].ptSite.y-36)/100*6+(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cAlive = NO;
				_ZOMBIE[iZomIndex].cPass =OK;
				_ZOMBIE[iZomIndex+1].cPass =OK;
				_ZOMBIE[iZomIndex+2].cPass =OK;
			}


			if ( _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cChomper == OK ) {
			
				iChomperTmp = iZomIndex;	
				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cChomper = DOING;
				killActivate(_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].ptSite.x,_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].ptSite.y,9,_qChompertKill);
			}
			if ( _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName == Squash ) {
				iSquashTmp = iZomIndex;		
				killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,4,_qSquashKill);
				mapClear((_ZOMBIE[iZomIndex].ptSite.y-36)/100,(_ZOMBIE[iZomIndex].ptSite.x-100)/80);
			
			}
			if( _MAP[(_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cBomb == OK ) {
// 				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80+1].cBomb =NO; 
// 				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80-1].cBomb =NO; 
// 				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80+2].cBomb =NO; 
// 				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80-2].cBomb =NO; 
// 				_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cBomb =NO; 
			    _ZOMBIE[iZomIndex].cAlive = NO;
				killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,20,_qBoomKill);
				
			}
			if ( _ZOMBIE[iZomIndex].cPoleVaulting == OK ) {
				if ( _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != NO && (_MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != Chomper && _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != Squash && _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != Jalapeno && _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName != CherryBomb) ) {
					_ZOMBIE[iZomIndex].cPoleVaulting = DOING;
					iPoleVaultingTmp = iZomIndex;
					killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,17,_qPoleVaultingZombieJump);
				}
			}
		}
// 		if ( _ZOMBIE[iZomIndex].cAlive == OK && _ZOMBIE[iZomIndex].cPoleVaulting == OK ) {
// 			if ( _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName == Chomper || _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName == Squash || _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName == Jalapeno || _MAP[ (_ZOMBIE[iZomIndex].ptSite.y-36)/100][(_ZOMBIE[iZomIndex].ptSite.x-100)/80].cName == CherryBomb ) {
// 				_ZOMBIE[iZomIndex].cAlive = NO;
// 			}
// 		} 
	}
}

void moverActive()
{
	for ( int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
		if ( _ZOMBIE[iZomIndex].cAlive == OK ) {
			if( _ZOMBIE[iZomIndex].ptSite.x < 100 ) {
				_LAWNMOVER[(_ZOMBIE[iZomIndex].ptSite.y-36)/100].cActive = OK;
			}
		}
	}
}

void moverHitZom()
{
	for ( int iMoverIndex = 0; iMoverIndex < 5; iMoverIndex++ ) {
		if ( _LAWNMOVER[iMoverIndex].cAlive == OK &&_LAWNMOVER[iMoverIndex].cActive == OK ) {
			for ( int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
				if ( _ZOMBIE[iZomIndex].cAlive == OK && _LAWNMOVER[iMoverIndex].ptSite.x >= _ZOMBIE[iZomIndex].ptSite.x +30 && (iMoverIndex*100+36) == _ZOMBIE[iZomIndex].ptSite.y) {
					_ZOMBIE[iZomIndex].cAlive = NO;
					if ( _ZOMBIE[iZomIndex].cName == PoleVaultingZombie)
						killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,9,_qPoleVaultingZombieDie);
					else if ( _ZOMBIE[iZomIndex].cName == NewspaperZombie)
								killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,9,_qNewspaperZombieDie);
					else
						killActivate(_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y,10,_qBulletKill);
				}
			}
		}
	}
}

void hitDeal()
{
	zomHitPlant ();
	bulletHitZombie();
	moverHitZom();
	moverActive();
}