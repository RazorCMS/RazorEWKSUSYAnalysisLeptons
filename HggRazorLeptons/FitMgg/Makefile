CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = $(Repo)/Aux
HggRazor = $(Repo)/HggRazorLeptons
CommonTools = $(HggRazor)/CommonTools

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(CommonTools)/include -I$(Aux)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore -L$(INC)/include -lCustomPdfs

CPPFLAGS += -g -std=c++1y

TARGET = MakeFit
TARGET1 = MakeFitRun2
TARGET2 = PlotAllBiasTest
TARGET4 = CreateDataCardCommands
TARGET5 = testCustomPdf
TARGET6 = GetDCBParameters
TARGET7 = PrintSignalSnipped
TARGET8 = GetRefMass
TARGET9 = CompareFit
TARGET10 = PlotFitWithErrors
#TARGET11 = TestGaussianContraint
TARGET12 = CreateCombineCommands

SRC = app/testapp.cc src/makeInvertedANFit_v2.cc $(Aux)/src/CommandLineInput.cc
SRC1 = app/MakeFitRun2.cc src/RunTwoFitMgg.cc src/DefinePdfs.cc src/PrintAIC.cc $(Aux)/src/CommandLineInput.cc
SRC2 = app/PlotAllBiasTest.cc src/PlotBias.cc $(Aux)/src/CommandLineInput.cc $(CommonTools)/src/HggAux.cc
SRC4 = app/CreateDataCardCommands.cc $(Aux)/src/CommandLineInput.cc
SRC5 = app/testCustomPdf.cc
SRC6 = app/GetDCBParameters.cc
SRC7 = app/PrintSignalSnipped.cc $(Aux)/src/CommandLineInput.cc
SRC8 = scripts/PlotRefAnalysisMass.cc $(Aux)/src/CommandLineInput.cc
SRC9 = scripts/CompareFit.cc $(Aux)/src/CommandLineInput.cc
SRC10 = scripts/PlotFitWithErrors.cc $(Aux)/src/CommandLineInput.cc
#SRC11 = app/TestGaussianContraint.cc src/RunTwoFitMgg.cc src/DefinePdfs.cc src/PrintAIC.cc $(Aux)/src/CommandLineInput.cc
SRC12 = app/CreateCombineCommands.cc $(Aux)/src/CommandLineInput.cc


OBJ = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ4 = $(SRC4:.cc=.o)
OBJ5 = $(SRC5:.cc=.o)
OBJ6 = $(SRC6:.cc=.o)
OBJ7 = $(SRC7:.cc=.o)
OBJ8 = $(SRC8:.cc=.o)
OBJ9 = $(SRC9:.cc=.o)
OBJ10 = $(SRC10:.cc=.o)
OBJ12 = $(SRC12:.cc=.o)

all : $(TARGET) $(TARGET1) $(TARGET2) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGET10) $(TARGET12) 

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

$(TARGET2) : $(OBJ2)
	$(LD) $(CPPFLAGS) -o $(TARGET2) $(OBJ2) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^


$(TARGET4) : $(OBJ4)
	$(LD) $(CPPFLAGS) -o $(TARGET4) $(OBJ4) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET5) : $(OBJ5)
	$(LD) $(CPPFLAGS) -o $(TARGET5) $(OBJ5) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET6) : $(OBJ6)
	$(LD) $(CPPFLAGS) -o $(TARGET6) $(OBJ6) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET7) : $(OBJ7)
	$(LD) $(CPPFLAGS) -o $(TARGET7) $(OBJ7) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET8) : $(OBJ8)
	$(LD) $(CPPFLAGS) -o $(TARGET8) $(OBJ8) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET9) : $(OBJ9)
	$(LD) $(CPPFLAGS) -o $(TARGET9) $(OBJ9) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET10) : $(OBJ10)
	$(LD) $(CPPFLAGS) -o $(TARGET10) $(OBJ10) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET12) : $(OBJ12)
	$(LD) $(CPPFLAGS) -o $(TARGET12) $(OBJ12) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^


%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<


clean :
	rm -f *.o app/*.o src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET) $(TARGET1) $(TARGET2) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGET10) $(TARGET12) *~
