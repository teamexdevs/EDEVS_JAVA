
// DEVSView.cpp: CDEVSView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DEVS.h"
#endif

#include "DEVSDoc.h"
#include "DEVSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDEVSView

IMPLEMENT_DYNCREATE(CDEVSView, CEditView)

BEGIN_MESSAGE_MAP(CDEVSView, CEditView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDEVSView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CDEVSView::OnSimulationStart)
END_MESSAGE_MAP()

// CDEVSView 생성/소멸

CDEVSView::CDEVSView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDEVSView::~CDEVSView()
{
}

BOOL CDEVSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 자동 줄바꿈을 사용합니다.

	return bPreCreated;
}


// CDEVSView 인쇄


void CDEVSView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDEVSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 CEditView 준비
	return CEditView::OnPreparePrinting(pInfo);
}

void CDEVSView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 시작 인쇄
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDEVSView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 종료 인쇄
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CDEVSView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDEVSView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDEVSView 진단

#ifdef _DEBUG
void CDEVSView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDEVSView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDEVSDoc* CDEVSView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDEVSDoc)));
	return (CDEVSDoc*)m_pDocument;
}
#endif //_DEBUG


// CDEVSView 메시지 처리기
#include "Tglobal.h"

void CDEVSView::OnSimulationStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MakeSES();
	StartSimulation();
}