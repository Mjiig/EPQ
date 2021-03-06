#include "../vm.h"
#include <cxxtest/TestSuite.h>

class ExecTests: public CxxTest::TestSuite
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
		vm->exec(2);
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
		vm->exec(4);
		TS_ASSERT_EQUALS(vm->ip, 4); //Notice 1 is subtracted to account for the instruction pointer moving forward
		vm->r2=10;
		vm->exec(4);
		TS_ASSERT_EQUALS(vm->ip, 9);
	}

	void test_jmpif(void)
	{
		vm->ip=10;
		vm->r2=5;
		vm->r1=0;
		vm->exec(3);
		TS_ASSERT_EQUALS(vm->ip, 4);
		vm->r2=6;
		vm->r1=1;
		vm->exec(3);
		TS_ASSERT_EQUALS(vm->ip, 4);
	}

	void test_load1(void)
	{
		vm->exec(5*256);
		TS_ASSERT_EQUALS(vm->r1, 5);
		vm->exec(0*256);
		TS_ASSERT_EQUALS(vm->r1, 0);
	}

	void test_load2(void)
	{
		vm->exec(5*256 +1);
		TS_ASSERT_EQUALS(vm->r2, 5);
		vm->exec(0*256 +1);
		TS_ASSERT_EQUALS(vm->r2, 0);
	}

	void test_store(void)
	{
		vm->r2=15;
		vm->r1=10;
		vm->exec(5);
		TS_ASSERT_EQUALS(vm->memory[15], 10);
		vm->r2=255;
		vm->r1=3;
		vm->exec(5);
		TS_ASSERT_EQUALS(vm->memory[255], 3);
	}
	
	void test_load(void)
	{
		vm->r1=5;
		vm->memory[255]=12;
		vm->r2=255;
		vm->exec(6);
		TS_ASSERT_EQUALS(vm->r1, 12);
		vm->r1=16;
		vm->memory[0]=255;
		vm->r2=0;
		vm->exec(6);
		TS_ASSERT_EQUALS(vm->r1, 255);
	}

	void test_swap2(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->exec(7);
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r2, 0);
		vm->r1=7;
		vm->r2=9;
		vm->exec(7);
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r2, 7);
	}


	void test_swap3(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->exec(8);
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r3, 0);
		vm->r1=7;
		vm->r3=9;
		vm->exec(8);
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r3, 7);
	}
		
	void test_swap4(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->exec(9);
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r4, 0);
		vm->r1=7;
		vm->r4=9;
		vm->exec(9);
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r4, 7);
	}

	void test_swap5(void)
	{
		vm->r1=0;
		vm->r2=0;
		vm->exec(10);
		TS_ASSERT_EQUALS(vm->r1, 0);
		TS_ASSERT_EQUALS(vm->r5, 0);
		vm->r1=7;
		vm->r5=9;
		vm->exec(10);
		TS_ASSERT_EQUALS(vm->r1, 9);
		TS_ASSERT_EQUALS(vm->r5, 7);
	}

	void test_term(void)
	{
		vm->exec(11);
		TS_ASSERT(vm->finished);
	}

	void test_inc(void)
	{
		vm->r1=0;
		vm->exec(12);
		TS_ASSERT_EQUALS(vm->r1, 1);
		vm->exec(12);
		vm->exec(12);
		TS_ASSERT_EQUALS(vm->r1, 3);
		vm->r1=255;
		vm->exec(12);
		TS_ASSERT_EQUALS(vm->r1, 0);
	}

	void test_add(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=0;
		vm->exec(13);
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->memory[5]=3;
		vm->exec(13);
		TS_ASSERT_EQUALS(vm->r1, 3);
		vm->memory[5]=3;
		vm->exec(13);
		TS_ASSERT_EQUALS(vm->r1, 6);
		vm->r1=255;
		vm->memory[5]=7;
		vm->exec(13);
		TS_ASSERT_EQUALS(vm->r1, 6);
	}

	void test_sub(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=0;
		vm->exec(14);
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->memory[5]=3;
		vm->exec(14);
		TS_ASSERT_EQUALS(vm->r1, 253);
		vm->memory[5]=3;
		vm->exec(14);
		TS_ASSERT_EQUALS(vm->r1, 250);
	}

	void test_mult(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=0;
		vm->exec(16);
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->r1=5;
		vm->exec(16);
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->r1=5;
		vm->memory[5]=6;
		vm->exec(16);
		TS_ASSERT_EQUALS(vm->r1, 30);
		vm->memory[5]=10;
		vm->exec(16);
		TS_ASSERT_EQUALS(vm->r1, 44);
	}

	void test_div(void)
	{
		vm->r1=0;
		vm->r2=5;
		vm->memory[5]=2;
		vm->exec(15);
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->r1=10;
		vm->exec(15);
		TS_ASSERT_EQUALS(vm->r1, 5);
		vm->memory[5]=0;
		vm->exec(15);
		TS_ASSERT_EQUALS(vm->r1, 0);
		vm->memory[5]=0;
		vm->exec(15);
		TS_ASSERT_EQUALS(vm->r1, 0);
	}
};
