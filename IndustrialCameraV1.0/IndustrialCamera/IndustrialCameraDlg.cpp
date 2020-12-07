// IndustrialCameraDlg.cpp : 实现文件
#include "stdafx.h"
#include "IndustrialCamera.h"
#include "IndustrialCameraDlg.h"
#include "afxdialogex.h"

#include "ImgAnalysis.h"

/*============================存储空间================================*/
#define INPUT_LINT_END		(50)
/*==============================================控件ID===============================================================*/
const UINT g_auiWidgetID[] = { IDC_STATIC_SPLIT1, IDC_STATIC_SPLIT2, IDC_STATIC_SPLIT3, IDC_STATIC_SPLIT4, 
							   IDC_STATIC_SPLIT5, IDC_STATIC_SPLIT6, /*分隔线*/
							   IDC_RADIO_SOCK, IDC_RADIO_UART,/*radio*/
							   IDC_BTN_CONNECT, IDC_BTN_CLEAR, IDC_BTN_OPENCONSOLE, IDC_BTN_CLOSECONSOLE,
							   IDC_BTN_HANDSHAKE, IDC_BTN_READCMOS, IDC_BTN_SETCMOS, IDC_BTN_SOFTWARE, 
							   IDC_BTN_HARDWARE, IDC_BTN_BATCH, IDC_BTN_NORMAL, IDC_BTN_RECUART, IDC_BTN_RECRESULT,/*button*/
							   IDC_BTN,/*预留的button*/
							   IDC_EDIT_OUTPUT };/*edit*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CIndustrialCameraDlg 对话框
CIndustrialCameraDlg::CIndustrialCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIndustrialCameraDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIndustrialCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_objEdit);
}

BEGIN_MESSAGE_MAP(CIndustrialCameraDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CTRL, &CIndustrialCameraDlg::OnBtnComCtrl)
	ON_BN_CLICKED(IDC_BTN_PRM, &CIndustrialCameraDlg::OnBtnSetParam)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CIndustrialCameraDlg::OnBtnComConnect)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CIndustrialCameraDlg::OnBtnClearEdit)
	ON_BN_CLICKED(IDC_BTN_OPENCONSOLE, &CIndustrialCameraDlg::OnBtnOpenConsole)
	ON_BN_CLICKED(IDC_BTN_CLOSECONSOLE, &CIndustrialCameraDlg::OnBtnCloseConsole)
	ON_BN_CLICKED(IDC_BTN_HANDSHAKE, &CIndustrialCameraDlg::OnBtnHandshake)
	ON_BN_CLICKED(IDC_BTN_READCMOS, &CIndustrialCameraDlg::OnBtnReadCMOS)
	ON_BN_CLICKED(IDC_BTN_SETCMOS, &CIndustrialCameraDlg::OnBtnSetCMOS)
	ON_BN_CLICKED(IDC_BTN_SOFTWARE, &CIndustrialCameraDlg::OnBtnSoftware)
	ON_BN_CLICKED(IDC_BTN_HARDWARE, &CIndustrialCameraDlg::OnBtnHardware)
	ON_BN_CLICKED(IDC_BTN_BATCH, &CIndustrialCameraDlg::OnBtnBatchMode)
	ON_BN_CLICKED(IDC_BTN_NORMAL, &CIndustrialCameraDlg::OnBtnNormalMode)
	ON_BN_CLICKED(IDC_BTN_RECUART, &CIndustrialCameraDlg::OnBtnRecUart)
	ON_BN_CLICKED(IDC_BTN_RECRESULT, &CIndustrialCameraDlg::OnBtnRecResult)
	ON_BN_CLICKED(IDC_RADIO_SOCK, &CIndustrialCameraDlg::OnRadioSock)
	ON_BN_CLICKED(IDC_RADIO_UART, &CIndustrialCameraDlg::OnRadioUart)
	ON_MESSAGE(WM_SEND_DATA, &CIndustrialCameraDlg::OnSendData)
	ON_MESSAGE(WM_RECV_DATA, &CIndustrialCameraDlg::OnRecvData)
END_MESSAGE_MAP()


// CIndustrialCameraDlg 消息处理程序
BOOL CIndustrialCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化代码
	InitUI();
	InitProc();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIndustrialCameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CIndustrialCameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIndustrialCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CIndustrialCameraDlg::PreTranslateMessage(MSG *pMsg)
{
	if ((WM_KEYDOWN == pMsg->message) &&
		((GetKeyState(VK_CONTROL) & 0x8000)) &&
		(('t' == pMsg->wParam) || ('T' == pMsg->wParam)))
	{
		CImgAnalysis m_objImgAnalysis;
		m_objImgAnalysis.DoModal();

		return TRUE;/*注意这里一定要返回，让消息循环正常*/
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CIndustrialCameraDlg::OnBtnComCtrl()
{
	ShowWidget(SW_SHOW);
	m_objSetParam.ShowWindow(SW_HIDE);
}

void CIndustrialCameraDlg::OnBtnSetParam()
{
	ShowWidget(SW_HIDE);
	m_objSetParam.ShowWindow(SW_SHOW);
}

void CIndustrialCameraDlg::OnRadioUart()
{
	m_enDrvType = EN_DRV_UART;
}

void CIndustrialCameraDlg::OnRadioSock()
{
	m_enDrvType = EN_DRV_SOCK;
}

