// bbt.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "InstanceMonitor.h"

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

//CWinApp theApp;
CInstanceMonitor theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	theApp.AppStart();
	return 0;
}
