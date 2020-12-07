
//绘图===========================================================================================
/*功能：该函数得到一个能够完包含当前可见区域的最小矩形的大小。该可见区域由当前的剪切区域定义或由剪切路径所定义或者由任何重迭的窗口所定义。
  参数：hdc--设备环境句柄   lprc--RECT结构的一个指针，用来接收矩形的大小
  返回：基于给定设备上下文环境的逻辑坐标
  对比：GetClipBox得到的是要刷新的最小矩形区域 GetClientRect得到的是客户区*/
int GetClipBox(HDC hdc, LPRECT lprc);

/*功能：创建一个由lpRect确定度的矩形区域
  参数：lpRect 矩形4点坐标
  返回：执行成功则为区版域句柄，失败则为0*/
HRGN CreateRectRgnIndirect(RECT *lprect);

/*功能：该函数通过特定的方式把一个特定的区域与当前的剪切区域合并在一起
  参数：hdc--设备环境句柄  hrgn--标识被选择的区域  
       fnMode：RGN_AND：新的剪切区域与当前剪切区域的重叠部分合并，该区域由hrgn标识。
	   RGN_COPY：新的剪切区域是由hrgn标识区域的一个拷贝，这和select clipRgn是统一的。如果由hrgn所定义的区域为空。那么新的剪切区域就是缺省的剪切区域（缺省的剪切区域是个空区域）。
       RGN_DIFF：新的剪切区域与由hrgn定义的区域之外的区域合并。
       RGN_OR：新的剪切区域与当前的剪切区域合并，并且该区域由hrgn标识。
       RGN_XOR：新的剪切区域与当前的剪切区域合并，并且该区域由hrgn指定，但是不包括任何重叠区域。
  返回：NULLREGION--区域为空； SIMPLEREGION--区域为单个矩形； COMPLEXREGION--区域为多个矩形； ERROR--发生了错误。
  说明：CreateRectRgnIndirect 和 ExtSelectClipRgn 是通过指定区域来定义剪切区域
       剪切区域也是区域的一种, 窗口在重绘时只会重绘剪切区域中的内容*/
int ExtSelectClipRgn(HDc hdc, HRGN hrgn, int fnMode);

/*功能：选择当前的路径作为设备环境的一个剪切区域。通过使用特定的模式把新的区域与任何存在的剪切区域合并。
  参数：hdc--设备环境句柄  iMode:同上fnMode
  返回：如果函数执行成功，返回非零值；如果函数执行失败，返回值为零*/
BOOL SelectClipPath(HDC hdc, int iMode);

/*功能：将两个区域Src1,Src2根据指定的模式进行合并，得到一个新的区域Dest
  参数：hrgnDest--合并后得到的新区域  hrgnSrc1--需要合并的区域1  hrgnSrc2--需要合并的区域2 fnCombineMode--同上iMode
  返回：NULLREGION--区域为空； SIMPLEREGION--区域为单个矩形； COMPLEXREGION--区域为多个矩形； ERROR--发生了错误*/
int CombineRgn(_In_ HRGN hrgnDest, _In_ HRGN hrgnSrc1, _In_ HRGN hrgnSrc2, _In_ int  fnCombineMode);

/*功能：得到一个包含lrcSrc1和lprcSrc2两个源矩形的最小矩形lprcDst
  参数：lprcDst--得到的最小源矩形  lprcSrc1--源矩形  lprcSrc2--源矩形
  返回：非零表示成功;零表示失败*/
BOOL WINAPI UnionRect(_Out_ LPRECT lprcDst, _In_ CONST RECT *lprcSrc1, _In_ CONST RECT *lprcSrc2);

/*功能：向指定窗体更新区域添加一个矩形,这个矩形区域将被重绘制(产生WM_PAINT)
  参数：hWnd--指定窗体句柄  lpRect--存放矩形结构体指针,NULL则指定窗体客户区将全被重绘
       bErase--重绘时是否擦除背景
  返回：非零表示成功;零表示失败*/
BOOL InvalidateRect(HWND hWnd, CONST RECT *lpRect, BOOL bErase);

