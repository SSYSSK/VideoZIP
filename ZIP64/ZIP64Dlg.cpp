
// ZIP64Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZIP64.h"
#include "ZIP64Dlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <tchar.h> 
#include <stdio.h>  
#include <iostream>  
#include <math.h>  


#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <atlconv.h>

using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZIP64Dlg 对话框



CZIP64Dlg::CZIP64Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZIP64_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZIP64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, path);

}

BEGIN_MESSAGE_MAP(CZIP64Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CZIP64Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CZIP64Dlg::OnEnChangeEdit1)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CZIP64Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CZIP64Dlg 消息处理程序

BOOL CZIP64Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZIP64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZIP64Dlg::OnPaint()
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
HCURSOR CZIP64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

vector<String> getFilePath(string path) {
	String dir_path = path;

	vector<String> videos_list;           // opencv 2 String 改为 string即可

	/*
函数名：glob
参数：String pattern 字符串，由文件夹路径和所要读取的文件名的格式构成的一个正则模板
参数： std::vector<String>& result 字符串容器，存放所有符合模板的路径
参数：bool recursive = false 标志位，是否使用递归的方式（没发现使用true和false的结果有什么区别）
功能描述：遍历指定的文件夹，读取符合搜索模板的所有文件路径
*/
	glob(dir_path, videos_list, true);

	for (size_t j = 0; j < videos_list.size(); ++j)
	{
		string fileName = videos_list[j];
	}
	return videos_list;
}

void unZip(string path, string path1, long number)
{


	vector<String> listPath = getFilePath(path);
	long allTotalFrame = 0;
	for (int i = 0; i < listPath.size(); i++) {
		VideoCapture cap;
		cap.open(listPath[i]);

		// 获取整视频帧数
		long totalFrame = cap.get(CV_CAP_PROP_FRAME_COUNT);
		allTotalFrame = allTotalFrame + totalFrame;
		cout << "第 " << i << " 个视频宗贞数=" << totalFrame << endl;

	}

	cout << "总视频宗贞数=" << allTotalFrame << endl;

	// 根据全部视频总帧数截取10000张图片，也就是每隔 allTotalFrame/10000 帧取一张

	int imgIndex = 0;
	for (int i = 0; i < listPath.size(); i++) {
		VideoCapture cap;
		cap.open(listPath[i]);

		Mat frame;
		cap >> frame;

		for (;;)
		{
			Mat frame;
			cap >> frame;
			if (frame.empty())
			{
				break;
			}

			//char* imageSaveName = new char[200];
			//将图片的路径及名称输入到imageSaveName中
			string str = path1; // "F:\\test2\\";
			string res = str + "\\" + to_string(imgIndex) + ".jpg";

			cout << "index == " << imgIndex << endl;

			if (number == 0) {
				if (imgIndex % (int)(allTotalFrame / 10000) == 0) { //假如取10000张，就是每 allTotalFrame/10000 帧截取一张
					cout << "输出图片" << endl;
					imwrite(res, frame);
				}
			}
			else {
				if (imgIndex % (int)(allTotalFrame / number) == 0) { //假如取number张，就是每 allTotalFrame/number 帧截取一张
					cout << "输出图片" << endl;
					imwrite(res, frame);
				}
			}
			imgIndex++;
		}
	}

}

 
void CZIP64Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
 //CDialogEx::OnOK();
 //获得EDIT
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	//取值
	CString str;
	pBoxOne->GetWindowText(str);
	//MessageBox(str, _T("程序运行结果"), MB_OK);
	
	string path1 = CT2A(str.GetBuffer()); //转化为非unicode.

	CEdit* pBoxOne2;
	pBoxOne2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	//取值
	CString str2;
	pBoxOne2->GetWindowText(str2);
	//MessageBox(str, _T("程序运行结果"), MB_OK);
	
	string strPath2 = CT2A(str2.GetBuffer()); //转化为非unicode.


	CEdit* pBoxOne3;
	pBoxOne3 = (CEdit*)GetDlgItem(IDC_EDIT6);
	//取值
	CString str3;
	pBoxOne3->GetWindowText(str3);
	//MessageBox(str, _T("程序运行结果"), MB_OK);

	string numberstr = CT2A(str3.GetBuffer()); //转化为非unicode.
	long b = atoi(numberstr.c_str());
	unZip(path1, strPath2, b);
	str.ReleaseBuffer();
	str2.ReleaseBuffer();
	
}




void CZIP64Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


long allImageNumber(string path)
{


	vector<String> listPath = getFilePath(path);
	long allTotalFrame = 0;
	for (int i = 0; i < listPath.size(); i++) {
		VideoCapture cap;
		cap.open(listPath[i]);

		// 获取整视频帧数
		long totalFrame = cap.get(CV_CAP_PROP_FRAME_COUNT);
		allTotalFrame = allTotalFrame + totalFrame;
	}
	cout << "总视频宗贞数=" << allTotalFrame << endl;
	return  allTotalFrame;
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}






void CZIP64Dlg::OnEnChangeEditc6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CZIP64Dlg::OnBnClickedButton5()
{
	
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	//取值
	CString str;
	pBoxOne->GetWindowText(str);
	//MessageBox(str, _T("程序运行结果"), MB_OK);

	string path1 = CT2A(str.GetBuffer()); //转化为非unicode.

	long l = allImageNumber(path1);

	ostringstream os;
	os << l;
	string result;
	istringstream is(os.str());
	is >> result;

	CEdit* pBoxOneAll;
	pBoxOneAll = (CEdit*)GetDlgItem(IDC_EDIT5);
	pBoxOneAll->SetWindowText(stringToLPCWSTR(result));

}
