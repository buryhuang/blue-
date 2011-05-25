/** \addtogroup application
 *  @{
 */

#include "config.h"
#include "BTDeviceDetector.h"
#include "BTDeviceManager.h"


CBTDeviceDetector* CBTDeviceDetector::m_instance=NULL;

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

	//Utils::ShowError(TEXT("_tmain"));
	while(true){

		wprintf(L"BlueTooth initialization status: %d\n",DEF_BTDEVICE->InitializationStatus());
		DEF_BTDEVICE->RegisterHandler(DEF_BTDEV_HANDLER);
		DEF_BTDEVICE->RunDeviceInquiry(BT_DETECT_DURATION_SECONDS);

		Sleep(BT_DETECT_INTERVAL_MS);
	}

	return 0;
}

/** @}*/
