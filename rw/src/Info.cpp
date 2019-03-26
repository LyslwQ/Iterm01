#include "Info.h"


InputInfo InputInfo::getTestInfo()
{
    InputInfo info;
	info.setFileName("L2B.h5");

	//定义变量
	VarInfo var01("NLongitude", "wvc_lon");
	var01.setFillVal(169999997607218210000000000000000000000.000000 );
	var01.setOffSet(0.0);
	var01.setScale(1.0);
	
	VarInfo var02("NLatitude", "wvc_lat");
	var02.setFillVal(169999997607218210000000000000000000000.000000);
	var02.setOffSet(0.0);
	var02.setScale(1.0);
	
//	VarInfo var03("SSC","SSC");
//	var03.setFillVal(0.0);
//	var03.setOffSet(0.0);
//	var03.setScale(1.0);

	VarInfo var04("wind_dir","wind_dir_selection");
	var04.setFillVal(-32767.0);
	var04.setOffSet(0.0);
	var04.setScale(0.1);
//
	VarInfo var05("wind_speed","wind_speed_selection");
	var05.setFillVal(-32767.0);
	var05.setOffSet(0.0);
	var05.setScale(0.01);


	info.addVar(var01);
	info.addVar(var02);
//	info.addVar(var03);
	info.addVar(var04);
	info.addVar(var05);
	
	info.date_ = "yymmddhh";
    return info;    //没有返回时，会报错
}
