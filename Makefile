TARGET = demo

OBJS = $(sort \
	   $(patsubst %.cpp,%.o,$(wildcard Src/*.cpp)) \
	   $(patsubst %.c,%.o,$(wildcard Src/*.c)))

include Makefile.include 
