# This file is part of Mongoose project, http://code.google.com/p/mongoose
# $Id: Makefile 473 2009-09-02 11:20:06Z valenok $

PROG=	uGuru

#all: 
#	@echo "make (linux|bsd|solaris|mac|windows|mingw)"

all : mingw

# Possible COPT values: (in brackets are rough numbers for 'gcc -O2' on i386)
# -DHAVE_MD5		- use system md5 library (-2kb)
# -DNDEBUG		- strip off all debug code (-5kb)
# -DDEBUG		- build debug version (very noisy) (+7kb)
# -DNO_CGI		- disable CGI support (-5kb)
# -DNO_SSL		- disable SSL functionality (-2kb)
# -DCONFIG_FILE=\"file\" - use `file' as the default config file
# -DHAVE_STRTOUI64	- use system strtoui64() function for strtoull()



##########################################################################
###                 UNIX build: linux, bsd, mac, rtems
##########################################################################

CFLAGS=		-g -W -Wall -std=c99 -pedantic -O2 -fomit-frame-pointer $(COPT)
CXXFLAGS=       -g -W -Wall -pedantic -O2 -fomit-frame-pointer $(COPT)
MAC_SHARED=	-flat_namespace -bundle -undefined suppress
LINFLAGS=	-ldl -pthread -lcurl $(CFLAGS)
LIB=		_$(PROG).so

linux:
	gcc -c $(CFLAGS) src/mongoose.c src/main.c -I./include
	gcc -c $(CFLAGS) src/download.c -I./include -DCURL_STATICLIB
	g++ -c $(CXXFLAGS) src/*.cpp -Itinyxml -I./include
	g++ -c $(CXXFLAGS) -Wno-format tinyxml/*.cpp -Itinyxml
	g++ $(LINFLAGS)	*.o -o $(PROG).exe -lcurl

bsd:
	$(CC) $(CFLAGS) mongoose.c -shared -pthread -fpic -fPIC -o $(LIB)
	$(CC) $(CFLAGS) mongoose.c main.c -pthread -o $(PROG)

mac:
	$(CC) $(CFLAGS) $(MAC_SHARED) mongoose.c -pthread -o $(LIB)
	$(CC) $(CFLAGS) mongoose.c main.c -pthread -o $(PROG)

solaris:
	gcc $(CFLAGS) mongoose.c -pthread -lnsl \
		-lsocket -fpic -fPIC -shared -o $(LIB)
	gcc $(CFLAGS) mongoose.c main.c -pthread -lnsl -lsocket -o $(PROG)


##########################################################################
###            WINDOWS build: Using Visual Studio or Mingw
##########################################################################

# Using Visual Studio 6.0. To build Mongoose:
#  o  Set VC variable below to where VS 6.0 is installed on your system
#  o  Run "PATH_TO_VC6\bin\nmake windows"

VC=	z:
CYA=	y:
#DBG=	/Zi /DDEBUG /Od
DBG=	/DNDEBUG /O1
CL=	cl /MD /TC /nologo $(DBG) /Gz /W3 /DNO_SSL_DL
GUILIB=	user32.lib shell32.lib
LINK=	/link /incremental:no /libpath:$(VC)\lib /subsystem:windows \
	ws2_32.lib advapi32.lib cyassl.lib

CYAFL=	/c /I $(CYA)\ctaocrypt\include /I $(CYA)\include /D_LIB

CYASRC= $(CYA)/src/cyassl_int.c \
	$(CYA)/src/cyassl_io.c \
	$(CYA)/src/keys.c \
	$(CYA)/src/tls.c \
	$(CYA)/ctaocrypt/src/aes.c \
	$(CYA)/ctaocrypt/src/arc4.c \
	$(CYA)/ctaocrypt/src/asn.c \
	$(CYA)/ctaocrypt/src/des3.c \
	$(CYA)/ctaocrypt/src/dh.c \
	$(CYA)/ctaocrypt/src/dsa.c \
	$(CYA)/ctaocrypt/src/hc128.c \
	$(CYA)/ctaocrypt/src/hmac.c \
	$(CYA)/ctaocrypt/src/integer.c \
	$(CYA)/ctaocrypt/src/md4.c \
	$(CYA)/ctaocrypt/src/md5.c \
	$(CYA)/ctaocrypt/src/misc.c \
	$(CYA)/ctaocrypt/src/rabbit.c \
	$(CYA)/ctaocrypt/src/random.c \
	$(CYA)/ctaocrypt/src/ripemd.c \
	$(CYA)/ctaocrypt/src/rsa.c \
	$(CYA)/ctaocrypt/src/sha.c \
	$(CYA)/ctaocrypt/src/sha256.c

cyassl:
	$(CL) $(CYA)/src/ssl.c $(CYA)/ctaocrypt/src/coding.c \
		$(CYAFL) /DOPENSSL_EXTRA
	$(CL) $(CYASRC) $(CYAFL)
	lib *.obj /out:cyassl.lib

windows:
	rc res\res.rc
	$(CL) main.c mongoose.c /GA $(LINK) win32\res.res \
		$(GUILIB) /out:$(PROG).exe
	$(CL) mongoose.c /GD $(LINK) /DLL /DEF:win32\dll.def /out:_$(PROG).dll

# Build for Windows under MinGW
MINGWDBG= -DDEBUG -O0 -g -DHAVE_STDINT
#MINGWDBG= -DNDEBUG -Os
#MINGWOPT= -W -Wall -mthreads -Wl,--subsystem,console $(MINGWDBG) -DHAVE_STDINT
MINGWOPT= -W -Wall -mthreads -Wl,--subsystem,windows $(MINGWDBG)



mingw:
	windres res\res.rc res\res.o
#	gcc $(MINGWOPT) src\mongoose.c -lws2_32 \
#		-shared -Wl,--out-implib=$(PROG).dll.a -o _$(PROG).dll -Isrc
	gcc -c $(MINGWOPT) src\mongoose.c src\main.c -I./include
	gcc -c $(MINGWOPT) src\download.c -I./include -Iwinhttp
	g++ -c $(MINGWOPT) src/*.cpp -Itinyxml -I./include
	g++ -c $(MINGWOPT) tinyxml/*.cpp -Itinyxml
	g++ $(MINGWOPT)	*.o res\res.o -lws2_32 -ladvapi32 -Lwinhttp -lwinhttp -o $(PROG).exe 

##########################################################################
###            Manuals, cleanup, test, release
##########################################################################

man:
	groff -man -T ascii mongoose.1 | col -b > mongoose.txt
	groff -man -T ascii mongoose.1 | less

# "TEST=unit make test" - perform unit test only
# "TEST=embedded" - test embedded API by building and testing test/embed.c
# "TEST=basic_tests" - perform basic tests only (no CGI, SSI..)
test: do_test
do_test:
	perl test/test.pl $(TEST)

release: clean
	F=mongoose-`perl -lne '/define\s+MONGOOSE_VERSION\s+"(\S+)"/ and print $$1' mongoose.c`.tgz ; cd .. && tar --exclude \*.hg --exclude \*.svn --exclude \*.swp --exclude \*.nfs\* --exclude win32 -czf x mongoose && mv x mongoose/$$F

clean:
	rm -rf *.o *.core $(PROG) *.obj $(PROG).txt *.dSYM *.tgz *.exe
