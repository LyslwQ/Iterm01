/*************************************************************************
    > File Name: H5Reader.h
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 11时21分48秒
 ************************************************************************/
#ifndef H5READER_H_
#define H5READER_H_

#include <string>
#include <iostream>

#include "H5Cpp.h"
#include "Var.h"
#ifndef H5_NO_NAMESPACE
using namespace H5;
using std::string;

#endif

class H5Reader
{
public:
    H5Reader(const string& fileName);
    Var getVar(const string& dataSetNamg);
    string getGroupOfVar(const string& dataSetName);
    H5T_class_t getGlobalAttType(const string& attName);
    void getGlobalAtt(const string& attName, void* buffer);

    ~H5Reader();
private:
    H5File file_;
};

#endif // endif H5READER_H_
