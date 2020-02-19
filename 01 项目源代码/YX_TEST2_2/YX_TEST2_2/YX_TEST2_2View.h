
// YX_TEST2_2View.h : CYX_TEST2_2View ��Ľӿ�
//

#pragma once
#include "Question.h"
#include "GenerateProblem.h"
#include "History.h"


class CYX_TEST2_2View : public CView
{
	CButton m_questionBnt;
	CButton m_socreBnt;
	

protected: // �������л�����
	CYX_TEST2_2View();
	DECLARE_DYNCREATE(CYX_TEST2_2View)

// ����
public:
	CYX_TEST2_2Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CYX_TEST2_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClickedGenerateProblem();
	afx_msg void OnClickedHistory();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStart();
	afx_msg LRESULT generate (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT submit (WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuGenerate();
	afx_msg void OnMenuHistory();
};

#ifndef _DEBUG  // YX_TEST2_2View.cpp �еĵ��԰汾
inline CYX_TEST2_2Doc* CYX_TEST2_2View::GetDocument() const
   { return reinterpret_cast<CYX_TEST2_2Doc*>(m_pDocument); }
#endif