/*功能：得到指定图形对象的信息，根据图形对象，函数把填满的或结构，或表项（用于逻辑调色板）数目放入一个指定的缓冲区
  参数：hgdiobj--指向感兴趣的图形对象的句柄，它可以是这样的一个句柄：一个逻辑位图、一个刷子、一种字体、一个调色板、
                笔或通过调用CreateDIBSection函数创建的与设备无关位图
	   cbBuffer--指定将要写到缓冲区的信息的字节数目
	   lpvObject--指向一个缓冲区的指针，该缓冲区将要检索指定图形对象的信息：常用结构HPEN LOGPEN; HBRUSH LOGBRUSH; HFONT LOGFONT
  返回：如果函数调用成功，且lpvObject为一个有效指针，则返回值为贮存到缓冲区的字节数目;如果函数调用失败，则返回值为0*/
int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject);

/*功能：检索预定义的备用笔、刷子、字体或者调色板的句柄
  参数：fnObject--指定对象的类型===============
	   BLACK_BRUSH：黑色画笔；
	   DKGRAY_BRUSH：暗灰色画笔；
	   DC_BRUSH：在Windows98,Windows NT 5.0和以后版本中为纯颜色画笔，缺省色为白色。
	   GRAY_BRUSH：灰色画笔；
	   HOLLOW_BRUSH：空画笔（相当于HOLLOW_BRUSH）；
　　	   LTGRAY_BRUSH：亮灰色画笔；
	   NULL_BRUSH：空画笔（相当于HOLLOW_BRUSH）；
　　    WHITE_BRUSH：白色画笔；
	   BLACK_PEN：黑色钢笔；
　　    DC_PEN：在Windows98、Windows NT 5.0和以后版本中为纯色钢笔，缺省色为白色。
　　    WHITE_PEN：白色钢笔；
	   ANSI_FIXED_FONT：在Windows中为固定间距（等宽）系统字体；
　　    ANSI_VAR_FONT：在Windows中为变间距（比例间距）系统字体；
　　    DEVICE_DEFAUCT_FONT：在WindowsNT中为设备相关字体；
　　    DEFAULT_GUI_FONT：用户界面对象缺省字体，如菜单和对话框；
　　    OEM_FIXED_FONT：原始设备制造商（OEM）相关固定间距（等宽）字体；
　　    SYSTEM_FONT：系统字体，在缺省情况下，系统使用系统字体绘制菜单，对话框控制和文本；
　　    SYSTEM_FIXED_FONT：固定间距（等宽）系统字体，该对象仅提供给兼容16位Windows版本；
　　    DEFAULT_PALETTE：缺省调色板，该调色板由系统调色板中的静态色彩组成
  返回：如果成功，返回值标识申请的逻辑对象，如果失败，返回值为NULL。*/
HGDIOBJ GetStockObject(int fnObject)

/*RGB：三基色		R:红						G:绿							B:蓝
HSL：色彩模式	H:色相(eg:红色,黄色等)		S:饱和度(越高越纯,越低越灰)		L:亮度*/

//字体===============================================================================================
/*功能：返回设备对象dc当前所使用的字体字符的有关尺寸
  参数：hDC--设备环境句柄   lpMetric--指向结构TEXTMETRIC的指针，该结构用于获得字体信息
  返回：如果函数调用成功，返回值非零，如果函数调用失败，返回值是0
  备注：TEXTMETRIC结构详解=============================
       typedef struct tagTEXTMETRIC 
	   { // tm 
　　		LONG tmHeight;			//字符高度
　　		LONG tmAscent;			//字符上部高度(基线以上)
　　		LONG tmDescent;			//字符下部高度(基线以下)
　　		LONG tmInternalLeading; //由tmHeight定义的字符高度的顶部空间数目
　　		LONG tmExternalLeading; //加在两行之间的空间数目
　　		LONG tmAveCharWidth;	//平均字符宽度
　　		LONG tmMaxCharWidth;	//最宽字符的宽度
　　		LONG tmWeight;			//字体的粗细轻重程度
　　		LONG tmOverhang;		//加入某些拼接字体上的附加高度
　　		LONG tmDigitizedAspectX;//字体设计所针对的设备水平方向
　　		LONG tmDigitizedAspectY;//字体设计所针对的设备垂直方向
　　		BCHAR tmFirstChar;		//为字体定义的第一个字符
　　		BCHAR tmLastChar;		//为字体定义的最后一个字符
　　		BCHAR tmDefaultChar;	//字体中所没有字符的替代字符
　　		BCHAR tmBreakChar;		//用于拆字的字符
　　		BYTE tmItalic;			//字体为斜体时非零
　　		BYTE tmUnderlined;		//字体为下划线时非零
　　		BYTE tmStruckOut;		//字体被删去时非零
　　		BYTE tmPitchAndFamily;	//字体间距(低4位)和族(高4位)
　　		BYTE tmCharSet;			//字体的字符集
　　	  } TEXTMETRIC;*/
DWORD GetTextMetrics(HDC hDC, LPTEXTMETRIC lpMetric);

