MATLABDIR = "/cygdrive/c/Program Files (x86)/MATLAB/R2013b"

MATLABARCH = win32
MEXEXT = $(shell $(MATLABDIR)/bin/mexext.bat)

#MATLABLIBS = -L$(MATLABDIR)/bin/$(MATLABARCH) -lmx -lmex -lmat
MATLABLIBS = -L$(MATLABDIR)/bin/$(MATLABARCH) -lmex -lmx -lmwlapack -lmwblas 
MAPFILE = $(MATLABDIR)/extern/lib/$(MATLABARCH)/mex.def
#MAPFILE = mex.def

MATLABINCLUDE = -I$(MATLABDIR)/extern/include
INCLUDES += $(MATLABINCLUDE)
LDFLAGS += -shared $(MAPFILE) $(MATLABLIBS)

