/** \addtogroup bluetooth
 *  @{
 */

#pragma once

#include "BlueTooth.h"
#include "Utils.h"
#include <vector>
using namespace std;

class CSocketHandler
{
public:
	virtual void OnAccept(SOCKET)=0;
	virtual void OnReceive(SOCKET,BYTEBUFFER)=0;
	virtual void OnConnect()=0;
	virtual void OnClose()=0;
};

class CBlueToothSocket
{
public:
	enum CONNECT_STATUS_T {
		NOT_CREATED,
		CREATED,
		LISTENING,
		ACCEPTED,
		CONNECTING,
		CONNECTION_AUTH_FAILED,
		CONNECTION_TIMEOUT,
		CONNECTION_FAILED,
		CONNECTED,
		RECV_FAILED,
		CLOSED
	};


	CBlueToothSocket();
	CBlueToothSocket(SOCKET);
	virtual ~CBlueToothSocket();
	BOOL   Create(BOOL authenticate, BOOL encrypt);
	BOOL   Connect(BTH_ADDR address, int channel, int retryUnreachable);
	BOOL   Bind();
	BOOL   Listen();
	SOCKET Accept();
	int    RecveiveAvailable();
	void   Close();
	int    RecveiveChar();
	size_t Recveive();
	size_t Send(BYTEBUFFER buff);
	bool RegisterHandler(CSocketHandler*);
	wstring GetStatusString();
	CONNECT_STATUS_T GetStatus() {return m_iStatus;}
	void SetPasskey(wstring passkey);

protected:
	SOCKET m_socket;
	BOOL m_bConnected;
	BOOL m_bStarted;
	BOOL m_bCreated;
	vector<SOCKET> m_listSocket;
	CSocketHandler* m_pHandler;
	CONNECT_STATUS_T m_iStatus;
	wstring m_passkey;
	BOOL m_bAuth;
	HBLUETOOTH_AUTHENTICATION_REGISTRATION m_hAuth;
};


/** @}*/