/*功能：创建一个逻辑字体，创建的字体具有LOGFONT对象确定的特性。创建的字体后边就可以由任何设备环境选择作为当前的字体。
  参数：lplf--定义逻辑字体特性的LOGFONT结构指针==========
       typedef struct tagLOGFONT 
	   {
		LONG  lfHeight;			//字体高度
		LONG  lfWidth;			//字体宽度
		LONG  lfEscapement;		//字体显示的角度
		LONG  lfOrientation;	//字体的角度
		LONG  lfWeight;			//字体的磅数
		BYTE  lfItalic;			//斜体字体
		BYTE  lfUnderline;		//带下划线字体
		BYTE  lfStrikeOut;		//带删除线字体
		BYTE  lfCharSet;		//所需字符集
		BYTE  lfOutPrecision;	//输出的精度
		BYTE  lfClipPrecision;	//裁剪精度
		BYTE  lfQuality;		//逻辑字体和输出设备的实际字体间的间距
		BYTE  lfPitchAndFamily; //字体间距和字体集
		TCHAR lfFaceName[LF_FACESIZE];//字体名称
	   } LOGFONT, *PLOGFONT;
  返回：如果函数创建成功，返回逻辑字体的句柄，否则返回NULL值*/
HFONT CreateFontIndirect(CONST LOGFONT *lplf);

/*功能：从存储图像的系统添加字体资源(自定义自体文件)
  参数：pFileView--指向字体资源的指针
       cjSize--pbFont指向的字体资源中的字节数。
	   pvResrved--保留。必须为0。
	   pNumFonts--指向指定安装字体数量的变量的指针。
  返回：如果函数成功，则返回值指定添加字体的句柄;如果函数失败，则返回值为零
  备注：此功能允许应用程序获取嵌入在文档或网页中的字体。由AddFontMemResourceEx添加的字体始终是进行调用的进程的私有属性，并且不能枚举*/
HANDLE AddFontMemResourceEx(PVOID pFileView, DWORD cjSize, PVOID pvResrved, DWORD *pNumFonts);

//图片 /*DDB与DIB详解*/================================================================================
//转换BMP文件为PNG文件            
BOOL CMakePNG::BMptoPNG(LPCWSTR StrBMp, LPCWSTR StrPNG)
{
	CLSID encoderClsid;
	Status stat;
	Image* image = NULL;
	image = Bitmap::FromFile(StrBMp, TRUE);
	if (!GetEncoderClsid(L"image/png", &encoderClsid))
	{
		return FALSE;
	}
	stat = image->Save(StrPNG, &encoderClsid, NULL);
	if (stat != Ok)
	{
		return FALSE;
	}
	delete image;
	return TRUE;
}

//	功能描述:		转换PNG文件为BMP文件      
BOOL CMakePNG::PNGtoBMp(LPCWSTR StrPNG, LPCWSTR StrBMp)
{
	CLSID encoderClsid;
	Status stat;
	Image* pImage;
	pImage = Bitmap::FromFile(StrPNG, TRUE);
	if (!GetEncoderClsid(L"image/bmp", &encoderClsid))
	{
		return FALSE;
	}
	stat = pImage->Save(StrBMp, &encoderClsid, NULL);
	if (stat != Ok)
	{
		return FALSE;
	}
	delete pImage;
	return TRUE;
}

