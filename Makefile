OPT:=
KIND:=

CXX = u++										# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD ${OPT}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q1student.o q1bank.o q1configparams.o q1main.o
EXEC1 = soda

OBJECTS = ${OBJECTS1}				# all object files
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2}						# all executables

.PHONY : all clean

all : ${EXECS}									# build all executables

#############################################################

${EXEC1} : ${OBJECTS1}							# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################
${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :											# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType
