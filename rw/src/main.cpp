/*************************************************************************
    > File Name: main.cpp
    > Author: Ys
    > Created Time: 2019年02月26日 星期二 16时54分57秒
 ************************************************************************/
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include <netcdf>

#include "H5Reader.h"
#include "NcWriter.h"
#include "Info.h"
#include "Handler.h"
#include "DataTypeH2N.h"

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::map;
using std::pair;

using namespace netCDF;
using namespace netCDF::exceptions;

#define BufferLen 200

int main()
{
	//todo: 改为单例模式
	DataTypeH2N dataTypeH2N;	
	InputInfo inInfo = InputInfo::getTestInfo();
	OutputInfo outInfo;
	Handler handler;
	//根据不同type，调用相应的handle
	Function_t func = handler.getHandle("OPER_SCA_L2B");
	//Function_t func = handler.getHandle("OPER_CZI_L2C");
	//Function_t func = handler.getHandle("ERTP_CZI_L2D");
	if( !func(inInfo, outInfo))
		cout << "func(): return error!!!!" << endl;
	else{
		map<string, string>::iterator it = outInfo.getFileInfo().begin();
		for(; it != outInfo.getFileInfo().end(); ++it){
			cout << "the result file path = " << it->second << endl;
			cout << "the result file name = " << it->first << endl;
		}
	}
	return 0;
}