/*功能：显示具有指定透明度的图像
  参数：	hdcDest：指向目标设备环境的句柄。
		nXoriginDest：指定目标矩形区域左上角的X轴坐标，按逻辑单位。
		nYOriginDest：指定目标矩形区域左上角的Y轴坐标，按逻辑单位。
		nWidthDest：指定目标矩形区域的宽度，按逻辑单位。
		hHeghtdest：指向目标矩形区域高度的句柄，按逻辑单位。
		hdcSrc：指向源设备环境的句柄。
		nXOriginSrc：指定源矩形区域左上角的X轴坐标，按逻辑单位。
		nYOriginSrc：指定源矩形区域左上角的Y轴坐标，按逻辑单位。
		nWidthSrc：指定源矩形区域的宽度，按逻辑单位。
		nHeightSrc：指定源矩形区域的高度，按逻辑单位。
		blendFunction：指定用于源位图和目标位图使用的alpha混合功能，用于整个源位图的全局alpha值和格式信息。源和目标混合功能当前只限为AC_SRC_OVER。
  返回：如果函数执行成功，那么返回值为TRUE；如果函数执行失败，那么返回值为FALSE
  对比：流程=======::CreateCompatibleDC(hDC)画布---->
       ::SelectObject(hCloneDC, hBitmap)填入装置---->
	   ::SetStretchBltMode(hDC, HALFTONE)模式---->
	   lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, 
	                hCloneDC, rcBmpPart.left + rcCorners.left, rcBmpPart.top + rcCorners.top, 
				    rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right, 
					rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, bf)显示---->
	   ::SelectObject(hCloneDC, hOldBitmap);::DeleteDC(hCloneDC);释放*/
BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest, 
				HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, 
				BLENDFUNCTION blendFunction)；

//C++===================================================================================================
/*功能：将两个32位值相乘，然后将64位结果除以第三个32位值。最终结果将四舍五入到最接近的整数 iMultiplier * imolecule / iDenominator
  参数：iMultiplier--被乘数  iMolecule--分子  iDenominator--分母
  返回：运算结果，iDenominator为0时返回-1*/
int MulDiv(int iMultiplier, int iMolecule, int iDenominator)

/*override 关键字*/

/*win32的CLAMP宏*/
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))


//窗口部分============================================================================
/*窗口样式:
1.Pop-up窗口: 一个弹出窗口是必须具有WS_POPUP属性的窗口,弹出窗口只能是一个Top-Level窗口,不能是子窗口,弹出窗口多用于对话框和消
息框,也可以用于应用程序的主窗口, 弹出窗口可以不必具有标题栏

2.Overlapped窗口: 一个重叠窗口是一个必须具有WS_OVERLAPPED属性的窗口,也就是一个重叠窗口必须具有边框,标题栏,客户区域。重叠窗口
可以是一个子窗口，也可以是一个Top-Level窗口,重叠窗口一般都用于一个应用程序的主窗口

3.Top-Level窗口: 就是没有WS_CHILD属性的窗口,所有的Top-Level的父窗口为桌面窗口。并不是所有的Top-Level的窗口都在系统的任务栏中
显示，只有所有者窗口为NULL的Top-Level窗口才能在任务栏中显示窗口的标题

4.Child窗口: 具有父窗口的窗口叫子窗口, 子窗口必须具有WS_CHILD属性,同时子窗口也可以有子窗口,子窗口可以是一个重叠窗口,但不能是
一个弹出窗口。子窗口只能包含在父窗口的客户区，不能移出到父窗口客户区外，而且子窗口也不可能成为活动窗口，也不可能
将子窗口的标题显示在任务栏上。同时子窗口的最大化和最小化都在父窗口中显示，在建立一个子窗口时所指定的RECT是以父窗
口的客户区的左上角为原点。而建立一个非子窗口时所指定的RECT是以屏幕为坐标原点的。子窗口可以有系统菜单,但不能有菜
单栏.子窗口在父窗口销毁前被销毁,在父窗口隐藏前被隐藏,在父窗口显示后被显示,

5.Desktop窗口: 就是桌面,桌面窗口是一个特殊窗口,他既不是一个子窗口,也不是一个重叠窗口,也不是一个弹出窗口。

6.Parent窗口: 具有子窗口的窗口叫父窗口,父窗口销毁前所属的子窗口将自动被销毁。父窗口在最小化时,其子窗口也会被最小化,但不隐藏
而父窗口在恢复时其子窗口也会被恢复.

7.Owner窗口: 只有重叠窗口和弹出窗口才能是Owner窗口,子窗口不能为Owner窗口,Owner窗口销毁前,他的所有的Owned窗口都将被自动销毁,
当Owner窗口隐藏时他的所有Owned窗口不会隐藏。但当Owner最小化是他的Owned窗口会被隐藏。一个Owner窗口的所有Owned窗口都将在Owner窗口的前面显示,而不会在其后面显示。

8.Owned窗口:  一个Owned窗口总是在Z-Order顺序中一般是在他的Owner窗口之前,Owned窗口的生命可以被他的Owner窗口控制,Owned窗口的显
示并不局限于他的Owner窗口区域,一个Owned窗口在建立后不能改变他的owner窗口,子窗口,弹出窗口,重叠窗口都可以做Owned
窗口。

9.窗口的Z-ORDER:

10.message-only窗口: 消息窗口不能被显示,不能接受键盘和鼠标消息,不会接收广播来的消息,同时消息窗口也不会被列举,不会出现在窗口的
Z-Order顺序中。其他的于一般窗口一样。能接收和发送消息。重叠，弹出，子窗口都能为消息窗口

11.background窗口: 非foreground窗口就叫background窗口

12.foreground窗口: 如果用户正某个线程建立的窗口上时,这时这个线程称为前台线程,这个窗口则称为前台窗口,此时其他的线程都称为后台
线程,后台线程的窗口则称为后台窗口, 前台线程的优先级将必后台线程的优先级要稍微高一点。当一个窗口成为前台窗
口时，这个窗口也成为了活动窗口。系统有一个RIT线程来维护硬件输入队列SHIQ,每个GUI线程都维护者一个虚拟输入消
息队列,而且在一个时间内只有一个线程的虚拟输入队列于SHIQ相联系,则这个于SHIQ相联系的线程就叫前台线程.

13.active窗口: 活动窗口是用户正在操作的一个Top-Level窗口,活动窗口一般放置在Z order的顶端,并且窗口的标题栏颜色高亮显示。只有顶
层窗口才能作为活动窗口，当用户在一个子窗口上工作时，则子窗口所属的一个Top-Level父窗口成为活动窗口，在一个时间
内只有一个顶层窗口是活动窗口，活动窗口就是当前正接收键盘和鼠标输入的窗口

14.disabled窗口: 不能响应键盘和鼠标输入的窗口

15.visible窗口: 不可看见的窗口*/

