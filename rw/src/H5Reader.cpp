/*************************************************************************
    > File Name: H5Reader.cpp
    > Author: Ys
    > Created Time: 2019年02月20日 星期三 13时21分48秒
 ************************************************************************/
#include <vector>
#include "H5Reader.h"

using std::cout;
using std::endl;
using std::vector;
//todo: 优化为类成员
static vector<string> groupNames; 
static vector<string> dataSetNames;

extern "C"
herr_t getFileInfo(hid_t loc_id
                   , const char *name
                   , const H5L_info_t *linfo
                   , void* groupNames);

extern "C"
herr_t getGroupInfo(hid_t loc_id
                    , const char *name
                    , const H5L_info_t *linfo
                    , void* dataSetpNames); 



H5Reader::H5Reader(const string& fileName)
                  :file_(fileName.c_str(), H5F_ACC_RDONLY){

    
//    cout << "fileName = " <<  file_.getFileName() << endl;
}

H5T_class_t H5Reader::getGlobalAttType(const string& attName)
{
    Group rootGroup = file_.openGroup("/");
    if( !rootGroup.attrExists(attName)){
        //todo:异常处理，让用户知道    
    }
    return rootGroup.openAttribute(attName).getDataType().getClass();
}

void H5Reader::getGlobalAtt(const string& attName, void* buffer)
{
    Attribute att = file_.openAttribute(attName);
    att.read(DataType(att.getDataType()), buffer);
	cout << "get GlobalAtt = " << attName << endl;
}

Var H5Reader::getVar(const string& dataSetName)
{
    string groupName = getGroupOfVar(dataSetName);
    Group group = file_.openGroup(groupName);
    return group.openDataSet(dataSetName.c_str());  
}

//todo: 循环遍历获取根目录及其子目录下的目标dataset
//，找到第一个匹配项即返回Group对象
string H5Reader::getGroupOfVar(const string& dataSetName)
{
    try{
        Exception::dontPrint();
        groupNames.push_back("/");
        herr_t idx = H5Literate(file_.getId()
                                , H5_INDEX_NAME
                                , H5_ITER_INC
                                , NULL
                                , getFileInfo
                                , &groupNames);
        
        //由于缺少dataset的group信息，所以只能循环groups
        vector<string>::iterator itGroup = groupNames.begin();
        for(; itGroup != groupNames.end(); ++itGroup){
            cout << endl;
//            cout << "Group = " << *itGroup << endl;
            Group group = file_.openGroup(*itGroup);
            dataSetNames.clear();
            herr_t idx = H5Literate(group.getId()
                                    , H5_INDEX_NAME
                                    , H5_ITER_INC
                                    , NULL
                                    , getGroupInfo
                                    , &dataSetNames);
        
            vector<string>::iterator itDataSet = dataSetNames.begin();
            for(; itDataSet != dataSetNames.end(); ++itDataSet){
            //    cout << "DataSet = " << *itDataSet << endl;
                if(*itDataSet == dataSetName){
                    //找到目标dataSet，构造其所在group对象返回
                    //return h5File.openGroup(*itDataSet);
                    return *itGroup;
                }
            }
        }
    }
    // catch failure caused by the H5File operations
    catch( FileIException error )
    {
       error.printError();
       return nullptr;
    }
    
    // catch failure caused by the DataSet operations
    catch( DataSetIException error )
    {
       error.printError();
       return nullptr;
    }
    
    // catch failure caused by the DataSpace operations
    catch( DataSpaceIException error )
    {
       error.printError();
       return nullptr;
    }
    
    // catch failure caused by the DataSpace operations
    catch( DataTypeIException error )
    {
       error.printError();
       return nullptr;
    }
}
//todo: 相关资源的销毁动作
H5Reader::~H5Reader()
{

}

//todo：循环获取根目录下的group
herr_t
getFileInfo(hid_t loc_id
           , const char *name
           , const H5L_info_t *linfo
           , void* groupNames)
{
   hid_t group;
   //Open the group using its name.
   group = H5Gopen2(loc_id, name, H5P_DEFAULT);
   vector<string>* pVec = reinterpret_cast<vector<string>* >(groupNames);
   //Display group name.
   //vector<string>* pVec = reinterpret_cast<vector<string>>(groupNames);
   pVec->push_back(name);
   H5Gclose(group);
   return 0;
}

//todo：循环获取group下的dataset
herr_t
getGroupInfo(hid_t loc_id
           , const char *name
           , const H5L_info_t *linfo
           , void* dataSetNames)
{
   hid_t group;
   //Open the group using its name.
   //group = H5Gopen2(loc_id, name, H5P_DEFAULT);
   vector<string>* pVec = reinterpret_cast<vector<string>* >(dataSetNames);
   //Display group name.
   //vector<string>* pVec = reinterpret_cast<vector<string>>(groupNames);
   pVec->push_back(name);
   //H5Gclose(group);
   return 0;
}
