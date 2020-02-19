// History.cpp : 实现文件
//

#include "stdafx.h"
#include "YX_TEST2_2.h"
#include "History.h"
#include "afxdialogex.h"


// CHistory 对话框

IMPLEMENT_DYNAMIC(CHistory, CDialogEx)

CHistory::CHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHistory::IDD, pParent)
{
	 
}

CHistory::~CHistory()
{
}

void CHistory::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY_LIST, m_historyList);
	DDX_Control(pDX, IDC_FILE_TREE, m_timeTree);
	DDX_Control(pDX, IDC_NUMBER1, m_number1);
	DDX_Control(pDX, IDR_NUMBER2, m_number2);
	DDX_Control(pDX, IDC_NUMBER3, m_number3);
	DDX_Control(pDX, IDC_NUMBER4, m_number4);
	DDX_Control(pDX, IDC_TYPE, m_queType);
}

void CHistory::init()
{
	CImageList* pImgList;
	pImgList = new CImageList;
	pImgList -> Create(16,16, ILC_COLOR32 | ILC_MASK, 0, 1);
	pImgList->Add(AfxGetApp()->LoadIconW(IDI_FILE_ICON));

	m_timeTree.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_LINESATROOT |TVS_HASLINES);
	HTREEITEM hRoot;
	HICON hIcon;
	hIcon = theApp.LoadIconW(IDI_FILE_ICON);
	CImageList *m_imageList = new CImageList;
	m_imageList->Create(15, 15, ILC_COLOR32, 3, 3);
	m_imageList->Add(hIcon);
	m_timeTree.SetImageList(m_imageList, TVSIL_NORMAL);
	
	
	for(int i = 0; i< m_fileNames.size(); i++){
		hRoot = m_timeTree.InsertItem(m_fileNames[i], TVI_ROOT);
	}

	getHistory(m_fileNames.size()-1);

	CRect rect;
	m_historyList.GetClientRect(&rect); //获得当前listcontrol的宽度

	m_historyList.SetExtendedStyle(m_historyList.GetExtendedStyle() |
	LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_historyList.InsertColumn(0,_T("序号"),LVCFMT_CENTER,rect.Width()/3,0); // 插入列并设置每一列的宽度
	m_historyList.InsertColumn(1,_T("题目"),LVCFMT_CENTER,rect.Width()/3,1);
	m_historyList.InsertColumn(2,_T("结果"),LVCFMT_CENTER,rect.Width()/3,2);
	drawHistory();
	drawQuestion(0);
}


BEGIN_MESSAGE_MAP(CHistory, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_FILE_TREE, &CHistory::OnSelchangedFileTree)
//	ON_NOTIFY(NM_RDBLCLK, IDC_HISTORY_LIST, &CHistory::OnRdblclkHistoryList)
	ON_NOTIFY(NM_DBLCLK, IDC_HISTORY_LIST, &CHistory::OnDblclkHistoryList)
//	ON_STN_CLICKED(IDC_FIRST_SECOND, &CHistory::OnStnClickedFirstSecond)
END_MESSAGE_MAP()


// CHistory 消息处理程序


BOOL CHistory::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CenterWindow();
	
	getAllFile();
	init();
	return TRUE;  // return TRUE unless you set the focus to a control

}

void CHistory::getAllFile()
{
	CString csDirPath("..\\HISTORY\\*.txt");
	HANDLE file;
	WIN32_FIND_DATA fileData;
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	CString buf = fileData.cFileName;
	int postion=buf.Find('.');
	buf = buf.Left(postion);
	m_fileNames.push_back(buf);
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while(bState){
		buf = fileData.cFileName;
		postion=buf.Find('.');
		buf = buf.Left(postion);
		m_fileNames.push_back(buf);
		bState = FindNextFile(file, &fileData);
	}
	int a=0;
}

void CHistory::getHistory(int index)
{
	CString name(_T("..\\HISTORY\\"));
	name += m_fileNames[index];
	name += ".txt";
	CFileException fx;
	CStdioFile file;
	//获取文件
	bool flag = file.Open(name, CFile::typeText|CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate, &fx);
	if(!flag){
		AfxMessageBox(_T("文件打开失败！请重试！"));
		return ;
	}

	CString str(_T(""));
	CString num;  
	int number;
	//清除所有数据
	m_x.clear();
	m_type.clear();
	m_y.clear();
	m_res.clear();
	m_judgeRes.clear();
	m_correctRes.clear();
	int index1 = 0;
	//开始读文件数据
	while(file.ReadString(str)){
		int j = 0,i;
		//找第一个数字
		//从第j位开始找间断符所在位置，返回空格符下标
		i = str.Find(_T(" "),j);
		//从第j位开始，截取i-j的长度
		num = str.Mid(j, i - j);
		//CString转为int
		number = _ttoi(num);
		m_x.push_back(number);
		//下一次从空格符的下一位开始寻找
		j += (i - j + 1);
		//找运算类型
		i = str.Find(_T(" "),j);
		num = str.Mid(j, i - j);
		number = _ttoi(num);
		m_type.push_back(number);
		j += (i - j + 1);
		//找第二个数字
		i = str.Find(_T(" "),j);
		num = str.Mid(j, i - j);
		number = _ttoi(num);
		m_y.push_back(number);
		j += (i - j + 1);
		//找输入结果
		i = str.Find(_T(" "),j);
		num = str.Mid(j, i - j);
		number = _ttoi(num);
		m_res.push_back(number);
		j += (i - j + 1);
		
		int correctllyRes = 0;
		//算出正确答案
		if(m_type[index1] == 0){
			correctllyRes = m_x[index1]*m_y[index1];
		}else if(m_type[index1] ==1){
			correctllyRes = m_x[index1]+m_y[index1];
		}else{
			correctllyRes = m_x[index1]-m_y[index1];
		}
		//存储正确答案
		m_correctRes.push_back(correctllyRes);
		//判断结果
		if(m_res[index1] == -10001){
			m_judgeRes.push_back(-1);
		}else if(m_res[index1] == correctllyRes){
			m_judgeRes.push_back(1);
		}else{
			m_judgeRes.push_back(0);
		}
		//当前行数加一
		index1++;
	}
	//关闭文件
	file.Close();
}

