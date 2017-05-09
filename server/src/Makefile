CC = g++
CFLAGS = -c  --std=c++11 -I.
LFLAGS = -m64 -ldl

ifdef RELEASE
	CFLAGS += -Wall -Werror -g -O2
	LFLAGS += -Wall -Werror -g -O2
else
	CFLAGS += -g -DDEBUG
	LFLAGS += -g
endif

EVENT_LIB = $(wildcard ../3rd/libevent/build/linux/lib/*a)
INCLUED_EVENT= 

ifdef LINUX
	EVENT_LIB = $(wildcard ../3rd/libevent/build/linux/lib/*a)
	INCLUED_EVENT = -I../3rd/libevent/build/linux/include
endif

ifdef MAC
	EVENT_LIB = $(wildcard /usr/local/Cellar/libevent/2.1.8/lib/*a)
	INCLUED_EVENT = -I/usr/local/Cellar/libevent/2.1.8/include
endif

CFLAGS += $(INCLUED_EVENT)

LIB=$(wildcard lib/*.a) $(EVENT_LIB)

TARGET = ../bin/test_server
SOURCES = $(wildcard *.cpp)



OBJS = $(SOURCES:%.cpp=objs/%.o) $(LIB)
DEPS = $(SOURCES:%.cpp=objs/%.d)

default : $(TARGET)
rebuild : clean default

objs/%.d: %.cpp
	@$(CC) -MM $(CFLAGS) $< | sed 's,\($*\)\.o[ :]*,objs/\1.o $@ : ,g' >$@

objs/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

-include $(DEPS)

clean :
	rm -f $(TARGET) objs/*
	
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS) 
