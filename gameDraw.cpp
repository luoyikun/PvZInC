#include "stdafx.h"
#include "resource.h"
#include "config.h"
#include "stdio.h"
#include "time.h"  

int iFollowXpos = 0;
int iFollowYpos = 0;

int iShovelXpos =ShovelInitXpos;
int iShovelYpos =ShovelInitYpos;

int iPointerXpos = 0;
int iPointerYpos = 0;

// ͸������
void transparentPaint( HDC hdcDest, int nX, int nY, int nWidth, int nHeight, int nSrcX, int nSrcY, COLORREF nBkColor )
{
    TransparentBlt( hdcDest, nX, nY, nWidth, nHeight, hdcImageStore, nSrcX, nSrcY, nWidth, nHeight, nBkColor );
	//MSIMG32.dll Ҫʹ��͸����ͼ��Ч��
	//msimg32.dll
}
//������
void wordShow(HDC hdc,int iSize,int iXpos,int iYpos,char *szBuffer,int iColor)
{
	LOGFONT   logfont;       //�ı��������
	ZeroMemory(&logfont,   sizeof(LOGFONT));   
	logfont.lfCharSet   =   GB2312_CHARSET;   
	logfont.lfHeight   =   iSize;      //��������Ĵ�С
	HFONT   hFont   =   CreateFontIndirect(&logfont);   
	SetTextColor(hdc,iColor);
	SetBkColor(hdc,RGB(200,200,0));
	SetBkMode(hdc,TRANSPARENT);
	SelectObject(hdc, hFont); 
	TextOut(hdc,iXpos,iYpos,szBuffer,strlen(szBuffer) );
    DeleteObject(hFont);
}
//������Ϸ�ı���
void backgroudDraw()
{
	SelectObject(hdcImageStore, hBmpBackground );
	BitBlt( hdcImageDraw, 0,0, C_TILE_W*C_MAP_W,C_TILE_H*C_MAP_H, hdcImageStore,0, 0 , SRCCOPY);
	
	SelectObject(hdcImageStore, hBmpSun);
	transparentPaint( hdcImageDraw,110,9,123,34,0,0, RGB(255, 255, 255) );

	SelectObject(hdcImageStore, hBmpShovelBack);
	transparentPaint( hdcImageDraw,237,9,71,35,0,0, RGB(255, 255, 255) );

	SelectObject(hdcImageStore, hBmpZomBack);
	transparentPaint( hdcImageDraw,820,9,123,34,0,0, RGB(255, 255, 255) );
}

//����ֲ��Ŀ�Ƭ
void cardDraw()
{
	for (char cCardIndex = PeaShooter; cCardIndex <= CherryBomb; cCardIndex++) {
		if ( _CARD[cCardIndex].cCanFlg == OK ) {
			SelectObject(hdcImageStore, hBmpCard[cCardIndex]);
 			if (cCardIndex == CherryBomb|| cCardIndex == Jalapeno) 
 				transparentPaint( hdcImageDraw,5,4+64*cCardIndex,100,60,0,0, RGB(255, 0, 255));
			else if (cCardIndex == WallNut) 
					transparentPaint( hdcImageDraw,5,4+64*cCardIndex,100,59,0,0, RGB(255, 0, 0) );
 			else
 				transparentPaint( hdcImageDraw,5,4+64*cCardIndex,100,60,0,0, RGB(255, 0, 0) );
		}
		if ( _CARD[cCardIndex].cCanFlg == NO || iSunCount < _CARD[cCardIndex].iMoney ) {
			SelectObject(hdcImageStore, hBmpCard[cCardIndex+8]);
			if( cCardIndex == WallNut )
				transparentPaint( hdcImageDraw,5,4+64*cCardIndex,100,59,0,0, RGB(255, 0, 0) );
			else 
				transparentPaint( hdcImageDraw,5,4+64*cCardIndex,100,60,0,0, RGB(255, 0, 0) );
		}
	}
} 

