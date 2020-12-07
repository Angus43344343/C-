// IndustrialCameraDlg.h : 头文件
#pragma once

#include "mainctrl.h"
#include "SetParam.h"

//CIndustrialCameraDlg 对话框
class CIndustrialCameraDlg : public CDialogEx
{
//构造
public:
	CIndustrialCameraDlg(CWnd* pParent = NULL);	//标准构造函数
//对话框数据
	enum { IDD = IDD_INDUSTRIALCAMERA_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV 支持
//实现
private:

protected:
	HICON m_hIcon;
	//生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	DECLARE_MESSAGE_MAP()
public:
	//===================页面控制项
	afx_msg void OnBtnComCtrl();
	afx_msg void OnBtnSetParam();
	//===================流程控制项
	afx_msg void OnRadioUart();
	afx_msg void OnRadioSock();
	afx_msg void OnBtnComConnect();
	afx_msg void OnBtnClearEdit();
	afx_msg void OnBtnOpenConsole();
	afx_msg void OnBtnCloseConsole();
	//===================命令项
	afx_msg void OnBtnHandshake();
	afx_msg void OnBtnReadCMOS();
	afx_msg void OnBtnSetCMOS();
	afx_msg void OnBtnSoftware();
	afx_msg void OnBtnHardware();
	afx_msg void OnBtnBatchMode();
	afx_msg void OnBtnNormalMode();
	afx_msg void OnBtnRecUart();
	afx_msg void OnBtnRecResult();
//===========================app 自定义消息
	afx_msg LRESULT OnSendData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
//===========================app UI
private:
	FILE *m_pobjStdIn;
	FILE *m_pobjStdOut;

	CEdit m_objEdit;
	CSetParam m_objSetParam;
	EN_DRV_TYPE m_enDrvType;
private:
	void InitUI();
	void ShowWidget(UINT uiStatus);

	void EmptyEditText();
	void SetEditText(CString strPreExplain, PCHAR pcData, ULONG ulDataLen);
//===========================app PROC
private:
	BOOL m_bConnect;
	CMainCtrl m_objMainCtrl;
private:
	void InitProc();
	void SendCmd(EN_FRAME_TYPE enFrameType);
};
