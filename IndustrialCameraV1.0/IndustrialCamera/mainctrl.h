#ifndef _MAINCTRL_H__
#define _MAINCTRL_H__

#include "sockproc.h"
#include "uartproc.h"

class CMainCtrl
{
private:
	CProc *m_apobjProc[DRV_COUNT];
private:
	void InitProc(EN_DRV_TYPE enDrvType);
	void UninitProc(EN_DRV_TYPE enDrvType);
private:
	void Init();
	void Uninit();
public:
	void SetDlgHwnd(EN_DRV_TYPE enDrvType, HWND stHwnd);
	bool OpenDrvCtrl(EN_DRV_TYPE enDrvType);
	void SendDrvCtrl(EN_DRV_TYPE enDrvType, EN_FRAME_TYPE enFrameType);
public:
	CMainCtrl();
	~CMainCtrl();
};

#endif /*_MAINCTRL_H__*/