//���ƽ�ʬ�Ŀ�Ƭ
void cardZomDraw()
{
	for (char cCardIndex = Tombstone; cCardIndex < ZombieSum; cCardIndex++) {
		if ( _CARDZOM[cCardIndex].cCanFlg == OK ) {
			SelectObject(hdcImageStore, hBmpCardZom[cCardIndex]);
			BitBlt( hdcImageDraw, _CARDZOM[cCardIndex].ptSite.x,_CARDZOM[cCardIndex].ptSite.y, 100,60, hdcImageStore,0, 0 , SRCCOPY);
		}
		if ( _CARDZOM[cCardIndex].cCanFlg == NO || iZomCount < _CARDZOM[cCardIndex].iMoney) {
			SelectObject(hdcImageStore, hBmpCardZom[cCardIndex+7]);
			BitBlt( hdcImageDraw, _CARDZOM[cCardIndex].ptSite.x,_CARDZOM[cCardIndex].ptSite.y, 100,60, hdcImageStore,0, 0 , SRCCOPY);
		}

		char cZomCount[8];
		sprintf(cZomCount,"%d",_CARDZOM[cCardIndex].iMoney);
		wordShow(hdcImageDraw,22,_CARDZOM[Tombstone].ptSite.x,_CARDZOM[cCardIndex].ptSite.y+20,cZomCount,RGB(0, 0, 0));
	}

	SelectObject(hdcImageStore, hBmpCursorCard);
	transparentPaint( hdcImageDraw,_CARDZOM[Tombstone].ptSite.x,_CARDZOM[iCursorCardIndex].ptSite.y,100,60,0,0, RGB(255, 255, 255));
	//BitBlt( hdcImageDraw, _CARDZOM[Tombstone].ptSite.x,_CARDZOM[Tombstone].ptSite.y, 100,60, hdcImageStore,0, 0 , SRCCOPY);
}

//����ֲ��
void plantDraw () 
{
	Graphics graphics(hdcImageDraw);
	for ( char cRow = 0; cRow < 5; cRow++ ) {
		for ( char cCol = 0; cCol < 9; cCol++ ) {
			if ( _MAP[cRow][cCol].cName != NO ) {
				if ( _MAP[cRow][cCol].cName == Chomper ) {
					if (_MAP[cRow][cCol].cChomper == OK ) 
						graphics.DrawImage(imageGif[_MAP[cRow][cCol].cName],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y-35);
					if (_MAP[cRow][cCol].cChomper == NO)
						graphics.DrawImage(imageGif[GChomperDigest],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y-35);
				}	
				else  if ( _MAP[cRow][cCol].cName == WallNut) {
					if ( _MAP[cRow][cCol].iLife <= WallNutLife-5 && _MAP[cRow][cCol].iLife > WallNutLife-15)
						graphics.DrawImage(imageGif[GWallnut_cracked1],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y+10);
				    if ( _MAP[cRow][cCol].iLife <= WallNutLife-15 && _MAP[cRow][cCol].iLife > WallNutLife-20)
						graphics.DrawImage(imageGif[GWallnut_cracked2],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y+10);
					if ( _MAP[cRow][cCol].iLife <= WallNutLife && _MAP[cRow][cCol].iLife > WallNutLife-5) 
						graphics.DrawImage(imageGif[GWallNut],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y+10);
				}
				else
					graphics.DrawImage(imageGif[_MAP[cRow][cCol].cName],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y+10);
			} 
			if (/*_MAP[cRow][cCol].cName == SunFlower &&*/ _MAP[cRow][cCol].cSun == OK )
					graphics.DrawImage(imageGif[GSun],_MAP[cRow][cCol].ptSite.x,_MAP[cRow][cCol].ptSite.y+50);
		}
	}
}

