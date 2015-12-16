// PropertiesViewBar.cpp : implementation of the LFPropBar class
//

#include "stdafx.h"
#include "AutoWatcher.h"
#include "PropertiesViewBar.h"
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// LFPropBar class

LFPropBar::LFPropBar()
{
	m_BorderColor = LFColor::Orange;
	m_FillBrush.SetColors(LFColor::LightSteelBlue, LFColor::White, LFBrush::BCGP_GRADIENT_RADIAL_TOP_LEFT, 0.75);
	m_TextBrush.SetColor(LFColor::SteelBlue);
}

LFPropBar::~LFPropBar()
{
}

BEGIN_MESSAGE_MAP(LFPropBar, LFDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_COMMAND_CLICKED, OnCommandClicked)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_MENU_ITEM_SELECTED, OnMenuItemSelected)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void LFPropBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width (), rectClient.Height (), SWP_NOACTIVATE | SWP_NOZORDER);
}

int LFPropBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (LFDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 1))
	{
		TRACE0("�������Դ���ʧ�� \n");
		return -1;      // fail to create
	}

	InitPropList ();
	AdjustLayout ();

	return 0;
}

void LFPropBar::OnSize(UINT nType, int cx, int cy) 
{
	LFDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void LFPropBar::InitPropList ()
{
	// Add commands:
	CStringList lstCommands;
	lstCommands.AddTail (_T("���� 1..."));
	lstCommands.AddTail (_T("���� 2..."));

	m_wndPropList.SetCommands (lstCommands);

	// Add custom menu items:
	CStringList lstCustomMenuItem;
	lstCustomMenuItem.AddTail (_T("�Զ���˵��� 1"));
	lstCustomMenuItem.AddTail (_T("�Զ���˵��� 2"));
	lstCustomMenuItem.AddTail (_T("�Զ���˵��� 3"));

	m_wndPropList.SetCustomMenuItems(lstCustomMenuItem);

	// Setup general look:
	m_wndPropList.EnableToolBar();
	m_wndPropList.EnableSearchBox();
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	m_wndPropList.EnableContextMenu();

	// Add properties:
	LFProp* pGroup1 = new LFProp (_T("���"));

	pGroup1->AddSubItem (new LFProp (_T("��ά�߿�"), (_variant_t) false,
		_T("���öԻ��������Ϊ�Ǻ��壬�ؼ�������ά��ʽ")));

	LFProp* pProp = new LFProp (_T("�߿�"), _T("�Ի���"),
		_T("�ޱ߿�, �ݱ߿�, �ɱ�߿�, ���߶Ի���߿���֮һ"));
	pProp->AddOption (_T("�ޱ߿�"));
	pProp->AddOption (_T("�ݱ߿�"));
	pProp->AddOption (_T("�ɱ�߿�"));
	pProp->AddOption (_T("�Ի���߿�"));
	pProp->AllowEdit (FALSE);

	pGroup1->AddSubItem (pProp);
	pGroup1->AddSubItem (new LFProp (_T("����"), (_variant_t) _T("����"),
		_T("�����ڶԻ������������ʾ���ı�")));

	m_wndPropList.AddProperty (pGroup1);

	LFProp* pSize = new LFProp (_T("���ڴ�С"), 0, TRUE);

	pProp = new LFProp (_T("�߶�"), (_variant_t) 250l,
							_T("���öԻ���߶�"));
	pProp->EnableSpinControl (TRUE, 0, 1000);
	pSize->AddSubItem (pProp);

	pProp = new LFProp (	_T("���"), (_variant_t) 150l,
							_T("���öԻ���Ŀ��"));
	pProp->EnableSpinControl (TRUE, 0, 1000);
	pSize->AddSubItem (pProp);

	m_wndPropList.AddProperty (pSize);

	LFProp* pGroup2 = new LFProp (_T("����"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT));
	font->GetLogFont (&lf);

	lstrcpy (lf.lfFaceName, _T("����"));

	pGroup2->AddSubItem (new LFFontProp (_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("���öԻ���Ĭ������")));
	pGroup2->AddSubItem (new LFProp (_T("ʹ��ϵͳ����"), (_variant_t) true, _T("���öԻ�����Ϊ����")));

	m_wndPropList.AddProperty (pGroup2);

	LFProp* pGroup3 = new LFProp (_T("��ˢ"));

	LFColorProp* pColorProp = new LFColorProp (_T("����ɫ"), m_BorderColor, NULL, _T("���öԻ���Ĭ����ɫ"));
	pColorProp->EnableOtherButton (_T("����..."));
	pColorProp->EnableAutomaticButton (_T("Ĭ��"), globalData.clrBarShadow);
	pGroup3->AddSubItem (pColorProp);

	pGroup3->AddSubItem (new LFBrushProp (_T("����"), m_FillBrush, NULL,
		_T("����Ĭ�ϱ���ɫ")));

	pGroup3->AddSubItem (new LFBrushProp (_T("ǰ��"), m_TextBrush, NULL,
		_T("����Ĭ��ǰ��ɫ")));

	m_wndPropList.AddProperty (pGroup3);

	LFProp* pGroup4 = new LFProp (_T("����"));
	pProp = new LFProp (_T("(����)"), _T("IDD_ABOUT_BOX (�Ի���)"));
	pProp->Enable (FALSE);
	pGroup4->AddSubItem (pProp);

	static TCHAR BASED_CODE szFilter[] = _T("ͼ���ļ� (*.ico)|*.ico|�����ļ� (*.*)|*.*||");
	pGroup4->AddSubItem (new LFFileProp (_T("ͼ��"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the dialog icon")));

	pGroup4->AddSubItem (new LFFileProp (_T("�ļ���"), _T("c:\\")));

	COleDateTime date = COleDateTime::GetCurrentTime ();
	pGroup4->AddSubItem (new LFDateTimeProp (_T("����"), date,
		_T("Set a date"), 0, LFDateTimeCtrl::DTM_DATE));

	pGroup4->AddSubItem (new LFDateTimeProp (_T("ʱ��"), date,
		_T("Set a time"), 0, LFDateTimeCtrl::DTM_TIME));

	m_wndPropList.AddProperty (pGroup4);

	LFProp* pGroup5 = new LFProp (_T("ˮƽ"));

	LFProp* pGroup51 = new LFProp (_T("��һˮƽ"));
	pGroup5->AddSubItem (pGroup51);

	LFProp* pGroup511 = new LFProp (_T("�ڶ�ˮƽ"));
	pGroup51->AddSubItem (pGroup511);

	pGroup511->AddSubItem (new LFProp (_T("��Ŀ 1"), (_variant_t) _T("��ֵ 1"),
		_T("This is a description")));
	pGroup511->AddSubItem (new LFProp (_T("��Ŀ 2"), (_variant_t) _T("��ֵ 2"),
		_T("This is a description")));
	pGroup511->AddSubItem (new LFProp (_T("��Ŀ 3"), (_variant_t) _T("��ֵ 3"),
		_T("This is a description")));

	pGroup5->Expand (FALSE);
	m_wndPropList.AddProperty (pGroup5);
}

void LFPropBar::OnSetFocus(CWnd* pOldWnd) 
{
	LFDockingControlBar::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus ();
}

LRESULT LFPropBar::OnCommandClicked(WPARAM, LPARAM lp)
{
//	int nCommandIndex = (int)lp;

	// TODO: Add your command handler code here
	std::cout << "paing" << std::endl;

	return 0;
}

LRESULT LFPropBar::OnMenuItemSelected(WPARAM /*wp*/, LPARAM /*lp*/)
{
//	int nMenuIndex = (int)wp;

//	LFProp* pProp = (LFProp*)lp;
//	ASSERT_VALID(pProp);

	// TODO: Add your menu item processing code here

	return 0;
}
