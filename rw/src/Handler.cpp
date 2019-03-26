#include <iostream>
#include <cmath>
#include <unistd.h>
#include "Handler.h"
#include "H5Reader.h"
#include "NcWriter.h"
#include "Var.h"

#define BufferLen 200


using std::cout;
using std::endl;

struct Atts{
	double fillVal_;
	double scale_;
	double offSet_;
};

void putAtts(NcVar& ncVar, double fillVal, double scale, double offSet);

static bool OPER_SCA_L2B(const InputInfo& inInfo
				, OutputInfo& outInfo);

static bool OPER_OCT_L2C(const InputInfo& inInfo
					   , OutputInfo& outInfo);


static bool OPER_OCT_L2B(const InputInfo& inInfo
					   , OutputInfo& outInfo);

static bool OPER_CZI_L2B(const InputInfo& inInfo
					   , OutputInfo& outInfo);

static bool OPER_CZI_L2C(const InputInfo& inInfo
					   , OutputInfo& outInfo);

static bool ERTP_OCT_L2D(const InputInfo& inInfo
					   , OutputInfo& outInfo);
static bool ERTP_CZI_L2D(const InputInfo& inInfo
                       , OutputInfo& outInfo);  

static bool NO_HANDLE(const InputInfo& inInfo
             , OutputInfo& outInfo){
	cout << "NO_HANDLE():error---" << inInfo.getFileName() << "  have not handle" << endl;
}

Handler::Handler(){
	handleMap_.insert(pair<string, Function_t>("OPER_OCT_L2C", OPER_OCT_L2C));
	handleMap_.insert(pair<string, Function_t>("OPER_OCT_L2B", OPER_OCT_L2B));
	handleMap_.insert(pair<string, Function_t>("OPER_CZI_L2B", OPER_CZI_L2B));
	handleMap_.insert(pair<string, Function_t>("OPER_CZI_L2C", OPER_CZI_L2C));
	handleMap_.insert(pair<string, Function_t>("OPER_SCA_L2B", OPER_SCA_L2B));
	handleMap_.insert(pair<string, Function_t>("ERTP_OCT_L2D", ERTP_OCT_L2D));
	handleMap_.insert(pair<string, Function_t>("ERTP_CZI_L2D", ERTP_CZI_L2D));
	handleMap_.insert(pair<string, Function_t>("NoHandle", NO_HANDLE));
}


Function_t Handler::getHandle(const string& handleName){
	map<string, Function_t>::iterator it = handleMap_.find(handleName);
	if(it != handleMap_.end())
		return it->second;
	else
		return handleMap_.find("NoHandle")->second; 
}


