#include "stdafx.h"
#include "resource.h"
#include "config.h"
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib")

HDC			hdcImageStore;		//���ڴ���ͼ����ڴ�DC
HDC         hdcImageDraw;		//���ڻ���ͼ����ڴ�DC

HWND	    hwndWindow;			//windows���ھ��
HBITMAP     hBmpGame;			// ��Ϸ����

HBITMAP		hBmpBackground;     //��Ϸʱ�ı���

HBITMAP     hBmpSun;  //̫���÷ֵı���
HBITMAP     hBmpPlan;
HBITMAP     hBmpShovel;    //����
HBITMAP     hBmpShovelBack;//���ӵı���

HBITMAP		hBmpCard[16];
HBITMAP		hBmpCardZom[14];

HBITMAP     hBmpZomBack;
HBITMAP		hBmpCursorCard;

HBITMAP     hBmpLawnMower;

HBITMAP     hBmpTraget[2];
HBITMAP		hBmpTombstone[2];
HBITMAP     hBmpBullet;
HBITMAP		hBmpPeaBulletHit;
HBITMAP		hBmpZombieDie;
HBITMAP     hBmpChomperAttack;
HBITMAP     hBmpSquashAttack;
HBITMAP     hBmpJalapenoAttack;
HBITMAP     hBmpBoomDie;
HBITMAP		hBmpBoom;
HBITMAP		hBmpPoleVaultingZombieJump;
HBITMAP		hBmpPoleVaultingZombieDie;
HBITMAP		hBmpNewspaperZombieDie;

