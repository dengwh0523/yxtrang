CFLAGS += -O3 $(DBG) -Wall -D_BSD_SOURCE
CFLAGS += -I/usr/local/include -D_REENTRANT    # BSDs want this

OBJECTS = base64.o daemon.o httpserver.o json.o jsonq.o \
			linda.o list.o network.o rational.o scriptlet.o \
			skiplist.o store.o thread.o tree.o uncle.o uuid.o

all: $(OBJECTS) yxtrang.a

yxtrang.a: $(OBJECTS)
	ar -r yxtrang.a $(OBJECTS)
	ranlib yxtrang.a

clean:
	rm -f *.o *.a

# DO NOT DELETE

base64.o: base64.h
daemon.o: daemon.h
httpserver.o: httpserver.h network.h
json.o: json.h
jsonq.o: jsonq.h
linda.o: linda.h skiplist.h skiplist_uuid.h store.h json.h uuid.h
list.o: list.h
network.o: network.h skiplist.h skiplist_int.h skiplist_string.h thread.h uncle.h
rational.o: rational.h
scriptlet.o: scriptlet.h skiplist.h skiplist_string.h
skiplist.o: skiplist.h
store.o: store.h uuid.h tree.h thread.h
thread.o: thread.h
tree.o: tree.h uuid.h
uncle.o: uncle.h jsonq.h network.h skiplist.h skiplist_string.h thread.h
uuid.o: uuid.h
