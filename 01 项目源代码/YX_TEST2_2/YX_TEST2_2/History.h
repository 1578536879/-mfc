#pragma once
#include "afxcmn.h"
#include <vector>
#include "afxwin.h"
using namespace std;

// CHistory 对话框

class CHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CHistory)
	
	vector<CString> m_fileNames;
	vector<int> m_x;
	vector<int> m_type;
	vector<int> m_y;
	vector<int> m_res;
	vector<int> m_judgeRes;
	vector<int> m_correctRes;
public:
	CHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHistory();
	void init();

// 对话框数据
	enum { IDD = IDD_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_historyList;
	CTreeCtrl m_timeTree;
	void getAllFile();
	void getHistory(int index);
	void drawHistory();
	void drawQuestion(int index);
	afx_msg void OnSelchangedFileTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_number1;
	void setBitMap(int index1, int index2);
	CStatic m_number2;
	CStatic m_number3;
	CStatic m_number4;
	CStatic m_queType;
};