/*分层窗口:窗口A和窗口B，窗口A作为显示窗口，也就是异形窗口，而窗口B作为逻辑窗口，就是你要处理使用的窗口，即主窗口，
		 然后让这两个窗口重叠在一块，也可以说是在窗口B上创建了窗口A，然后通过UpdateLayeredWindow对窗口A实现
		 异形，因为窗口A在窗口B上，那么势必会遮盖住窗口B的控件，然后我们就要对窗口A通过SetWindowRgn进行裁剪，
		 通过镂空出控件的位置从而达到显示出控件。*/

/*窗口子类化和超类化===================================================================================
  子类化:修改窗口过程函数
		m_OldWndProc = SubclassWindow(hWnd, __WndProc);//子类化窗口,设置新的窗口过程函数,并保存旧的窗口过程函数
		... ...
		窗口销毁时SubclassWindow(m_hWnd, m_OldWndProc);//反子类化
  超类化:超类化修改窗口类(新的窗口类名)
		WNDCLASSEX  wc; 
		wc.cbSize=sizeof(wc); //Windows用来进行版本检查的，与窗口特征无关 
		GetClassInfoEx(hinst,”XXXXXX”,&wc);
		// hinst—定义窗口类XXXXXX的模块的句柄，如为系统定义的窗口类（如：EDIT、BUTTON）则hinst=NULL.。 
		wc.lpszClassName = “YYYYYYY”;//必须改变窗口类的名字 
		wc.hbrBackGround = CreateSolidBrush(RGB(0,0.0));//改变背景刷 
		wc.lpfnWndProc = NewWndProc;//改变窗口函数 
		……	
		RegisterClassEx(&wc);// 注册新窗口类
  总结:	（0） 子类化修改窗口过程函数,超类化修改窗口类(新的窗口类名)
		（1） 子类化是在窗口实例级别上的,超类化是在窗口类（WNDCLASS）级别上的。 
		（2） 超类化可以完成比子类化更复杂的功能,在SDK范畴上，可以认为子类化是超类化的子集。 
		（3） 子类化只能改变窗口创建后的性质,对于窗口创建期间无能为力(无法截获ON_CREATE 事件),而超类化可以实现;超类化不能用于Windows已创建的窗口，子类化可以.*/

