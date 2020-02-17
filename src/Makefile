# build runcpp executable when user executes "make"
runcpp: runcpp.o
	$(CXX) $(LDFLAGS) runcpp.o -o runcpp $(LIBS)
runcpp.o: runcpp.cpp
	$(CXX) $(CXXFLAGS) -c runcpp.cpp

# remove object files and executable when user executes "make clean"
clean:
	rm *.o runcpp
