/*************************************************************************
    > File Name: DataMemory.cpp
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 11时22分48秒
 ************************************************************************/
#include <malloc.h>
#include "DataMemory.h"
//todo: 分配空间后初始化
DataMemory::DataMemory(const H5::DataSet& dataSet)
    :pointer_(nullptr)
{
    size_     = static_cast<long>(dataSet.getStorageSize());
    pointer_  = malloc(size_);
}

DataMemory::DataMemory(size_t size)
	:size_(size)
{
    pointer_ = malloc(size_);
}

DataMemory::~DataMemory()
{
    if(pointer_ != nullptr){
        free(pointer_);
        pointer_ = nullptr;
    }
}
