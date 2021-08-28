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

enum ENUM_GAMEMENU            //��Ϸ�˵�����
{
    GM_START,
	GM_EXIT
};
enum ENUM_GAMEOVERMENU        //��ϷOVER����
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
extern HDC			hdcImageStore;		//���ڴ���ͼ����ڴ�DC
extern HDC         hdcImageDraw;		//���ڻ���ͼ����ڴ�DC
extern HBITMAP		hBmpBackground;     //��Ϸʱ�ı���
extern HWND	    hwndWindow;                                   //windows���ھ��
extern HBITMAP		hBmpLoge;                                 //logo���� ���λͼ�ľ��,Ҳ��ָ��
extern char cMenuSelecte;                            // �˵�ѡ��
extern int		iGameState;                               // ��Ϸ״̬
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