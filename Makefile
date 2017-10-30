P=ramutils
OBJECTS=ram-str.o
HEADERS=ram-err.h ram-str.h
CFLAGS = -g -Wall -std=c11 -pedantic -O3 `pkg-config --cflags ramutils`
LDLIBS = `pkg-config --cflags ramutils`
DESTDIR=$(HOME)/opt

# just for testing, move down afterwards
check: test-ram-str
	./test-ram-str

all: shared static

shared: lib$(P).so
static: lib$(P).a

lib$(P).so: $(OBJECTS)
	$(CC) -shared -o lib$(P).so $(OBJECTS)

lib$(P).a: $(OBJECTS)
	ar rcs lib$(P).a $(OBJECTS)

test-ram-str: test-ram-str.o

clean:
	rm -f $(OBJECTS) lib$(P).so lib$(P).a test-ram-str.o test-ram-str

install: all
	cp -f $(HEADERS) $(DESTDIR)/include
	cp -f lib$(P).so lib$(P).a $(DESTDIR)/lib
	cp -f $(P).pc $(DESTDIR)/lib/pkgconfig
	sed -i "s#HOME#$(HOME)#g" $(DESTDIR)/lib/pkgconfig/$(P).pc

.-PHONY: check clean shared static install all
