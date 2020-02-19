#pragma once
#include <vector>

using namespace std;

// CQuestion �Ի���

class CQuestion : public CDialogEx
{
	DECLARE_DYNAMIC(CQuestion)
	vector<int> m_x;
	vector<int> m_y;
	vector<int> m_type;
	vector<int> m_result;
	vector<int> m_correctResult;
	vector<int> m_checkResult;
	int m_allNumber;
	int m_alreadyNumber;
	int m_index;
public:
	CQuestion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQuestion();
	void init(vector<int> *pro);
	void repaint();

// �Ի�������
	enum { IDD = IDD_QUESTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedQuestionNext();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQueationPrevious();
	afx_msg void OnBnClickedQuestionSubmit();
	afx_msg void OnBnClickedButton4();
};