//����������ֲ��
void followPlantDraw () 
{
	Graphics graphics(hdcImageDraw);
	if ( cFollowFlg == OK ) 
		graphics.DrawImage(imageGif[cCardChoose],iFollowXpos,iFollowYpos);
}
//���ӵĻ���
void shovelDraw ()
{
	SelectObject(hdcImageStore, hBmpShovel);
	transparentPaint( hdcImageDraw,iShovelXpos,iShovelYpos,76,34,0,0, RGB(255, 255, 255) );
}
//��ʬ��ָ���ͷ
void pointerDownDraw ()
{
	Graphics graphics(hdcImageDraw);
	graphics.DrawImage(imageGif[GPointerDown],_MAPZOM[iPointerXpos][iPointerYpos].ptSite.x+20,_MAPZOM[iPointerXpos][iPointerYpos].ptSite.y+30);
}
//����ֲ��ʱ�������
void timeDraw ()
{
	for ( char cCardIndex = PeaShooter; cCardIndex <= CherryBomb; cCardIndex++ ) {
		if ( _CARD[cCardIndex].cCanFlg == NO ) {
			sprintf(_CARD[cCardIndex].pTime,"%d",_CARD[cCardIndex].iCount);
			wordShow(hdcImageDraw,60,_CARD[cCardIndex].ptSite.x+30,_CARD[cCardIndex].ptSite.y,_CARD[cCardIndex].pTime,RGB(255, 0, 0));
		}
	}
}

//���ƽ�ʬ��ʱ������
void timeZomDraw ()
{
	for ( char cCardIndex = Tombstone; cCardIndex < ZombieSum; cCardIndex++ ) {
		if ( _CARDZOM[cCardIndex].cCanFlg == NO ) {
			sprintf(_CARD[cCardIndex].pTime,"%d",_CARDZOM[cCardIndex].iCount);
			wordShow(hdcImageDraw,60,_CARDZOM[cCardIndex].ptSite.x+30,_CARDZOM[cCardIndex].ptSite.y,_CARD[cCardIndex].pTime,RGB(255, 0, 0));
		}
	}
}

//����̫���ķ���
void sunDraw () 
{
	char cSunCount[8];
	sprintf(cSunCount,"%d",iSunCount);
	wordShow(hdcImageDraw,35,150,10,cSunCount,RGB(255, 0, 0));
}

//���ƽ�ʬ�ķ���
void zomBrainDraw () 
{
	char cSunCount[8];
	sprintf(cSunCount,"%d",iZomCount);
	wordShow(hdcImageDraw,35,859,10,cSunCount,RGB(255, 0, 0));
}

//�������������
void sunRandomDraw ()
{
	Graphics graphics(hdcImageDraw);
	graphics.DrawImage(imageGif[GSun],_MAPZOM[iRandomXpos][iRandomYpos].ptSite.x,_MAPZOM[iRandomXpos][iRandomYpos].ptSite.y+50);
}

