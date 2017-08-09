#pragma once

//代码规范:使用大写字符串来定义这些常量

//err array size 
constexpr int ERR_SIZE = 256;
//result array size 1024*1024
constexpr int RESULT_SIZE = 1048576;

//definition for DLL_NAME 
//const static char * DLL_NAME = "Trade.dll";

//constants definitions for SendOrde::category
enum SendOrder_Category
{
	//买入
	BUY = 0,
	//卖出
	SELL,
	//融资买入
	LEVERAGE_BUY,
	//融券卖出
	RENT_COUPONS_TO_SELL,
	//买券还券
	BUY_COUPONS_TO_RETURN_COUPONS,
	//卖券还款
	SELL_COUPONS_TO_RETURN_MONEY,
	//现券还券
	USE_COUPONS_TO_RETURN_COUPONS,
};

//constants definitions for SendOrder PriceType 
enum SendOrder_PriceType
{
	//沪深限价委托
	LIMIT_CHARGE = 0,
	//(市价委托) 深圳对方最优价格
	SZ_OTHER_OPTIMAL,
	//(市价委托) 深圳本方最优价格
	SZ_SELF_OPTIMAL,
	//深圳即时成交剩余撤销
	SZ_MARKET_ORDER,
	//(市价委托)上海五档即时成交剩余撤销，深圳五档即时成交剩余撤销
	FIVE_LEVEL_MARKET_ORDER,
	//深圳全额成交或者撤销
	SZ_DEAL_ALL_OR_CANCEL,
	//(市价委托)上海五档即时成交转限价 
	SH_REAL_DEAL_TO_LIMIT,
};


//constants definitions for QueryData::Category
enum QueryData_Category
{
	//资金
	BALANCE = 0,
	//股份
	SHARES,
	//当日委托
	TODAY_ENTRUSTMENT,
	//当日成交
	TODAY_TRANSACTION,
	//可撤单
	CAN_CANCEL,
	//股东代码
	GDDM,
	//融资余额
	MARGIN_DEBT,
	//融券余额
	MARGIN_BALANCE,
	//可融证券
	FINANCING_STOCKS,
};


//constants definitions for QueryHistoryData
enum QueryHistoryData_Category
{
	//历史委托
	HISTORY_ENTRUST,
	//历史成交
	HISTORY_TRANSACTION,
	//交割单
	DELIVERY_ORDER,
};