bool ERTP_CZI_L2D(const InputInfo& inInfo
                       , OutputInfo& outInfo)
 {
	try{
		Exception::dontPrint();
        H5Reader reader(inInfo.getFileName());
		try{
			//先取出相应的变量
    	    const VarInfo varInfoSDD = inInfo.getVar("SDD");
    	    Var varSDD = reader.getVar(varInfoSDD.getName());
    	    shared_ptr<DataMemory> dataSDD = varSDD.getData();

    	    const VarInfo varInfoSSC = inInfo.getVar("SSC");															Var varSSC = reader.getVar(varInfoSSC.getName());
    	    shared_ptr<DataMemory> dataSSC = varSSC.getData();
    	    
			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
    	    Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
    	    shared_ptr<DataMemory> dataLon = varNLongitude.getData();
    	    
			const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
    	    Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
    	    shared_ptr<DataMemory> dataLat = varNLatitude.getData();
    	    
			float* pSDD   = reinterpret_cast<float*>(dataSDD->getPointer());
    	    float* pSSC   = reinterpret_cast<float*>(dataSSC->getPointer());
    	    float* pLon   = reinterpret_cast<float*>(dataLon->getPointer());
    	    float* pLat   = reinterpret_cast<float*>(dataLat->getPointer());
    	    //统计元素个数
    	    long counter  = dataSDD->getSize()/sizeof(float); 
    	    
			double sDDFill = varInfoSDD.getFillVal();
    	    double sDDScale = varInfoSDD.getScale();
    	    double sDDOffSet = varInfoSDD.getOffSet();
    	    
			double sSCFill = varInfoSSC.getFillVal();
    	    double sSCScale = varInfoSSC.getScale();
    	    double sSCOffSet = varInfoSSC.getOffSet();
    	   
			double lonFill = varInfoNLongitude.getFillVal();
    	    double lonScale = varInfoNLongitude.getScale();
    	    double lonOffSet = varInfoNLongitude.getOffSet();
    	    
			double latFill = varInfoNLatitude.getFillVal();
    	    double latScale = varInfoNLatitude.getScale();
    	    double latOffSet = varInfoNLatitude.getOffSet();
    	    
			for(long i = 0; i != counter; ++i){
    	        //todo:忽略无效值的计算
    	        if(*(pSDD+i) == sDDFill){
    	            continue;
    	        }
    	        *(pSDD+i) = *(pSDD+i) * sDDScale + sDDOffSet;
			}
    	    for(long i = 0; i != counter; ++i){
    	        //todo:忽略无效值的计算
    	        if(*(pSSC+i) == sSCFill){
    	            continue;
    	        }
    	        *(pSSC+i) = *(pSSC+i) * sSCScale + sSCOffSet;
    	    }
    	    for(long i = 0; i != counter; ++i){
    	        //todo:忽略无效值的计算
    	        if(*(pLon+i) == lonFill){
    	            continue;
    	        }
    	        *(pLon+i) = *(pLon+i) * lonScale + lonOffSet;
    	    }
    	    for(long i = 0; i != counter; ++i){
    	        //todo:忽略无效值的计算
    	        if(*(pLat+i) == latFill){
    	            continue;
    	        }
    	        *(pLat+i) = *(pLat+i) * latScale + latOffSet; 
    	    }
    	    double offset, scale;
    	    char pathBuff[1000];
    	    NcWriter writer("ND3"+ inInfo.getDate()+ ".nc");
    	    NcWriter writer01("NC3"+ inInfo.getDate()+ ".nc");
    	    DataMemory::toShortInt<float>(dataSDD, scale, offset, sDDFill);
    	    NcVar ncSDD = writer.defVar("SDD", ncShort, varSDD.getDims());
    	    putAtts(ncSDD, sDDFill, scale, offset);
    	    ncSDD.putVar(dataSDD->getPointer());
    	    DataMemory::toShortInt<float>(dataLat, scale, offset, latFill);
    	    NcVar ncLat = writer.defVar("NLatitude", ncShort, varNLatitude.getDims());
    	    putAtts(ncLat, latFill, scale, offset);
    	    ncLat.putVar(dataLat->getPointer());
    	    NcVar ncLat01 = writer01.defVar("NLatitude", ncShort, varNLatitude.getDims());
    	    putAtts(ncLat01, latFill, scale, offset);
    	    ncLat01.putVar(dataLat->getPointer());
    	    DataMemory::toShortInt<float>(dataLon, scale, offset, lonFill);
    	    NcVar ncLon = writer.defVar("NLongitude", ncShort, varNLongitude.getDims());                                                                                                                           
    	    putAtts(ncLon, lonFill, scale, offset);
    	    ncLon.putVar(dataLon->getPointer());
    	    NcVar ncLon01 = writer01.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon01, lonFill, scale, offset);
    	    ncLon01.putVar(dataLon->getPointer());
    	    DataMemory::toShortInt<float>(dataSSC, scale, offset, sSCFill);                                                                                                                                        
    	    NcVar ncSSC = writer01.defVar("SSC", ncShort, varSSC.getDims());
    	    putAtts(ncSSC, sSCFill, scale, offset);
    	    ncSSC.putVar(dataSSC->getPointer());
    	    getcwd(pathBuff, 1000);
    	    outInfo.addFileInfo("ND3"+ inInfo.getDate() + ".nc", pathBuff);
    	    outInfo.addFileInfo("NC3"+ inInfo.getDate() + ".nc", pathBuff);
			return true;
		}CATCH_INPUTINFO_EXCEPTION
	}CATCH_H5_EXCEPTION
 }


