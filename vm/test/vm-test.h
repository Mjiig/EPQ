#include "../vm.h"
#include <cxxtest/TestSuite.h>

class VMTests: public CxxTest::TestSuite
{
	VM* vm;

	void setUp(void)
	{
		vm=new VM("");
	}

	void tearDown(void)
	{
		delete vm;
	}

	public:
	void test_nop(void)
	{
		vm->nop();
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r2, 0);
		TS_ASSERT_EQUALS(vm->r3, 0);
		TS_ASSERT_EQUALS(vm->r4, 0);
		TS_ASSERT_EQUALS(vm->r5, 0);
		TS_ASSERT_EQUALS(vm->ip, 0);
	}

	void test_jmp(void)
	{
		vm->r2=5;
		vm->jmp();
		TS_ASSERT_EQUALS(vm->ip, 5);
		vm->r2=10;
		vm->jmp();
		TS_ASSERT_EQUALS(vm->ip, 10);
	}

};
