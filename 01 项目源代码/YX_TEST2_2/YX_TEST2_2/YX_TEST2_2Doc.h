
// YX_TEST2_2Doc.h : CYX_TEST2_2Doc ��Ľӿ�
//


#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

class CYX_TEST2_2Doc : public CDocument
{
	vector<int> *m_questions;
	vector<int> *m_results;
protected: // �������л�����
	CYX_TEST2_2Doc();
	DECLARE_DYNCREATE(CYX_TEST2_2Doc)

// ����
public:

// ����
public:
	vector<int>* GetQuestions();
	void SetQuestions(LPARAM lParam);
	vector<int>* GetResults();
	void SetResults(LPARAM lParam);
	void saveFile();
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CYX_TEST2_2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
