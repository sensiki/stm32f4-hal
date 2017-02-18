TARGET = demo

OBJS = $(sort \
	   $(patsubst %.cpp,%.o,$(wildcard Hardware/*.cpp)) \
	   $(patsubst %.c,%.o,$(wildcard Hardware/*.c)) \
	   $(patsubst %.cpp,%.o,$(wildcard Src/*.cpp)) \
	   $(patsubst %.c,%.o,$(wildcard System/*.c)) \
	   $(patsubst %.c,%.o,$(wildcard Src/*.c)))

include Makefile.include 
