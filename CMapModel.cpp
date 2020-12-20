#include "pch.h"
#include "CMapModel.h"
#include <cmath>



IMPLEMENT_SERIAL(CMapModel, CObject, VERSIONABLE_SCHEMA | 2)

CMapModel::CMapModel() {}
CMapModel::~CMapModel() {}

void CMapModel::Serialize(CArchive& ar) {
	CObject::Serialize(ar);

	if (ar.IsStoring()) {
		//序列化
		ar << this->m_sMapFilePath << this->m_sLocationFilePath << this->m_sEdgeFilePath << this->m_sOrgFilePath;
	}
	else {
		//反序列化
		ar >> this->m_sMapFilePath >> this->m_sLocationFilePath >> this->m_sEdgeFilePath >> this->m_sOrgFilePath;
	}
}


CString CMapModel::GetMapFilePath() {
	return this->m_sMapFilePath;
}
CString CMapModel::GetLocationFilePath() {
	return this->m_sLocationFilePath;
}
CString CMapModel::GetEdgeFilePath() {
	return this->m_sEdgeFilePath;
}
CString CMapModel::GetOrgFilePath() {
	return this->m_sOrgFilePath;
}
void CMapModel::setMapFilePath(CString path) {
	this->m_sMapFilePath = path;
}
void CMapModel::setLocationFilePath(CString path) {
	this->m_sLocationFilePath = path;
}
void CMapModel::setEdgeFilePath(CString path) {
	this->m_sEdgeFilePath = path;
}
void CMapModel::setOrgFilePath(CString path) {
	this->m_sOrgFilePath = path;
}


void CMapModel::setLocInfo() {
	LocInfo[1].position.x = 990; LocInfo[1].position.y = 383;
	LocInfo[2].position.x = 916; LocInfo[2].position.y = 376;
	LocInfo[3].position.x = 883; LocInfo[3].position.y = 380;
	LocInfo[4].position.x = 867; LocInfo[4].position.y = 287;
	LocInfo[5].position.x = 812; LocInfo[5].position.y = 298;
	LocInfo[6].position.x = 805; LocInfo[6].position.y = 270;
	LocInfo[7].position.x = 997; LocInfo[7].position.y = 337;
	LocInfo[8].position.x = 971; LocInfo[8].position.y = 254;
	LocInfo[9].position.x = 811; LocInfo[9].position.y = 222;
	LocInfo[10].position.x = 1099; LocInfo[10].position.y = 299;
	LocInfo[11].position.x = 976; LocInfo[11].position.y = 206;
	LocInfo[12].position.x = 1014; LocInfo[12].position.y = 209;
	LocInfo[13].position.x = 969; LocInfo[13].position.y = 284;
	LocInfo[14].position.x = 931; LocInfo[14].position.y = 226;
LocInfo[15].position.x = 936; LocInfo[15].position.y = 200;
LocInfo[16].position.x = 928; LocInfo[16].position.y = 278;
LocInfo[17].position.x = 923; LocInfo[17].position.y = 329;
LocInfo[18].position.x = 877; LocInfo[18].position.y = 352;
LocInfo[19].position.x = 919; LocInfo[19].position.y = 346;
LocInfo[20].position.x = 888; LocInfo[20].position.y = 220;
LocInfo[21].position.x = 891; LocInfo[21].position.y = 195;
LocInfo[22].position.x = 858; LocInfo[22].position.y = 217;
LocInfo[23].position.x = 852; LocInfo[23].position.y = 191;
LocInfo[24].position.x = 1035; LocInfo[24].position.y = 342;
LocInfo[25].position.x = 1040; LocInfo[25].position.y = 292;



}

