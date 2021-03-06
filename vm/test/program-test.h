#include "../vm.h"
#include <cxxtest/TestSuite.h>

class ProgramTests: public CxxTest::TestSuite
{
	public:
	void test_load_board(void)
	{
		VM vm("");
		vm.load_board("111222000");
		for(size_t i=0; i<3;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 1);
		}
		for(size_t i=30; i<6; i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 2);
		}
		for(size_t i=60; i<256;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 0);
		}

		vm.load_board("111111111");
		for(size_t i=0; i<9;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i], 1);
		}
		for(size_t i=64;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm.memory[i],0);
		}

		vm.load_board("222222222");
		for(size_t i=0; i<9;i++)
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
		
		TS_ASSERT_EQUALS(vm->program[0], 2);
		TS_ASSERT_EQUALS(vm->program[1], 2);
		TS_ASSERT_EQUALS(vm->program[2], 11);
		TS_ASSERT_EQUALS(vm->program.size(), 3);

		delete vm;

		vm = new VM("NOP");
		TS_ASSERT_EQUALS(vm->program[0], 2);
		TS_ASSERT_EQUALS(vm->program.size(), 1);

		delete vm;

		vm=new VM("NOP\n");
		TS_ASSERT_EQUALS(vm->program[0], 2);
		TS_ASSERT_EQUALS(vm->program[1], 2);
		TS_ASSERT_EQUALS(vm->program.size(), 2);
		delete vm;
	}

	void test_run(void)
	{
		VM *vm = new VM("NOP\nNOP\nTERM");
		vm->run("111111111");
		TS_ASSERT_EQUALS(vm->steps, 3);
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r2, 0);
		TS_ASSERT_EQUALS(vm->r3, 0);
		TS_ASSERT_EQUALS(vm->r4, 0);
		TS_ASSERT_EQUALS(vm->r5, 0);
		TS_ASSERT_EQUALS(vm->ip, 3);

		delete vm;

		vm= new VM("LOAD1 5\nTERM");
		vm->run("111111111");
		TS_ASSERT_EQUALS(vm->steps, 2);
		TS_ASSERT_EQUALS(vm->r1, 5);
		TS_ASSERT_EQUALS(vm->r2, 0);
		TS_ASSERT_EQUALS(vm->r3, 0);
		TS_ASSERT_EQUALS(vm->r4, 0);
		TS_ASSERT_EQUALS(vm->r5, 0);
		TS_ASSERT_EQUALS(vm->ip, 2);

		delete vm;

		vm=new VM("SWAP2\nSTORE\nSWAP2\nINC\nLOAD2 8\nJMPIF\nLOAD2 0\nJMP\nTERM"); //zero the memory
		vm->run("111111111");
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r2, 8);
		TS_ASSERT_EQUALS(vm->ip, 9);
		for(size_t i=0;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm->memory[i], 0);
		}
		TS_ASSERT_EQUALS(vm->steps, 2047);

		vm->run("111111111");
		for(size_t i=0;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm->memory[i], 0);
		}
		vm->run("000000000");
		for(size_t i=0;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm->memory[i], 0);
		}

		delete vm;

		vm=new VM("SWAP2\nLOAD\nSWAP2\nSWAP3\nSWAP2\nLOAD2 11\nJMPIF\nSWAP3\nINC\nLOAD2 0\nJMP\nSWAP3\nTERM");
		TS_ASSERT_EQUALS(vm->run("110110111"), 2);
		TS_ASSERT_EQUALS(vm->run("121212101"), 7); 

		delete vm;
	}
};
