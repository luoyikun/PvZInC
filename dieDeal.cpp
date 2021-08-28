#include "stdafx.h"
#include "resource.h"
#include "config.h"

__CARTOON  *_qBulletKill = NULL;   // 子弹杀死僵尸链表头
__CARTOON  *_qChompertKill = NULL;   // 食人花杀死僵尸链表头
__CARTOON *_qSquashKill = NULL;
__CARTOON *_qJalapenoKill = NULL;
__CARTOON *_qBoomKill = NULL;
__CARTOON *_qPoleVaultingZombieJump = NULL;
__CARTOON *_qPoleVaultingZombieDie = NULL;
__CARTOON *_qNewspaperZombieDie = NULL;

__CARTOON * killInit()
{
	int  i;
	__CARTOON *_qKill =NULL;
	__CARTOON *e;
	
	//创建子弹杀死僵尸链表
	if(_qKill==NULL)
	{
		_qKill=(struct __CARTOON*)malloc(sizeof(struct __CARTOON));
		_qKill->next=NULL;
	}
	e=_qKill;
    for( i=0; i<SameTime; i++ )
    {
        e->next=(struct  __CARTOON*)malloc(sizeof(struct  __CARTOON));
		e->iCurFrame=-1;
		e->iUpdate=0;
		e->iType=0;
		e->next->next=NULL;
		e=e->next;
	}
	return _qKill;
}

//激活一个地方杀死僵尸
void killActivate( int nX, int nY, int nType,__CARTOON * _qKill)
{
	int i;
	struct  __CARTOON *e;
	e=_qKill;

    for( i=0; i<SameTime; i++ )
    {
		if( e->iCurFrame==-1 )	
        {
            e->iXpos= nX;
			e->iYpos= nY;
			e->iType= nType;
			e->iCurFrame = 0;
            break;//这个break很重要
        }
		e=e->next;
    }
}

void dieInit()
{
	_qBulletKill =	killInit();
	_qChompertKill = killInit();
	_qSquashKill=killInit();
	_qJalapenoKill=killInit();
	_qBoomKill = killInit();
	_qPoleVaultingZombieJump= killInit();
	_qPoleVaultingZombieDie = killInit();
	_qNewspaperZombieDie = killInit();
}
