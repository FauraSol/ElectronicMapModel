// CMapDialog.cpp: 实现文件
//

//#include "Resource.h"
#include "pch.h"
#include "HustMap.h"
#include "CMapDialog.h"
#include "afxdialogex.h"
#include"MainFrm.h"
#include"HustMapView.h"
#include"HustMapDoc.h"
#include"CMapModel.h"
#include"dijkstra.h"

// CMapDialog 对话框

IMPLEMENT_DYNAMIC(CMapDialog, CDialogEx)

CMapDialog::CMapDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAP_DIALOG, pParent)
{

}

CMapDialog::~CMapDialog()
{
}

void CMapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_START, m_ComboStart);
	DDX_Control(pDX, IDC_COMBO_END, m_ComboEnd);
}


BEGIN_MESSAGE_MAP(CMapDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMapDialog::OnBnClickedOk)
END_MESSAGE_MAP()




// CMapDialog 消息处理程序


BOOL CMapDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CComboBox* pComboBoxStart =
		dynamic_cast<CComboBox*>(this->GetDlgItem(IDC_COMBO_START));
	CComboBox* pComboBoxEnd =
		dynamic_cast<CComboBox*>(this->GetDlgItem(IDC_COMBO_END));


	pComboBoxStart->AddString(_T("华中科技大学正门"));
	pComboBoxStart->AddString(_T("华中科技大学南二门"));
	pComboBoxStart->AddString(_T("华中科技大学南三门"));
	pComboBoxStart->AddString(_T("化学学院"));
	pComboBoxStart->AddString(_T("煤燃烧实验室"));
	pComboBoxStart->AddString(_T("紫菘学生公寓"));
	pComboBoxStart->AddString(_T("计算机学院"));
	pComboBoxStart->AddString(_T("电信学院"));
	pComboBoxStart->AddString(_T("图书馆"));
	pComboBoxStart->AddString(_T("西一学生食堂"));
	pComboBoxStart->AddString(_T("人文学院"));
	pComboBoxStart->AddString(_T("法学院"));
	pComboBoxStart->AddString(_T("科技楼"));
	pComboBoxStart->AddString(_T("友谊公寓"));
	pComboBoxStart->AddString(_T("教工活动中心"));
	pComboBoxStart->AddString(_T("印刷厂"));
	pComboBoxStart->AddString(_T("计算中心"));
	pComboBoxStart->AddString(_T("华中教育网中心"));
	pComboBoxStart->AddString(_T("电信收费中心"));
	pComboBoxStart->AddString(_T("档案馆"));
	pComboBoxStart->AddString(_T("八号楼"));
	pComboBoxStart->AddString(_T("招待所"));
	pComboBoxStart->AddString(_T("静园"));
	pComboBoxStart->AddString(_T("南三楼"));
	pComboBoxStart->AddString(_T("西五楼"));
	pComboBoxStart->AddString(_T("西十二楼"));
	pComboBoxStart->AddString(_T("建筑学院"));
	pComboBoxStart->AddString(_T("西五舍"));
	pComboBoxStart->AddString(_T("西六舍"));
	pComboBoxStart->AddString(_T("西学超市"));
	pComboBoxStart->AddString(_T("图像防伪中心"));
	pComboBoxStart->AddString(_T("醉晚亭"));


	pComboBoxEnd->AddString(_T("华中科技大学正门"));
	pComboBoxEnd->AddString(_T("华中科技大学南二门"));
	pComboBoxEnd->AddString(_T("华中科技大学南三门"));
	pComboBoxEnd->AddString(_T("化学学院"));
	pComboBoxEnd->AddString(_T("煤燃烧实验室"));
	pComboBoxEnd->AddString(_T("紫菘学生公寓"));
	pComboBoxEnd->AddString(_T("计算机学院"));
	pComboBoxEnd->AddString(_T("电信学院"));
	pComboBoxEnd->AddString(_T("图书馆"));
	pComboBoxEnd->AddString(_T("西一学生食堂"));
	pComboBoxEnd->AddString(_T("人文学院"));
	pComboBoxEnd->AddString(_T("法学院"));
	pComboBoxEnd->AddString(_T("科技楼"));
	pComboBoxEnd->AddString(_T("友谊公寓"));
	pComboBoxEnd->AddString(_T("教工活动中心"));
	pComboBoxEnd->AddString(_T("印刷厂"));
	pComboBoxEnd->AddString(_T("计算中心"));
	pComboBoxEnd->AddString(_T("华中教育网中心"));
	pComboBoxEnd->AddString(_T("电信收费中心"));
	pComboBoxEnd->AddString(_T("档案馆"));
	pComboBoxEnd->AddString(_T("八号楼"));
	pComboBoxEnd->AddString(_T("招待所"));
	pComboBoxEnd->AddString(_T("静园"));
	pComboBoxEnd->AddString(_T("南三楼"));
	pComboBoxEnd->AddString(_T("西五楼"));
	pComboBoxEnd->AddString(_T("西十二楼"));
	pComboBoxEnd->AddString(_T("建筑学院"));
	pComboBoxEnd->AddString(_T("西五舍"));
	pComboBoxEnd->AddString(_T("西六舍"));
	pComboBoxEnd->AddString(_T("西学超市"));
	pComboBoxEnd->AddString(_T("图像防伪中心"));
	pComboBoxEnd->AddString(_T("醉晚亭"));


	this->UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMapDialog::OnBnClickedOk()
{
	CString csStart, csEnd;
	int selIndex = this->m_ComboStart.GetCurSel();
	this->m_ComboStart.GetLBText(selIndex, csStart);
	int endIndex = this->m_ComboEnd.GetCurSel();
	this->m_ComboEnd.GetLBText(endIndex, csEnd);

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("起始位置为：") + csStart);
	pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("终止位置为：") + csEnd);
	CDialogEx::OnOK();
	

	CMapModel temp;
	temp.setLocInfo();
	temp.setOrgInfo();
	temp.setDisInfo();

	int route[26][26];




	CHustMapView* pView = dynamic_cast<CHustMapView*>(pMainFrm->GetActiveView());
	int bg_num, ed_num;

	for (int i = 1; i <= 25; i++) {
		for (int j = 0; j < 2; j++) {
			if (temp.LocInfo[i].org[j] == csStart) {
				bg_num = i;
			}
			if (temp.LocInfo[i].org[j] == csEnd) {
				ed_num = i;
			}
		}
	}

	if (bg_num == ed_num) return;

	Dijkstra(26, bg_num, dist, ::prev, temp.Edge);
	int que[maxnum];
	int tot = 1;
	que[tot] = ed_num;
	tot++;
	int tmp = ::prev[ed_num];
	while (tmp != bg_num)
	{
		que[tot] = tmp;
		tot++;
		tmp = ::prev[tmp];
	}
	que[tot] = bg_num;
	int last;
	for (int i = tot; i >= 1; --i)
	{
		last =i==1?bg_num: que[i - 1];
		if (i != 1)
			pView->DrawRubberLine(temp.LocInfo[last].position, temp.LocInfo[que[i]].position);
	}
	
	
	
	
}
