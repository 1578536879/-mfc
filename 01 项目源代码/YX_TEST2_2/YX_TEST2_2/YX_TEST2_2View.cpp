
// YX_TEST2_2View.cpp : CYX_TEST2_2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CYX_TEST2_2View ����/����

CYX_TEST2_2View::CYX_TEST2_2View()
{
	// TODO: �ڴ˴���ӹ������

}

CYX_TEST2_2View::~CYX_TEST2_2View()
{
}

BOOL CYX_TEST2_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return CView::PreCreateWindow(cs);
}

// CYX_TEST2_2View ����

void CYX_TEST2_2View::OnDraw(CDC* /*pDC*/)
{
	CYX_TEST2_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CDC *pdc = GetDC();
	CFont font;
	font.CreateFont(
		20, 10,0,0,100,
		FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("����"));
	pdc->TextOut(100 ,50, _T("��ѡ������Ҫ�Ĳ�����"));
	
	

}


// CYX_TEST2_2View ��ӡ


void CYX_TEST2_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CYX_TEST2_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CYX_TEST2_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CYX_TEST2_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CYX_TEST2_2View ���

#ifdef _DEBUG
void CYX_TEST2_2View::AssertValid() const
{
	CView::AssertValid();
}

void CYX_TEST2_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYX_TEST2_2Doc* CYX_TEST2_2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYX_TEST2_2Doc)));
	return (CYX_TEST2_2Doc*)m_pDocument;
}
#endif //_DEBUG



// CYX_TEST2_2View ��Ϣ�������


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
	int result = MessageBox( TEXT("ȷ����ʼ������") , TEXT("��ʾ") ,MB_YESNO);
	switch(result)
	{
	  case IDYES:
		{
			//���YES��ť�ľ���ʵ�ֹ���
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
	
	int result = MessageBox( TEXT("�Ƿ�鿴�����¼��") , TEXT("��ʾ") ,MB_YESNO);
	switch(result)
	{
	  case IDYES:
		{
			//���YES��ť�ľ���ʵ�ֹ���
			CHistory his;
			his.DoModal();
		}
	 case IDNO:
		break;
	}
}



void CYX_TEST2_2View::OnMenuGenerate()
{
	// TODO: �ڴ���������������
	CGenerateProblem gb;
	gb.DoModal();
}


void CYX_TEST2_2View::OnMenuHistory()
{
	// TODO: �ڴ���������������
	CHistory his;
	his.DoModal();
}
