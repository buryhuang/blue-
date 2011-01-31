#include "StdAfx.h"
#include "InstanceMonitor.h"

#include "BTDeviceDetector.h"
#include "BTDeviceManager.h"

#include "PersistentStorage.h"
#include "Utils.h"

#include <iostream>
using namespace std;


CInstanceMonitor::CInstanceMonitor(void)
{
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
	}
}

CInstanceMonitor::~CInstanceMonitor(void)
{
	GraceShutdown();
	vector<CManagedThread*>::iterator vi=m_listThreads.begin();
	for(;vi!=m_listThreads.end();vi++){
		if((*vi)!=NULL){
			delete (*vi);
		}
	}
}

void CInstanceMonitor::AppStart()
{
	Utils::LogEvent(L"Starting App");
#if 0
	//Register services
	CBTDeviceDetector* pBTDeviceDetector=new CBTDeviceDetector(L"BT Device Detector");
	this->m_listThreads.push_back(pBTDeviceDetector);

	CBTDeviceManager* pBTDeviceManager=new CBTDeviceManager(L"BT Device Manager");
	this->m_listThreads.push_back(pBTDeviceManager);


	//Start services
	vector<CManagedThread*>::iterator vi=m_listThreads.begin();
	for(;vi!=m_listThreads.end();vi++){
		(*vi)->Start();
		wcout<<_L(IDS_DEBUG_STARTED_SERVICE)<<(*vi)->GetName()<<endl;
	}


	//Main loop: Monitor workers and keep alive.
	while(true){
		vector<CManagedThread*>::iterator vi=m_listThreads.begin();
		for(;vi!=m_listThreads.end();vi++){
			STDOUT<<_L(IDS_DEBUG_CHECKING_SERVICE)<<(*vi)->GetName()<<endl;
			if(!(*vi)->IsAlive()){
				STDOUT<<_T("Retarting ")<<(*vi)->GetName()<<endl;
				(*vi)->Restart();
			}
		}

		Sleep(2000);
	}
#endif
}

void CInstanceMonitor::GraceShutdown()
{
	vector<CManagedThread*>::iterator vi=m_listThreads.begin();
	for(;vi!=m_listThreads.end();vi++){
		if((*vi)!=NULL){
			(*vi)->GraceShutdown();
		}
		wcout<<_L(IDS_DEBUG_STARTED_SERVICE)<<(*vi)->GetName()<<endl;
	}

}