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

EVENT_LIB = $(wildcard ../3rd/libevent/.libs/*.a) -lrt
PROTO_LIB = $(wildcard ../3rd/protobuf-2.6.1/src/.libs/*.a)
EVENT_INCLUDE = -I../3rd/libevent/include
PROTO_INCLUDE = -I../3rd/protobuf-2.6.1/src

COMMON_LIB = $(wildcard ../lib/*.a) 

#mac
ifeq ($(shell uname), Darwin)
	EVENT_LIB = $(wildcard /usr/local/Cellar/libevent/2.1.8/lib/*.a)
	EVENT_INCLUDE = -I/usr/local/Cellar/libevent/2.1.8/include
endif

ALL_INCLUDE = $(EVENT_INCLUDE) $(PROTO_INCLUDE)
ALL_LIB = $(EVENT_LIB) $(PROTO_LIB) $(COMMON_LIB)

CFLAGS += $(ALL_INCLUDE)

TARGET = ../bin/test_server
SOURCES = $(wildcard *.cpp)



OBJS = $(SOURCES:%.cpp=objs/%.o) $(ALL_LIB)
DEPS = $(SOURCES:%.cpp=objs/%.d)

default : $(TARGET)
rebuild : clean default

objs/%.d: %.cpp|checkdir
	$(MAKE) -C common
	@$(CC) -MM $(CFLAGS) $< | sed 's,\($*\)\.o[ :]*,objs/\1.o $@ : ,g' >$@

objs/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<
	
checkdir:
	python ../checkdir.py

-include $(DEPS)

clean :
	$(MAKE) clean -C common
	rm -rf $(TARGET) objs/*
	
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS) 
