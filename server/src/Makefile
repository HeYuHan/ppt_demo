CC = g++
CFLAGS = -c  --std=c++11 -I.
LFLAGS = -m64 -ldl

EVENT_LIB = $(wildcard 3rd/libevent/.libs/*.a) -lrt
INCLUED_EVENT= -I3rd/libevent/include

#mac
ifeq ($(shell uname), Darwin)
	EVENT_LIB = $(wildcard /usr/local/Cellar/libevent/2.1.8/lib/*.a)
	INCLUED_EVENT = -I/usr/local/Cellar/libevent/2.1.8/include
endif

CFLAGS += $(INCLUED_EVENT)

ifdef RELEASE
	CFLAGS += -Wall -Werror -g -O2
	LFLAGS += -Wall -Werror -g -O2
else
	CFLAGS += -g -DDEBUG
	LFLAGS += -g
endif





LIB=$(wildcard lib/*.a) $(EVENT_LIB)

TARGET = ../bin/test_server
SOURCES = $(wildcard *.cpp)



OBJS = $(SOURCES:%.cpp=objs/%.o) $(LIB)
DEPS = $(SOURCES:%.cpp=objs/%.d)

default : $(TARGET)
rebuild : clean default

objs/%.d: %.cpp | dircheck
	$(MAKE) -C common
	@$(CC) -MM $(CFLAGS) $< | sed 's,\($*\)\.o[ :]*,objs/\1.o $@ : ,g' >$@

objs/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

dircheck:
	python checkdir.py

-include $(DEPS)

clean :
	$(MAKE) clean -C common
	rm -rf $(TARGET) objs/*
	
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS) 