void attackDraw (char cPass, char iZomIndex,int iXpos,int iYpos) 
{
	Graphics graphics(hdcImageDraw);
	if( cPass == OK )
		graphics.DrawImage(imageGif[iZomIndex],iXpos,iYpos);
	if( cPass == NO)
		graphics.DrawImage(imageGif[iZomIndex+1],iXpos,iYpos);
}
//�����ƶ��Ľ�ʬ
void zomDraw ()
{
// 	for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
// 		if ( _ZOMBIE[iZomIndex].cAlive == OK ) {
// 			Graphics graphics(hdcImageDraw);
// 			graphics.DrawImage(imageGif[GZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
// 		}
// 	}
	for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
		if ( _ZOMBIE[iZomIndex].cAlive == OK ) {
			Graphics graphics(hdcImageDraw);
			switch (_ZOMBIE[iZomIndex].cName)
			{
			case Zombie:{
// 							if(_ZOMBIE[iZomIndex].cPass == OK )
// 								graphics.DrawImage(imageGif[GZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
// 							if(_ZOMBIE[iZomIndex].cPass == NO)
// 								graphics.DrawImage(imageGif[GZombieAttack],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							attackDraw (_ZOMBIE[iZomIndex].cPass,GZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
						}break;
			case FlagZombie:{
							attackDraw(_ZOMBIE[iZomIndex].cPass,GFlagZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							//graphics.DrawImage(imageGif[GFlagZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
						}break;
			case ConeheadZombie:{
							if (_ZOMBIE[iZomIndex].cProtect == OK )
								attackDraw(_ZOMBIE[iZomIndex].cPass,GConeheadZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							if (_ZOMBIE[iZomIndex].cProtect == NO )
								attackDraw (_ZOMBIE[iZomIndex].cPass,GZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							//graphics.DrawImage(imageGif[GConeheadZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
						}break;
			case BucketheadZombie:{
							if (_ZOMBIE[iZomIndex].cProtect == OK )
								attackDraw(_ZOMBIE[iZomIndex].cPass,GBucketheadZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							if (_ZOMBIE[iZomIndex].cProtect == NO )
								attackDraw (_ZOMBIE[iZomIndex].cPass,GZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							//graphics.DrawImage(imageGif[GBucketheadZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
						}break;
			case NewspaperZombie:{
							if (_ZOMBIE[iZomIndex].cProtect == OK )
								attackDraw(_ZOMBIE[iZomIndex].cPass,GHeadWalk1,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							if (_ZOMBIE[iZomIndex].cProtect == NO )
								attackDraw(_ZOMBIE[iZomIndex].cPass,GHeadWalk0,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							//graphics.DrawImage(imageGif[GHeadWalk1],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
						}break;
			case PoleVaultingZombie:{
							if (_ZOMBIE[iZomIndex].cPoleVaulting == OK )
								//attackDraw(_ZOMBIE[iZomIndex].cPass,GPoleVaultingZombie,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
								graphics.DrawImage(imageGif[GPoleVaultingZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							if( _ZOMBIE[iZomIndex].cPoleVaulting == NO )
								attackDraw(_ZOMBIE[iZomIndex].cPass,GPoleVaultingZombieWalk,_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
							//graphics.DrawImage(imageGif[GPoleVaultingZombie],_ZOMBIE[iZomIndex].ptSite.x,_ZOMBIE[iZomIndex].ptSite.y);
						}break;
			}		
		}
	}
}

//�����Ƴ�
void lawnMowerDraw()
{
	for (char cMoverindex = 0; cMoverindex < 5; cMoverindex++ ) {
		SelectObject(hdcImageStore, hBmpLawnMower);
		if (_LAWNMOVER[cMoverindex].cAlive ==OK)
			transparentPaint( hdcImageDraw,_LAWNMOVER[cMoverindex].ptSite.x,_LAWNMOVER[cMoverindex].ptSite.y,70,57,0,0, RGB(255, 255, 255) );
	}
}

//���ư���
void tragetDraw()
{
	for (char cMoverindex = 0; cMoverindex < 5; cMoverindex++ ) {
		if (_TARGET[cMoverindex].iLife > 0) {
			if (_TARGET[cMoverindex].iLife > TargetLife-10 && _TARGET[cMoverindex].iLife <= TargetLife) 
				SelectObject(hdcImageStore, hBmpTraget[0]);
			if(_TARGET[cMoverindex].iLife > 0 && _TARGET[cMoverindex].iLife <= TargetLife-10)
				SelectObject(hdcImageStore, hBmpTraget[1]);
			transparentPaint( hdcImageDraw,_TARGET[cMoverindex].ptSite.x,_TARGET[cMoverindex].ptSite.y,80,100,0,0, RGB(255, 255, 255) );
		}
	}

}

//����Ĺ��
void tombstoneDraw()
{
	
	for ( char cRow = 0; cRow < 5; cRow++ ) {
		for ( char cCol = 0; cCol < 3; cCol++ ) {
			if ( _MAPZOM[cRow][cCol].cName == Tombstone ) {
				if (_MAPZOM[cRow][cCol].iLife > TombstoneLife-30 && _MAPZOM[cRow][cCol].iLife <= TombstoneLife) 
					SelectObject(hdcImageStore, hBmpTombstone[0]);
				if (_MAPZOM[cRow][cCol].iLife > 0 && _MAPZOM[cRow][cCol].iLife <= TombstoneLife-30)
					SelectObject(hdcImageStore, hBmpTombstone[1]);
				transparentPaint( hdcImageDraw,_MAPZOM[cRow][cCol].ptSite.x,_MAPZOM[cRow][cCol].ptSite.y,80,100,0,0, RGB(255, 255, 255) );
				//BitBlt( hdcImageDraw, _MAPZOM[cRow][cCol].ptSite.x,_MAPZOM[cRow][cCol].ptSite.y, 80,100, hdcImageStore,0, 0 , SRCCOPY);
			}
		}
	}
}
//�����ӵ�
void bulletDraw ()
{
	
	for (int i =0 ;i < 30; i++)                                  //�жϵз�̹���ӵ��Ƿ���Ҫ����
	{
 		if (_BULLET[i].cOpen == OK && _BULLET[i].cAlive == OK) {
 			SelectObject( hdcImageStore, hBmpBullet);
 			transparentPaint( hdcImageDraw, _BULLET[i].ptNew.x, _BULLET[i].ptNew.y, 30,30, 0, 0, RGB(255, 255, 255) );
 		}
		if (_TWOBULLET[i].cOpen == OK && _TWOBULLET[i].cAlive == OK) {
			SelectObject( hdcImageStore, hBmpBullet);
			transparentPaint( hdcImageDraw, _TWOBULLET[i].ptNew.x-40, _TWOBULLET[i].ptNew.y, 30,30, 0, 0, RGB(255, 255, 255) );
 		}
	}
}

//�����ӵ��ı�ըЧ��
void beatDraw()
{
	for (int iZomIndex = 0; iZomIndex < ZOMMAX; iZomIndex++ ) {
		if ( _ZOMBIE[iZomIndex].cBeat == OK ) {
			SelectObject( hdcImageStore, hBmpPeaBulletHit);
			transparentPaint( hdcImageDraw, _ZOMBIE[iZomIndex].ptSite.x+40,_ZOMBIE[iZomIndex].ptSite.y+20, 52,46, 0, 0, RGB(255, 255, 255) );
		}
	}

	for ( int row = 0; row < 5; row++ ) {
		for (int col = 0; col < 3;col ++) {
			if ( _MAPZOM[row][col].cName == Tombstone &&  _MAPZOM[row][col].cBeat == OK) {
				SelectObject( hdcImageStore, hBmpPeaBulletHit);
				transparentPaint( hdcImageDraw, _MAPZOM[row][col].ptSite.x,_MAPZOM[row][col].ptSite.y+10, 52,46, 0, 0, RGB(255, 255, 255) );
			}
		}
	}

	for (int iTargetIndex = 0; iTargetIndex < 5; iTargetIndex++ ) {
		if ( _TARGET[iTargetIndex].cBeat == OK ) {
			SelectObject( hdcImageStore, hBmpPeaBulletHit);
			transparentPaint( hdcImageDraw, _TARGET[iTargetIndex].ptSite.x,_TARGET[iTargetIndex].ptSite.y+10, 52,46, 0, 0, RGB(255, 255, 255) );
		}
	}
}

void killLoad( int iXpos , int iYpos,HBITMAP hBmp,int iXsize,int iYsize,int iCurFrame)
{
	if( iCurFrame != -1 )   //����-1�����Ʊ�ը
    {       
        SelectObject(hdcImageStore , hBmp);
        transparentPaint( hdcImageDraw, iXpos, iYpos, iXsize,iYsize, 0,iCurFrame*iYsize, RGB(255, 255, 255) );
    }
}

void killDraw(__CARTOON * _qKill,HBITMAP hBmp,int iXoffset,int iYoffset,int iXsize,int iYsize)
{
	int i=0;
	struct __CARTOON *e;
	e=_qKill;
    for( i=0; i<10; i++ )
    {
        killLoad(e->iXpos+iXoffset, e->iYpos+iYoffset, hBmp, iXsize,iYsize,e->iCurFrame);
		e=e->next;
    }
}

void cherryBombDraw ()
{
	for (char row = 0; row < 5; row++ ) {
		for (char col = 0; col < 9; col++ ) {
			if ( _MAP[row][col].cCherryBomb == OK ) {
				SelectObject(hdcImageStore , hBmpBoom);
				transparentPaint( hdcImageDraw, _MAP[row][col].ptSite.x-50, _MAP[row][col].ptSite.y-50, 213,160, 0,0, RGB(255, 255, 255) );
				//_MAP[row][col].cCherryBomb = NO;
			}
		}
	}
}

// ��ʾ��Ϸ����
bool gameInterface()
{
    BitBlt( hdcImageDraw, 0, 0, C_MAP_W*C_TILE_W, C_MAP_H*C_TILE_H, hdcImageDraw,0, 0, BLACKNESS );
    
	backgroudDraw();
	cardZomDraw();
	zomBrainDraw ();
    plantDraw ();
	tombstoneDraw();
	sunDraw ();
	zomDraw ();
	pointerDownDraw ();
	followPlantDraw () ;
	shovelDraw ();
	lawnMowerDraw();
	tragetDraw();
	bulletDraw ();
	cherryBombDraw ();
	beatDraw();
	
	killDraw(_qBulletKill,hBmpZombieDie,0,0,166,144);
	killDraw(_qChompertKill,hBmpChomperAttack,0,-35,130,114);
	killDraw(_qSquashKill,hBmpSquashAttack,40,-100,100,226);
	killDraw(_qJalapenoKill,hBmpJalapenoAttack,-80,0,240,100);
	killDraw(_qBoomKill,hBmpBoomDie,0,0,166,144);
	killDraw(_qPoleVaultingZombieJump,hBmpPoleVaultingZombieJump,-100,-80,348,218);
	killDraw(_qPoleVaultingZombieDie,hBmpPoleVaultingZombieDie,0,0,166,144);
	killDraw(_qNewspaperZombieDie,hBmpNewspaperZombieDie,0,0,166,144);

	cardDraw();//ֲ��Ŀ�Ƭ����
	timeDraw ();//��ȴ��ʱ��
	cardZomDraw();
	timeZomDraw ();

    return true;
}

// �����ܻ���
void picturerDraw()
{
	PAINTSTRUCT		ps;
    HDC     hdc;
	
   	hdc = BeginPaint(hwndWindow,&ps);//����Ϊָ�����ڽ��л�ͼ������׼�������ý��ͻ�ͼ�йص���Ϣ��䵽һ��PAINTSTRUCT�ṹ�С�
	//��һ���Ǵ��ڵľ��  �������ǻ��Ƶ���Ϣ  ����ֵ����ֵ��ָ�����ڵġ���ʾ�豸���������
	SelectObject(hdcImageDraw, hBmpGame);//�ú���ѡ��һ����ָ�����豸�����Ļ����У����¶����滻��ǰ����ͬ���͵Ķ��� 

	BitBlt( hdc, 0, 0, C_MAP_W*C_TILE_W, C_MAP_H*C_TILE_H,hdcImageDraw,0,0, SRCCOPY );
    //�ڰ�Ҫ���ͼ��hdcImageDraw���Ƶ�hdc����ܵĴ���
	EndPaint(hwndWindow,&ps);
}
