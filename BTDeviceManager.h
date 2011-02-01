#pragma once

#include "ManagedThread.h"
#include "BlueTooth.h"
#include <map>
using namespace std;

#define DEF_BTDEV_MGR CBTDeviceManager::GetInstance(L"BT Device Manager")

class CBTDevice: public CManagedObject
{
public:
	CBTDevice(BTH_ADDR deviceAddr, int deviceClass, wstring deviceName, bool paired);
	BTH_ADDR GetAddr(){
		return m_addrBth;
	}
	bool IsPaired(){
		return m_bPaired;
	}
	int GetDeviceClass(){
		return m_iDeviceClass;
	}
	void SetName(wstring name){
		m_name = name;
	}
	void SetAddr(BTH_ADDR deviceAddr){
		m_addrBth=deviceAddr;
	}
	void SetPaired(bool paired){
		m_bPaired=paired;
	}
	void SetDeviceClass(int deviceClass){
		m_iDeviceClass=deviceClass;
	}


private:
	BTH_ADDR m_addrBth;
	bool m_bPaired;
	int m_iDeviceClass;
};

typedef map<BTH_ADDR, CBTDevice*> BT_DEV_MAP;


class CBTDeviceManager: public CManagedThread
{
public:
	CBTDeviceManager(void);
	CBTDeviceManager(wstring name):CManagedThread(name){};
	virtual ~CBTDeviceManager(void);
	virtual int Run();

	virtual bool RegisterDevice(CBTDevice* pDevice);
	virtual bool RegisterDevice(BTH_ADDR deviceAddr, int deviceClass, wstring deviceName, bool paired);
	virtual bool UnregisterDevice(CBTDevice* pDevice);
	virtual bool UnregisterDevice(BTH_ADDR deviceAddr);
	virtual bool UpdateDevice(BTH_ADDR deviceAddr, int deviceClass, wstring deviceName, bool paired);
	virtual bool UpdateDevice(CBTDevice* pDevice);

	virtual BT_DEV_MAP GetDeviceMap();

	static CBTDeviceManager* GetInstance(wstring name){
		if(m_instance==NULL){
			m_instance = new CBTDeviceManager(name);
		}
		return m_instance;
	}

protected:
	BT_DEV_MAP m_mapBTDevice;
	static CBTDeviceManager* m_instance;
};
