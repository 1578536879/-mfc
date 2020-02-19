// GenerateProblem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YX_TEST2_2.h"
#include "GenerateProblem.h"
#include "afxdialogex.h"
#include "Question.h"

// CGenerateProblem �Ի���

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


// CGenerateProblem ��Ϣ�������


void CGenerateProblem::init()
{
	m_digit.AddString(TEXT("��λ��"));
	m_digit.AddString(TEXT("һλ��"));
	
	m_type.AddString(TEXT("�ӷ�"));
	m_type.AddString(TEXT("����"));
	m_type.AddString(TEXT("�˷�"));
	int startIndex = 1;
	m_digit.SetCurSel(startIndex);
	m_type.SetCurSel(startIndex);
}

void CGenerateProblem::generateProblem(int num){
	//��ȡ����λ��
	int digit = m_digit.GetCurSel();
	//��ȡ��������
	int type = m_type.GetCurSel();
	int range = 0;
	//�������λ����1����ô������1~10���ڵ����֣���������10~100���ڵ�����
	if(digit == 1){
		range = 10;
	}else{
		range = 100;
	}
	//ÿ������������������һ��
	srand(time(NULL));
	//�����������m_problems�洢����������������ֺ���������
	for(int i=0;i<num;i++){
		int x = range / 10 + rand()%range;
		m_problems.push_back(x);
		m_problems.push_back(type); 
		int y = range / 10 + rand()%range;
		m_problems.push_back(y);
	}
	CString str;
	//�����������ı�
	str.Format(_T("%d"), m_problems.size()/3);
	SetDlgItemText(IDC_ALL_NUMBER, str);
	SetDlgItemText(IDC_PROBLEM_NUMBER, _T(""));
}

void CGenerateProblem::OnClickedConfirmBnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_problems.size()==0){
		AfxMessageBox(_T("��δ������Ŀ�����ȵ����Ӱ�ť�������Ŀ���ٵ�����ɰ�ť"));
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
		if (pWnd->GetDlgCtrlID() == IDC_PROBLEM_WARNING)//�ض���ĳһ����ǩ��IDC_STATIC_FONTΪ��ǩ�ؼ�ID
		{
			CBrush brush;
			brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));//��ʼ����ˢ,��GetSysColor���ضԻ��򱳾�ɫ
			pDC->SetBkMode(BKMODE_LAST);//͸��
			pDC->SetTextColor(RGB(255, 0, 0)); //������ɫ  
			return (HBRUSH)brush.GetSafeHandle();
		}
	}
	return hbr;
}


void CGenerateProblem::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString num;
	GetDlgItemText(IDC_PROBLEM_NUMBER, num);
	int number;
	number = _ttoi(num);
	if(number == 0 || number > 100){
		CString waring(_T("������1~100���ڵ�����"));
		CRect rect;
		GetDlgItem(IDC_PROBLEM_WARNING)->GetWindowRect(&rect);
		SetDlgItemText(IDC_PROBLEM_WARNING, waring);
	}else{
		generateProblem(number);
	}
}
