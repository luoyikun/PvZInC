#ifndef _CONFIG_H
#define _CONFIG_H

#define                               C_TILE_W     37
#define                               C_TILE_H     30

#define                               C_MAP_W      30
#define                               C_MAP_H      20

#define TIMER_REDRAW 1
#define TIMER_FIR 2
#define TIMER_SEC 3


#define PeaShooterTime 10
#define SunFlowerTime 10
#define WallNutTime   20
#define ChomperTime   10
#define RepeaterTime  10
#define SquashTime    10
#define JalapenoTime  15
#define CherryBombTime 15

#define PeaShooterLife   10
#define SunFlowerLife	 10
#define WallNutLife		 20
#define ChomperLife      8
#define RepeaterLife	 15
#define SquashLife        0
#define JalapenoLife		10
#define CherryBombLife		0

#define PeaShooterMoney   100
#define SunFlowerMoney	 50
#define WallNutMoney		 50
#define ChomperMoney      75
#define RepeaterMoney	 150
#define SquashMoney        50
#define JalapenoMoney		125
#define CherryBombMoney		150

#define  ShovelInitXpos   237
#define  ShovelInitYpos   4

#define TombstoneTime		20
#define ZombieTime			10
#define FlagZombieTime      10
#define ConeheadZombieTime      10
#define BucketheadZombieTime    10
#define NewspaperZombieTime     15
#define PoleVaultingZombieTime  15 

#define TombstoneMoney		100
#define ZombieMoney			100
#define FlagZombieMoney		100
#define ConeheadZombieMoney			100
#define BucketheadZombieMoney		100
#define NewspaperZombieMoney		150
#define PoleVaultingZombieMoney		150 

#define  ZombieSpeed				10
#define  FlagZombieSpeed			30
#define  ConeheadZombieSpeed		10
#define  BucketheadZombieSpeed		10
#define  NewspaperZombieSpeed		5
#define  PoleVaultingZombieSpeed	20

#define  TombstoneLife			15	
#define  ZombieLife				15
#define  FlagZombieLife			15
#define  ConeheadZombieLife		15
#define  BucketheadZombieLife	15
#define  NewspaperZombieLife	15
#define  PoleVaultingZombieLife	15
#define  TargetLife              30

#define  ZOMMAX  2000	
#define  SameTime 30
enum
{
	GAMESTART,
	GAMEMENU,
	GAMELOOP,
    GAMEOVER
};

enum ENUM_GAMEMENU            //????????????
{
    GM_START,
	GM_EXIT
};
enum ENUM_GAMEOVERMENU        //????OVER????
{
    REPLAY,
	OVER
};

enum {
	PeaShooter,
	SunFlower,
	WallNut,
	Chomper,
	Repeater,
	Squash,
	Jalapeno,
	CherryBomb,
	Grassland,
	Shovel,
	Card,
	NO,
	OK,
	DOING,
	ZomWin,
	PlantWin
};

enum {
	Tombstone,
	Zombie,
	FlagZombie,
	ConeheadZombie,
	BucketheadZombie,
	NewspaperZombie,
	PoleVaultingZombie,
	ZombieSum
};

enum {
	GPeashooter,
	GSunFlower,
	GWallNut,
	GChomper,
	GRepeater,
	GSquash,
	GJalapeno,
	GCherryBomb,

	GZombie,
	GZombieAttack,
	GFlagZombie,
	GFlagZombieAttack,
	GConeheadZombie,
	GConeheadZombieAttack,
	GBucketheadZombie,
	GBucketheadZombieAttack,
	GHeadWalk1,
    GHeadAttack1,
	GHeadWalk0,
    GHeadAttack0,
	GPoleVaultingZombieWalk,
	GPoleVaultingZombieAttack,
	GPoleVaultingZombie,

	GSun,
	GWallnut_cracked1,
	GWallnut_cracked2,
	GChomperAttack,
	GChomperDigest,
	
	GPointerDown,
	
	GMax,	
	
};

enum{
	CBulletKill,
	CSquashKill,
	CChompertKill,
	CJalapenoKill,
	CBoomKill,
	CPoleVaulting
};
typedef struct 
{
	char cName;		//????????????????
	int iLife;		//??????????????????
	char cSun;		//????????????????
	char cChomper;  //????????????
	char cSquash;   //??????????
    char cBomb;		//??????????
	char cCherryBomb;//??????????
	POINT ptSite;   //??????????????
	char cBeat;		//??????????????????????????
}__MAPNATURE;

typedef struct {
	char cCanFlg; //????????????
	int iCount;   //??????????
	POINT ptSite; //??????????
	char pTime[8];//??????????
	int iColor;   //????????????
	int iMoney;   //????????????????
}__CARDNATURE;
//??????????
typedef struct {
	char cAlive;  //????????
	char cName;	  //??????????
	int  iLife;	  //????????????
	char cPole;	  //??????????????????????
	int  iSpeed;  //????????????????
	POINT ptSite; //??????????
	char cBeat;   //??????????????????
	char cAttack; //??????????????????
	char cPass;   //????????????????????????????
	char cProtect;//????????????????????????????????????
	char cPoleVaulting;//????????????????????
}__ZOMBIENATURE;
//????
typedef struct {
	char cActive;  //????????????????????????????
	char cAlive;   //????????????????????????
	POINT ptSite;  //????????
}__LAWNMOVERNATURE;
//????????
typedef struct {
	int iLife;    //????????????????
	POINT ptSite; //??????????
	char cBeat;   //??????????????
}__TARGETNATURE;
//????????
typedef struct
{
	char  cAlive;     //????????????????????????????????
	char  cOpen;      //????????????
	POINT ptSite;     //????????????
	POINT ptNew;	  //????????????
}__BULLETNATURE;

