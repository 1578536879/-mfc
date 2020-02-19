// GenerateProblem.cpp : 实现文件
//

#include "stdafx.h"
#include "YX_TEST2_2.h"
#include "GenerateProblem.h"
#include "afxdialogex.h"
#include "Question.h"

// CGenerateProblem 对话框

IMPLEMENT_DYNAMIC(CGenerateProblem, CDialogEx)

CGenerateProblem::CGenerateProblem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGenerateProblem::IDD, pParent)
{	
	
}

CGenerateProblem::~CGenerateProblem()
{
}

void CGenerateProblem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROBLEM_DIGIT, m_digit);
	DDX_Control(pDX, IDC_PROBLEM_TYPE, m_type);
	init();
	DDX_Control(pDX, IDC_PROBLEM_WARNING, m_warning);
}


BEGIN_MESSAGE_MAP(CGenerateProblem, CDialogEx)
	ON_BN_CLICKED(IDC_CONFIRM_BNT, &CGenerateProblem::OnClickedConfirmBnt)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ADD, &CGenerateProblem::OnBnClickedAdd)
END_MESSAGE_MAP()


// CGenerateProblem 消息处理程序


void CGenerateProblem::init()
{
	m_digit.AddString(TEXT("二位数"));
	m_digit.AddString(TEXT("一位数"));
	
	m_type.AddString(TEXT("加法"));
	m_type.AddString(TEXT("减法"));
	m_type.AddString(TEXT("乘法"));
	int startIndex = 1;
	m_digit.SetCurSel(startIndex);
	m_type.SetCurSel(startIndex);
}

void CGenerateProblem::generateProblem(int num){
	//获取运算位数
	int digit = m_digit.GetCurSel();
	//获取运算类型
	int type = m_type.GetCurSel();
	int range = 0;
	//如果运算位数是1，那么就生成1~10以内的数字，否则生成10~100以内的数字
	if(digit == 1){
		range = 10;
	}else{
		range = 100;
	}
	//每次重启后的随机数都不一样
	srand(time(NULL));
	//生成随机数，m_problems存储的是运算的两个数字和运算类型
	for(int i=0;i<num;i++){
		int x = range / 10 + rand()%range;
		m_problems.push_back(x);
		m_problems.push_back(type); 
		int y = range / 10 + rand()%range;
		m_problems.push_back(y);
	}
	CString str;
	//设置总题数文本
	str.Format(_T("%d"), m_problems.size()/3);
	SetDlgItemText(IDC_ALL_NUMBER, str);
	SetDlgItemText(IDC_PROBLEM_NUMBER, _T(""));
}

void CGenerateProblem::OnClickedConfirmBnt()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_problems.size()==0){
		AfxMessageBox(_T("还未生成题目，请先点击添加按钮，添加题目后再点击生成按钮"));
	}
	FIRST[0] = m_problems[0];
	FIRST[1] = m_problems[1];
	FIRST[2] = m_problems[2];
	FIRST[3] = m_problems.size();
	CDialogEx::OnOK();
	GetParent()->SendMessage(WM_GENERATE_QUESTION, 0, (LPARAM) &m_problems);
}


HBRUSH CGenerateProblem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_STATIC){
		if (pWnd->GetDlgCtrlID() == IDC_PROBLEM_WARNING)//特定的某一个标签，IDC_STATIC_FONT为标签控件ID
		{
			CBrush brush;
			brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));//初始化画刷,用GetSysColor返回对话框背景色
			pDC->SetBkMode(BKMODE_LAST);//透明
			pDC->SetTextColor(RGB(255, 0, 0)); //文字颜色  
			return (HBRUSH)brush.GetSafeHandle();
		}
	}
	return hbr;
}


void CGenerateProblem::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString num;
	GetDlgItemText(IDC_PROBLEM_NUMBER, num);
	int number;
	number = _ttoi(num);
	if(number == 0 || number > 100){
		CString waring(_T("请输入1~100以内的数字"));
		CRect rect;
		GetDlgItem(IDC_PROBLEM_WARNING)->GetWindowRect(&rect);
		SetDlgItemText(IDC_PROBLEM_WARNING, waring);
	}else{
		generateProblem(number);
	}
}
