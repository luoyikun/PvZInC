#include "stdafx.h"
#include "resource.h"
#include "config.h"
#include "conio.h"



char cZomChoose ;

int iAZomSpeed[6]={ZombieSpeed,FlagZombieSpeed,ConeheadZombieSpeed,BucketheadZombieSpeed,NewspaperZombieSpeed,PoleVaultingZombieSpeed};
int iAZomLife[6] = {ZombieLife,FlagZombieLife,ConeheadZombieLife,BucketheadZombieLife,NewspaperZombieLife,PoleVaultingZombieLife};
int iAZomName[6] = {Zombie,FlagZombie,ConeheadZombie,BucketheadZombie,NewspaperZombie,PoleVaultingZombie
};


void keyDeal( WPARAM wKey )
{
    switch( wKey )
    {
	case 'S':
	case 's': {
		iCursorCardIndex++;
		if( iCursorCardIndex >= 7 )
			iCursorCardIndex = 0;
					  }
		break;
	case 'w':
	case 'W':{
		iCursorCardIndex--;
		if( iCursorCardIndex < 0 )
			iCursorCardIndex = 6;
		}
		break;
	case VK_RETURN: {
				if (cWinFlg == NO) {
					if (_CARDZOM[iCursorCardIndex].cCanFlg == OK ) {
						cZomChoose = iCursorCardIndex;
					}
				}
				if(cWinFlg != NO) {
					switch ( cMenuSelecte ) {
					case REPLAY:{
									cWinFlg = NO;
									allInit();
								}break;
					case OVER: {
									PostQuitMessage(0);
							   }break;
					}

				}
			}break;
	case VK_UP:
		{	if( cWinFlg ==NO) {
				iPointerXpos--;
				if(iPointerXpos < 0)
					iPointerXpos = 4;
			}
			if (cWinFlg !=NO) {
				if( cMenuSelecte==0 )
					cMenuSelecte = 1;
				else if(cMenuSelecte>=1)
					cMenuSelecte = 0;
			}
			
		}break;
	case VK_DOWN:
		{
			if(cWinFlg ==NO) {
				iPointerXpos++;
				if(iPointerXpos >4)
					iPointerXpos = 0;
			}
			if(cWinFlg !=NO) {
				if( cMenuSelecte==0 )
					cMenuSelecte = 1;
				else if(cMenuSelecte>=1)
					cMenuSelecte = 0;
			}
		}break;
	case VK_RIGHT:
		{
			iPointerYpos++;
			if(iPointerYpos >2)
				iPointerYpos = 0;
		}break;
	case VK_LEFT:
		{
			iPointerYpos--;
			if(iPointerYpos < 0)
				iPointerYpos = 2;
		}break;
	case VK_SPACE:
		{
			if ( _CARDZOM[cZomChoose].iMoney <= iZomCount && _CARDZOM[cZomChoose].cCanFlg != NO) {
				if ( cZomChoose == Tombstone ) {
					if ( _MAPZOM[iPointerXpos][iPointerYpos].cName == NO) {
						_MAPZOM[iPointerXpos][iPointerYpos].cName = Tombstone;
						_MAPZOM[iPointerXpos][iPointerYpos].iLife = TombstoneLife;
						iZomCount -= _CARDZOM[cZomChoose].iMoney;
					}		
				}
				else {
					_ZOMBIE[iZomSum].cAlive = OK; 
					if ( cZomChoose == PoleVaultingZombie) {
						_ZOMBIE[iZomSum].ptSite.x = _MAPZOM[iPointerXpos][iPointerYpos].ptSite.x-120;
						_ZOMBIE[iZomSum].ptSite.y = _MAPZOM[iPointerXpos][iPointerYpos].ptSite.y-40;
						_ZOMBIE[iZomSum].cPoleVaulting = OK;
					}

					else {
						_ZOMBIE[iZomSum].ptSite.x = _MAPZOM[iPointerXpos][iPointerYpos].ptSite.x-80;
						_ZOMBIE[iZomSum].ptSite.y = _MAPZOM[iPointerXpos][iPointerYpos].ptSite.y-40;
					}
					_ZOMBIE[iZomSum].cName = iAZomName[cZomChoose-1];
					_ZOMBIE[iZomSum].iLife = iAZomLife[cZomChoose-1];
					_ZOMBIE[iZomSum].iSpeed = iAZomSpeed[cZomChoose-1];
					iZomCount -= _CARDZOM[cZomChoose].iMoney;
					iZomSum++;
				}
				_CARDZOM[cZomChoose].cCanFlg = NO;
			}			
		}break;
	}
}