#include "BTDeviceDetector.h"
#include "BTHandler.h"

CBTDeviceDetector::CBTDeviceDetector(void)
{
}

CBTDeviceDetector::~CBTDeviceDetector(void)
{
}

int CBTDeviceDetector::Run()
{

	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	BTHandler mbt;

	//Utils::ShowError(TEXT("_tmain"));

	wprintf(L"BT status %d\n",mbt.InitializationStatus());

	mbt.RunDeviceInquiry(10);

	return 0;
}