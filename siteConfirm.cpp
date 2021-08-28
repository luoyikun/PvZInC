#include "stdafx.h"
#include "resource.h"
#include "config.h"

char cCardChoose = NO;
char cACardisOK[8]={OK,OK,OK,OK,OK,OK,OK,OK};

void cardChoose(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	//char cCardChoose = NO;
	
	for (char cCradIndex = PeaShooter; cCradIndex <= CherryBomb; cCradIndex++) {
		if ( /*iSunCount >= _CARD[cCardChoose].iMoney &&*/ LOWORD(lParam) >= 5 && LOWORD(lParam) <= 105 && HIWORD(lParam) > (2+64*cCradIndex) && HIWORD(lParam) <= (2+64*(cCradIndex+1)) && _CARD[cCradIndex].cCanFlg == OK) {
			cCardChoose = cCradIndex;
		}
	}
	
	//return cCardChoose;
}

POINT coordLocate(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	POINT ptCoord;
	
	for (int index = 1; index <= 17; index = index+2 ) {
		if ( LOWORD(lParam) > 180+40*(index-1) && LOWORD(lParam) <= 180+40*(index+1) )
			ptCoord.y = (index-1)/2;
		if ( HIWORD(lParam) > 76+50*(index-1) && HIWORD(lParam) <= 76+50*(index+1) )
			ptCoord.x = (index-1)/2;
	}
	return ptCoord;
}

char grasslandEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam) 
{
	char cGrasslandFlg = NO;
	
	if ( LOWORD(lParam) >= 180 && LOWORD(lParam) <= 665 && HIWORD(lParam) >= 74 && HIWORD(lParam) <= 576 ) {
		cGrasslandFlg = Grassland;
	}
	else
		cGrasslandFlg = NO;

	return  cGrasslandFlg;
}

char shovelEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam) 
{
	char cShovelFlg = NO;
	
	if ( LOWORD(lParam) >= 237 && LOWORD(lParam) <= 308 && HIWORD(lParam) >= 4 && HIWORD(lParam) <= 39 ) {
		cShovelFlg = Shovel;
	}

	return  cShovelFlg;
}

char cardEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam) 
{
	char cCardFlg = NO;
	
	if ( LOWORD(lParam) >= 0 && LOWORD(lParam) <= 180 && HIWORD(lParam) >= 0 && HIWORD(lParam) <= 600 ) {
		cCardFlg = Card;
	}
	
	return  cCardFlg;
}




