
// YX_TEST2_2Doc.cpp : CYX_TEST2_2Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "YX_TEST2_2.h"
#endif

#include "YX_TEST2_2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CYX_TEST2_2Doc

IMPLEMENT_DYNCREATE(CYX_TEST2_2Doc, CDocument)

BEGIN_MESSAGE_MAP(CYX_TEST2_2Doc, CDocument)
END_MESSAGE_MAP()


// CYX_TEST2_2Doc 构造/析构

CYX_TEST2_2Doc::CYX_TEST2_2Doc()
{
	// TODO: 在此添加一次性构造代码
	
	M_BITMAP[0].LoadBitmap(IDB_ZERO);   
	M_HBMP[0] = (HBITMAP)M_BITMAP[0].GetSafeHandle();  

	M_BITMAP[1].LoadBitmap(IDB_ONE);   
	M_HBMP[1] = (HBITMAP)M_BITMAP[1].GetSafeHandle();   

	M_BITMAP[2].LoadBitmap(IDB_TWO);   
	M_HBMP[2] = (HBITMAP)M_BITMAP[2].GetSafeHandle();   

	M_BITMAP[3].LoadBitmap(IDB_THREE);   
	M_HBMP[3] = (HBITMAP)M_BITMAP[3].GetSafeHandle();   

	M_BITMAP[4].LoadBitmap(IDB_FOUR);   
	M_HBMP[4] = (HBITMAP)M_BITMAP[4].GetSafeHandle();  

	M_BITMAP[5].LoadBitmap(IDB_FIVE);   
	M_HBMP[5] = (HBITMAP)M_BITMAP[5].GetSafeHandle();     

	M_BITMAP[6].LoadBitmap(IDB_SIX);   
	M_HBMP[6] = (HBITMAP)M_BITMAP[6].GetSafeHandle();   

	M_BITMAP[7].LoadBitmap(IDB_SEVEN);   
	M_HBMP[7] = (HBITMAP)M_BITMAP[7].GetSafeHandle();     

	M_BITMAP[8].LoadBitmap(IDB_EIGHT);   
	M_HBMP[8] = (HBITMAP)M_BITMAP[8].GetSafeHandle();    

	M_BITMAP[9].LoadBitmap(IDB_NINE);  
	M_HBMP[9] = (HBITMAP)M_BITMAP[9].GetSafeHandle();     

	//乘
	M_BITMAP[10].LoadBitmap(IDB_PLUS);   
	M_HBMP[10] = (HBITMAP)M_BITMAP[10].GetSafeHandle();  
	//减
	M_BITMAP[11].LoadBitmap(IDB_REDUCE);   
	M_HBMP[11] = (HBITMAP)M_BITMAP[11].GetSafeHandle();    
	//加
	M_BITMAP[12].LoadBitmap(IDB_ADD);   
	M_HBMP[12] = (HBITMAP)M_BITMAP[12].GetSafeHandle();        


}

CYX_TEST2_2Doc::~CYX_TEST2_2Doc()
{
}

BOOL CYX_TEST2_2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CYX_TEST2_2Doc 序列化

void CYX_TEST2_2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CYX_TEST2_2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CYX_TEST2_2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CYX_TEST2_2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CYX_TEST2_2Doc 诊断

#ifdef _DEBUG
void CYX_TEST2_2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CYX_TEST2_2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CYX_TEST2_2Doc 命令

void CYX_TEST2_2Doc::SetQuestions(LPARAM lParam){
	vector<int> *vec = (vector<int> *)lParam;
	 m_questions = vec;
}

vector<int>* CYX_TEST2_2Doc::GetQuestions(){
	return m_questions;
}

void CYX_TEST2_2Doc::SetResults(LPARAM lParam){
	vector<int> *vec = (vector<int> *)lParam;
	m_results = vec;
}

vector<int>* CYX_TEST2_2Doc::GetResults(){
	return m_results;
}


void CYX_TEST2_2Doc::saveFile(){
	CTime time;
	time = CTime::GetCurrentTime();
	CString title("..\\HISTORY\\");
	title += time.Format("%Y-%m-%d");
	title += (".txt");
	CStdioFile file;
	CFileException fx;
	bool flag = file.Open(title, CFile::typeText|CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate, &fx);
	if(flag){
		CString msg;
		file.SeekToEnd();
		std::stringstream s1;
		string que;
		std::copy(m_questions->begin(),m_questions->end(),ostream_iterator<int>(s1," "));
		que = s1.str();
		que+=" ";
		
		std::stringstream s2;
		string res;
		std::copy(m_results->begin(),m_results->end(),ostream_iterator<int>(s2," "));
		res = s2.str();
		int j=0;
		int index, len;
		for(int i=0;i<res.length();){
			string x;
			index = que.find(" ", j);
			len = index - j;
			x = que.substr(j,len);
			j+=(len + 1);

			string ty;
			index = que.find(" ", j);
			len = index - j;
			ty = que.substr(j,len);
			j+=(len + 1);
			
			string y;
			index = que.find(" ", j);
			len = index - j;
			y =  que.substr(j,len);
			j+=(len + 1);
			
			string r;
			index = res.find(" ", i);
			len = index - i;
			r =  res.substr(i,len);
			i+=(len + 1);

			string info = x + " " + ty + " " + y + " " + r + " " + "\n";
			msg = info.c_str();
			file.WriteString(msg);
		}
		file.Close();
		AfxMessageBox(_T("写入记录成功！"));
	}else {
		AfxMessageBox(_T("打开文件失败！请重试！"));
	}
}