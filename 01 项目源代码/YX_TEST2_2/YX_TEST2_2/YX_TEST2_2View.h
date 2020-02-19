
// YX_TEST2_2View.h : CYX_TEST2_2View 类的接口
//

#pragma once
#include "Question.h"
#include "GenerateProblem.h"
#include "History.h"


class CYX_TEST2_2View : public CView
{
	CButton m_questionBnt;
	CButton m_socreBnt;
	

protected: // 仅从序列化创建
	CYX_TEST2_2View();
	DECLARE_DYNCREATE(CYX_TEST2_2View)

// 特性
public:
	CYX_TEST2_2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CYX_TEST2_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // YX_TEST2_2View.cpp 中的调试版本
inline CYX_TEST2_2Doc* CYX_TEST2_2View::GetDocument() const
   { return reinterpret_cast<CYX_TEST2_2Doc*>(m_pDocument); }
#endif

