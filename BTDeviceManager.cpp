#include "StdAfx.h"
#include "BTDeviceManager.h"

#include "BTHandler.h"

CBTDeviceManager::CBTDeviceManager(void)
{
}

CBTDeviceManager::~CBTDeviceManager(void)
{
}

int CBTDeviceManager::Run()
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	BTHandler mbt;

	//Utils::ShowError(TEXT("_tmain"));

	wprintf(L"BT status %d\n",mbt.InitializationStatus());

	mbt.RunDeviceInquiry(10);

	return 0;
}