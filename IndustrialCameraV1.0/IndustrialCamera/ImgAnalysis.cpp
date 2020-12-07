// ImgAnalysis.cpp : ʵ���ļ�

#include "stdafx.h"
#include "IndustrialCamera.h"
#include "ImgAnalysis.h"
#include "afxdialogex.h"

#define IMG_INI_HIGTH	(690)
#define IMG_INI_WIDTH	(1581)
#define CLIENT_WIDGET	(40)

// CImgAnalysis �Ի���
IMPLEMENT_DYNAMIC(CImgAnalysis, CDialog)

CImgAnalysis::CImgAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CImgAnalysis::IDD, pParent)
{
	m_rZoom = 1.0f;
	m_PtStart.X = 0.0f;
	m_PtStart.Y = 0.0f;
	m_mouseDown.X = 0.0f;
	m_mouseDown.Y = 0.0f;
	m_bMousePressed = false;

	m_strImgPath.Empty();
	memset(&m_stImgSize, 0, sizeof (m_stImgSize));
	memset(&m_rectClient, 0, sizeof (m_rectClient)); 
	memset(&m_stImgOffset, 0, sizeof (m_stImgOffset));
}

CImgAnalysis::~CImgAnalysis()
{
	Uninit();
}

BOOL CImgAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();

	Init();

	return TRUE;
}

void CImgAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImgAnalysis, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTN_SELECTIMG, &CImgAnalysis::OnSelectImg)
	
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// CImgAnalysis ��Ϣ�������
void CImgAnalysis::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nFlags & MK_LBUTTON)
	{
		if (false == m_bMousePressed)
		{
			m_bMousePressed = true;

			m_mouseDown.X = (REAL)(point.x);
			m_mouseDown.Y = (REAL)(point.y);

			m_PtStart.X = m_stImgOffset.unImgX.rImgX;
			m_PtStart.Y = m_stImgOffset.unImgY.rImgY;
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void CImgAnalysis::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bMousePressed = false;

	CDialog::OnLButtonUp(nFlags, point);
}


void CImgAnalysis::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)/*���������²�����*/
	{
		REAL rMoveX = point.x - m_mouseDown.X;
		REAL rMoveY = point.y - m_mouseDown.Y;/*�����������϶�ͼƬ�ƶ��ľ���*/

		m_stImgOffset.unImgX.rImgX = m_PtStart.X + (rMoveX / m_rZoom);
		m_stImgOffset.unImgY.rImgY = m_PtStart.Y + (rMoveY / m_rZoom);/*m_PtStart��ͼƬ���ڿͻ�����ԭ������*/

		Invalidate();
		//set scroll vert
		SetScrollAttr(SB_VERT, (UINT)(m_stImgSize.unImgY.rImgHigth - 1), (UINT)(-m_stImgOffset.unImgY.rImgY));
		//set scroll horz
		SetScrollAttr(SB_HORZ, (UINT)(m_stImgSize.unImgX.rImgWidth - 1), (UINT)(-m_stImgOffset.unImgX.rImgX));
	}

	CDialog::OnMouseMove(nFlags, point);
}


BOOL CImgAnalysis::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	REAL rOldZoom = m_rZoom;
	ST_IMG_INFO stPrePosition = { 0 };
	ST_IMG_INFO stCurPosition = { 0 };

	m_rZoom = (zDelta == 120) ? (m_rZoom + 0.1f) : (m_rZoom - 0.1f);/*���ֹ���(�ϣ���)���ϵ��*/

	this->ScreenToClient(&pt); /*����Ļ����תΪ�ͻ�������*/
	stPrePosition.unImgX.rImgX = pt.x / rOldZoom;
	stPrePosition.unImgY.rImgY = pt.y / rOldZoom;

	stCurPosition.unImgX.rImgX = pt.x / m_rZoom;
	stCurPosition.unImgY.rImgY = pt.y / m_rZoom;

	m_stImgOffset.unImgX.rImgX = stCurPosition.unImgX.rImgX - stPrePosition.unImgX.rImgX + m_stImgOffset.unImgX.rImgX;
	m_stImgOffset.unImgY.rImgY = stCurPosition.unImgY.rImgY - stPrePosition.unImgY.rImgY + m_stImgOffset.unImgY.rImgY;
	Invalidate(); /*��ͼ*/ 
	//������VERTSCROLL
	SetScrollAttr(SB_VERT, (UINT)(m_stImgSize.unImgY.rImgHigth - 1), (UINT)(-m_stImgOffset.unImgY.rImgY));
	//������HORZSCROLL
	SetScrollAttr(SB_HORZ, (UINT)(m_stImgSize.unImgX.rImgWidth - 1), (UINT)(-m_stImgOffset.unImgX.rImgX));

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CImgAnalysis::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
	GetClientRect(m_rectClient);
	m_rectClient.top += CLIENT_WIDGET;
}

