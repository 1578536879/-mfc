
// YX_TEST2_2View.cpp : CYX_TEST2_2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "YX_TEST2_2.h"
#endif

#include "YX_TEST2_2Doc.h"
#include "YX_TEST2_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYX_TEST2_2View

IMPLEMENT_DYNCREATE(CYX_TEST2_2View, CView)

BEGIN_MESSAGE_MAP(CYX_TEST2_2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CYX_TEST2_2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_START, &CYX_TEST2_2View::OnStart)
	ON_BN_CLICKED(IDC_GENERATE_PROBLEM, &CYX_TEST2_2View::OnClickedGenerateProblem)
	ON_BN_CLICKED(IDC_HISTORY, &CYX_TEST2_2View::OnClickedHistory)
	ON_MESSAGE (WM_GENERATE_QUESTION, generate)
	ON_MESSAGE (WM_SAVE_RESULT, submit)

	ON_COMMAND(ID_MENU_GENERATE, &CYX_TEST2_2View::OnMenuGenerate)
	ON_COMMAND(ID_MENU_HISTORY, &CYX_TEST2_2View::OnMenuHistory)
END_MESSAGE_MAP()

// CYX_TEST2_2View 构造/析构

CYX_TEST2_2View::CYX_TEST2_2View()
{
	// TODO: 在此处添加构造代码

}

CYX_TEST2_2View::~CYX_TEST2_2View()
{
}

BOOL CYX_TEST2_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CYX_TEST2_2View 绘制

void CYX_TEST2_2View::OnDraw(CDC* /*pDC*/)
{
	CYX_TEST2_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC *pdc = GetDC();
	CFont font;
	font.CreateFont(
		20, 10,0,0,100,
		FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("宋体"));
	pdc->TextOut(100 ,50, _T("请选择您需要的操作："));
	
	

}


// CYX_TEST2_2View 打印


void CYX_TEST2_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CYX_TEST2_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CYX_TEST2_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CYX_TEST2_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CYX_TEST2_2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CYX_TEST2_2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CYX_TEST2_2View 诊断

#ifdef _DEBUG
void CYX_TEST2_2View::AssertValid() const
{
	CView::AssertValid();
}

void CYX_TEST2_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYX_TEST2_2Doc* CYX_TEST2_2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYX_TEST2_2Doc)));
	return (CYX_TEST2_2Doc*)m_pDocument;
}
#endif //_DEBUG



// CYX_TEST2_2View 消息处理程序


void CYX_TEST2_2View::OnClickedGenerateProblem(){
	CGenerateProblem gb;
	gb.DoModal();

}

void CYX_TEST2_2View::OnClickedHistory(){
	CHistory his;
	his.DoModal();
}

LRESULT CYX_TEST2_2View::generate (WPARAM wParam, LPARAM lParam)
{
	
	//EndDialog(-1);
	//CQuestion *que;
	CYX_TEST2_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;
	//m_questions = (vector<int> *)lParam;
	vector<int> *vec = (vector<int> *)lParam;
	pDoc->SetQuestions(lParam);
	int result = MessageBox( TEXT("确定开始做题吗？") , TEXT("提示") ,MB_YESNO);
	switch(result)
	{
	  case IDYES:
		{
			//点击YES按钮的具体实现功能
			CQuestion que;
			que.init((vector<int>*)lParam);
			que.DoModal();
			
		}
	 case IDNO:
		break;
	}

	return 0;

}

LRESULT CYX_TEST2_2View::submit (WPARAM wParam, LPARAM lParam)
{
	
	//EndDialog(-1);
	//CQuestion *que;
	CYX_TEST2_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;
	pDoc->SetResults(lParam);
	pDoc->saveFile();
	UpdateData(true);
	
	int result = MessageBox( TEXT("是否查看做题记录？") , TEXT("提示") ,MB_YESNO);
	switch(result)
	{
	  case IDYES:
		{
			//点击YES按钮的具体实现功能
			CHistory his;
			his.DoModal();
		}
	 case IDNO:
		break;
	}
}



void CYX_TEST2_2View::OnMenuGenerate()
{
	// TODO: 在此添加命令处理程序代码
	CGenerateProblem gb;
	gb.DoModal();
}


void CYX_TEST2_2View::OnMenuHistory()
{
	// TODO: 在此添加命令处理程序代码
	CHistory his;
	his.DoModal();
}
