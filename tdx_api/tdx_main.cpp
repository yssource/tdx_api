// tdx_api.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "tdx_instance.h"
#include "util.h"

#include <iostream>
#include <vector>

#include <boost/python.hpp>
#include <boost/ref.hpp>
#include <boost/foreach.hpp>

using namespace std;

boost::python::dict format(vector<tdx_data>& datas, vector<tdx_error>& errors) {
	boost::python::dict rt;
	boost::python::list dt, er;
	for (auto& item : datas) {
		dt.append(item.string());
	}

	for (auto& item : errors) {
		er.append(item.string());
	}

	rt["data"] = dt;
	rt["errInfo"] = er;

	return rt;
}

struct TdxApi {
	TdxInstance instance;
	void init(string dll) {
		instance.Init(dll);
	}
	
	int login(char* IP, short Port, char* Version, short YybID, char* AccountNo, char* TradeAccount, char* JyPassword, char* TxPassword, char* ErrInfo) {
		return instance.Logon(IP, Port, Version, YybID, AccountNo, TradeAccount, JyPassword, TxPassword, ErrInfo);
	}

	void logoff(int ClientID) {
		instance.Logoff(ClientID);
	}

	boost::python::dict QueryHistoryData(int ClientID, int Category, char* StartDate, char* EndDate) {
		tdx_data Result;
		tdx_error ErrInfo;
		instance.QueryHistoryData(ClientID, Category, StartDate, EndDate, Result, ErrInfo);
		boost::python::dict rt;
		rt["data"] = Result.string();
		rt["errInfo"] = ErrInfo.string();
		return rt;
	}

	boost::python::dict QueryData(int ClientID, int Category) {
		tdx_data Result;
		tdx_error ErrInfo;
		instance.QueryData(ClientID, Category, Result, ErrInfo);
		boost::python::dict rt;
		rt["data"] = Result.string();
		rt["errInfo"] = ErrInfo.string();
		return rt;
	}

	boost::python::dict QueryDatas(int ClientID, boost::python::list Category) {
		std::vector<int> cats = from_python_list<int>(Category);
		int size = cats.size();
		vector<tdx_data> datas(size);
		vector<tdx_error> errors(size);

		instance.QueryDatas(ClientID, &cats[0], size, (char**)(void*)&datas[0], (char**)(void*)&errors[0]);
		return format(datas,errors);
	}

	boost::python::dict SendOrder(int ClientID, int Category, int PriceType, char* Gddm, char* Zqdm, float Price, int Quantity) {
		tdx_data Result;
		tdx_error ErrInfo;
		instance.SendOrder(ClientID, Category, PriceType, Gddm, Zqdm, Price, Quantity, Result, ErrInfo);
		boost::python::dict rt;
		rt["data"] = Result.string();
		rt["errInfo"] = ErrInfo.string();
		return rt;
	}

	boost::python::dict SendOrders(int ClientID,
		boost::python::list Category,
		boost::python::list PriceType,
		boost::python::list Gddm,
		boost::python::list Zqdm,
		boost::python::list Price, 
		boost::python::list Quantity) {

		std::vector<int> cats = from_python_list<int>(Category);
		int size = cats.size();
		vector<tdx_data> datas(size);
		vector<tdx_error> errors(size);
		vector<int> category_array = from_python_list<int>(Category);
		vector<int> price_type_array = from_python_list<int>(PriceType);
		vector<char*> gddm_array = from_python_list<char*>(Gddm);
		vector<char*> zqdm_array = from_python_list<char*>(Zqdm);
		vector<float> price_array = from_python_list<float>(Price);
		vector<int> quantity_array = from_python_list<int>(Quantity);

		instance.SendOrders(ClientID,&category_array[0],&price_type_array[0],&gddm_array[0],&zqdm_array[0],&price_array[0],&quantity_array[0],size, (char**)(void*)&datas[0], (char**)(void*)&errors[0]);
		return format(datas,errors);
	}

	boost::python::dict CancelOrder(int ClientID, char* ExchangeID, char* hth) {
		tdx_data Result;
		tdx_error ErrInfo;
		instance.CancelOrder(ClientID, ExchangeID, hth, Result, ErrInfo);
		boost::python::dict rt;
		rt["data"] = Result.string();
		rt["errInfo"] = ErrInfo.string();
		return rt;
	}

	boost::python::dict CancelOrders(int ClientID,
		boost::python::list ExchangeID,
		boost::python::list hth){
		vector<char*> exchange_array = from_python_list<char*>(ExchangeID);
		vector<char*> hth_array = from_python_list<char*>(hth);
		int size = exchange_array.size();
		vector<tdx_data> datas(size);
		vector<tdx_error> errors(size);
		instance.CancelOrders(ClientID,&exchange_array[0],&hth_array[0],size, (char**)(void*)&datas[0], (char**)(void*)&errors[0]);
		return format(datas,errors);
	}

	boost::python::dict GetQuote(int ClientID, char* Zqdm) {
		tdx_data Result;
		tdx_error ErrInfo;
		instance.GetQuote(ClientID, Zqdm, Result, ErrInfo);
		boost::python::dict rt;
		rt["data"] = Result.string();
		rt["errInfo"] = ErrInfo.string();
		return rt;
	}

	boost::python::dict GetQuotes(int ClientID, boost::python::list Zqdm) {
		vector<char*> zqdm_array = from_python_list<char*>(Zqdm);
		int size = zqdm_array.size();
		vector<tdx_data> datas(size);
		vector<tdx_error> errors(size);
		instance.GetQuotes(ClientID,&zqdm_array[0],size, (char**)(void*)&datas[0], (char**)(void*)&errors[0]);
		return format(datas, errors);
	}

	boost::python::dict Repay(int ClientID, char* Amount) {
		tdx_data Result;
		tdx_error ErrInfo;
		instance.Repay(ClientID, Amount, Result, ErrInfo);
		boost::python::dict rt;
		rt["data"] = Result.string();
		rt["errInfo"] = ErrInfo.string();
		return rt;
	}
};

BOOST_PYTHON_MODULE(tdx_api)
{
	using namespace boost::python;
	class_<TdxApi>("TdxApi").
		def("init", &TdxApi::init).
		def("login", &TdxApi::login).
		def("logoff", &TdxApi::logoff).
		def("QueryHistoryData", &TdxApi::QueryHistoryData).
		def("QueryData", &TdxApi::QueryData).
		def("QueryDatas", &TdxApi::QueryDatas).
		def("SendOrder", &TdxApi::SendOrder).
		def("SendOrders", &TdxApi::SendOrders).
		def("CancelOrder", &TdxApi::CancelOrder).
		def("CancelOrders", &TdxApi::CancelOrders).
		def("GetQuote", &TdxApi::GetQuote).
		def("GetQuotes", &TdxApi::GetQuotes).
		def("Repay", &TdxApi::Repay);
}