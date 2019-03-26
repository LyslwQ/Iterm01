/*************************************************************************
    > File Name: DataMemory.h
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 11时21分48秒
 ************************************************************************/
#ifndef DATA_MEMORY_H_
#define DATA_MEMORY_H_

#include <iostream>
#include <memory>

#include "H5Cpp.h"

using std::shared_ptr;
using std::cout;
using std::endl;

//作为数据存储介质，RALL封装，自动管理内存空间。
class DataMemory
{
public:
    DataMemory(const H5::DataSet& dataSet);
    DataMemory(size_t size);
    void* getPointer(){return pointer_;}
    long getSize(){return size_;}
	template<typename T>
	static void toShortInt(shared_ptr<DataMemory>& data
						 , double &scale
						 , double &offSet
						 , double fillVal);
    ~DataMemory();
private:
    void    *pointer_;
    long    size_;
};

template<typename T>
void DataMemory::toShortInt(shared_ptr<DataMemory>& data
						  , double &scale
						  , double &offSet
						  , double fillVal)
{
	//计算元素个数
	long counter = data->getSize()/sizeof(T);
	T *src = reinterpret_cast<T*>(data->getPointer());
	
	
	DataMemory *des = new DataMemory(counter * sizeof(short));
	T max = *src, min = *src;
	//找出极值
	for(long index = 0; index != counter; ++index){
		if(*(src+index) - fillVal < 0.000001)	//跳过无效值
			continue;
		max = *(src+index) > max ? *(src+index) : max;
		min = *(src+index) < min ? *(src+index) : min;
	}
	//通过极值确定偏移量和放大倍数。
	if(max > 327 && min >= 0){
		scale  = 1.0/100.0;
		offSet = 327; 
	}
	else {
		scale  = 1.0/100.0;
		offSet = 0;
	}

	//scale = 1;
	//offSet = 0;
	short *pDes = reinterpret_cast<short*>(des->getPointer());
	for(long index = 0; index != counter; ++index){

		if((*(src+index) - fillVal) < 0.000001 
				&&  (*(src+index) - fillVal) > -0.000001 ){	//跳过无效值
			*(pDes+index)=static_cast<short>(*(src+index));
			continue;
		}
		*(pDes+index)=static_cast<short>((*(src+index) -offSet)/scale);
	}
	
	data.reset(des);
}

#endif  //endif DATA_MEMORY_H_
