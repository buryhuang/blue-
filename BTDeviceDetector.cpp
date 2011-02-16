/** \addtogroup application
 *  @{
 */

#include "config.h"
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
	CBTHandler mbt;

	//Utils::ShowError(TEXT("_tmain"));
	while(true){

		wprintf(L"BlueTooth initialization status: %d\n",mbt.InitializationStatus());

		mbt.RunDeviceInquiry(BT_DETECT_DURATION_SECONDS);

		Sleep(BT_DETECT_INTERVAL_MS);
	}

	return 0;
}

/** @}*/
