#ifndef HANDLER_H_
#define HANDLER_H_
#include <map>
#include <string>
#include <functional>

#include "H5Cpp.h"
#include <netcdf>

#include "DataTypeH2N.h"
#include "Info.h"

class InputInfo;
using std::map;
using std::pair;
using std::function;
using std::string;

using namespace netCDF;
using namespace netCDF::exceptions;

typedef function<bool(const InputInfo& inInfo, OutputInfo& outInfo)> Function_t;

class Handler
{
public:
	Handler();
	Function_t getHandle(const string& handleName);
private:
	map<string, Function_t> handleMap_;
};

#define	CATCH_H5_EXCEPTION	 \
       catch( FileIException error ){\
          error.printError();\
          return false;\
       }\
       catch( DataSetIException error )\
       {\
          error.printError();\
          return false;\
       }\
       catch( DataSpaceIException error )\
       {\
          error.printError();\
          return false;\
       }\
       catch( DataTypeIException error )\
       {\
          error.printError();\
          return false;\
       }\



#endif // endif HANDLER_H_
