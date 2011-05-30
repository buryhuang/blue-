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

		//Be sure to use new Bluetooth class to correctly init WSA
		CBlueTooth cbt;
		wprintf(L"BlueTooth initialization status: %d\n",cbt.InitializationStatus());
		cbt.RegisterHandler(DEF_BTDEV_HANDLER);
		cbt.RunDeviceInquiry(BT_DETECT_DURATION_SECONDS);

		Sleep(BT_DETECT_INTERVAL_MS);
	}

	return 0;
}

/** @}*/