/*SendMessage和PostMessage===========================================================================
1.POSTMESSAGE(非阻塞)与SENDMESSAGE(阻塞):PostMessage发送消息后就立即返回;SendMessage发送消息后，等待消息处理函数处理完后才返回。
2.处理过程:(1)在同一个线程中，PostMessage发送消息时，消息要先放入系统消息队列中,系统会根据存放的消息,找到对应的线程(窗口、程序)的消息队
			列中，然后由GetMessage/PeekMessage提交给TranslateMessage，如果是键盘、鼠标消息，TranslateMessage会处理提交给
			DispatchMessage，如不是，则直接提交给DispatchMessage，最后DispatchMessage经USER模块协助，将消息传递给窗口处理函数;
			而SendMessage发送消息时，由USER模块调用目标窗口的处理函数处理消息，并将结果返回。
		  (2)不在同一个线程，基本都是用PostThreadMessage代替PostMessage，因为PostThreadMessage是直接指定线程ID来确定目标线程；
		    而SendMessage发送消息到目标窗口所属的线程的消息队列中，然后发送消息的线程在UESR模块内监视和等待消息处理，直到目标窗口处理完返回。
3.对于WM_USER消息：如果发送的消息码在WM_USER之下(非自定义消息)且消息参数中带有指针，那么PostMessage，SendNotifyMessage，
			SendMessageCallback这些异步消息发送函数将会失败。原因是异步消息发送函数发送后会立即返回，这样会导致消息处理函数还未处理消息，
			消息参数中的指针就被释放了。
4.返回值:从函数定义上来看，PostMessage的返回值是BOOL，意思是返回非0值，消息执行成功，返回0，执行不成功;
		SendMessage的返回值是LRESULT,返回的是消息处理函数后的返回值。*/

/*功能:获取标识了指定窗口的所有者窗口（如果存在）
  参数:hWnd--窗口句柄    nCmd--窗口样式
  返回:如果函数成功，返回值为窗口句柄；如果与指定窗口有特定关系的窗口不存在，则返回值为NULL
  对比：注意Owner窗口特性--只有重叠窗口和弹出窗口才能是Owner窗口*/
#define GetWindowOwner(hwnd) GetWindow(hwnd, GW_OWNER)
HWND GetWindow（HWND hWnd，UINT nCmd）;

#define SubclassWindow（hwnd，lpfn）\
	（（WNDPROC）SetWindowLongPtr（（hwnd），GWLP_WNDPROC，（LPARAM）（WNDPROC）（lpfn）））
/*功能:改变指定窗口属性
  参数:hWnd--窗口句柄     nIndex--索引,具体参数如下:     dwNewLong--指定替换的值 
	  GWL_EXSTYLE:设置新的扩展窗口样式。有关更多信息，请参见CreateWindowEx。
	  GWL_STYLE:设置新的窗口样式。
	  GWLP_WNDPROC:设置窗口过程的新地址。
	  GWLP_HINSTANCE:设置新的应用程序实例句柄。
	  GWLP_ID:设置窗口的新标识符。
	  GWLP_USERDATA:设置与窗口关联的用户数据。该数据供创建该窗口的应用程序使用。其值最初为零。
	当hWnd参数标识对话框时，以下值也可用==========================================
	  DWLP_DLGPROC:将新指针设置为对话框过程。
	  DWLP_MSGRESULT:设置在对话框过程中处理的消息的返回值。
	  DWLP_USER:设置应用程序专用的新的额外信息，例如句柄或指针。
  返回:如果函数成功，则返回值是指定偏移量的先前值,成功返回的是设置前的值LONG_PTR这个类型;如果函数失败，则返回值为零。    
  对比:SetWindowLongPtr代替SetWindowLong是为了兼容32位64位windows os*/
LONG_PTR SetWindowLongPtr（HWND  hWnd，int  nIndex，LONG_PTR  dwNewLong）;

/*功能:确定给定的窗口句柄是否标识标识一个已存在的窗口
  参数:hWnd--窗口句柄
  返回:如果窗口句柄标识了一个已存在的窗口，返回值为非零；如果窗口句柄标识的窗口不存在，返回值为零。*/
BOOL IsWindow（HWND hWnd）;

/*功能:嵌套的窗口处理函数，我们可以把不关心的消息都丢给它来处理.
  参数:hWnd--窗口句柄   Msg--窗口消息  wParam--消息指定信息  IParam--消息指定信息
  返回:返回值就是消息处理结果，它与发送的消息有关。*/
LRESULT DefWindowProc（HWND hWnd，UINT Msg，WPARAM wParam，LPARAM IParam）；

