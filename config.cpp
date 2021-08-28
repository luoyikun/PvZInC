#ifndef _CONFIG_H
#define _CONFIG_H

#define                               C_TILE_W     30
#define                               C_TILE_H     30

#define                               C_MAP_W      32
#define                               C_MAP_H      20

enum
{
	GAMESTART,
	GAMEMENU,
	GAMELOOP,
    GAMEOVER
};

enum ENUM_GAMEMENU            //游戏菜单界面
{
    GM_START,
	GM_EXIT
};
enum ENUM_GAMEOVERMENU        //游戏OVER界面
{
    GM_OVER_REPLAY,
	GM_OVER_RESTART
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
	NO,
	OK,
	Grassland
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
	GSun,
	GWallnut_cracked1,
	GWallnut_cracked2,
	GChomperAttack,
	GChomperDigest,

	GMax
};
typedef struct 
{
	char cName;
	char cLife;
	char cSun;
	char cChomper;
	char cSquash;
    char cBomb;
	POINT ptSite;
}__MAPNATURE;

extern int iTx;
extern int iTy;
extern char flg;
extern HBITMAP     hBmpCard[16];
extern Image *imageGif[GMax];
extern HDC			hdcImageStore;		//用于储存图像的内存DC
extern HDC         hdcImageDraw;		//用于绘制图像的内存DC
extern HBITMAP		hBmpBackground;     //游戏时的背景
extern HWND	    hwndWindow;                                   //windows窗口句柄
extern HBITMAP		hBmpLoge;                                 //logo画面 相关位图的句柄,也是指针
extern char cMenuSelecte;                            // 菜单选项
extern int		iGameState;                               // 游戏状态
extern __MAPNATURE _MAP[5][9];
extern char cCardChoose;
extern char cACardisOK[8];
extern HBITMAP     hBmpTest;
extern HBITMAP     hBmpOverRestart;
extern bool frameInto(HINSTANCE hinstance,DWORD dwTime);
extern void windowInit(HINSTANCE hinstance);
extern void picturerDraw();
extern bool menuDisplay();
extern bool keyDeal( WPARAM wKey );
extern bool gameProgress( DWORD dwTime );
extern void cardChoose(HWND hWnd,WPARAM wParam,LPARAM lParam);
extern void mapInit();
extern char grasslandEnsure(HWND hWnd,WPARAM wParam,LPARAM lParam);
extern POINT coordLocate(HWND hWnd,WPARAM wParam,LPARAM lParam);

extern void transparentPaint( HDC hdcDest, int nX, int nY, int nWidth, int nHeight, int nSrcX, int nSrcY, COLORREF nBkColor );
extern  Image *image;
#endif