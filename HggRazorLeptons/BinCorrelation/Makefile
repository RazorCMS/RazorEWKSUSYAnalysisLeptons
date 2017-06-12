CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = $(Repo)/Aux
HggRazor = $(Repo)/HggRazorLeptons
CommonTools = $(HggRazor)/CommonTools

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(CommonTools)/include -I$(Aux)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore
CPPFLAGS += -g -std=c++1y

TARGET = CreateCorrelation
TARGET1 = CreateCorrelationAsimov

SRC = app/CreateCorrelation.cc src/ToysAndIntegralFunctions.cc  $(Aux)/src/CommandLineInput.cc src/TTree_fit_sb.cc
SRC1 = app/CreateCorrelationAsimov.cc $(Aux)/src/CommandLineInput.cc

OBJ = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)

all : $(TARGET) $(TARGET1)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET1) : $(OBJ1)
	$(LD) $(CPPFLAGS) -o $(TARGET1) $(OBJ1) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o app/*.o src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET) $(TARGET1)*~
