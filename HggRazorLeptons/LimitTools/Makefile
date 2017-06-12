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

TARGET  = CreateCE_CombinedCards
TARGET1 = GetEffectiveSigma 
TARGET2 = testMinNll
TARGET3 = GetSignificance
TARGET4 = PlotLimits
TARGET5 = GetEffectiveSigmaHMD
TARGET6 = PlotSignificance
TARGET7 = GetFWHM
TARGET8 = PrintSignificanceHggRazor
TARGET9 = PlotSignificanceHggRazor
TARGET10 = GetSigmaMoverMeff
TARGET11 = PlotLimitsTChi
TARGET12 = DefineBinningHggRazorLeptons
TARGET13 = DefineHggRazorLeptonsBinning_HggPt_vs_MET


SRC  = app/CreateCE_CombinedCard.cc src/CountingExperiment.cc $(Aux)/src/CommandLineInput.cc $(CommonTools)/src/HggAux.cc
SRC1 = app/GetEffectiveSigma.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc
SRC2 = app/testMinNll.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc
SRC3 = app/GetSignificance.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc
SRC4 = app/PlotLimits.cc $(Aux)/src/CommandLineInput.cc
SRC5 = app/GetEffectiveSigmaHMD.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc
SRC6 = app/PlotSignificance.cc $(Aux)/src/CommandLineInput.cc
SRC7 = app/GetFWHM_FromFit.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc
SRC8 = app/PrintSignificanceHggRazor.cc $(Aux)/src/CommandLineInput.cc
SRC9 = app/PlotSignificanceHggRazor.cc $(Aux)/src/CommandLineInput.cc
SRC10 = app/GetSigmaMoverMeff.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc
SRC11 = app/PlotLimitsTChi.cc $(Aux)/src/CommandLineInput.cc
SRC12 = app/DefineHggRazorLeptonsBinning.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc
SRC13 = app/DefineHggRazorLeptonsBinning_HggPt_vs_MET.cc src/AssortedFunctions.cc $(Aux)/src/CommandLineInput.cc

OBJ  = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ3 = $(SRC3:.cc=.o)
OBJ4 = $(SRC4:.cc=.o)
OBJ5 = $(SRC5:.cc=.o)
OBJ6 = $(SRC6:.cc=.o)
OBJ7 = $(SRC7:.cc=.o)
OBJ8 = $(SRC8:.cc=.o)
OBJ9 = $(SRC9:.cc=.o)
OBJ10 = $(SRC10:.cc=.o)
OBJ11 = $(SRC11:.cc=.o)
OBJ12 = $(SRC12:.cc=.o)
OBJ13 = $(SRC13:.cc=.o)


all : $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGET10) $(TARGET11) $(TARGET12) $(TARGET13)

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

$(TARGET3) : $(OBJ3)
	$(LD) $(CPPFLAGS) -o $(TARGET3) $(OBJ3) $(LDFLAGS)
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

$(TARGET11) : $(OBJ11)
	$(LD) $(CPPFLAGS) -o $(TARGET11) $(OBJ11) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET12) : $(OBJ12)
	$(LD) $(CPPFLAGS) -o $(TARGET12) $(OBJ12) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET13) : $(OBJ13)
	$(LD) $(CPPFLAGS) -o $(TARGET13) $(OBJ13) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o app/*.o src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGTE8) $(TARGET9) $(TARGET10) $(TARGET11) $(TARGET12) $(TARGET13) *~
