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

LDFLAGS += -O3 -static-libgcc -static-libstdc++
