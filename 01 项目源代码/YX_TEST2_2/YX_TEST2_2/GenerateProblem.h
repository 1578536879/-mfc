#pragma once
#include "afxwin.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;

// CGenerateProblem 对话框

class CGenerateProblem : public CDialogEx
{
	DECLARE_DYNAMIC(CGenerateProblem)
	vector<int> m_problems;
public:
	CGenerateProblem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGenerateProblem();
	void init();
	void generateProblem(int num);

// 对话框数据
	enum { IDD = IDD_GENERATE_PROBLEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_digit;
	CComboBox m_type;
	afx_msg void OnClickedConfirmBnt();
	CStatic m_warning;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedAdd();
};
