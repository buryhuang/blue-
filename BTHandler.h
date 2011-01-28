#pragma once

#include "BlueTooth.h"

class BTHandler :
	public CBlueTooth
{
public:
	BTHandler(void);
	virtual ~BTHandler(void);

	void OnDeviceDiscovered(BTH_ADDR deviceAddr, int deviceClass, wstring deviceName, BOOL paired);
};
