# PRODUCE_REPORTS = 1 
# USE_GUIDE = 1
# GENERATE_PROFILE = 1 
# USE_PROFILE = 1
# DEBUG_MODE = 1

include gcc.mk

ROOTDIR = .
INCLUDEDIR = $(ROOTDIR)/include
LIBDIR = $(ROOTDIR)/lib
SRCDIR = $(ROOTDIR)/src
MEXDIR = $(ROOTDIR)/mexfiles
BINDIR = $(ROOTDIR)/bin
INCLUDES += -I$(INCLUDEDIR)

all: tests camera filter
	
tests: $(MEXDIR)/temp_mex.$(MEXEXT)

camera: $(MEXDIR)/nuanceget.$(MEXEXT) $(MEXDIR)/nuanceset.$(MEXEXT) \
		$(MEXDIR)/nuancequery.$(MEXEXT) $(MEXDIR)/nuancecheck.$(MEXEXT) \
		$(MEXDIR)/nuanceopen.$(MEXEXT) $(MEXDIR)/nuanceclose.$(MEXEXT)

filter: $(MEXDIR)/filterget.$(MEXEXT) $(MEXDIR)/filterset.$(MEXEXT) \
		$(MEXDIR)/filterquery.$(MEXEXT) $(MEXDIR)/filtercheck.$(MEXEXT) \
		$(MEXDIR)/filteropen.$(MEXEXT) $(MEXDIR)/filterclose.$(MEXEXT)

## test mex executable 
$(MEXDIR)/%.$(MEXEXT): $(MEXDIR)/%.o $(SRCDIR)/nuancefx_mex.o  
	$(CC) $(LDFLAGS) -o $@ $^

# mex object files
$(MEXDIR)/%.o: $(MEXDIR)/%.cpp $(INCLUDEDIR)/nuancefx_mex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	
# src object files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	
clean:	
	rm -rf *.o *~
	rm -rf $(MEXDIR)/*.o $(MEXDIR)/*~
	rm -rf $(SRCDIR)/*.o $(SRCDIR)/*~
	rm -rf $(LIBDIR)/*.o $(LIBDIR)/*~

distclean:	
	rm -rf *.o *~
	rm -rf $(MEXDIR)/*.o $(MEXDIR)/*.$(MEXEXT) $(MEXDIR)/*~
	rm -rf $(SRCDIR)/*.o $(SRCDIR)/*~
	rm -rf $(LIBDIR)/*.o $(LIBDIR)/*~ $(LIBDIR)/*.so*
