tests: test/runner
	./test/runner

test/runner: test/runner.cpp test/exec-test.cpp test/instruction-test.cpp test/program-test.cpp vm.o
	$(CXX) -I$(HOME)/bin/cxxtest -o test/runner test/runner.cpp test/exec-test.cpp test/instruction-test.cpp test/program-test.cpp vm.o

test/runner.cpp: 
	cd test; \
	cxxtestgen --root -o runner.cpp --error-printer 

test/exec-test.cpp: test/exec-test.h
	cd test; \
	cxxtestgen --part -o exec-test.cpp --error-printer exec-test.h

test/instruction-test.cpp: test/instruction-test.h
	cd test; \
	cxxtestgen --part -o instruction-test.cpp --error-printer instruction-test.h

test/program-test.cpp: test/program-test.h
	cd test; \
	cxxtestgen --part -o program-test.cpp --error-printer program-test.h

vm.o: vm.cpp vm.h
	g++ vm.cpp -c -o vm.o -Wall

clean:
	rm test/runner test/runner.cpp test/exec-test.cpp test/instruction-test.cpp test/program-test.cpp vm.o

