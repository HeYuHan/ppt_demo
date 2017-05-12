CC = g++
AR = ar
CFLAGS = -c -fPIC -I. --std=c++11

ifdef RELEASE
	CFLAGS += -Wall -Werror -g -O2
else
	CFLAGS += -Wall -Werror -g -DDEBUG
endif

EVENT_LIB = $(wildcard ../3rd/libevent/*.a)
INCLUED_EVENT= -I../3rd/libevent/include

#mac
ifeq ($(shell uname), Darwin)
	EVENT_LIB = $(wildcard /usr/local/Cellar/libevent/2.1.8/lib/*a)
	INCLUED_EVENT = -I/usr/local/Cellar/libevent/2.1.8/include
endif

CFLAGS += $(INCLUED_EVENT)

TARGET = ../lib/libcommon.a



SOURCES = $(wildcard *.cpp) $(wildcard network/*.cpp)

OBJS = $(SOURCES:%.cpp=objs/%.o) $(EVENT_LIB)
DEPS = $(SOURCES:%.cpp=objs/%.d)


default : $(TARGET)
rebuild : clean default


objs/%.d: %.cpp | dircheck
	@$(CC) -MM $(CFLAGS) $< | sed 's,\($*\)\.o[ :]*,objs/\1.o $@ : ,g' >$@

objs/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

dircheck:
	python ../checkdir.py

-include $(DEPS)


clean :
	rm -rf $(TARGET) objs

	
$(TARGET) : $(OBJS)
	$(AR) rcs $@ $(OBJS)

