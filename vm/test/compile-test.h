#include "../vm.h"
#include <cxxtest/TestSuite.h>
#include <sstream>

class CompileTests: public CxxTest::TestSuite
{
	public:
	void test_compile(void)
	{
		VM vm("NOP");
		TS_ASSERT_EQUALS(vm.compile("NOP"), 2);
		TS_ASSERT_EQUALS(vm.compile("JMPIF"), 3);
		TS_ASSERT_EQUALS(vm.compile("JMP"), 4);
		TS_ASSERT_EQUALS(vm.compile("STORE"), 5);
		TS_ASSERT_EQUALS(vm.compile("LOAD"), 6);
		TS_ASSERT_EQUALS(vm.compile("SWAP2"), 7);
		TS_ASSERT_EQUALS(vm.compile("SWAP3"), 8);
		TS_ASSERT_EQUALS(vm.compile("SWAP4"), 9);
		TS_ASSERT_EQUALS(vm.compile("SWAP5"), 10);
		TS_ASSERT_EQUALS(vm.compile("TERM"), 11);
		TS_ASSERT_EQUALS(vm.compile("INC"), 12);
		TS_ASSERT_EQUALS(vm.compile("ADD"), 13);
		TS_ASSERT_EQUALS(vm.compile("SUB"), 14);
		TS_ASSERT_EQUALS(vm.compile("DIV"), 15);
		TS_ASSERT_EQUALS(vm.compile("MULT"), 16);
	}

	void test_load1(void)
	{
		VM vm("NOP");
		TS_ASSERT_EQUALS(vm.compile("LOAD1 0"), 0);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 1"), 256);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 2"), 512);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 3"), 768);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 4"), 1024);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 5"), 1280);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 6"), 1536);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 255"), 65280);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 254"), 65024);
		TS_ASSERT_EQUALS(vm.compile("LOAD1 253"), 64768);
	}
	void test_load2(void)
	{
		VM vm("NOP");
		TS_ASSERT_EQUALS(vm.compile("LOAD2 0"), 1);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 1"), 257);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 2"), 513);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 3"), 769);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 4"), 1025);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 5"), 1281);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 6"), 1537);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 255"), 65281);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 254"), 65025);
		TS_ASSERT_EQUALS(vm.compile("LOAD2 253"), 64769);
	}
};
