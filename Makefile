# To build with a specific architecture, set the ARCH flag on the make command line like this:
# make ARCH=i386
# or
# make ARCH=x86_64

CFLAGS=-g -Wall -Werror

ifdef ARCH
LDFLAGS+=-arch ${ARCH}
CFLAGS+=-arch ${ARCH}
endif

all: 
	rm -rf build
	python setup.py build
	cp build/lib.linux-x86_64-2.7/pyhuffman.so .

install:
	cp pyhuffman.so /usr/lib/python2.7/

uninstall:
	rm /usr/lib/python2.7/pyhuffman.so

clean:
	$(RM) -rf build *.so *.o
