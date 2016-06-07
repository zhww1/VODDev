// NetClient.h: interface for the CNetClient class.
//
//////////////////////////////////////////////////////////////////////
#include "afxsock.h"
#if !defined(AFX_NETCLIENT_H__EE147879_B044_4D72_B3EB_503590C3B2BD__INCLUDED_)
#define AFX_NETCLIENT_H__EE147879_B044_4D72_B3EB_503590C3B2BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��ͷ
typedef struct _tagVODHeader{
    DWORD dwVer;
    DWORD dwCmd;
    DWORD dwLen;
}VODHEADER,* LPVODHEADER;

//��¼��ID�ͽṹ
#define VODNETCMD_LOGIN 0x00000001

typedef struct _tagVODLogin{
    CHAR szUserName[128];
    CHAR szPassword[128];
}VODLOGIN,* LPVODLOGIN;

//��¼���ص�ID�ͽṹ
#define VODNETCMD_LOGIN_RET 0x80000001
typedef struct _tagVODLoginRet{
    DWORD dwSuccess;
}VODLOGINRET,* LPVODLOGINRET;

//����ý�����͵���Ϣ��ID
#define  VODNETCMD_TYPES 0x00000002
//����ý�����͵���Ϣ��ID
#define  VODNETCMD_TYPES_RET 0x80000002

//����ĳһ�����µ�����ӰƬ����Ϣ��ID
#define VODNETCMD_GETVIDES 0x00000003
typedef struct _tagGetVideos
{
	DWORD typdID;//ý�����͵�ID
}GETVIDEOS,*LPGETVIDEOS; 
//���ظ�����������ӰƬ����Ϣ
#define VODNETCMD_GETVIDEOS_RET 0x80000003


//�����������ӰƬ��ID
#define VODNETCMD_MEDIADATA 0x00000006
typedef struct _tagMediaData{
    DWORD videoID;//����ӰƬID
}MEDIADATA,* LPMEDIADATA;
//���ظ�ӰƬ����Ϣ��Ϊ���ظ�ӰƬ��Ӧ���ļ���׼��
#define VODNETCMD_MEDIADATA_RET 0x80000006
typedef struct _tagMediaDataRet{
    CHAR szFileName[128];//
    DWORD dwFileLen;//�ļ�����
}MEDIADATARET,* LPMEDIADATARET;
class CNetClient  
{
public:
	CNetClient();
	virtual ~CNetClient();
	//1 �����̣߳��̺߳���ClientThread
	BOOL Initialize();
	//ҵ���߼���ClientThread������ʵ��
	static DWORD WINAPI ClientThread(LPVOID pParam);
	//2 ����ͻ��˵�¼
	BOOL OnLogin();
	//3 �������е���Ƶ������Ϣ
	BOOL OnAllVideoTypes();
	//4 ����ָ������ID��������Ƶ��Ϣ
	BOOL OnVideosByTypeID();
	//5 ����ͻ����������Ƶ�ļ�
    BOOL OnMediaData();
    //ԭʼ�������շ�����
	BOOL RecvData(LPVOID  pData,UINT nLen);
    BOOL SendData(DWORD dwCmdID,LPVOID pData,UINT nLen );
    BOOL SendRaw(LPVOID  pData,UINT nLen);	
public:
	SOCKET m_hClientSocket;
};

#endif // !defined(AFX_NETCLIENT_H__EE147879_B044_4D72_B3EB_503590C3B2BD__INCLUDED_)
