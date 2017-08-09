#pragma once
#include"tdx_api.h"

#include <string>
#include <windows.h>
using namespace std;

class TdxInstance 
{
public:
	//constructor private 
	void Init(string dll_name);
	//destructor
	~TdxInstance();
	int login(string& ip, short& port, string& version, short& yybId, string& AccountNo, string& TradeAccount, string& jyPassword, string& txPassword) noexcept;
	void log_off(const int& client_ID);
	//definitions for functions 
	QueryDataDelegate QueryData;
	SendOrderDelegate SendOrder;
	CancelOrderDelegate CancelOrder;
	GetQuoteDelegate GetQuote;
	RepayDelegate Repay;
	//new functions
	QueryDatasDelegate QueryDatas;
	QueryHistoryDataDelegate QueryHistoryData;
	SendOrdersDelegate SendOrders;
	CancelOrdersDelegate CancelOrders;
	GetQuotesDelegate GetQuotes;

	
	//definition for function that can be protected from outer of the class 
	OpenTdxDelegate OpenTdx;
	CloseTdxDelegate CloseTdx;
	LogonDelegate Logon;
	LogoffDelegate Logoff;
private:
	HMODULE module_;
};