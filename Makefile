SYSTEM = x86-64_linux
LIBFORMAT = static_pic

CPLEXDIR = ../../../../../opt/ibm/ILOG/CPLEX_Studio128/cplex
CONCERTDIR = ../../../../../opt/ibm/ILOG/CPLEX_Studio128/concert

CCC = g++ -O0
CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

CPLEXLIBDIR = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CCLNDIRS = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)
CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -lpthread -ldl

CPP_EX = blend

all: $(CPP_EX)

execute: $(CPP_EX) ./blend

blend: blend.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o blend blend.o $(CCLNFLAGS)
blend.o: blend.cpp
	$(CCC) -c $(CCFLAGS) blend.cpp -o blend.o