void CImgAnalysis::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int iOffset = 0;
	SCROLLINFO stScrollHorz;
	GetScrollInfo(SB_HORZ, &stScrollHorz, SIF_ALL);

	switch (nSBCode)
	{
	case SB_LEFT:
		stScrollHorz.nPos = stScrollHorz.nMin;
		break;
	case SB_RIGHT:
		stScrollHorz.nPos = stScrollHorz.nMax - m_rectClient.Width() + 1;
		break;
	case SB_LINELEFT:
		iOffset -= 1;
		break;
	case SB_LINERIGHT:
		iOffset += 1;
		break;
	case SB_PAGELEFT:
		iOffset -= stScrollHorz.nPage;
		break;
	case SB_PAGEDOWN:
		iOffset += stScrollHorz.nPage;
		break;
	case SB_THUMBTRACK:
		iOffset = nPos - stScrollHorz.nPos;
		break;
	default:
		break;
	}
	stScrollHorz.nPos += iOffset;
	SetScrollAttr(SB_HORZ, (UINT)(m_stImgSize.unImgX.rImgWidth - 1), stScrollHorz.nPos);
	/*��ͼ*/
	m_stImgOffset.unImgX.rImgX -= iOffset;
	Invalidate();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImgAnalysis::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int iOffset = 0;
	SCROLLINFO stScrollVert;
	GetScrollInfo(SB_VERT, &stScrollVert, SIF_ALL);

	switch (nSBCode)
	{
	case SB_TOP:
		stScrollVert.nPos = stScrollVert.nMin;
		break;
	case SB_BOTTOM:
		stScrollVert.nPos = stScrollVert.nMax - m_rectClient.Height() + 1;
		break;
	case SB_LINEUP:
		iOffset -= 1;
		break;
	case SB_LINEDOWN:
		iOffset += 1;
		break;
	case SB_PAGEUP:
		iOffset -= stScrollVert.nPage;
		break;
	case SB_PAGEDOWN:
		iOffset += stScrollVert.nPage;
		break;
	case SB_THUMBTRACK:
		iOffset = nPos - stScrollVert.nPos;
		break;
	default:
		break;
	}
	stScrollVert.nPos += iOffset;
	SetScrollAttr(SB_VERT, (UINT)(m_stImgSize.unImgY.rImgHigth - 1), stScrollVert.nPos);
	/*��ͼ*/
	m_stImgOffset.unImgY.rImgY -= iOffset;
	Invalidate();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CImgAnalysis::OnSelectImg()
{
	CFileDialog ObjFile(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
						_T("ͼƬ�ļ�(*.png; *.jpg; *.jpeg; *.bmp)|*.png; *.jpg; *.jpeg; *.bmp|�����ļ�(*.*)|*.*||"), NULL);
	if (IDOK == ObjFile.DoModal())
	{
		m_strImgPath = ObjFile.GetPathName();
		((CEdit *)GetDlgItem(IDC_EDIT_FILEPATH))->SetWindowTextW(m_strImgPath);
		//show img
		Invalidate();
		//set scroll vert
		SetScrollAttr(SB_VERT, (UINT)(m_stImgSize.unImgY.rImgHigth - 1), 0);
		//set scroll horz
		SetScrollAttr(SB_HORZ, (UINT)(m_stImgSize.unImgX.rImgWidth - 1), 0);
	}
}

