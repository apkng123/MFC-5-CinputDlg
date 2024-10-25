
// WinP_53View.cpp: CWinP53View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinP_53.h"
#endif

#include "WinP_53Doc.h"
#include "WinP_53View.h"
#include "CInputDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinP53View

IMPLEMENT_DYNCREATE(CWinP53View, CView)

BEGIN_MESSAGE_MAP(CWinP53View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CWinP53View 생성/소멸

CWinP53View::CWinP53View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWinP53View::~CWinP53View()
{
}

BOOL CWinP53View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWinP53View 그리기

void CWinP53View::OnDraw(CDC* pDC)
{
	CWinP53Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 배경을 투명하게 설정 (필요한 경우)
	pDC->SetBkMode(TRANSPARENT);

	// 텍스트 색상 설정 및 출력
	if (pDoc->m_nDocColor == 0)
	{
		pDC->SetTextColor(RGB(0, 0, 0));  // 검은색 텍스트
		pDC->TextOut(pDoc->m_nDocX, pDoc->m_nDocY, pDoc->m_strDocText);
	}
	else if (pDoc->m_nDocColor == 1)
	{
		pDC->SetTextColor(RGB(255, 0, 0));  // 빨간색 텍스트
		pDC->TextOut(pDoc->m_nDocX, pDoc->m_nDocY, pDoc->m_strDocText);
	}

}


// CWinP53View 인쇄

BOOL CWinP53View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWinP53View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWinP53View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CWinP53View 진단

#ifdef _DEBUG
void CWinP53View::AssertValid() const
{
	CView::AssertValid();
}

void CWinP53View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinP53Doc* CWinP53View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinP53Doc)));
	return (CWinP53Doc*)m_pDocument;
}
#endif //_DEBUG


// CWinP53View 메시지 처리기


void CWinP53View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CInputDlg* pInput = new CInputDlg;

	if (pInput->DoModal() == IDOK)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CWinP53Doc* pDoc = (CWinP53Doc*)pFrame->GetActiveDocument();
		UpdateData(TRUE);

		pDoc->m_nDocX = pInput->m_nX;
		pDoc->m_nDocY = pInput->m_nY;
		pDoc->m_strDocText = pInput->m_strText;

		Invalidate();
	}

	CView::OnRButtonDown(nFlags, point);
}
