
// IndustrialCamera.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIndustrialCameraApp: 
// �йش����ʵ�֣������ IndustrialCamera.cpp
//

class CIndustrialCameraApp : public CWinApp
{
public:
	CIndustrialCameraApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIndustrialCameraApp theApp;