bool  OPER_SCA_L2B(const InputInfo& inInfo
				, OutputInfo& outInfo)
{
	try{
		Exception::dontPrint();
		H5Reader reader(inInfo.getFileName());
		try{
			//先取出相应的变量
			const VarInfo varInfoWindSpeed = inInfo.getVar("wind_speed");
			Var varWindSpeed = reader.getVar(varInfoWindSpeed.getName());
			shared_ptr<DataMemory> dataWindSpeed = varWindSpeed.getData();
			
			const VarInfo varInfoWindDir = inInfo.getVar("wind_dir");
			Var varWindDir = reader.getVar(varInfoWindDir.getName());
			shared_ptr<DataMemory> dataWindDir = varWindDir.getData();
					
			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
			Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
			shared_ptr<DataMemory> dataLon = varNLongitude.getData();
					
			const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
			Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
			shared_ptr<DataMemory> dataLat = varNLatitude.getData();
			
			short* pSrcDir   = reinterpret_cast<short*>(dataWindDir->getPointer());
			short* pSrcSpeed = reinterpret_cast<short*>(dataWindSpeed->getPointer());
			float* pSrcLon = reinterpret_cast<float*>(dataLon->getPointer());
			float* pSrcLat = reinterpret_cast<float*>(dataLat->getPointer());
			
			//统计元素个数
			long counter  = dataWindDir->getSize()/sizeof(short);
			//数据可能占用内存过大，使用堆内存
			shared_ptr<DataMemory> u = make_shared<DataMemory>(counter * sizeof(float));
			shared_ptr<DataMemory> v = make_shared<DataMemory>(counter * sizeof(float));
			shared_ptr<DataMemory> speed = make_shared<DataMemory>(counter * sizeof(float));
			shared_ptr<DataMemory> lon = make_shared<DataMemory>(counter * sizeof(float));
			shared_ptr<DataMemory> lat = make_shared<DataMemory>(counter * sizeof(float));
			float* pSpeed = reinterpret_cast<float*>(speed->getPointer());
			float* pU = reinterpret_cast<float*>(u->getPointer());
			float* pV = reinterpret_cast<float*>(v->getPointer());
			float* pLon = reinterpret_cast<float*>(lon->getPointer());
			float* pLat = reinterpret_cast<float*>(lat->getPointer());
			
			double dirFill   = varInfoWindDir.getFillVal();
			double speedFill = varInfoWindSpeed.getFillVal();
			double lonFill = varInfoNLongitude.getFillVal();
			double latFill = varInfoNLatitude.getFillVal();
		
			double dirScale   = varInfoWindDir.getScale();
			double speedScale = varInfoWindSpeed.getScale();
			double lonScale = varInfoNLongitude.getScale();
			double latScale = varInfoNLatitude.getScale();
			
			double dirOffSet   = varInfoWindDir.getOffSet();
			double speedOffSet = varInfoWindSpeed.getOffSet();
			double lonOffSet = varInfoNLongitude.getOffSet();
			double latOffSet = varInfoNLatitude.getOffSet();
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
				if(*(pSrcDir+i) == dirFill || *(pSrcSpeed+i) == speedFill){
					*(pU+i) = speedFill;
					*(pV+i) = speedFill;
					*(pSpeed+i) = speedFill;
					continue;
				}
				
		
				//sin计算是用弧度
				*(pU+i) = (*(pSrcSpeed+i) * speedScale + speedOffSet) 
						  * sin((*(pSrcDir+i) * dirScale + dirOffSet) *3.14/180);
				
				*(pV+i) = (*(pSrcSpeed+i) * speedScale + speedOffSet )
						  * cos((*(pSrcDir+i) * dirScale + dirOffSet) *3.14/180);
				*(pSpeed+i) = sqrt(pow(*(pU+i), 2) + pow(*(pV+i), 2));
			}

    	    for(long i = 0; i != counter; ++i){
    	        //todo:忽略无效值的计算
    	        if( *(pSrcLon+i) == lonFill){
    	            continue;
    	        }
    	        *(pLon+i) = *(pSrcLon+i) * lonScale + lonOffSet;
    	    }
    	    for(long i = 0; i != counter; ++i){
    	        //todo:忽略无效值的计算
    	        if(*(pSrcLat+i) == latFill){
    	            continue;
    	        }
    	        *(pLat+i) = *(pSrcLat+i) * latScale + latOffSet; 
    	    }
			
			//设置文件名和路径
			NcWriter writer("NW8"+ inInfo.getDate() + ".nc");
			char pathBuff[1000];
			getcwd(pathBuff, 1000);
			outInfo.addFileInfo(pathBuff, "NW8"+ inInfo.getDate() + ".nc");
			
			//offset, scale会根据结果数据自动调整
			double offset, scale;
			DataMemory::toShortInt<float>(u, scale, offset, speedFill);
			NcVar ncU = writer.defVar("u", ncShort, varWindSpeed.getDims());
			putAtts(ncU, speedFill, scale, offset);
			ncU.putVar(u->getPointer());
			
			DataMemory::toShortInt<float>(v, scale, offset, speedFill);
			NcVar ncV = writer.defVar("v", ncShort, varWindSpeed.getDims());
			putAtts(ncV, speedFill, scale, offset);
			ncV.putVar(v->getPointer());	//当内存数据的ncType跟变量的ncType不一致时，会导致error
			
			DataMemory::toShortInt<float>(speed, scale, offset, speedFill);
			NcVar ncSpeed = writer.defVar(varInfoWindSpeed.getIdName(), ncShort, varWindSpeed.getDims());
			putAtts(ncSpeed, speedFill, scale, offset);
			ncSpeed.putVar(speed->getPointer());
		
		
			DataMemory::toShortInt<float>(lon, scale, offset, lonFill);
			NcVar ncLon = writer.defVar(varInfoNLongitude.getIdName(), ncShort, varNLongitude.getDims());
			putAtts(ncLon, lonFill, scale, offset);
			ncLon.putVar(lon->getPointer());
			
			DataMemory::toShortInt<float>(lat, scale, offset, latFill);
			NcVar ncLat = writer.defVar(varInfoNLatitude.getIdName(), ncShort, varNLatitude.getDims());
			putAtts(ncLat, latFill, scale, offset);
			ncLat.putVar(lat->getPointer());
		return true;
		}CATCH_INPUTINFO_EXCEPTION
	}
	CATCH_H5_EXCEPTION
}

