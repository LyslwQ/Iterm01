/*************************************************************************
    > File Name: NcWriter.cpp
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 15时21分48秒
 ************************************************************************/
#include <iostream>

#include "NcWriter.h"

using std::cout;
using std::endl;


NcWriter::NcWriter(const string& fileName
                  , NcFile::FileMode mode
                  , NcFile::FileFormat fFormat)
                  :file_(fileName, mode, fFormat)
{
	dimsNameSet_   = {"firstDim", "secondDim", "threeDim", "fourDim"};
	itDimsNameSet_ = dimsNameSet_.begin();
    //cout << "NcWriter(): open the fille = " << fileName << endl;
};

//void NcWriter::addVar(H5Reader& h5Reader
//                     , const VarInfo& varInfo
//                     , DataTypeH2N& dataTypeH2N)
//{
//    cout << "addVar():starting process var: " << varInfo.getName() << endl;
//	//通过变量名获取变量        
//    Var h5Var = h5Reader.getVar(varInfo.getName());
//    vector<hsize_t> dims = h5Var.getDims();
//
//	//define var att
//    {
//        map<string, string> attsName =  varInfo.atts_;
//        map<string, string>::iterator itAtt = attsName.begin();
//		//define var
//        NcVar ncVar = defVar(varInfo.writeName_, dataTypeH2N.find(h5Var.getType()), dims);
//        shared_ptr<DataMemory> data = h5Var.getData();	//获取变量数据
//		
//		for(; itAtt != attsName.end(); ++itAtt){
//			NcType ncType = dataTypeH2N.find(h5Var.getAttType(itAtt->second));
//			if(ncType == ncShort){
//				shortBuffer_ = 0;
//				h5Var.getAtt(itAtt->second, &shortBuffer_);
//				ncVar.putAtt(itAtt->second
//							 , ncType
//					         , shortBuffer_);
//			}
//			else if(ncType == ncString){
//				memset(strBuffer_, '\0', BufferLen);
//				h5Var.getAtt(itAtt->second, strBuffer_);
//				ncVar.putAtt(itAtt->second
//					         , strBuffer_);
//			}
//
//        }
//		cout << "finish process var = " << varInfo.name_ << endl<< endl;
//    }
//}

void NcWriter::addGlobalAtt(H5Reader& h5Reader
							, const map<string, string>& atts
							, const map<H5T_class_t, NcType>& dataTypeH2N)
{
    map<H5T_class_t, NcType>::const_iterator itDT = dataTypeH2N.end();
    map<string, string>::const_iterator itAtt = atts.begin();
    for(; itAtt != atts.end(); ++itAtt){
        itDT = dataTypeH2N.find(h5Reader.getGlobalAttType(itAtt->second));
        //debug info
        if(itDT == dataTypeH2N.end())
            cout << "dataTypeH2N is not complete" << endl;
    
        if(itDT->second == ncString){
			//cout << itAtt->second << ":type = " << "string" << endl;
            memset(strBuffer_, '\0', BufferLen);
            h5Reader.getGlobalAtt(itAtt->second, strBuffer_);
            putAtt(itAtt->second, strBuffer_);
        }
        else if(itDT->second == ncFloat){
			floatBuffer_ = 0.0;
            h5Reader.getGlobalAtt(itAtt->second, &floatBuffer_);
            putAtt(itAtt->second
                  , itDT->second
                  , floatBuffer_);
			//cout << itAtt->second << ":type = " << "float" << endl;
			//cout << ":value = " << floatBuffer_ << endl;
        }
        else if(itDT->second == ncInt){
            intBuffer_ = 0;
			//cout << itAtt->second << ":type = " << "int" << endl;
            h5Reader.getGlobalAtt(itAtt->second,&intBuffer_);
            putAtt(itAtt->second
                   , itDT->second
                   , intBuffer_);
		}
		else 
			cout << itAtt->second << "can't mattch the type " << endl;
    }
}



void NcWriter::defDim(const string& dimName, hsize_t dimLen)
{
    NcDim dimObj = file_.addDim(dimName, dimLen);
    dimsLenToObj_.insert(pair<hsize_t, NcDim>(dimLen, dimObj)); 
}

NcVar NcWriter::defVar(const string& varName
                      , const NcType& varType
                      , const vector<hsize_t>& dimsLen)
{
	//def var's dims
    vector<hsize_t>::const_iterator it = dimsLen.begin();
    for(; it != dimsLen.end(); ++it){
        if(dimsLen2Name_.find(*it) == dimsLen2Name_.end()){ //not found and insert
            defDim(*itDimsNameSet_, *it);
            dimsLen2Name_.insert(pair<hsize_t, string>(*it, *itDimsNameSet_++));
        }
    }
    
	vector<NcDim> dims;
    vector<hsize_t>::const_iterator itVec = dimsLen.begin();
    map<hsize_t, NcDim>::iterator itMap = dimsLenToObj_.end();
    for(; itVec != dimsLen.end(); ++itVec){
        itMap = dimsLenToObj_.find(*itVec);
        if(itMap == dimsLenToObj_.end()) {//todo: 找不到,应该抛出异常让用户知道
            return NcVar();     
        }
        dims.push_back(itMap->second);
    }
    return file_.addVar(varName, varType, dims);
}

void NcWriter::putVar(Var& var)
{
   // vector<hsize_t> dims = var.getDims();
   // vector<hsize_t>::iterator it = dims.begin();
   // for(; it != dims.end(); ++it){
   //     dimsNameToLen_.insert(pair<string, hsize_t>(*it, dimsNameToLen_.size()));
   // }
}

void NcWriter::putAtt(const string& name, const string& value)
{
    file_.putAtt(name, value);
}


void NcWriter::putAtt(const string& name
                      , const NcType& type
                      , const double dataValues)
{
    file_.putAtt(name, type, dataValues);
}

void NcWriter::putAtt(const string& name
                      , const NcType& type
                      , const int dataValues)
{
    file_.putAtt(name, type, dataValues);
}

//相关资源的释放动作
NcWriter::~NcWriter(){}
