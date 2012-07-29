#include "../vm.h"
#include <cxxtest/TestSuite.h>

class InstructionTests: public CxxTest::TestSuite
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
		for(size_t i=0;i<256;i++)
		{
			TS_ASSERT_EQUALS(vm->memory[i], 0);
		}
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

	void test_jmpif(void)
	{
		vm->ip=10;
		vm->r2=5;
		vm->r1=0;
		vm->jmpif();
		TS_ASSERT_EQUALS(vm->ip, 5);
		vm->r2=6;
		vm->r1=1;
		vm->jmpif();
		TS_ASSERT_EQUALS(vm->ip, 5);
	}

	void test_load1(void)
	{
		vm->load1(5);
		TS_ASSERT_EQUALS(vm->r1, 5);
		vm->load1(0);
		TS_ASSERT_EQUALS(vm->r1, 0);
	}

	void test_load2(void)
	{
		vm->load2(5);
		TS_ASSERT_EQUALS(vm->r2, 5);
		vm->load2(0);
		TS_ASSERT_EQUALS(vm->r2, 0);
	}

	void test_store(void)
	{
		vm->r2=15;
		vm->r1=10;
		vm->store();
		TS_ASSERT_EQUALS(vm->memory[15], 10);
		vm->r2=255;
		vm->r1=3;
		vm->store();
		TS_ASSERT_EQUALS(vm->memory[255], 3);
	}
	
	void test_load(void)
	{
		vm->r1=5;
		vm->memory[255]=12;
		vm->r2=255;
		vm->load();
		TS_ASSERT_EQUALS(vm->r1, 12);
		vm->r1=16;
		vm->memory[0]=255;
		vm->r2=0;
		vm->load();
		TS_ASSERT_EQUALS(vm->r1, 255);
	}

	void test_swap2(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->swap2();
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r2, 0);
		vm->r1=7;
		vm->r2=9;
		vm->swap2();
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r2, 7);
	}


	void test_swap3(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->swap3();
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r3, 0);
		vm->r1=7;
		vm->r3=9;
		vm->swap3();
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r3, 7);
	}
		
	void test_swap4(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->swap4();
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r4, 0);
		vm->r1=7;
		vm->r4=9;
		vm->swap4();
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r4, 7);
	}

	void test_swap5(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->swap5();
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r5, 0);
		vm->r1=7;
		vm->r5=9;
		vm->swap5();
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r5, 7);
	}

	void test_term(void)
	{
		vm->term();
		TS_ASSERT(vm->finished);
	}

	void test_inc(void)
	{
		vm->r1=0;
		vm->inc();
		TS_ASSERT_EQUALS(vm->r1, 1);
		vm->inc();
		vm->inc();
		TS_ASSERT_EQUALS(vm->r1, 3);
		vm->r1=255;
		vm->inc();
		TS_ASSERT_EQUALS(vm->r1, 0);
	}

	void test_add(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=0;
		vm->add();
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->memory[5]=3;
		vm->add();
		TS_ASSERT_EQUALS(vm->r1, 3);
		vm->memory[5]=3;
		vm->add();
		TS_ASSERT_EQUALS(vm->r1, 6);
		vm->r1=255;
		vm->memory[5]=7;
		vm->add();
		TS_ASSERT_EQUALS(vm->r1, 6);
	}

	void test_sub(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=0;
		vm->sub();
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->memory[5]=3;
		vm->sub();
		TS_ASSERT_EQUALS(vm->r1, 253);
		vm->memory[5]=3;
		vm->sub();
		TS_ASSERT_EQUALS(vm->r1, 250);
	}

	void test_mult(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=0;
		vm->mult();
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->r1=5;
		vm->mult();
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->r1=5;
		vm->memory[5]=6;
		vm->mult();
		TS_ASSERT_EQUALS(vm->r1, 30);
		vm->memory[5]=10;
		vm->mult();
		TS_ASSERT_EQUALS(vm->r1, 44);
	}

	void test_div(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=2;
		vm->div();
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->r1=10;
		vm->div();
		TS_ASSERT_EQUALS(vm->r1, 5);
		vm->memory[5]=0;
		vm->div();
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->memory[5]=0;
		vm->div();
		TS_ASSERT_EQUALS(vm->r1, 0);
	}
};
