SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic

#------------------------------------------------------------
#
# When you adapt this makefile to compile your CPLEX programs
# please copy this makefile and set CPLEXDIR and CONCERTDIR to
# the directories where CPLEX and CONCERT are installed.
#
#------------------------------------------------------------

CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio2211/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio2211/concert

# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++
CC  = gcc
JAVAC = javac 

# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -O2 -fopenmp
COPT  = -m64 -fPIC
JOPT  = -classpath $(CPLEXDIR)/lib/cplex.jar -O

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXJARDIR   = $(CPLEXDIR)/lib/cplex.jar
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

# For dynamic linking
CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIB      = cplex$(dynamic:yes=2211)
run           = $(dynamic:yes=LD_LIBRARY_PATH=$(CPLEXBINDIR))

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR) $(dynamic:yes=-L$(CPLEXBINDIR))
CLNDIRS   = -L$(CPLEXLIBDIR) $(dynamic:yes=-L$(CPLEXBINDIR))
CCLNFLAGS = -lconcert -lilocplex -l$(CPLEXLIB) -lm -lpthread -ldl
CLNFLAGS  = -l$(CPLEXLIB) -lm -lpthread -ldl
JAVA      = java   -Djava.library.path=$(CPLEXDIR)/bin/x86-64_linux -classpath $(CPLEXJARDIR):


CONCERTINCDIR = $(CONCERTDIR)/include/
CPLEXINCDIR   = $(CPLEXDIR)/include/

EXDIR         = $(CPLEXDIR)/examples
EXINC         = $(EXDIR)/include
EXDATA        = $(EXDIR)/data
EXSRCC        = $(EXDIR)/src/c
EXSRCCX       = $(EXDIR)/src/c_x
EXSRCCPP      = $(EXDIR)/src/cpp
EXSRCJAVA     = $(EXDIR)/src/java

CFLAGS  = $(COPT)  -I$(CPLEXINCDIR)
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 
JCFLAGS = $(JOPT)


#------------------------------------------------------------
#  make all      : to compile the examples. 
#  make execute  : to compile and execute the examples.
#------------------------------------------------------------


C_EX = lpex1 lpex2 lpex3 lpex4 lpex5 lpex6 lpex7 lpex8 \
       mipex1 mipex2 mipex3 mipex4 miqpex1 multiobjex1 netex1 netex2 \
       qcpex1 qpex1 qpex2 indefqpex1 globalqpex1 globalmiqpex1 \
       steel diet fixnet foodmanu adpreex1 \
       admipex1 admipex2 admipex3 admipex4 admipex5 admipex6 admipex7 \
       admipex8 admipex9 populate transport tuneset \
       benders bendersatsp bendersatsp2 conflictex1 \
       socpex1 qcpdual genericbranch genericbranchpi

CX_EX = xlpex1 xlpex2 xlpex3 xlpex4 xlpex5 xlpex6 xlpex7 xlpex8 \
       xmipex1 xmipex2 xmipex3 xmipex4 xmiqpex1 xmultiobjex1 xnetex1 xnetex2 \
       xqcpex1 xqpex1 xqpex2 xindefqpex1 xglobalqpex1 xglobalmiqpex1 \
       xsteel xdiet xfixnet xfoodmanu xadpreex1 \
       xadmipex1 xadmipex2 xadmipex3 xadmipex4 xadmipex5 xadmipex6 xadmipex7 \
       xadmipex8 xadmipex9 xpopulate xtransport xtuneset \
       xbenders xbendersatsp xbendersatsp2 xconflictex1 \
       xsocpex1 xqcpdual xgenericbranch xgenericbranchpi

CPP_EX = blend cutstock etsp facility fixcost1 foodmanufact \
         iloadmipex1 iloadmipex2 iloadmipex3 iloadmipex4 \
         iloadmipex5 iloadmipex6 iloadmipex8 iloadmipex9 \
         iloindefqpex1 iloglobalqpex1 iloconflictex1 ilodiet ilofixnet \
         ilolpex1 ilolpex2 ilolpex3 ilolpex4 ilolpex6 ilolpex7 \
         ilomipex1 ilomipex2 ilomipex3 ilomipex4 ilomiqpex1 ilomultiobjex1 \
         ilogoalex1 ilogoalex2 ilogoalex3 iloqcpex1 iloqpex1 iloqpex2 \
         iloqpex3 inout1 inout3 mixblend rates ilotransport ilosteel \
         warehouse ilopopulate ilotuneset ilobenders ilobendersatsp \
         ilobendersatsp2 ilosocpex1 iloqcpdual ilogenericbranch

JAVA_EX = Blend.class MixBlend.class ConflictEx1.class CutStock.class Diet.class \
          Etsp.class Facility.class FixCost1.class FixNet.class \
          FoodManufact.class InOut1.class InOut3.class \
          Rates.class Steel.class Transport.class \
          LPex1.class LPex2.class LPex3.class LPex4.class \
          LPex6.class LPex7.class IndefQPex1.class GlobalQPex1.class \
          MIPex1.class MIPex2.class MIPex3.class MIPex4.class MIQPex1.class MultiObjEx1.class \
          AdMIPex1.class AdMIPex2.class AdMIPex3.class \
          AdMIPex4.class AdMIPex5.class AdMIPex6.class AdMIPex8.class AdMIPex9.class\
          QCPex1.class \
          QPex1.class QPex2.class QPex3.class Goalex1.class Goalex2.class \
          TuneSet.class Benders.class BendersATSP.class BendersATSP2.class \
          Goalex3.class Populate.class Warehouse.class CplexServer.class \
          SocpEx1.class QCPDual.class GenericBranch.class


program.exe: main.o MetricDimension.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) main.o MetricDimension.o -o program.exe $(CCLNFLAGS)

main.o: main.cc
	$(CCC) -c $(CCFLAGS) main.cc 
MetricDimension.o: MetricDimension.hh MetricDimension.cc
	$(CCC) -c $(CCFLAGS) $(CCLNDIRS) MetricDimension.cc 



default: $(file).o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o program $(file).o $(CCLNFLAGS)
$(file).o: $(file).cc
	$(CCC) -c $(CCFLAGS) $(file).cc -o $(file).o



execute_c: $(C_EX) $(CX_EX)
	$(run) ./indefqpex1
	

execute_cpp: $(CPP_EX)
	$(run) ./blend
	
execute_java: $(JAVA_EX)
	 $(JAVA) Goalex1 $(EXDATA)/mexample.mps
	 $(JAVA) Goalex2
	 
# ------------------------------------------------------------

clean :
	/bin/rm -rf *.o *~ *.class
	/bin/rm -rf $(C_EX) $(CX_EX) $(CPP_EX)
	/bin/rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log *.clp

# ------------------------------------------------------------
#
# The examples
#
indefqpex1: indefqpex1.o
	$(CC) $(CFLAGS) $(CLNDIRS) -o indefqpex1 indefqpex1.o $(CLNFLAGS)
indefqpex1.o: $(EXSRCC)/indefqpex1.c
	$(CC) -c $(CFLAGS) $(EXSRCC)/indefqpex1.c -o indefqpex1.o
	
	
blend: blend.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o blend blend.o $(CCLNFLAGS)
blend.o: $(EXSRCCPP)/blend.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/blend.cpp -o blend.o

IndefQPex1.class: $(EXSRCJAVA)/IndefQPex1.java
	$(JAVAC) $(JCFLAGS) -d . $(EXSRCJAVA)/IndefQPex1.java 


# Local Variables:
# mode: makefile
# End:
