#pragma once
#include <afx.h>
#include<vector>

struct info {
    CPoint position;
    CString org[2];
};





class CMapModel :
    public CObject
{
private:
    CString m_sMapFilePath = _T("");
    CString m_sLocationFilePath = _T("");
    CString m_sEdgeFilePath = _T("");
    CString m_sOrgFilePath = _T("");
public:
    DECLARE_SERIAL(CMapModel)
    CMapModel();
    virtual ~CMapModel();
public:
    virtual void Serialize(CArchive& ar);
public:
    CString GetMapFilePath();
    CString GetLocationFilePath();
    CString GetEdgeFilePath();
    CString GetOrgFilePath();
    void setMapFilePath(CString path);
    void setLocationFilePath(CString path);
    void setEdgeFilePath(CString path);
    void setOrgFilePath(CString path);

    std::vector<CString> GetOrganizations(CPoint point);

public:
    int Edge[26][26];
    info LocInfo[26];
    void setLocInfo();
    void setOrgInfo();
    void setDisInfo();
};

