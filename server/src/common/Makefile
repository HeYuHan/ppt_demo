CC = g++-4.8
AR = ar
CFLAGS = -c -fPIC -I. -I../3rd/libevent/build/linux/include --std=c++11

ifdef RELEASE
	CFLAGS += -Wall -Werror -g -O2
else
	CFLAGS += -Wall -Werror -g -DDEBUG
endif

TARGET = ../lib/libcommon.a

LIB_EVENT = $(wildcard ../3rd/libevent/build/linux/lib/*a)

SOURCES = $(wildcard *.cpp) $(wildcard network/*.cpp)

OBJS = $(SOURCES:%.cpp=objs/%.o) $(LIB_EVENT)
DEPS = $(SOURCES:%.cpp=objs/%.d)

default : $(TARGET)
rebuild : clean default

objs/%.d: %.cpp
	@$(CC) -MM $(CFLAGS) $< | sed 's,\($*\)\.o[ :]*,objs/\1.o $@ : ,g' >$@

objs/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

-include $(DEPS)

clean :
	rm -rf $(TARGET) objs/*.d objs/*.o objs/network/*
	
$(TARGET) : $(OBJS)
	$(AR) rcs $@ $(OBJS)

