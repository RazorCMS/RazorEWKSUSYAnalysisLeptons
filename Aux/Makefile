CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = $(Repo)/Aux
HggCommon = $(Repo)/HggRazor/CommonTools

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(Aux)/include -I$(HggCommon)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR)

CPPFLAGS += -g -std=c++11

TARGET = NormalizeNtuples

SRC = app/NormalizeNtuples.cc  $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(HggCommon)/src/HggAux.cc

OBJ = $(SRC:.cc=.o)

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o app/*.o src/*.o $(Aux)/src/*.o $(TARGET) *~
