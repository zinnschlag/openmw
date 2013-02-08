GXX=g++

I_OGRE=$(shell pkg-config --cflags OGRE)
L_OGRE=$(shell pkg-config --libs OGRE)
INC=-I../../.. $(I_OGRE)
LIB=$(L_OGRE) -lboost_system -lboost_filesystem
FLAGS=-O0 -g

all: niftool nif_bsa_test

niftool: niftool.cpp ../nif_file.hpp ../nif_file.cpp ../record.hpp
	$(GXX) $(FLAGS) $(INC) $(LIB) $< ../nif_file.cpp ../../misc/stringops.cpp -o $@

nif_bsa_test: nif_bsa_test.cpp ../nif_file.cpp ../../bsa/bsa_archive.cpp ../../bsa/bsa_file.cpp \
              ../../files/constrainedfiledatastream.cpp ../../files/lowlevelfile.cpp ../../misc/stringops.cpp
	$(GXX) $(FLAGS) $(INC) $(LIB) $^ -o $@

clean:
	rm niftool nif_bsa_test