void CIndustrialCameraDlg::OnBtnComConnect()
{
	if (DRV_ID_ERROR != m_enDrvType)
	{
		if (m_objMainCtrl.OpenDrvCtrl(m_enDrvType))
		{
			m_bConnect = TRUE;
			m_objMainCtrl.SetDlgHwnd(m_enDrvType, this->m_hWnd);
			SetEditText(_T("上电连接成功"), nullptr, 0);
		}
		else
		{
			AfxMessageBox(_T("连接失败"));
		}
	}
	else
	{
		AfxMessageBox(_T("请选择设备：UART or SOCK"));
	}
}

void CIndustrialCameraDlg::OnBtnClearEdit()
{
	EmptyEditText();
}

void CIndustrialCameraDlg::OnBtnOpenConsole()
{
	if ((nullptr == m_pobjStdIn) && (nullptr == m_pobjStdOut))
	{
		AllocConsole();/*申请控制台*/
		/*重定向输入/输出*/
		freopen_s(&m_pobjStdOut, "CONOUT$", "w + t", stdout);
		freopen_s(&m_pobjStdIn, "CONIN$", "r + t", stdin);
		/*设定控制台属性*/
		SetConsoleTitle(_T("项目调试信息")); /*标题*/
		HMENU hMenu = ::GetSystemMenu(GetConsoleWindow(), FALSE);
		::DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);/*屏蔽关闭按钮*/
	}
}

void CIndustrialCameraDlg::OnBtnCloseConsole()
{
	if ((nullptr != m_pobjStdOut) && (nullptr != m_pobjStdIn))
	{
		fclose(m_pobjStdIn);
		m_pobjStdIn = nullptr;
		fclose(m_pobjStdOut);
		m_pobjStdOut = nullptr;
		FreeConsole();/*释放控制台*/
	}
}

void CIndustrialCameraDlg::OnBtnHandshake()
{
	SendCmd(EN_TYPE_HANDSHAKE);
}

void CIndustrialCameraDlg::OnBtnReadCMOS()
{
	SendCmd(EN_TYPE_READCMOS);
}

void CIndustrialCameraDlg::OnBtnSetCMOS()
{
	SendCmd(EN_TYPE_SETCMOS);
}

void CIndustrialCameraDlg::OnBtnSoftware()
{
	SendCmd(EN_TYPE_GETDATA_SOFTWARE);
}

void CIndustrialCameraDlg::OnBtnHardware()
{
	SendCmd(EN_TYPE_GETDATA_HARDWARE);
}

void CIndustrialCameraDlg::OnBtnBatchMode()
{
	SendCmd(EN_TYPE_MODE_BATCH);
}

void CIndustrialCameraDlg::OnBtnNormalMode()
{
	SendCmd(EN_TYPE_MODE_NORMAL);
}

void CIndustrialCameraDlg::OnBtnRecUart()
{
	SendCmd(EN_TYPE_ALG_RECUART);
}

void CIndustrialCameraDlg::OnBtnRecResult()
{
	SendCmd(EN_TYPE_ALG_RECRESULT);
}

LRESULT CIndustrialCameraDlg::OnSendData(WPARAM wParam, LPARAM lParam)
{
	SetEditText(_T("发送命令："), (PCHAR)lParam, wParam);

	return NULL;
}

LRESULT CIndustrialCameraDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	SetEditText(_T("接收数据："), (PCHAR)lParam, wParam);

	return NULL;
}

void CIndustrialCameraDlg::InitUI()
{
	m_pobjStdIn = nullptr;
	m_pobjStdOut = nullptr;

	RECT stRect = { 0 };
	GetClientRect(&stRect);

	stRect.left += 108;
	m_objSetParam.Create(IDD_CHILD_PRM, this);
	m_objSetParam.MoveWindow(&stRect);
}

void CIndustrialCameraDlg::ShowWidget(UINT uiStatus)
{
	for (UINT uiNum = 0; uiNum < sizeof (g_auiWidgetID) / sizeof (g_auiWidgetID[0]); uiNum++)
	{
		GetDlgItem(g_auiWidgetID[uiNum])->ShowWindow(uiStatus);
	}
}

void CIndustrialCameraDlg::EmptyEditText()
{
	m_objEdit.SetWindowText(_T(""));
}

void CIndustrialCameraDlg::SetEditText(CString strPreExplain, PCHAR pcData, ULONG ulDataLen)
{
	CString strHexData;//将数据转换成16进制数，方便调试
	strHexData.Empty();
	ULONG ulTextLen = 0;
	ULONG ulAlgData = 0;
	for (ULONG ulCount = 0; ulCount < ulDataLen; ulCount++)
	{
		ulAlgData = ulCount + 1;
		strHexData.Format(_T("0x%02x "), pcData[ulCount]);
		if (0 == ulAlgData % INPUT_LINT_END)
		{
			strPreExplain += strHexData;
			strPreExplain += "\r\n";
			strPreExplain += "               ";
		}
		else
		{
			strPreExplain += strHexData;
		}
	}
	strPreExplain += "\r\n";
	ulTextLen = m_objEdit.GetWindowTextLength();
	m_objEdit.SetSel(ulTextLen, ulTextLen, TRUE);
	m_objEdit.ReplaceSel(strPreExplain);
}

void CIndustrialCameraDlg::InitProc()
{
	m_bConnect = FALSE;
	m_enDrvType = (EN_DRV_TYPE)DRV_ID_ERROR;
}

void CIndustrialCameraDlg::SendCmd(EN_FRAME_TYPE enFrameType)
{
	if (TRUE == m_bConnect)
	{
		m_objMainCtrl.SendDrvCtrl(m_enDrvType, enFrameType);
	}
	else
	{
		AfxMessageBox(_T("请先连接设备"));
	}
}