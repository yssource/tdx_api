#include "stdafx.h"
#include "tdx_instance.h"
#include "consts.h"
#include "Shlwapi.h"

#include <windows.h>
#include <strsafe.h>

#include <string>
#include <stdio.h>

void print_error() {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("failed with error %d: %s"),
		dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

void TdxInstance::Open(string dll_name)
{
	module_ = LoadLibrary(dll_name.c_str());

	if (module_ == NULL) {
		print_error();
		printf("failed to load dll %s\n", dll_name.c_str());
		char pwd[MAX_PATH];
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, pwd);
		PathCombine((char*)path, (char*)pwd, (char*)dll_name.c_str());

		module_ = LoadLibrary(path);
		if(module_ == NULL){
			printf("failed to load dll %s\n", path);
			print_error();
			exit(-1);
		}

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

