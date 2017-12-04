#include "stdafx.h"
#include "tdx_instance.h"
#include "consts.h"
#include <iostream>
#include <string>

using namespace std;

std::string GetLastErrorStdStr()
{
	DWORD error = GetLastError();
	if (error)
	{
		LPVOID lpMsgBuf;
		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			std::string result(lpMsgStr, lpMsgStr + bufLen);

			LocalFree(lpMsgBuf);

			return result;
		}
	}
	return std::string();
}

void TdxInstance::Open(string dll_name)
{
	module_ = LoadLibrary(dll_name.c_str());
	if (module_ == NULL) {
		cout <<"dll加载失败: '"<<dll_name<<"',"<<GetLastErrorStdStr()<< endl;
		exit(-1);
	}
	//获取api函数
	OpenTdx = (OpenTdxDelegate)GetProcAddress(module_, "OpenTdx");
	CloseTdx = (CloseTdxDelegate)GetProcAddress(module_, "CloseTdx");
	Logon = (LogonDelegate)GetProcAddress(module_, "Logon");
	Logoff = (LogoffDelegate)GetProcAddress(module_, "Logoff");
	QueryData = (QueryDataDelegate)GetProcAddress(module_, "QueryData");
	SendOrder = (SendOrderDelegate)GetProcAddress(module_, "SendOrder");
	CancelOrder = (CancelOrderDelegate)GetProcAddress(module_, "CancelOrder");
	GetQuote = (GetQuoteDelegate)GetProcAddress(module_, "GetQuote");
	Repay = (RepayDelegate)GetProcAddress(module_, "Repay");

	//普通批量版新增函数
	QueryDatas = (QueryDatasDelegate)GetProcAddress(module_, "QueryDatas");
	QueryHistoryData = (QueryHistoryDataDelegate)GetProcAddress(module_, "QueryHistoryData");
	SendOrders = (SendOrdersDelegate)GetProcAddress(module_, "SendOrders");
	CancelOrders = (CancelOrdersDelegate)GetProcAddress(module_, "CancelOrders");
	GetQuotes = (GetQuotesDelegate)GetProcAddress(module_, "GetQuotes");

	//打开通达信实例 
	OpenTdx();
}

void TdxInstance::Close() {
	CloseTdx();
	FreeLibrary(module_);
}

