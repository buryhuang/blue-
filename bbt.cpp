// bbt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BlueTooth.h"
#include <iostream>

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

class MyBT: public CBlueTooth
{
	void OnDeviceDiscovered(BTH_ADDR deviceAddr, int deviceClass, wstring deviceName, BOOL paired)
	{
		wcout<<deviceAddr<<" - "<<deviceName<<endl;
	}
};


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		MyBT mbt;

		//Utils::ShowError(TEXT("_tmain"));

		wprintf(L"BT status %d\n",mbt.InitializationStatus());
		while(true){
		mbt.RunDeviceInquiry(10);
		}
	}

	return nRetCode;
}