bool  OPER_CZI_L2C(const InputInfo& inInfo
				, OutputInfo& outInfo)
{
	try{
        Exception::dontPrint();
		H5Reader reader(inInfo.getFileName());
		try{
			//先取出相应的变量
    	    const VarInfo varInfoSDD = inInfo.getVar("SDD");
    	    Var varSDD = reader.getVar(varInfoSDD.getName());
    	    shared_ptr<DataMemory> dataSDD = varSDD.getData();
			
    	    const VarInfo varInfoChl_a = inInfo.getVar("Chl_a");
    	    Var varChl_a = reader.getVar(varInfoChl_a.getName());
    	    shared_ptr<DataMemory> dataChl_a = varChl_a.getData();
			
			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
    	    Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
    	    shared_ptr<DataMemory> dataLon = varNLongitude.getData();

    	    const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
    	    Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
    	    shared_ptr<DataMemory> dataLat = varNLatitude.getData();
			
			float* pSDD   = reinterpret_cast<float*>(dataSDD->getPointer());
			float* pChl_a   = reinterpret_cast<float*>(dataChl_a->getPointer());
			float* pLon   = reinterpret_cast<float*>(dataLon->getPointer());
			float* pLat   = reinterpret_cast<float*>(dataLat->getPointer());
			//统计元素个数
			long counter  = dataSDD->getSize()/sizeof(float); 
    	    
    	    double sDDFill = varInfoSDD.getFillVal();
    	    double sDDScale = varInfoSDD.getScale();
    	    double sDDOffSet = varInfoSDD.getOffSet();
    	    
    	    double chl_aFill = varInfoChl_a.getFillVal();
    	    double chl_aScale = varInfoChl_a.getScale();
    	    double chl_aOffSet = varInfoChl_a.getOffSet();
			
			double lonFill = varInfoNLongitude.getFillVal();
    	    double lonScale = varInfoNLongitude.getScale();
    	    double lonOffSet = varInfoNLongitude.getOffSet();

			double latFill = varInfoNLatitude.getFillVal();
    	    double latScale = varInfoNLatitude.getScale();
    	    double latOffSet = varInfoNLatitude.getOffSet();
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pSDD+i) == sDDFill){
    	    	    continue;
    	    	}
    	    	*(pSDD+i) = *(pSDD+i) * sDDScale + sDDOffSet; 
			}
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pChl_a+i) == chl_aFill){
    	    	    continue;
    	    	}
    	    	*(pChl_a+i) = *(pChl_a+i) * chl_aScale + chl_aOffSet; 
			}
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLon+i) == lonFill){
    	    	    continue;
    	    	}
    	    	*(pLon+i) = *(pLon+i) * lonScale + lonOffSet; 
			}

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLat+i) == latFill){
    	    	    continue;
    	    	}
    	    	*(pLat+i) = *(pLat+i) * latScale + latOffSet; 
			}
			
			
			double offset, scale;
			char pathBuff[1000];
			
			NcWriter writer("ND3"+ inInfo.getDate()+ ".nc");
			NcWriter writer01("NA3"+ inInfo.getDate()+ ".nc");
    	    
			DataMemory::toShortInt<float>(dataSDD, scale, offset, sDDFill);
			NcVar ncSDD = writer.defVar("SDD", ncShort, varSDD.getDims());
			putAtts(ncSDD, sDDFill, scale, offset);
    	    ncSDD.putVar(dataSDD->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLat, scale, offset, latFill);
			NcVar ncLat = writer.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat, latFill, scale, offset);
    	    ncLat.putVar(dataLat->getPointer());
    	    
			NcVar ncLat01 = writer01.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat01, latFill, scale, offset);
    	    ncLat01.putVar(dataLat->getPointer());
			
			DataMemory::toShortInt<float>(dataLon, scale, offset, lonFill);
			NcVar ncLon = writer.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon, lonFill, scale, offset);
    	    ncLon.putVar(dataLon->getPointer());

			NcVar ncLon01 = writer01.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon01, lonFill, scale, offset);
    	    ncLon01.putVar(dataLon->getPointer());
			
			
			DataMemory::toShortInt<float>(dataChl_a, scale, offset, lonFill);
			NcVar ncChl_a = writer01.defVar("Chl_a", ncShort, varChl_a.getDims());
			putAtts(ncChl_a, chl_aFill, scale, offset);
    	    ncChl_a.putVar(dataChl_a->getPointer());
    	    

    	    getcwd(pathBuff, 1000);
    	    outInfo.addFileInfo("ND3"+ inInfo.getDate() + ".nc", pathBuff);
    	    outInfo.addFileInfo("NA3"+ inInfo.getDate() + ".nc", pathBuff);
			return true;
		}CATCH_INPUTINFO_EXCEPTION
	}
	CATCH_H5_EXCEPTION
}



