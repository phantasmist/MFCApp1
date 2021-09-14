
// MFCApp1View.cpp: CMFCApp1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApp1.h"
#endif

#include "MFCApp1Doc.h"
#include "MFCApp1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApp1View

IMPLEMENT_DYNCREATE(CMFCApp1View, CEditView)

BEGIN_MESSAGE_MAP(CMFCApp1View, CEditView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApp1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MN_ZOOMIN, &CMFCApp1View::OnMnZoomin)
	ON_COMMAND(ID_MN_ZOOMOUT, &CMFCApp1View::OnMnZoomout)
END_MESSAGE_MAP()

// CMFCApp1View 생성/소멸

CMFCApp1View::CMFCApp1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApp1View::~CMFCApp1View()
{
}

BOOL CMFCApp1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 자동 래핑을 사용합니다.

	return bPreCreated;
}


// CMFCApp1View 인쇄


void CMFCApp1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApp1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 CEditView 준비
	return CEditView::OnPreparePrinting(pInfo);
}

void CMFCApp1View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 시작 인쇄
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMFCApp1View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 종료 인쇄
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CMFCApp1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApp1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApp1View 진단

#ifdef _DEBUG
void CMFCApp1View::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCApp1View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCApp1Doc* CMFCApp1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApp1Doc)));
	return (CMFCApp1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApp1View 메시지 처리기

//static int fSize = 100;
CFont tf;
void CMFCApp1View::OnMnZoomin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LOGFONT lf; //로컬 변수들은 스택에 존재함
	//ZeroMemory(&lf, sizeof(lf));
	//fSize++;
	//lf.lfHeight = fSize;
	if (GetFont() == NULL)
	{
		CFont* pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
		pFont->GetLogFont(&lf);// 음수값이 기본인 경우가 많음
	}
	else
		GetFont()->GetLogFont(&lf); // 현재 포인터 lf로 읽어오기

	if (lf.lfHeight < 0)
		lf.lfHeight = abs(lf.lfHeight);
	lf.lfHeight++;

	//CFont* cf = new CFont; // 이걸 스택에 만드는건 별로 좋지 않음
	tf.DeleteObject();
	tf.CreateFontIndirect(&lf);
	SetFont(&tf); //MSD SDI 모델에서 View를 이용하는 이유
}


void CMFCApp1View::OnMnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LOGFONT lf;
	//ZeroMemory(&lf, sizeof(lf));
	//fSize -= 10;
	if (GetFont() == NULL)
	{
		CFont* pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
		pFont->GetLogFont(&lf);// 음수값이 기본인 경우가 많음
	}
	else
		GetFont()->GetLogFont(&lf); // 현재 포인터 lf로 읽어오기

	if (lf.lfHeight < 0)
		lf.lfHeight = abs(lf.lfHeight);
	lf.lfHeight--;

	//CFont* cf = new CFont; //new로 스택에 생성하지 말자
	tf.DeleteObject();
	tf.CreateFontIndirect(&lf); //CreatePointFontIndirect(&lf)여서 문제가 발생했던 것
	SetFont(&tf);
}


//여기에 PreTranslateMessage 넣어도 실행된다
//하지만 App에서도 받아 쓰니까 오작동의 여지가 있음
//BOOL CMFCApp1View::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	switch (pMsg->message)
//	{
//	case WM_KEYDOWN:
//		switch (pMsg->wParam)
//		{
//		case VK_OEM_PLUS:
//			if(GetKeyState(VK_CONTROL) < 0)
//				OnMnZoomin(); break;
//		case VK_OEM_MINUS:
//			if(GetKeyState(VK_CONTROL) < 0)
//				OnMnZoomout(); break;
//		default: break;
//		}
//	}
//	return CEditView::PreTranslateMessage(pMsg);
//}
