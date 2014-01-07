

MATLABDIR = "/cygdrive/c/Program Files (x86)/MATLAB/R2013b"
NUANCEDIR = "/cygdrive/c/Program Files (x86)/CRi/MSI_API_1.0.0/"

MATLABARCH = win32
MEXEXT = $(shell $(MATLABDIR)/bin/mexext.bat)

#MATLABLIBS = -L$(MATLABDIR)/bin/$(MATLABARCH) -lmx -lmex -lmat
MATLABLIBS = -L$(MATLABDIR)/bin/$(MATLABARCH) -lmex -lmx -lmwlapack -lmwblas 
#NUANCELIBS = 
ifdef DEBUG_MODE
	NUANCELIBS = -L$(NUANCEDIR)/bin/Debug/ -lCriMsiAPI-1_00D
else
	NUANCELIBS = -L$(NUANCEDIR)/bin/Release/ -lCriMsiAPI-1_00
endif
MAPFILE = $(MATLABDIR)/extern/lib/$(MATLABARCH)/mex.def
#MAPFILE = mex.def

MATLABINCLUDE = -I$(MATLABDIR)/extern/include
NUANCEINCLUDE = -I$(NUANCEDIR)/include
INCLUDES = $(MATLABINCLUDE) $(NUANCEINCLUDE)

#CC = x86_64-w64-mingw32-g++
CC = i686-w64-mingw32-g++
MEXFLAGS = -DMX_COMPAT_32 -fexceptions
GENERALFLAGS = -W -Wall -Wextra -pedantic
OPTIMFLAGS = -O3
REPORTSFLAGS = -Winline -Wimplicit
DEBUGFLAG = -g
ifdef DEBUG_MODE
	CFLAGS = $(DEBUGFLAG) $(MEXFLAGS) $(GENERALFLAGS) $(OPTIMFLAGS) 
else
	CFLAGS = $(MEXFLAGS) $(GENERALFLAGS) $(OPTIMFLAGS)
	ifdef PRODUCE_REPORTS
		CFLAGS += $(REPORTSFLAGS) 
	endif
endif 

LDFLAGS = -O3 -static-libgcc -static-libstdc++ -shared $(MAPFILE) $(MATLABLIBS) $(NUANCELIBS)  