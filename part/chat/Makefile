PROG=	chat.exe
#CFLAGS=	-W -Wall -I.. -pthread -g
CFLAGS=	-W -Wall -I.. -g

all:
	  $(CC) $(CFLAGS) chat.c -o $(PROG) \
		-I.. -ID:\GS\MinGW\ThirdParty\pthread\include -DHAVE_STDINT -lws2_32 \
		-LD:\GS\MinGW\ThirdParty\pthread\lib -lpthreadGC2 ../mongoose.lib
#	./$(PROG)