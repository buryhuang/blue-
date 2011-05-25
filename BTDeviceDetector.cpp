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

	// 初始化 MFC 并在失败时显示错误

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