void CHistory::drawHistory(){
	CString num;
	CString question;
	//删除列表所有数据
	m_historyList.DeleteAllItems();
	for(int i=0;i<m_res.size();i++){
		num.Format(_T("%d"), i);
		//插入行
		m_historyList.InsertItem(i,num); 
		if(m_type[i] == 0){
			question.Format(_T("%d*%d"),m_x[i], m_y[i]);
		}else if(m_type[i] ==1){
			question.Format(_T("%d+%d"),m_x[i], m_y[i]);
		}else{
			question.Format(_T("%d-%d"),m_x[i], m_y[i]);
		}
		//插入问题
		if(!m_historyList.SetItemText(i,1,question)){
			AfxMessageBox(_T("写入数据失败！"));
		}
		//插入结果
		if(m_judgeRes[i] == -1){
			m_historyList.SetItemText(i,2,_T("未做"));
		}else if(m_judgeRes[i] == 1){
			m_historyList.SetItemText(i,2,_T("正确"));
		}else{
			m_historyList.SetItemText(i,2,_T("错误"));
		}
	}

}


void CHistory::OnSelchangedFileTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString tmp = m_timeTree.GetItemText(m_timeTree.GetSelectedItem());
	int index = 0;
	for(int i=0;i<m_fileNames.size();i++){
		if(m_fileNames[i] == tmp){
			index = i;
			break;
		}
	}

	getHistory(index);
	drawHistory();
	drawQuestion(0);
	*pResult = 0;
}


void CHistory::OnDblclkHistoryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int sel;
	sel = m_historyList.GetNextItem(-1, LVIS_SELECTED);
	if (sel < 0)
	{
		return;
	}
	drawQuestion(sel);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CHistory::drawQuestion(int index)
{
	//清除Picture控件的图片
	m_number1.ShowWindow(FALSE);
	m_number2.ShowWindow(FALSE);
	m_number3.ShowWindow(FALSE);
	m_number4.ShowWindow(FALSE);
	m_queType.ShowWindow(FALSE);
	//获取第一个数字的前后两位
	int a = m_x[index] / 10;
	int b = m_x[index] % 10;
	//如果前一个数字不为0，则表示这个为两位数，那么就设置其图片
	if(a != 0){
		setBitMap(1,a);
	}
	//设置后一个数字图片
	setBitMap(2,b);

	a = m_y[index] / 10;
	b = m_y[index] % 10;
	//如果第二个数字是两位数，那么就设置两个图片
	if(a!=0){
		setBitMap(3, a);
		setBitMap(4, b);
	}else {
		//如果不是两位数，那么就将数字设置到前一个图片位
		setBitMap(3, b);
	}
	if(m_type[index] == 0){//如果运算位为乘
		setBitMap(5, 10);
	}else if(m_type[index] == 1){//如果运算位为减
		setBitMap(5, 12);
	}else {//如果运算位为加
		setBitMap(5, 11);
	}
	//设置正确答案
	CString corrent;
	corrent.Format(_T("%d"), m_correctRes[index]);
	SetDlgItemText(IDC_HISTORY_CORRECT, corrent);
	//设置结果
	CString res;
	res.Format(_T("%d"), m_res[index]);
	//如果答案是-10001，那么这道题就是没有回答的
	if(m_res[index] == -10001){
		SetDlgItemText(IDC_HISTORY_RESULT, _T("未回答"));
		
	}else{
		SetDlgItemText(IDC_HISTORY_RESULT, res);
	}
}


void CHistory::setBitMap(int index1, int index2)
{
	// TODO: 在此添加控件通知处理程序代码
	if(index1 == 1){
		m_number1.ShowWindow(TRUE);
		m_number1.SetBitmap(M_HBMP[index2]);
	}else if(index1 ==2){
		m_number2.ShowWindow(TRUE);
		m_number2.SetBitmap(M_HBMP[index2]);
	}else if(index1 == 3){
		m_number3.ShowWindow(TRUE);
		m_number3.SetBitmap(M_HBMP[index2]);
	}else if(index1 ==4){
		m_number4.ShowWindow(TRUE);
		m_number4.SetBitmap(M_HBMP[index2]);
	}else if(index1 == 5){
		m_queType.ShowWindow(TRUE);
		m_queType.SetBitmap(M_HBMP[index2]);
	}
}
