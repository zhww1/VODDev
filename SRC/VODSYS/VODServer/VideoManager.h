// VideoManager.h: interface for the CVideoManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOMANAGER_H__96A660D0_C1B6_4A35_8316_A862BFE364A2__INCLUDED_)
#define AFX_VIDEOMANAGER_H__96A660D0_C1B6_4A35_8316_A862BFE364A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include ".\ado\Ado.h"
struct CVideo
{
	int nVideoID;
	CString strVideoName;
    CString strVideoDesp;
	CString strVideoPath;
	int nTypeid;
};
class CVideoManager  
{
public:
	CVideoManager(CAdoConnection *pConn);
	virtual ~CVideoManager();
	//插入
    void InsertVideo(CVideo v);
	//更新
	void UpdateVideo(CVideo nv,long videoID);
	//删除
	void DeleteVideo(long videoID);
	//根据类型ID，返回该类型下所有的视频信息
	void GetVideosByTypeID(long typeID,CList<CVideo,CVideo> *pLstVideo);
	//根据视频信息ID，返回视频文件的路径
	CString GetVideoPathByID(long videoID);
	CAdoConnection *m_pConn;
	CAdoRecordSet m_RecordSet;
};

#endif // !defined(AFX_VIDEOMANAGER_H__96A660D0_C1B6_4A35_8316_A862BFE364A2__INCLUDED_)
