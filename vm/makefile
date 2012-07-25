tests: test/runner
	./test/runner

test/runner: test/runner.cpp vm.o
	$(CXX) -I$(HOME)/bin/cxxtest -o test/runner test/runner.cpp

test/runner.cpp: test/vm-test.h
	cd test; \
	cxxtestgen -o runner.cpp --error-printer vm-test.h

vm.o: vm.cpp vm.h
	g++ vm.cpp -c -o vm.o -Wall

