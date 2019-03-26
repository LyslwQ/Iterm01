/*************************************************************************
    > File Name: Var.h
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 16时21分48秒
 ************************************************************************/
#ifndef VAR_H_
#define VAR_H_

#include <vector>
#include <memory>
#include <string>
#include "DataMemory.h"

#include "H5Cpp.h"

using namespace H5;
using std::vector;
using std::shared_ptr;
using std::string;

//对DataSet的封装
class Var
{
public:
    Var(const DataSet& dataSet);
    //返回该变量的所有维长度
    vector<hsize_t> getDims();
    DataType getType();
    shared_ptr<DataMemory> getData();
    DataType getAttType(const string& attName);
	void getAtt(const string& attName, void* buffer);
	//返回的并不是Att里的接口，想返回Att里的接口可用getAtt()
	double getFillVal();    //只提供double接口
    //vector<hsize_t> getDims() const;
    ~Var();

private:
    DataSet dataSet_;
};

#endif //endif VAR_H_