bool OPER_CZI_L2B(const InputInfo& inInfo
					   , OutputInfo& outInfo)
{
	try{
        Exception::dontPrint();
		H5Reader reader(inInfo.getFileName());
		try{
			//先取出相应的变量
    	    const VarInfo varInfoSSC = inInfo.getVar("SSC");
    	    Var varSSC = reader.getVar(varInfoSSC.getName());
    	    shared_ptr<DataMemory> dataSSC = varSSC.getData();
			
			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
    	    Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
    	    shared_ptr<DataMemory> dataLon = varNLongitude.getData();

    	    const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
    	    Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
    	    shared_ptr<DataMemory> dataLat = varNLatitude.getData();
			
			float* pSSC   = reinterpret_cast<float*>(dataSSC->getPointer());
			float* pLon   = reinterpret_cast<float*>(dataLon->getPointer());
			float* pLat   = reinterpret_cast<float*>(dataLat->getPointer());
			//统计元素个数
			long counter  = dataSSC->getSize()/sizeof(float); 
    	    
    	    double sSCFill = varInfoSSC.getFillVal();
    	    double sSCScale = varInfoSSC.getScale();
    	    double sSCOffSet = varInfoSSC.getOffSet();
    	    
			double lonFill = varInfoNLongitude.getFillVal();
    	    double lonScale = varInfoNLongitude.getScale();
    	    double lonOffSet = varInfoNLongitude.getOffSet();

			double latFill = varInfoNLatitude.getFillVal();
    	    double latScale = varInfoNLatitude.getScale();
    	    double latOffSet = varInfoNLatitude.getOffSet();
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pSSC+i) == sSCFill){
    	    	    continue;
    	    	}
    	    	*(pSSC+i) = *(pSSC+i) * sSCScale + sSCOffSet; 
			}
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLon+i) == lonFill){
    	    	    continue;
    	    	}
    	    	*(pLon+i) = *(pLon+i) * lonScale + lonOffSet; 
			}

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLat+i) == latFill){
    	    	    continue;
    	    	}
    	    	*(pLat+i) = *(pLat+i) * latScale + latOffSet; 
			}
			
			
			NcWriter writer("NC3"+ inInfo.getDate()+ ".nc");
			double offset, scale;
    	    DataMemory::toShortInt<float>(dataSSC, scale, offset, sSCFill);
			NcVar ncSSC = writer.defVar("SSC", ncShort, varSSC.getDims());
			putAtts(ncSSC, sSCFill, scale, offset);
    	    ncSSC.putVar(dataSSC->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLat, scale, offset, latFill);
			NcVar ncLat = writer.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat, latFill, scale, offset);
    	    ncLat.putVar(dataLat->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLon, scale, offset, lonFill);
			NcVar ncLon = writer.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon, lonFill, scale, offset);
    	    ncLon.putVar(dataLon->getPointer());

			char pathBuff[1000];
    	    getcwd(pathBuff, 1000);
    	    outInfo.addFileInfo(pathBuff, "NC3"+ inInfo.getDate() + ".nc");
			return true;
		}CATCH_INPUTINFO_EXCEPTION
	}
	CATCH_H5_EXCEPTION
}

