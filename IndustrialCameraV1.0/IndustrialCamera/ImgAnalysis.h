#pragma once
//CImgAnalysis 对话框

#include <Gdiplus.h>
using namespace Gdiplus;

typedef union
{
	REAL rImgX;		/*图片在客户区左上角的点的坐标X*/	
	REAL rImgWidth;	/*图片宽*/
}UN_IMG_X, *PUN_IMG_X;

typedef union
{
	REAL rImgY;
	REAL rImgHigth;
}UN_IMG_Y, *PUN_IMG_Y;

typedef struct
{
	UN_IMG_X unImgX;
	UN_IMG_Y unImgY;
}ST_IMG_INFO, *PST_IMG_INFO;

class CImgAnalysis : public CDialog
{
	DECLARE_DYNAMIC(CImgAnalysis)
public:
	CImgAnalysis(CWnd* pParent = NULL);//标准构造函数
	virtual ~CImgAnalysis();
//对话框数据
	enum { IDD = IDD_DLG_IMG };
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelectImg();
	afx_msg void OnDropFiles(HDROP hDropInfo);
//app======================================================UI
private:
	REAL m_rZoom;//绽放系数
	PointF m_PtStart;
	PointF m_mouseDown;
	CRect m_rectClient;
	ST_IMG_INFO m_stImgSize;
	ST_IMG_INFO m_stImgOffset;//图片偏移量

	CString m_strImgPath;
	bool m_bMousePressed;

	ULONG_PTR m_GdiplusToken;
	GdiplusStartupInput m_GdiplusStartupInput;
private:
	void DrawImg(CDC *pDC, CString strImgPath);
private:
	void Invalidate();
	void SetScrollAttr(UINT uiScrollType, UINT uiMax, UINT uiPos);
//app======================================================APP
private:
	void Init();
	void Uninit();
};
