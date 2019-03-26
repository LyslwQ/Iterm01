/*************************************************************************
    > File Name: DataTypeH2N.cpp
    > Author: Ys
    > Created Time: 2019年03月01日 星期五 10时26分21秒
 ************************************************************************/

#include <iostream>

#include "DataTypeH2N.h"

using std::cout;
using std::endl;


NcType DataTypeH2N::find(const DataType& dataType)
{
	H5T_class_t type = dataType.getClass();
	size_t      size = dataType.getSize();
	if(type == H5T_INTEGER){
		if(size == 2)
			return ncShort;
		else if(size == 4)
			return ncInt;
		else 
			cout << "the DataTypeH2N is not complate..." << endl;
	}
	else if(type == H5T_FLOAT){
		if(size == 4)
			return ncFloat;
		else if(size == 8)
			return ncDouble;
		else 
			cout << "the DataTypeH2N is not complate..." << endl;
	}
	else if(type == H5T_STRING){
		return ncString;
	}
	else 
		cout << "the DataTypeH2N is not complate..." << endl;
}