static bool OPER_OCT_L2B(const InputInfo& inInfo

					   , OutputInfo& outInfo)
{
	try{
        Exception::dontPrint();
		cout << "fileName = " << inInfo.getFileName() << endl;
		try{
			H5Reader reader(inInfo.getFileName());
  		    //先取出相应的变量
    	    const VarInfo varInfoSSC = inInfo.getVar("SSC");
    	    Var varSSC = reader.getVar(varInfoSSC.getName());
    	    shared_ptr<DataMemory> dataSSC = varSSC.getData();
			
    	    const VarInfo varInfoSST = inInfo.getVar("SST");
    	    Var varSST = reader.getVar(varInfoSST.getName());
    	    shared_ptr<DataMemory> dataSST = varSST.getData();
		
    	    const VarInfo varInfoChl_a = inInfo.getVar("Chl_a");
    	    Var varChl_a = reader.getVar(varInfoChl_a.getName());
    	    shared_ptr<DataMemory> dataChl_a = varSST.getData();

			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
    	    Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
    	    shared_ptr<DataMemory> dataLon = varNLongitude.getData();

    	    const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
    	    Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
    	    shared_ptr<DataMemory> dataLat = varNLatitude.getData();
			
			float* pSSC   = reinterpret_cast<float*>(dataSSC->getPointer());
			float* pSST   = reinterpret_cast<float*>(dataSST->getPointer());
			float* pChl_a   = reinterpret_cast<float*>(dataChl_a->getPointer());
			float* pLon   = reinterpret_cast<float*>(dataLon->getPointer());
			float* pLat   = reinterpret_cast<float*>(dataLat->getPointer());
			//统计元素个数
			long counter  = dataSSC->getSize()/sizeof(float); 
    	    
    	    double sSCFill = varInfoSSC.getFillVal();
    	    double sSCScale = varInfoSSC.getScale();
    	    double sSCOffSet = varInfoSSC.getOffSet();
			
    	    double sSTFill = varInfoSST.getFillVal();
    	    double sSTScale = varInfoSST.getScale();
    	    double sSTOffSet = varInfoSST.getOffSet();
    	    
			double chl_aFill = varInfoChl_a.getFillVal();
    	    double chl_aScale = varInfoChl_a.getScale();
    	    double chl_aOffSet = varInfoChl_a.getOffSet();
			
			double lonFill = varInfoNLongitude.getFillVal();
    	    double lonScale = varInfoNLongitude.getScale();
    	    double lonOffSet = varInfoNLongitude.getOffSet();

			double latFill = varInfoNLatitude.getFillVal();
    	    double latScale = varInfoNLatitude.getScale();
    	    double latOffSet = varInfoNLatitude.getOffSet();
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pSSC+i) == sSCFill){
    	    	    continue;
    	    	}
    	    	*(pSSC+i) = *(pSSC+i) * sSCScale + sSCOffSet; 
			}
		

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pSST+i) == sSTFill){
    	    	    continue;
    	    	}
    	    	*(pSST+i) = *(pSST+i) * sSTScale + sSTOffSet; 
			}
		

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pChl_a+i) == chl_aFill){
    	    	    continue;
    	    	}
    	    	*(pChl_a+i) = *(pChl_a+i) * chl_aScale + chl_aOffSet; 
			}

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLon+i) == lonFill){
    	    	    continue;
    	    	}
    	    	*(pLon+i) = *(pLon+i) * lonScale + lonOffSet; 
			}

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLat+i) == latFill){
    	    	    continue;
    	    	}
    	    	*(pLat+i) = *(pLat+i) * latScale + latOffSet; 
			}
			
			
			double offset, scale;
			char pathBuff[1000];
			
			NcWriter writer01("NC1"+ inInfo.getDate()+ ".nc");
			NcWriter writer02("NT1"+ inInfo.getDate()+ ".nc");
			NcWriter writer03("NA1"+ inInfo.getDate()+ ".nc");
			 
    	    
			DataMemory::toShortInt<float>(dataLat, scale, offset, latFill);
			NcVar ncLat01 = writer01.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat01, latFill, scale, offset);
    	    ncLat01.putVar(dataLat->getPointer());
    	    
			NcVar ncLat02 = writer02.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat02, latFill, scale, offset);
    	    ncLat02.putVar(dataLat->getPointer());

			NcVar ncLat03 = writer03.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat03, latFill, scale, offset);
    	    ncLat03.putVar(dataLat->getPointer());
			
			DataMemory::toShortInt<float>(dataLon, scale, offset, latFill);
			NcVar ncLon01 = writer01.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon01, lonFill, scale, offset);
    	    ncLon01.putVar(dataLon->getPointer());

			NcVar ncLon02 = writer02.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon02, lonFill, scale, offset);
    	    ncLon02.putVar(dataLon->getPointer());
    	    
			
			NcVar ncLon03 = writer03.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon03, lonFill, scale, offset);
    	    ncLon03.putVar(dataLon->getPointer());

			DataMemory::toShortInt<float>(dataSSC, scale, offset, sSCFill);
			NcVar ncSSC = writer01.defVar("SSC", ncShort, varSSC.getDims());
			putAtts(ncSSC, sSCFill, scale, offset);
    	    ncSSC.putVar(dataSSC->getPointer());

			DataMemory::toShortInt<float>(dataSST, scale, offset, sSTFill);
			NcVar ncSST = writer02.defVar("SST", ncShort, varSST.getDims());
			putAtts(ncSST, sSTFill, scale, offset);
    	    ncSST.putVar(dataSST->getPointer());

			DataMemory::toShortInt<float>(dataChl_a, scale, offset, lonFill);
			NcVar ncChl_a = writer03.defVar("Chl_a", ncShort, varChl_a.getDims());
			putAtts(ncChl_a, chl_aFill, scale, offset);
    	    ncChl_a.putVar(dataChl_a->getPointer());
    	    

    	    getcwd(pathBuff, 1000);
    	    outInfo.addFileInfo("NC1"+ inInfo.getDate() + ".nc", pathBuff);
    	    outInfo.addFileInfo("NT1"+ inInfo.getDate() + ".nc", pathBuff);
    	    outInfo.addFileInfo("NA1"+ inInfo.getDate() + ".nc", pathBuff);
			return true;
		}CATCH_INPUTINFO_EXCEPTION
	}
	CATCH_H5_EXCEPTION
}

