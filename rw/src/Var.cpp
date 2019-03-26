/*************************************************************************
    > File Name: Var.cpp
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 16时21分48秒
 ************************************************************************/
#include <iostream>
#include "Var.h"

using std::cout;
using std::endl;
using std::make_shared;
static double UnsetFillValue = 0.0;

Var::Var(const DataSet& dataSet)
        :dataSet_(dataSet)
{

}

DataType Var::getAttType(const string& attName)
{
    cout << "Var::getAttType():attrivate type : " 
         << attName << "->" << dataSet_.openAttribute(attName).getDataType().getClass() 
         << endl;
    return dataSet_.openAttribute(attName).getDataType();
}

void Var::getAtt(const string& attName, void* buffer)
{
    Attribute att = dataSet_.openAttribute(attName);
    att.read(DataType(att.getDataType()), buffer);
}

double Var::getFillVal()
{
    //获取dataSet相关信息
    DSetCreatPropList dProList = dataSet_.getCreatePlist ();
    //@1.get fillValue
    float fillValue = UnsetFillValue;
    if( H5D_FILL_VALUE_UNDEFINED != dProList.isFillValueDefined()){
        dProList.getFillValue(PredType::NATIVE_DOUBLE, &fillValue);
        cout << "the fillValue = " << fillValue << endl;
    }
}

shared_ptr<DataMemory> Var::getData()
{
    shared_ptr<DataMemory> data = make_shared<DataMemory>(dataSet_);
    //dataSet_.read(data->getPointer(), PredType::NATIVE_FLOAT);
    dataSet_.read(data->getPointer(), dataSet_.getDataType());
    return data;
}

DataType Var::getType()
{
    return dataSet_.getDataType();
}

vector<hsize_t> Var::getDims()
{
    DataSpace dataspace = dataSet_.getSpace();
     //Get the number of dimensions in the dataspace.
    int count = dataspace.getSimpleExtentNdims();
    vector<hsize_t> dims(count);
    //Get the dimension size of each dimension in the dataspace
    //    hsize_t dims_out[2];
    //todo: bug???
    dataspace.getSimpleExtentDims(dims.data(), NULL);
    return dims;
}


//vector<hsize_t> Var::getDims() const
//{
//    DataSpace dataspace = dataSet_.getSpace();
//     //Get the number of dimensions in the dataspace.
//    int count = dataspace.getSimpleExtentNdims();
//    vector<hsize_t> dims(count);
//    //Get the dimension size of each dimension in the dataspace
////    hsize_t dims_out[2];
//    //todo: bug???
//    int ndims = dataspace.getSimpleExtentDims(reinterpret_cast<hsize_t*>(dims.data()), NULL);
//    cout << "count" << count << ", dimensions " <<
//        (unsigned long)(dims[0]) << " x " <<
//        (unsigned long)(dims[1]) << endl;
//    cout << "ok" << endl;
//    return dims;
//}

//相关资源的销毁
Var::~Var()
{

}
