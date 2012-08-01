#include "../vm.h"
#include <cxxtest/TestSuite.h>

class ProgramTests: public CxxTest::TestSuite
{
	public:
	void test_load_board(void)
	{
		VM vm("");
		vm.load_board("1111111111111111111111111111112222222222222222222222222222220000");
		for(size_t i=0; i<30;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 1);
		}
		for(size_t i=30; i<60; i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 2);
		}
		for(size_t i=60; i<256;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 0);
		}

		vm.load_board("1111111111111111111111111111111111111111111111111111111111111111");
		for(size_t i=0; i<64;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 1);
		}
		for(size_t i=64;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i],0);
		}

		vm.load_board("2222222222222222222222222222222222222222222222222222222222222222");
		for(size_t i=0; i<64;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 2);
		}
		for(size_t i=64;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i],0);
		}
	}

	void test_init(void)
	{
		VM *vm = new VM("NOP\nNOP\nTERM");
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r2, 0);
		TS_ASSERT_EQUALS(vm->r3, 0);
		TS_ASSERT_EQUALS(vm->r4, 0);
		TS_ASSERT_EQUALS(vm->r5, 0);
		TS_ASSERT_EQUALS(vm->ip, 0);
		TS_ASSERT_EQUALS(vm->steps, 0);

		for(size_t i=0;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm->memory[i], 0);
		}

		TS_ASSERT(!vm->finished);
		
		TS_ASSERT_EQUALS(vm->program[0], "NOP");
		TS_ASSERT_EQUALS(vm->program[1], "NOP");
		TS_ASSERT_EQUALS(vm->program[2], "TERM");
		TS_ASSERT_EQUALS(vm->program.size(), 3);

		delete vm;

		vm = new VM("NOP");
		TS_ASSERT_EQUALS(vm->program[0], "NOP");
		TS_ASSERT_EQUALS(vm->program.size(), 1);

		delete vm;

		vm=new VM("NOP\n");
		TS_ASSERT_EQUALS(vm->program[0], "NOP");
		TS_ASSERT_EQUALS(vm->program[1], "");
		TS_ASSERT_EQUALS(vm->program.size(), 2);
		delete vm;
	}

};