bool OPER_OCT_L2C(const InputInfo& inInfo
                 ,OutputInfo& outInfo)
{
	try{
        Exception::dontPrint();
		H5Reader reader(inInfo.getFileName());
  	    try{
			//先取出相应的变量
    	    const VarInfo varInfoSDD = inInfo.getVar("SDD");
    	    Var varSDD = reader.getVar(varInfoSDD.getName());
    	    shared_ptr<DataMemory> dataSDD = varSDD.getData();
			
			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
    	    Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
    	    shared_ptr<DataMemory> dataLon = varNLongitude.getData();

    	    const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
    	    Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
    	    shared_ptr<DataMemory> dataLat = varNLatitude.getData();
			
			float* pSDD   = reinterpret_cast<float*>(dataSDD->getPointer());
			float* pLon   = reinterpret_cast<float*>(dataLon->getPointer());
			float* pLat   = reinterpret_cast<float*>(dataLat->getPointer());
			//统计元素个数
			long counter  = dataSDD->getSize()/sizeof(float); 
    	    
    	    double sDDFill = varInfoSDD.getFillVal();
    	    double sDDScale = varInfoSDD.getScale();
    	    double sDDOffSet = varInfoSDD.getOffSet();
    	    
			double lonFill = varInfoNLongitude.getFillVal();
    	    double lonScale = varInfoNLongitude.getScale();
    	    double lonOffSet = varInfoNLongitude.getOffSet();

			double latFill = varInfoNLatitude.getFillVal();
    	    double latScale = varInfoNLatitude.getScale();
    	    double latOffSet = varInfoNLatitude.getOffSet();
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pSDD+i) == sDDFill){
    	    	    continue;
    	    	}
    	    	*(pSDD+i) = *(pSDD+i) * sDDScale + sDDOffSet; 
			}
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLon+i) == lonFill){
    	    	    continue;
    	    	}
    	    	*(pLon+i) = *(pLon+i) * lonScale + lonOffSet; 
			}

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLat+i) == latFill){
    	    	    continue;
    	    	}
    	    	*(pLat+i) = *(pLat+i) * latScale + latOffSet; 
			}
			
			
			NcWriter writer("ND1"+ inInfo.getDate()+ ".nc");
			double offset, scale;
    	    DataMemory::toShortInt<float>(dataSDD, scale, offset, sDDFill);
			NcVar ncSDD = writer.defVar("SDD", ncShort, varSDD.getDims());
			putAtts(ncSDD, sDDFill, scale, offset);
    	    ncSDD.putVar(dataSDD->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLat, scale, offset, latFill);
			NcVar ncLat = writer.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat, latFill, scale, offset);
    	    ncLat.putVar(dataLat->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLon, scale, offset, lonFill);
			NcVar ncLon = writer.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon, lonFill, scale, offset);
    	    ncLon.putVar(dataLon->getPointer());

			char pathBuff[1000];
    	    getcwd(pathBuff, 1000);
    	    outInfo.addFileInfo(pathBuff, "ND1"+ inInfo.getDate() + ".nc");
			return true;
		}CATCH_INPUTINFO_EXCEPTION
	}
	CATCH_H5_EXCEPTION
}


