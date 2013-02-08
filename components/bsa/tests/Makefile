GCC=g++

all: bsa_file_test bsatool ogre_archive_test

I_OGRE=$(shell pkg-config --cflags OGRE)
L_OGRE=$(shell pkg-config --libs OGRE)
INC=-I../../.. $(I_OGRE)
LIB=$(L_OGRE) -lboost_system -lboost_filesystem

bsa_file_test: bsa_file_test.cpp ../bsa_file.cpp ../../files/constrainedfiledatastream.cpp ../../files/lowlevelfile.cpp
	$(GCC) $^ -o $@ $(INC) $(LIB)

ogre_archive_test: ogre_archive_test.cpp ../bsa_file.cpp ../bsa_archive.cpp ../../files/constrainedfiledatastream.cpp ../../files/lowlevelfile.cpp
	$(GCC) $^ -o $@ $(INC) $(LIB)

bsatool: bsatool.cpp bsatool_cmd.c ../bsa_file.cpp ../../files/constrainedfiledatastream.cpp ../../files/lowlevelfile.cpp
	$(GCC) $^ -o $@ $(INC) $(LIB)

bsatool_cmd.c: bsatool.ggo
	gengetopt < bsatool.ggo

clean:
	rm *_test
	rm bsatool
