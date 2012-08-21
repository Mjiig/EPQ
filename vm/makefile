main: vm.o main.o
	$(CXX) vm.o main.o -o vm -Wall -O3

tests: test/runner
	./test/runner

test/runner: test/runner.cpp test/exec-test.cpp test/instruction-test.cpp test/program-test.cpp test/compile-test.cpp vm.o
	$(CXX) -I$(HOME)/bin/cxxtest -o test/runner test/runner.cpp test/exec-test.cpp test/instruction-test.cpp test/program-test.cpp test/compile-test.cpp vm.o

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

test/compile-test.cpp: test/compile-test.h
	cd test; \
	cxxtestgen --part -o compile-test.cpp --error-printer compile-test.h

vm.o: vm.cpp vm.h
	$(CXX) vm.cpp -c -o vm.o -Wall -O3

main.o: main.cpp vm.h
	$(CXX) main.cpp -c -o main.o -Wall -O3

clean:
	rm test/runner test/runner.cpp test/exec-test.cpp test/instruction-test.cpp test/program-test.cpp test/compile-test.cpp vm.o main.o vm -f