// ????
struct __CARTOON
{
	int iXpos;                                                           // ????X
	int iYpos;                                                           // ????Y
	int   iCurFrame;                        // ??????
    int   iType;                            // ????????????
    int   iUpdate;                        // ????????????
    struct __CARTOON *next;
};

extern struct __CARTOON  *_qBulletKill;   // ??????????
extern Image *imageGif[GMax];
extern HDC			hdcImageStore;		//??????????????????DC
extern HDC         hdcImageDraw;		//??????????????????DC
extern HBITMAP		hBmpBackground;     //????????????
extern HWND	    hwndWindow;                                   //windows????????
extern HBITMAP		hBmpLoge;                                 //logo???? ??????????????,????????
extern char cMenuSelecte;                            // ????????
extern int		iGameState;                               // ????????
extern __MAPNATURE _MAP[5][9];
extern char cCardChoose;
extern char cACardisOK[8];
extern HBITMAP     hBmpTest;
extern HBITMAP     hBmpOverRestart;
extern HBITMAP		hBmpCard[16];
extern HBITMAP     hBmpGame;			// ????????
extern __CARDNATURE _CARD[8];
extern int iACardTime[8];
extern char cFollowFlg;
extern int iFollowXpos;
extern int iFollowYpos; 
extern HBITMAP     hBmpSun;  //??????????????
extern HBITMAP     hBmpShovelBack; //??????????
extern HBITMAP     hBmpShovel;    //????
extern int iShovelXpos ;
extern int iShovelYpos ;
extern char cSunFlg;
extern int iSunCount;
extern HBITMAP		hBmpCardZom[14];
extern __CARDNATURE _CARDZOM[7];
extern HBITMAP     hBmpZomBack;
extern HBITMAP		hBmpCursorCard;
extern int iCursorCardIndex;
extern char cZomChoose;
extern __MAPNATURE _MAPZOM[5][3];
extern int iPointerXpos ;
extern int iPointerYpos ;
extern __ZOMBIENATURE _ZOMBIE[ZOMMAX];
extern int iZomCount;
extern int iZomSum ;
extern char cRandom;
extern int iRandomXpos;
extern int iRandomYpos;
extern HBITMAP     hBmpLawnMower;
extern __LAWNMOVERNATURE  _LAWNMOVER[5];
extern HBITMAP     hBmpTraget[2];
extern __TARGETNATURE   _TARGET[5];
extern HBITMAP		hBmpTombstone[2];
extern __BULLETNATURE   _BULLET[30];
extern HBITMAP		hBmpPeaBulletHit;
extern int iAMapLife[8];
extern int iPeaShooterCnt;
extern HBITMAP     hBmpBullet;
extern HBITMAP		hBmpZombieDie;
extern __BULLETNATURE   _TWOBULLET[30];
extern HBITMAP     hBmpChomperAttack;
extern struct __CARTOON  *_qChompertKill; 
extern int iChomperTmp;
extern HBITMAP     hBmpSquashAttack;
extern int iSquashTmp;
extern __CARTOON *_qSquashKill ;
extern __CARTOON *_qJalapenoKill;
extern HBITMAP     hBmpJalapenoAttack;
extern HBITMAP     hBmpBoomDie;
extern __CARTOON *_qBoomKill ;
extern HBITMAP		hBmpBoom;
extern HBITMAP		hBmpPoleVaultingZombieJump;
extern __CARTOON *_qPoleVaultingZombieJump;
extern int iPoleVaultingTmp;
extern char cWinFlg;
extern char cMenuSelecte;
extern int iZomCnt;
extern __CARTOON *_qPoleVaultingZombieDie;
extern HBITMAP		hBmpNewspaperZombieDie;
extern HBITMAP		hBmpPoleVaultingZombieDie;
extern __CARTOON *_qNewspaperZombieDie;
extern bool frameInto(HINSTANCE hinstance,DWORD dwTime);
extern void windowInit(HINSTANCE hinstance);
extern void picturerDraw();
extern bool gameProgress( DWORD dwTime );
extern void cardChoose(HWND hWnd,WPARAM wParam,LPARAM lParam);
extern void mapInit();
extern char grasslandEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam);
extern POINT coordLocate(HWND hWnd,WPARAM wParam,LPARAM lParam);
extern void transparentPaint( HDC hdcDest, int nX, int nY, int nWidth, int nHeight, int nSrcX, int nSrcY, COLORREF nBkColor );
extern void cardInit();
extern bool  timeDeal ( DWORD dwTime );
extern char shovelEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam);
extern bool  sunDeal ( DWORD dwTime );
extern char cardEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam); 
extern void cardZomInit ();
extern void keyDeal( WPARAM wKey );
extern void mapZomInit();
extern void mapZomInit();
extern void zombieInit ();
extern bool  zomDeal ( DWORD dwTime );
extern bool  sunRandomDeal ( DWORD dwTime );
extern void lawnMowerInit();
extern void tragetInit();
extern void allInit ();
extern void gifLoad();
extern void hitDeal();
extern void dieInit();
extern void killActivate( int nX, int nY, int nType,__CARTOON * _qBulletKill );
extern void mapClear( int cROw, int cCol );
extern bool gameInterface();
extern bool gameOver();
#endif