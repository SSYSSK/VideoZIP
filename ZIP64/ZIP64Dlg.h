
// ZIP64Dlg.h: 头文件
//

#pragma once


// CZIP64Dlg 对话框
class CZIP64Dlg : public CDialogEx
{
// 构造
public:
	CZIP64Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZIP64_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	CEdit path;
	afx_msg void OnBnClickedOk2();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEditc6();
	CEdit 需要解压的图片数量;
	afx_msg void OnBnClickedButton5();
};
