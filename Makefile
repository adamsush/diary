CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
CFLAGS=-Wall -pedantic -O2
CXXFLAGS=-std=c++11 -Wall -pedantic -O2
LDFLAGS=-lpthread -lsqlite3
SQLITE_INCLUDE=-I 3dparty/sqlite3/build/include
SQLITE_LIB=-L 3dparty/sqlite3/build/lib

all: diary

diary: sqlite version.hpp database
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c main.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c cdatabase.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c cdbhandler.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c cinteractivestate.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) main.o cdatabase.o cdbhandler.o cinteractivestate.o -o diary $(LDFLAGS)

version.hpp:
	sh configure.sh

sqlite:
	cd ./3dparty/sqlite3 &&\
	sh configure --prefix=`pwd`/build &&\
	make &&\
	make install &&\
	cd ../..

database: sqlite
	rm -f database.db
	cat ./database/struct.sql | ./3dparty/sqlite3/sqlite3 database.db

unit_tests: sqlite version.hpp database
	# SQLite3 library test
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c Test/test_sqlite.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) test_sqlite.o -o test_sqlite $(LDFLAGS)
	# CDataBase class test
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c Test/test_cdatabase.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c cdatabase.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) test_cdatabase.o cdatabase.o -o test_cdatabase $(LDFLAGS)
	# CDBHandler class test
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c Test/test_cdbhandler.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c cdbhandler.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) test_cdbhandler.o cdbhandler.o cdatabase.o -o test_cdbhandler $(LDFLAGS)
	# CInteractiveState class test
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c Test/test_cinteractivestate.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) $(CXXFLAGS) -c cinteractivestate.cpp
	$(CXX) $(SQLITE_INCLUDE) $(SQLITE_LIB) test_cinteractivestate.o cinteractivestate.o -o test_cinteractivestate $(LDFLAGS)


# Clean
clean: clean_tests clean_sqlite clean_objects clean_database
	rm -rf diary version.hpp

clean_tests:
	rm -f test_cdatabase test_cdbhandler test_sqlite test_cinteractivestate

clean_objects:
	rm -f *.o

clean_database:
	rm -f *.db

clean_sqlite:
	cd ./3dparty/sqlite3 &&\
	make uninstall &&\
	make clean &&\
	rm -rf build
	cd ../..
