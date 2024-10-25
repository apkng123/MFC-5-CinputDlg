
// WinP_53Doc.cpp: CWinP53Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinP_53.h"
#endif

#include "WinP_53Doc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinP53Doc

IMPLEMENT_DYNCREATE(CWinP53Doc, CDocument)

BEGIN_MESSAGE_MAP(CWinP53Doc, CDocument)
END_MESSAGE_MAP()


// CWinP53Doc 생성/소멸

CWinP53Doc::CWinP53Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CWinP53Doc::~CWinP53Doc()
{
}

BOOL CWinP53Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_nDocX = 0;
	m_nDocY = 0;
	m_strDocText = _T("");


	return TRUE;
}




// CWinP53Doc serialization

void CWinP53Doc::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		// 저장할 때 변수들을 차례대로 저장합니다.
		ar << m_nDocX;         // X 좌표 저장
		ar << m_nDocY;         // Y 좌표 저장 (기존 m_nDocX 중복 수정)
		ar << m_strDocText;    // 텍스트 저장
	}
	else
	{
		// 불러올 때 변수들을 차례대로 읽어옵니다.
		ar >> m_nDocX;         // X 좌표 불러오기
		ar >> m_nDocY;         // Y 좌표 불러오기
		ar >> m_strDocText;    // 텍스트 불러오기
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CWinP53Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CWinP53Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWinP53Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWinP53Doc 진단

#ifdef _DEBUG
void CWinP53Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinP53Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinP53Doc 명령