static bool ERTP_OCT_L2D(const InputInfo& inInfo
					   , OutputInfo& outInfo)
{

	try{
        Exception::dontPrint();
		H5Reader reader(inInfo.getFileName());
  	    try{
			//先取出相应的变量
    	    const VarInfo varInfoSST = inInfo.getVar("SST");
    	    Var varSST = reader.getVar(varInfoSST.getName());
    	    shared_ptr<DataMemory> dataSST = varSST.getData();
			
			const VarInfo varInfoNLongitude = inInfo.getVar("NLongitude");
    	    Var varNLongitude   = reader.getVar(varInfoNLongitude.getName());
    	    shared_ptr<DataMemory> dataLon = varNLongitude.getData();

    	    const VarInfo varInfoNLatitude = inInfo.getVar("NLatitude");
    	    Var varNLatitude   = reader.getVar(varInfoNLatitude.getName());
    	    shared_ptr<DataMemory> dataLat = varNLatitude.getData();
			
			float* pSST   = reinterpret_cast<float*>(dataSST->getPointer());
			float* pLon   = reinterpret_cast<float*>(dataLon->getPointer());
			float* pLat   = reinterpret_cast<float*>(dataLat->getPointer());
			//统计元素个数
			long counter  = dataSST->getSize()/sizeof(float); 
    	    
    	    double sSTFill = varInfoSST.getFillVal();
    	    double sSTScale = varInfoSST.getScale();
    	    double sSTOffSet = varInfoSST.getOffSet();
    	    
			double lonFill = varInfoNLongitude.getFillVal();
    	    double lonScale = varInfoNLongitude.getScale();
    	    double lonOffSet = varInfoNLongitude.getOffSet();

			double latFill = varInfoNLatitude.getFillVal();
    	    double latScale = varInfoNLatitude.getScale();
    	    double latOffSet = varInfoNLatitude.getOffSet();
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pSST+i) == sSTFill){
    	    	    continue;
    	    	}
    	    	*(pSST+i) = *(pSST+i) * sSTScale + sSTOffSet; 
			}
			
			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLon+i) == lonFill){
    	    	    continue;
    	    	}
    	    	*(pLon+i) = *(pLon+i) * lonScale + lonOffSet; 
			}

			for(long i = 0; i != counter; ++i){
				//todo:忽略无效值的计算
    	    	if(*(pLat+i) == latFill){
    	    	    continue;
    	    	}
    	    	*(pLat+i) = *(pLat+i) * latScale + latOffSet; 
			}
			
			
			NcWriter writer("NT1"+ inInfo.getDate()+ ".nc");
			double offset, scale;
    	    DataMemory::toShortInt<float>(dataSST, scale, offset, sSTFill);
			NcVar ncSST = writer.defVar("SST", ncShort, varSST.getDims());
			putAtts(ncSST, sSTFill, scale, offset);
    	    ncSST.putVar(dataSST->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLat, scale, offset, latFill);
			NcVar ncLat = writer.defVar("NLatitude", ncShort, varNLatitude.getDims());
			putAtts(ncLat, latFill, scale, offset);
    	    ncLat.putVar(dataLat->getPointer());
    	    
			DataMemory::toShortInt<float>(dataLon, scale, offset, lonFill);
			NcVar ncLon = writer.defVar("NLongitude", ncShort, varNLongitude.getDims());
			putAtts(ncLon, lonFill, scale, offset);
    	    ncLon.putVar(dataLon->getPointer());

			char pathBuff[1000];
    	    getcwd(pathBuff, 1000);
    	    outInfo.addFileInfo(pathBuff, "NT1"+ inInfo.getDate() + ".nc");
			return true;
		}CATCH_INPUTINFO_EXCEPTION
	}
	CATCH_H5_EXCEPTION
}

void putAtts(NcVar& ncVar, double fillVal, double scale, double offSet)
{
	ncVar.putAtt("the_Fill_Value",   ncDouble, static_cast<short>(fillVal));
	ncVar.putAtt("the_add_offset",   ncDouble, offSet);
	ncVar.putAtt("the_scale_factor", ncDouble, scale);
}
