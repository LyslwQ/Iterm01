/*************************************************************************
    > File Name: DataTypeH2N.h
    > Author: Ys
    > Created Time: 2019年03月01日 星期五 10时23分35秒
 ************************************************************************/
#ifndef DATA_TYPE_H2N_
#define DATA_TYPE_H2N_

#include <netcdf>
#include "H5Cpp.h"

using namespace H5;
using namespace netCDF;
using namespace netCDF::exceptions;


class DataTypeH2N
{
public:
	DataTypeH2N(){}
	~DataTypeH2N(){}
	//tod：当找不到相应类型时，暂时只是打印信息处理，
	//应该通过异常等方法让用户知道.
	NcType find(const DataType& dataType);
};

#endif //DATA_TYPE_H2N_
