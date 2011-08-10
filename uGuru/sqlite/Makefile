#
CC = gcc
CXX = g++
MAKE = make
RM   = -rm -vf
#
%.o : %.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCS)

#
#include $(TOPDIR)/make.inc

#
CFLAGS +=
CXXFLAGS +=
INCS +=
LIBS += -L. -lsqlite3

#
OBJ = test_sqlite.o
BIN = test_sqlite.exe
RC  = 
RES = ${RC:.rc=.res}
#
HEADER =
#
all: $(BIN)

#
$(BIN) : $(OBJ) $(RES)
	$(CXX) -o $(BIN) $^ $(LIBS)

#
.PHONY : test
test :
	$(WINE) $(BINDIR)/$(BIN)
#
clean :
	$(RM) ${OBJ} ${RES} ${BIN}
