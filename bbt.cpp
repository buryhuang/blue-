// bbt.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "InstanceMonitor.h"

#ifdef UNITTEST
#include "gtest/gtest.h"
#endif

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

//CWinApp theApp;
CInstanceMonitor theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
#ifdef UNITTEST
  std::cout << "Running main() from gtest_main.cc\n";

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();	
#else
	theApp.AppStart();
#endif
	return 0;
}
