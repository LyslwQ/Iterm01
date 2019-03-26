PROJECT_DIR := /home/ciker/HNProject/YsProject20190306

BIN_DIR := $(PROJECT_DIR)/bin

SRC_DIR := $(PROJECT_DIR)/src

OBJ_DIR := $(PROJECT_DIR)/obj

#DEP_DIR := $(PROJECT_DIR)/dep

Target := $(BIN_DIR)/main

INCLUDE_DIR := -I/opt/hdf5-1.8.20-linux-centos7-x86_64-gcc485-shared/include

LIB_DIR := -L/opt/hdf5-1.8.20-linux-centos7-x86_64-gcc485-shared/lib
#LIB_DIR := 

LIBS := -lhdf5_cpp  -lnetcdf-cxx4 -lnetcdf

LDFLAGS := -Wl,-rpath=/opt/hdf5-1.8.20-linux-centos7-x86_64-gcc485-shared/lib/
#LDFLAGS :=

#SRCS:
SRCS := $(notdir $(shell ls $(SRC_DIR)/*.cpp))
#OBJS:
OBJS := $(foreach s,$(SRCS:.cpp=.o),$(OBJ_DIR)/$(s))


CXX := /opt/hdf5-1.8.20-linux-centos7-x86_64-gcc485-shared/bin/h5c++
GCC := $(CXX)

#CXXFLAGS := -Wall -g -std=c++11
GCCFLAGS := -Wall -g -std=c++11

all : makedir $(Target)
makedir : 
	@-mkdir -p $(OBJ_DIR)

$(Target) : $(OBJS)
	$(GCC) $(OBJS)  $(GCCFLAGS)  $(LIB_DIR) $(LIBS) $(LDFLAGS) -o $(Target) $(TargetSrc)

$(OBJS) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(GCC) $(GCCFLAGS) $(INCLUDE_DIR) $(LDFLAGS) $(LIB_DIR) -o $(@) -c $(<)

clean :
	-rm -rf $(PROJECT_DIR)/obj
	-rm -rf $(BIN_DIR)/*