void CMapModel::setOrgInfo() {
	LocInfo[1].org[0] = _T("华中科技大学正门");
	LocInfo[2].org[0] = _T("华中科技大学南二门");
	LocInfo[3].org[0] = _T("华中科技大学南三门");
	LocInfo[4].org[0] = _T("化学学院");
	LocInfo[5].org[0] = _T("煤燃烧实验室");
	LocInfo[6].org[0] = _T("紫菘学生公寓");
	LocInfo[7].org[0] = _T("计算机学院");	LocInfo[7].org[1] = _T("电信学院");
	LocInfo[8].org[0] = _T("图书馆");
	LocInfo[9].org[0] = _T("西一学生食堂");
	LocInfo[10].org[0] = _T("人文学院");		LocInfo[10].org[1] = _T("法学院");
	LocInfo[11].org[0] = _T("科技楼");		LocInfo[11].org[1] = _T("友谊公寓");
	LocInfo[12].org[0] = _T("教工活动中心"); LocInfo[12].org[1] = _T("印刷厂");
	LocInfo[13].org[0] = _T("计算中心");	LocInfo[13].org[1] = _T("华中教育网中心");
	LocInfo[14].org[0] = _T("电信收费中心"); LocInfo[14].org[1] = _T("档案馆");
	LocInfo[15].org[0] = _T("八号楼");		LocInfo[15].org[1] = _T("招待所");
	LocInfo[16].org[0] = _T("静园");
	LocInfo[17].org[0] = _T("南三楼");		LocInfo[17].org[1] = _T("西五楼");
	LocInfo[18].org[0] = _T("西十二楼");
	LocInfo[19].org[0] = _T("建筑学院");
	LocInfo[20].org[0] = _T("西五舍");
	LocInfo[21].org[0] = _T("西边博士公寓");
	LocInfo[22].org[0] = _T("西六舍");
	LocInfo[23].org[0] = _T("西学超市");
	LocInfo[24].org[0] = _T("图像防伪中心");
	LocInfo[25].org[0] = _T("醉晚亭");
}
void CMapModel::setDisInfo() {
	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			Edge[i][j] = 0;
		}
	}

	Edge[1][2] = Edge[2][1] = 1;
	Edge[1][7] = Edge[7][1] = 1;
	Edge[2][3] = Edge[3][2] = 1;
	Edge[2][19] = Edge[19][2] = 1;
	Edge[3][18] = Edge[18][3] = 1;
	Edge[4][3] = Edge[3][4] = 1;
	Edge[4][16] = Edge[16][4] = 1;
	Edge[4][18] = Edge[18][4] = 1;
	Edge[4][22] = Edge[22][4] = 1;
	Edge[5][6] = Edge[6][5] = 1;
	Edge[6][9] = Edge[9][6] = 1;
	Edge[7][17] = Edge[17][7] = 1;
	Edge[7][24] = Edge[24][7] = 1;
	Edge[8][11] = Edge[11][8] = 1;
	Edge[8][13] = Edge[13][8] = 1;
	Edge[9][22] = Edge[22][9] = 1;
	Edge[10][25] = Edge[25][10] = 1;
	Edge[11][12] = Edge[12][11] = 1;
	Edge[11][15] = Edge[15][11] = 1;
	Edge[13][16] = Edge[16][13] = 1;
	Edge[13][25] = Edge[25][13] = 1;
	Edge[14][15] = Edge[15][14] = 1;
	Edge[14][16] = Edge[16][14] = 1;
	Edge[14][20] = Edge[20][14] = 1;
	Edge[15][21] = Edge[21][15] = 1;
	Edge[16][17] = Edge[17][16] = 1;
	Edge[17][19] = Edge[19][17] = 1;
	Edge[18][19] = Edge[19][18] = 1;
	Edge[20][22] = Edge[22][20] = 1;
	Edge[21][23] = Edge[23][21] = 1;
	Edge[22][23] = Edge[23][22] = 1;
	Edge[24][25] = Edge[25][24] = 1;

	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			if (Edge[i][j]) {
				Edge[i][j] = int(sqrt(pow((LocInfo[i].position.x - LocInfo[j].position.x), 2) + pow((LocInfo[i].position.y - LocInfo[j].position.y), 2)));
			}
			else Edge[i][j] = INT_MAX;
		}
	}

}

std::vector<CString> GetOrganizations(CPoint point) {
	std::vector<CString> orgs;
	CMapModel tmp_;
	tmp_.setLocInfo();
	tmp_.setOrgInfo();
	for (int i = 1; i < 26; i++) {
		if (abs(point.x - tmp_.LocInfo[i].position.x) <= 3 && abs(point.y - tmp_.LocInfo[i].position.y) <= 3) {
			for (int j = 0; j < 2; j++) {
				if (tmp_.LocInfo[i].org[j] != _T("")) {
					orgs.push_back(tmp_.LocInfo[i].org[j]);
				}
			}
		}
	}
}