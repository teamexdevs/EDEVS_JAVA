
// DEVSView.h: CDEVSView 클래스의 인터페이스
//

#pragma once


class CDEVSView : public CEditView
{
protected: // serialization에서만 만들어집니다.
	CDEVSView() noexcept;
	DECLARE_DYNCREATE(CDEVSView)

// 특성입니다.
public:
	CDEVSDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDEVSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSimulationStart();
};

#ifndef _DEBUG  // DEVSView.cpp의 디버그 버전
inline CDEVSDoc* CDEVSView::GetDocument() const
   { return reinterpret_cast<CDEVSDoc*>(m_pDocument); }
#endif

