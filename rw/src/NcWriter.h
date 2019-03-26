/*************************************************************************
    > File Name: NcWriter.h
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 15时21分48秒
 ************************************************************************/
#ifndef NCWRITER_H_
#define NCWRITER_H_

#include <string>
#include <map>
#include <netcdf>

#include "H5Reader.h"
#include "Var.h"
#include "Info.h"
#include "DataTypeH2N.h"

using std::string;
using std::map;
using std::pair;
using namespace netCDF;
using namespace netCDF::exceptions;

#define BufferLen 200

class NcWriter
{
public:
    NcWriter(const string& fileName
             , NcFile::FileMode mode = NcFile::replace
             , NcFile::FileFormat fFormat =  NcFile::FileFormat::nc4);
    
    ~NcWriter();
    
    void addGlobalAtt(H5Reader& h5Reader
                      , const map<string, string>& atts
                      , const map<H5T_class_t,NcType>& dataTypeH2N);

	//添加一个变量，变量由h5Reader读取，直接写入
 //   void addVar(H5Reader& h5Reader
 //               ,const VarInfo&
 //               ,DataTypeH2N& dataTypeH2N);
   
	void addVar(NcVar& ncVar);
    
	NcVar defVar(const string& varName
                , const NcType& varType
                , const vector<hsize_t>& dimsLen);
private:
    void defDim(const string& dimName, hsize_t dimLen);
    

    void putVar(Var& var);
    //put att which type is string.
    void putAtt(const string& name, const string& value);
    
    void putAtt(const string& name
                , const NcType& type
                , const double dataValues);
    
    void putAtt(const string& name
                , const NcType& type
                , const int dataValues);
   
private:
    NcFile file_;
    //dimLen->dimObj
    map<hsize_t, NcDim> dimsLenToObj_;
    //todo: 解决了nc必须先定义dim再定义变量的问题(可优化)
    vector<Var> vars_;

    char   strBuffer_[BufferLen];	//个别属性名很长
    float  floatBuffer_;
    int    intBuffer_;
    short  shortBuffer_;	
	map<hsize_t, string> dimsLen2Name_;
	vector<string> dimsNameSet_;
	vector<string>::iterator itDimsNameSet_;
};

#endif //endif NCWRITER_H_
