CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = $(Repo)/Aux
HggRazor = $(Repo)/HggRazorLeptons
Selection = $(HggRazor)/Selection
CommonTools = $(HggRazor)/CommonTools
FitTools = $(HggRazor)/FitMgg

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(CommonTools)/include -I$(Aux)/include -I$(Selection)/include -I$(FitTools)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore -L$(FitTools)/include -lCustomPdfs

CPPFLAGS += -g -std=c++1y

TARGET  = PlotCustomMrRsq
TARGET2 = PlotFromTree
TARGET3 = PlotFromInclusiveTree
TARGET11 = PlotTwoSamples
TARGET10 = MakeZeeCRPlots
TARGET4 = GetHggRazorSystematics
TARGET5 = GetHggRazorSystematicsQuadrature 
TARGET6 = GetHggRazorSMH_BkgTable 
TARGET7 = GetHggRazorSMHeff
TARGET8 = GetHggRazorSMH_BkgTableVar
#TARGETA = CalStyleRemix
#TARGETB = CompareHggMC
TARGET9 = CompareHggVariables
TARGET12 = GetSigmaMoverM_Correction
TARGET13 = GetHggRazorSystematicsQuadratureFaster
TARGET14 = GetHggRazorPull
TARGET15 = GetHggLeptonRazorSMH_BkgTable 
TARGET16 = copyTree

SRC = app/PlotCustomMrRsq.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc
SRC2 = app/PlotFromTree.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc
SRC3 = app/PlotFromInclusiveTree.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc
SRC11 = app/PlotTwoSamples.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc
SRC10 = app/MakeZeeCRPlots.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc
SRC4 = app/GetHggRazorSystematics.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc
SRC5 = app/GetHggRazorSystematicsQuadrature.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc
SRC6 = app/GetHggRazorSMH_BkgTable.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(FitTools)/src/DefinePdfs.cc
SRC7 = app/GetHggRazorSMHeff.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(FitTools)/src/DefinePdfs.cc
SRC8 = app/GetHggRazorSMH_BkgTableVar.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(FitTools)/src/DefinePdfs.cc
#SRCA =src/CalStyleRemix.cc
#SRCB =src/CompareHggMC.cc src/CalStyleRemix.cc
SRC9 = app/CompareHggVariables.cc src/CompareHggMC.cc src/CalStyleRemix.cc
SRC12 = app/GetSigmaMoverM_Correction.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc
SRC13 = app/GetHggRazorSystematicsQuadratureFaster.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc
SRC14 = app/GetHggRazorPullTable.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(FitTools)/src/DefinePdfs.cc
SRC15 = app/GetHggLeptonRazorSMH_BkgTable.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(FitTools)/src/DefinePdfs.cc
SRC16 = app/copyTree.cc

OBJ  = $(SRC:.cc=.o)
	OBJ2 = $(SRC2:.cc=.o)
OBJ3 = $(SRC3:.cc=.o)
	OBJ11 = $(SRC11:.cc=.o)
OBJ10 = $(SRC10:.cc=.o) 
	OBJ4 = $(SRC4:.cc=.o)
OBJ5 = $(SRC5:.cc=.o)
	OBJ6 = $(SRC6:.cc=.o)
OBJ7 = $(SRC7:.cc=.o)
	OBJ8 = $(SRC8:.cc=.o)
	#OBJA = $(SRCA:.cc=.o) 
	#OBJB = $(SRCB:.cc=.o) 
OBJ9 = $(SRC9:.cc=.o) 
	OBJ12 = $(SRC12:.cc=.o)
OBJ13 = $(SRC13:.cc=.o)
	OBJ14 = $(SRC14:.cc=.o)
OBJ15 = $(SRC15:.cc=.o)
OBJ16 = $(SRC16:.cc=.o)

all : $(TARGET) $(TARGET2) $(TARGET3) $(TARGET12) $(TARGET11) $(TARGET10) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGETA) $(TARGETB) $(TARGET9) $(TARGET13) $(TARGET14) $(TARGET15) $(TARGET16)

#comp : $(TARGETA) $(TARGETB) $(TARGET9)
comp : $(TARGET9)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
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

$(TARGET11) : $(OBJ11)
		$(LD) $(CPPFLAGS) -o $(TARGET11) $(OBJ11) $(LDFLAGS)
			@echo $@
				@echo $<
					@echo $^

$(TARGET10) : $(OBJ10)
		$(LD) $(CPPFLAGS) -o $(TARGET10) $(OBJ10) $(LDFLAGS)
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

$(TARGET14) : $(OBJ14) 
		$(LD) $(CPPFLAGS) -o $(TARGET14) $(OBJ14) $(LDFLAGS)
			@echo $@
				@echo $<
					@echo $^

$(TARGET15) : $(OBJ15) 
		$(LD) $(CPPFLAGS) -o $(TARGET15) $(OBJ15) $(LDFLAGS)
			@echo $@
				@echo $<
					@echo $^


$(TARGET16) : $(OBJ16)
	$(LD) $(CPPFLAGS) -o $(TARGET16) $(OBJ16) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
		$(CXX) $(CPPFLAGS) -o $@ -c $<
			@echo $@
				@echo $<
clean :
	rm -f *.o app/*.o src/*.o $(Selection)/src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET) $(TARGET2) $(TARGET3) $(TARGET10) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGETA) $(TARGETB) $(TARGET11) $(TARGET12) $(TARGET13) $(TARGET14) $(TARGET15) $(TARGET16) *~