/*功能:该函数允许/禁止指定的窗口或控件接受鼠标和键盘的输入，当输入被禁止时，窗口不响应鼠标和按键的输入，输入允许时，窗口接受所有的输入。
  参数:hWnd--窗口句柄  bEnable--允许/禁用
  返回:如果窗口此前已禁用，则返回值是非零。 返回值是0，则窗口先前启用或错误.*/
BOOL EnableWindow（HWND hWnd，BOOL bEnable）；

/*功能:该函数在指定窗口的属性表中增加一个新项，或者修改一个现有项
  参数:hWnd--窗口句柄  lpString--窗口属性    hData--指向要拷贝到属性表中的数据的句柄
  返回:如果该数据句柄和字符串以加到属性表中，那么返回值为非零。如果该函数失败，那么返回为零.
  对比:比SetWindowLongPtr功能更多一点，可以给窗口添加新的属性*/
BOOL SetProp（HWND hWnd，LPCTSTR lpString，HANDLE hData）；

/*功能:是将消息信息传送给指定的窗口过程的函数
  参数:lpPrevWndFunc--指向前一个窗口过程的指针   hWnd--指向接收消息的窗口过程的句柄.  Msg--指定消息类型
  返回:返回值指定了消息处理结果，它与发送的消息有关*/
LRESULT CallWindowProc(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM IParam);

/*功能：设置分层窗口的不透明度和透明度颜色键
  参数：hwnd--分层窗口的句柄。通过使用CreateWindowEx函数创建窗口时指定WS_EX_LAYERED或在创建窗口后通过SetWindowLong设置WS_EX_LAYERED来创建分层窗口
       crKey--一个COLORREF结构，它指定在组成分层窗口时要使用的透明色键
	   bAlpha--用于描述分层窗口的不透明度的Alpha值;当bAlpha为0时，窗口是完全透明的。当bAlpha为255时，窗口是不透明的。
	   dwFlags--LWA_ALPHA时：crKey参数无效,bAlpha参数有效;  LWA_COLORKEY：窗体中的所有颜色为crKey的地方将变为透明,bAlpha参数无效。其常量值为1。
				LWA_ALPHA | LWA_COLORKEY:crKey的地方将变为全透明，而其它地方根据bAlpha参数确定透明度
  返回：如果函数成功，则返回值为非零;如果函数失败，则返回值为零*/
BOOL SetLayeredWindowAttributes(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

/*功能：更新分层窗口的位置，大小，形状，内容和半透明
  参数：hWnd--分层窗口的句柄。使用CreateWindowEx函数创建窗口时，可以通过指定WS_EX_LAYERED来创建分层窗口
       hdcDst--屏幕DC的句柄
	   pptDst--指向指定分层窗口的新屏幕位置的结构的指针。如果当前位置未更改，则pptDst可以为NULL。
	   psize--指向指定分层窗口新大小的结构的指针。如果窗口的大小没有变化，则psize可以为NULL。如果hdcSrc为NULL，则psize必须为NULL。
	   hdcSrc--DC的句柄，用于定义分层窗口的表面。可以通过调用CreateCompatibleDC函数获得此句柄。如果窗口的形状和视觉上下文未更改，则hdcSrc可以为NULL。
	   pptSrc--指向指定设备上下文中层位置的结构的指针。如果hdcSrc为NULL，则pptSrc应该为NULL。
	   crKey--一个结构，用于指定在组成分层窗口时要使用的颜色键。要生成COLORREF，请使用RGB宏。
	   pblend--指向结构的指针，该结构指定组成分层窗口时要使用的透明度值。
	   dwFlags--ULW_ALPHA 0x00000002:使用pblend作为混合功能。如果显示模式为256色或更小，则此值的效果与ULW_OPAQUE的效果相同。
				ULW_COLORKEY 0x00000001:使用crKey作为透明颜色。
				ULW_OPAQUE 0x00000004:绘制一个不透明的分层窗口。
				ULW_EX_NORESIZE 0x00000008:如果当前窗口大小与psize中指定的大小不匹配,则强制UpdateLayeredWindowIndirect函数失败。
  返回：如果函数成功，则返回值为非零;如果函数失败，则返回值为零。
  备注：配合SetLayeredWindowAttributes使用*/
BOOL UpdateLayeredWindow(HWND hWnd, HDC hdcDst, POINT *pptDst, SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);