void CImgAnalysis::OnDropFiles(HDROP hDropInfo)
{
	int iDropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	if (1 == iDropCount)/*ֻ����һ���ļ�*/
	{
		DragQueryFile(hDropInfo, 0, m_strImgPath.GetBuffer(MAX_PATH), MAX_PATH);
		((CEdit *)GetDlgItem(IDC_EDIT_FILEPATH))->SetWindowTextW(m_strImgPath);/*��ʾ�ļ�λ��*/
		//show img
		Invalidate();
		//set scroll vert
		SetScrollAttr(SB_VERT, (UINT)(m_stImgSize.unImgY.rImgHigth - 1), 0);
		//set scroll horz
		SetScrollAttr(SB_HORZ, (UINT)(m_stImgSize.unImgX.rImgWidth - 1), 0);
	}

	CDialog::OnDropFiles(hDropInfo);
}


void CImgAnalysis::DrawImg(CDC *pDC, CString strImgPath)
{
	Image objImg(strImgPath);
	Graphics objGraph(pDC->GetSafeHdc());

	m_stImgSize.unImgX.rImgWidth = objImg.GetWidth() * m_rZoom;
	m_stImgSize.unImgY.rImgHigth = objImg.GetHeight() * m_rZoom;//��ȡ���ź�ͼƬ�Ĵ�С

	objGraph.SetInterpolationMode(InterpolationModeHighQualityBilinear);/*����ͼƬ��������*/
	objGraph.ScaleTransform(m_rZoom, m_rZoom);/*��ͼƬ��������*/
	objGraph.DrawImage(&objImg, RectF(m_stImgOffset.unImgX.rImgX, m_stImgOffset.unImgY.rImgY, m_stImgSize.unImgX.rImgWidth, m_stImgSize.unImgY.rImgHigth));/*ͼƬƫ�ƺ��������*/ 
}

void CImgAnalysis::Invalidate()/*˫�����ͼ��������˸*/
{	
	HDC stHdc = ::GetDC(this->m_hWnd);

	CDC objDC;
	CDC objMemDC;
	CBitmap objMemBitmap;

	objDC.Attach(stHdc);
	objMemDC.CreateCompatibleDC(NULL);/*�豸�������ʼ��*/
	objMemBitmap.CreateCompatibleBitmap(&objDC, m_rectClient.Width(), m_rectClient.Height());/*��������Ļ��ʾ���ݵ��ڴ���ʾ�豸*/
		
	objMemDC.SelectObject(objMemBitmap);/*ѡ��հ�λͼ*/
	objMemDC.FillSolidRect(0, 0, m_rectClient.Width(), m_rectClient.Height(), RGB(255, 255, 255));/*�������*/

	DrawImg(&objMemDC, m_strImgPath);//����ʽ���߸���ͼƬ
	objDC.BitBlt(0, 40, m_rectClient.Width(), m_rectClient.Height(), &objMemDC, 0, 0, SRCCOPY);/*�������ؼ�DC*/
	/*�ͷ�DC*/
	objMemBitmap.DeleteObject();
	objMemDC.DeleteDC();
	objDC.Detach();

	::ReleaseDC(this->m_hWnd, stHdc);
}

void CImgAnalysis::SetScrollAttr(UINT uiScrollType, UINT uiMax, UINT uiPos)
{
	SCROLLINFO stScrollInfo;
	GetScrollInfo(uiScrollType, &stScrollInfo, SIF_ALL);

	stScrollInfo.cbSize = sizeof (stScrollInfo);
	stScrollInfo.nMin = 0;
	stScrollInfo.nMax = uiMax;
	stScrollInfo.nPage = (SB_VERT == uiScrollType) ? m_rectClient.Height() : m_rectClient.Width();
	stScrollInfo.nPos = max(0, min(uiPos, uiMax - stScrollInfo.nPage + 1));
	SetScrollInfo(uiScrollType, &stScrollInfo, SIF_ALL);
}

void CImgAnalysis::Init()
{
	GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);
}

void CImgAnalysis::Uninit()
{
	GdiplusShutdown(m_GdiplusToken);
}