HBITMAP		hBmpZomWin;
HBITMAP     hBmpPlantWin;
HBITMAP		hBmpReplay;
HBITMAP		hBmpExit;
BITMAP      bmpInfo;			//������ȡͼ��ĸߺͿ�
char cMenuSelecte=0;
//����λͼ��ʼ��
void windowInit(HINSTANCE hinstance)
{
	char cCardIndex = PeaShooter;
	char cZomIndex = Tombstone;
	PAINTSTRUCT		ps;
	HDC				hdc;
	
	hdc=GetDC(NULL);//�ú�������һָ�����ڵĿͻ������������Ļ����ʾ�豸�����Ļ����ľ�����Ժ������GDI������ʹ�øþ�������豸�����Ļ����л�ͼ�� 
	
	hdcImageDraw=CreateCompatibleDC( hdc );//�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ�����DC����ͨ��GetDc()��ȡ��HDCֱ��������豸��ͨ����������������DC���������ڴ��е�һ�������������
	hdcImageStore=CreateCompatibleDC( hdc );
	hBmpGame = CreateCompatibleBitmap( hdc, C_MAP_W*C_TILE_W, C_MAP_H*C_TILE_H );//�ú���������ָ�����豸������ص��豸���ݵ�λͼ

	hBmpBackground=(HBITMAP)LoadImage( NULL, _T("tu/tool/Background1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	//�㶹����--ʳ�˻�
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/PeaShooter.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/SunFlower.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/WallNut.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/Chomper.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/Repeater.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/Squash.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/Jalapeno.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/CherryBomb.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/PeaShooterG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/SunFlowerG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/WallNutG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/ChomperG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/RepeaterG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/SquashG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/card/JalapenoG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCard[cCardIndex]   = (HBITMAP)LoadImage( NULL, _T("tu/card/CherryBombG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpSun= (HBITMAP)LoadImage( NULL, _T("tu/tool/SunBack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpShovelBack = (HBITMAP)LoadImage( NULL, _T("tu/tool/ShovelBack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ); 
	hBmpShovel  = (HBITMAP)LoadImage( NULL, _T("tu/tool/Shovel.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ); 

	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/TombstoneCard.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/CardZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/CardFlagZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/CardConeheadZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/CardBucketheadZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/CardNewspaperZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/CardPoleVaultingZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GTombstoneCard.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GCardZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GCardFlagZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GCardConeheadZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GCardBucketheadZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GCardNewspaperZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCardZom[cZomIndex++] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/blackCard/GCardPoleVaultingZombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpZomBack = (HBITMAP)LoadImage( NULL, _T("tu/tool/ZomBack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpCursorCard = (HBITMAP)LoadImage( NULL, _T("tu/tool/CursorCard.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpLawnMower = (HBITMAP)LoadImage( NULL, _T("tu/tool/LawnMower.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpTraget[0] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/TargetBig.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpTraget[1] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/TargetSmall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpTombstone[0] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/TombstoneBig.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpTombstone[1] = (HBITMAP)LoadImage( NULL, _T("tu/CardZom/TombstoneSmall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpBullet  = (HBITMAP)LoadImage( NULL, _T("tu/tool/bullet.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpPeaBulletHit = (HBITMAP)LoadImage( NULL, _T("tu/tool/PeaBulletHit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpZombieDie = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/ZombieDie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpChomperAttack = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/ChomperAttack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpSquashAttack =	(HBITMAP)LoadImage( NULL, _T("tu/cartoon/SquashAttack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpJalapenoAttack = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/JalapenoAttack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpBoomDie = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/BoomDie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpBoom = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/Boom.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpPoleVaultingZombieJump = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/PoleVaultingZombieJump.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpPoleVaultingZombieDie = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/PoleVaultingZombieDie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpNewspaperZombieDie = (HBITMAP)LoadImage( NULL, _T("tu/cartoon/NewspaperZombieDie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	hBmpZomWin = (HBITMAP)LoadImage( NULL, _T("tu/game/ZombiesWon.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpPlantWin = (HBITMAP)LoadImage( NULL, _T("tu/game/Credits_ZombieNote.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpReplay =  (HBITMAP)LoadImage( NULL, _T("tu/game/replay.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBmpExit =  (HBITMAP)LoadImage( NULL, _T("tu/game/menuexit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	ReleaseDC(hwndWindow,hdc);
	EndPaint(hwndWindow,&ps);
}

void gifLoad()
{
	imageGif[GPeashooter]=new Image(L"tu\\Peashooter.gif");
	imageGif[GSunFlower]=new Image(L"tu\\SunFlower.gif");
	imageGif[GWallNut]=new Image(L"tu\\WallNut\\WallNut.gif");
	imageGif[GWallnut_cracked1]=new Image(L"tu\\WallNut\\Wallnut_cracked1.gif");
	imageGif[GWallnut_cracked2]=new Image(L"tu\\WallNut\\Wallnut_cracked2.gif");
	
	imageGif[GChomper]=new Image(L"tu\\Chomper\\Chomper.gif");
	imageGif[GChomperAttack]=new Image(L"tu\\Chomper\\ChomperAttack.gif");
	imageGif[GChomperDigest]=new Image(L"tu\\Chomper\\ChomperDigest.gif");
	imageGif[GRepeater]=new Image(L"tu\\Repeater.gif");
	imageGif[GSquash]=new Image(L"tu\\Squash\\Squash.gif");
	imageGif[GJalapeno]=new Image(L"tu\\Jalapeno\\Jalapeno.gif");
	imageGif[GCherryBomb]=new Image(L"tu\\CherryBomb\\CherryBomb.gif");
	
	imageGif[GZombie]=new Image(L"tu\\Zombie\\Zombie.gif");
	imageGif[GZombieAttack]=new Image(L"tu\\Zombie\\ZombieAttack.gif");
	imageGif[GFlagZombie]=new Image(L"tu\\FlagZombie\\FlagZombie.gif");
	imageGif[GFlagZombieAttack]=new Image(L"tu\\FlagZombie\\FlagZombieAttack.gif");
	
	imageGif[GConeheadZombie]   =   new Image(L"tu\\ConeheadZombie\\ConeheadZombie.gif");
	imageGif[GConeheadZombieAttack]=new Image(L"tu\\ConeheadZombie\\ConeheadZombieAttack.gif");
	imageGif[GBucketheadZombie]     = new Image(L"tu\\BucketheadZombie\\BucketheadZombie.gif");
	imageGif[GBucketheadZombieAttack]=new Image(L"tu\\BucketheadZombie\\BucketheadZombieAttack.gif");
	
	imageGif[GPointerDown] =new Image(L"tu\\tool\\PointerDown.gif");
	imageGif[GSun]=new Image(L"tu\\tool\\Sun.gif");

	imageGif[GHeadAttack0] = new Image(L"tu\\NewspaperZombie\\HeadAttack0.gif");
	imageGif[GHeadAttack1] = new Image(L"tu\\NewspaperZombie\\HeadAttack1.gif");
	imageGif[GHeadWalk0] = new Image(L"tu\\NewspaperZombie\\HeadWalk0.gif");
	imageGif[GHeadWalk1] = new Image(L"tu\\NewspaperZombie\\HeadWalk1.gif");

	imageGif[GPoleVaultingZombie] = new Image(L"tu\\PoleVaultingZombie\\PoleVaultingZombie.gif");
	imageGif[GPoleVaultingZombieAttack] = new Image(L"tu\\PoleVaultingZombie\\PoleVaultingZombieAttack.gif");
	imageGif[GPoleVaultingZombieWalk] = new Image(L"tu\\PoleVaultingZombie\\PoleVaultingZombieWalk.gif");
}

// ��ʾ��Ϸ����
bool gameOver()
{
    int nHeigiht = 0;
    int nMenuStartHeight = 0;
    
    BitBlt( hdcImageDraw, 0, 0, C_MAP_W*C_TILE_W, C_MAP_H*C_TILE_H, hdcImageDraw,0, 0, BLACKNESS );
    
	if( cWinFlg == ZomWin) {
		SelectObject(hdcImageStore,hBmpZomWin);
		GetObject( hBmpZomWin, sizeof(bmpInfo), &bmpInfo );
	}
	if ( cWinFlg == PlantWin ) {
		SelectObject(hdcImageStore,hBmpPlantWin);
		GetObject(hBmpPlantWin, sizeof(bmpInfo), &bmpInfo );
	}
	
    BitBlt (hdcImageDraw, (C_MAP_W*C_TILE_W - bmpInfo.bmWidth)/2, nHeigiht, bmpInfo.bmWidth, bmpInfo.bmHeight, hdcImageStore, 0, 0, SRCCOPY) ;
	
    nHeigiht += bmpInfo.bmHeight ;
    nMenuStartHeight = nHeigiht;
	
    GetObject( hBmpReplay, sizeof(bmpInfo), &bmpInfo );
    SelectObject(hdcImageStore, hBmpReplay );
    BitBlt( hdcImageDraw, (C_MAP_W*C_TILE_W - bmpInfo.bmWidth)/2, nHeigiht, bmpInfo.bmWidth, 60, hdcImageStore,0, (cMenuSelecte == 0)?60:0 , SRCCOPY);
    nHeigiht += 60;
	
    GetObject( hBmpExit, sizeof(bmpInfo), &bmpInfo );
    SelectObject(hdcImageStore, hBmpExit );
    BitBlt( hdcImageDraw, (C_MAP_W*C_TILE_W - bmpInfo.bmWidth)/2, nHeigiht, bmpInfo.bmWidth, 60,hdcImageStore, 0,(cMenuSelecte == 1)?60:0 , SRCCOPY);
    
    return true;
}
