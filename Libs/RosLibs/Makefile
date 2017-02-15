OBJS = $(sort \
	   $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

LIB = libros.a

${LIB}:${OBJS}
	${AR} -rcs libros.a $@ ${OBJS}


include ../../Makefile.include

