/*************************************************************************
    > File Name: Info.h
    > Author: Ys
    > Created Time: 2019年02月25日 星期一 10时21分48秒
 ************************************************************************/
#ifndef INFO_H_
#define INFO_H_

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <exception>

using std::string;
using std::map;
using std::shared_ptr;
using std::make_shared;
using std::pair;
using std::vector;
using std::exception;

//todo：处理程序还没有对原名字错误产生的异常进行处理
//      ，所以会导致进程直接退出

#define CATCH_INPUTINFO_EXCEPTION  \
    catch(InputInfoException& e){\
             cout << e.what() << endl;\
             return false;\
     }\


class InputInfoException: public exception
{
	public:
		const char* what(){
			return "InputInfoException():input info error !!!!";
		}
};

class VarInfo
{
public:
	VarInfo(const string& idName, const string& varName)
		:varName_(varName)
		 , idName_(idName){}

	const string& getName() const { return varName_;}
	const string& getIdName() const {return idName_;}

	void   setFillVal(const double fillVal){ fillVal_ = fillVal;}
	void   setOffSet(const double offSet){ offSet_ = offSet;}
	void   setScale(const double scale){ scale_ = scale;}

	double getFillVal() const { return fillVal_;}
	double getOffSet() const { return offSet_;}
	double getScale() const { return scale_;}

private:
	double fillVal_;
	double offSet_;
	double scale_;
	string varName_;	//用于读取
	string idName_;		//用于处理程序获取到该变量
};


class InputInfo
{
public:
    const string& getFileName() const { return inFileName_;}
	void setFileName(const string& fileName){ inFileName_ = fileName;}

	void addVar(const VarInfo& var){
		vars_.push_back(var);
	}

	//因为变量个数不会太多，所以不必使用map来搜索。
	const VarInfo& getVar(const string& varIdName) const{
		vector<VarInfo>::const_iterator itVar = vars_.begin();
        for(; itVar != vars_.end(); ++itVar){
			if(itVar->getIdName() == varIdName){
				return *itVar;
			}
		}
		//找不到相应变量
		throw InputInfoException();		
	}

	const string& getDate() const { return date_;}
    
	static InputInfo getTestInfo();

private:
	string date_;
	vector<VarInfo> vars_;
	string inFileName_;          //原文件全名
};

class OutputInfo
{
public:
	map<string, string>& getFileInfo(){ return file_;}

	void addFileInfo(const string& name, const string& path){ 
		file_.insert(pair<string, string>(name, path));
	}
private:
	//fileName -> filePath
	map<string, string>  file_;
};

#endif // endif INFO_H_
