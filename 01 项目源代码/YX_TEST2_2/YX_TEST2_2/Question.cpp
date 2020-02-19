// Question.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YX_TEST2_2.h"
#include "Question.h"
#include "afxdialogex.h"


// CQuestion �Ի���

IMPLEMENT_DYNAMIC(CQuestion, CDialogEx)

CQuestion::CQuestion(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuestion::IDD, pParent)
{
}

CQuestion::~CQuestion()
{
}

void CQuestion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQuestion, CDialogEx)
	ON_BN_CLICKED(IDC_QUESTION_NEXT, &CQuestion::OnClickedQuestionNext)
	ON_BN_CLICKED(IDC_QUEATION_PREVIOUS, &CQuestion::OnBnClickedQueationPrevious)
	ON_BN_CLICKED(IDC_QUESTION_SUBMIT, &CQuestion::OnBnClickedQuestionSubmit)
	ON_BN_CLICKED(IDC_BUTTON4, &CQuestion::OnBnClickedButton4)
END_MESSAGE_MAP()


// CQuestion ��Ϣ�������


void CQuestion::OnClickedQuestionNext()
{
	CString answer;
	GetDlgItemText(IDC_QUESTION_RESULT, answer);
	int number;
	if(answer == ""){
		number = -10001;
		if(m_result[m_index] != -10001){
			m_alreadyNumber--;
		}
	}else {
		number = _ttoi(answer);
		if(m_result[m_index] == -10001){
			m_alreadyNumber++;
		}

	}
	m_result[m_index] = number;
	if(m_index>=m_allNumber-1){
		AfxMessageBox( _T("�Ѿ������һ������"));
	}else{
		m_index++;
		answer.Format(_T(""));
		SetDlgItemText(IDC_QUESTION_RESULT, answer);
		repaint();
	}
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CQuestion::init(vector<int> *pro){
	m_allNumber = pro->size()/3;
	m_alreadyNumber = 0;
	int i=0;
	for(vector<int>::const_iterator iter = pro->cbegin(); iter != pro->cend(); iter++){
		m_x.push_back((*iter));
		iter ++;
		m_type.push_back((*iter));
		iter ++;
		m_y.push_back((*iter));
		if(m_type[i]==0){
			m_correctResult.push_back(m_x[i]*m_y[i]);
		}else if(m_type[i]==1){
			m_correctResult.push_back(m_x[i]+m_y[i]);
		
		}else{
			m_correctResult.push_back(m_x[i]-m_y[i]);
		
		}
		m_result.push_back(-10001);
		i++;
	}
}

void CQuestion::repaint(){
	CString str1,str2,str;
	int x,y,type;
	//����ǵ�һ���ȡȫ�ֱ�������Ϊ��һ������ݴ洢��FIRST������
	if(m_index == 0 && m_result.size() == 0){
		x = FIRST[0];
		y = FIRST[2];
		type = FIRST[1];
		//�����ı�
		str.Format(_T("0/%d"), FIRST[3]/3);
		SetDlgItemText(IDC_QUESTION_RATE, str);
	}else{
		x = m_x[m_index];
		y = m_y[m_index];
		type = m_type[m_index];
		//�����ı�
		str.Format(_T("%d/%d"),m_alreadyNumber,m_allNumber);
		SetDlgItemText(IDC_QUESTION_RATE, str);
	}

	if(type == 0){
		str.Format(_T("%d*%d"),x,y);
	}else if(type ==1){
		str.Format(_T("%d+%d"),x,y);
	}else{
		str.Format(_T("%d-%d"),x,y);
	}
	//���������ı�
	SetDlgItemText(IDC_QUESTION_CONTENT, str);
	//���ô𰸿�
	if(m_result[m_index]!=-10001){
		str.Format(_T("%d"),m_result[m_index]);
		SetDlgItemText(IDC_QUESTION_RESULT, str);
	}else{
		//��������-10001����ʾ����⻹δ�����
		SetDlgItemText(IDC_QUESTION_RESULT, _T(""));
		
	}
	
}

BOOL CQuestion::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CenterWindow();
	m_index = 0;
	repaint();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}




void CQuestion::OnBnClickedQueationPrevious()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString answer;
	GetDlgItemText(IDC_QUESTION_RESULT, answer);
	//��ȡ������
	int number;
	//���û������ֵ���ʹ洢Ϊ-10001
	if(answer == ""){
		number = -10001;
		//���û������ֵ����֮ǰ�Ĵ���ֵ����ô�������һ
		if(m_result[m_index] != -10001){
			m_alreadyNumber--;
		}
	}else {
		number = _ttoi(answer);
		//���������ֵ����֮ǰ�Ĵ�û��ֵ����ô����������һ
		if(m_result[m_index] == -10001){
			m_alreadyNumber++;
		}

	}
	//������ֵ��������
	m_result[m_index] = number;
	//��ҳ
	if(m_index <= 0){
		AfxMessageBox(_T("�Ѿ��ǵ�һ������"));
	}else{
		m_index--;
		repaint();
	}
}


void CQuestion::OnBnClickedQuestionSubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString answer;
	GetDlgItemText(IDC_QUESTION_RESULT, answer);
	int number;
	if(answer != ""){
		number = _ttoi(answer);
		m_result[m_index] = number;
	}else{
		m_result[m_index] = -10001;
	}
	int n1=0,n2=0,n3=0;
	for(int i=0;i<m_correctResult.size();i++){
		if(m_result[i] == -10001){
			m_checkResult.push_back(-1);
			n1++;
		}else if(m_result[i] == m_correctResult[i]){
			m_checkResult.push_back(1);
			n2++;
		}else{
			m_checkResult.push_back(0);
			n3++;
		}
	}
	CString str;
	str.Format(_T("������ϰ��������%d���⣬���д��%d�⣬���%d�⣬δ��%d��"), m_allNumber, n2,n3,n1);
	AfxMessageBox(str);
	
	CDialogEx::OnOK();
	GetParent()->SendMessage(WM_SAVE_RESULT, 0,(LPARAM)&m_result);
}


void CQuestion::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int result = MessageBox( TEXT("�Ƿ�ȡ�����⣿") , TEXT("��ʾ") ,MB_YESNO);
	switch(result)
	{
	  case IDYES:
		{
			//���YES��ť�ľ���ʵ�ֹ���
			CDialogEx::OnOK();
		}
	 case IDNO:
		break;
	}
}
