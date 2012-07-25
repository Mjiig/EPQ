#include "vm.h"
#include <vector>
#include <string>
#include <cstdlib> //just for atoi

VM::VM(std::string programtext)
{
	size_t last=0;
	size_t next=programtext.find('\n', 0);
	while(next!=std::string::npos)
	{
		program.push_back(programtext.substr(last, next-last));
		last=next;
		next=programtext.find('\n', last+1);
	}
	program.push_back(programtext.substr(last, next));
}

unsigned char VM::run(std::string state)
{
	r1=r2=r3=r4=r5=0;
	for(int i=0; i<256;i++)
	{
		memory[i]=0;
	}

	finished=false;
	ip=0;
	steps=0;

	load_board(state);
	mainloop();
	return r1;
}

void VM::load_board(std::string board)
{
	for(size_t i=0; i<board.length();i++)
	{
		if(board[i]=='1')
		{
			memory[i]=1;
		}
		else if(board[i]=='2')
		{
			memory[i]=2;
		}
	}
}

void VM::mainloop(void)
{
	/*this would perhaps be better/more efficiently done by having a data structure hold a list of strings and appropriate function pointers, but that's a lot more work for probably a very small gain*/
	while(!finished) //Add in a steps limit later
	{
		exec(program[ip]);
		ip++;
		steps++;
	}
}

void VM::exec(std::string ins)
{
	/*Deal with the special case of load(1, 2) first*/
	if(!ins.compare(0, 5, "LOAD1"))
	{
		int literal=atoi(ins.substr(6).c_str());
		load1(literal);
	}
	if(!ins.compare(0, 5, "LOAD2"))
	{
		int literal=atoi(ins.substr(6).c_str());
		load2(literal);
	}

	if(!ins.compare(0, 3, "NOP"))
		nop();
	if(!ins.compare(0, 3, "JMP"))
		jmp();
	if(!ins.compare(0, 5, "JUMPIF"))
		jmpif();
	if(!ins.compare(0, 5, "STORE"))
		store();
	if(!ins.compare(0, 4, "LOAD"))
		load();
	if(!ins.compare(0, 5, "SWAP2"))
		swap2();
	if(!ins.compare(0, 5, "SWAP3"))
		swap3();
	if(!ins.compare(0, 5, "SWAP4"))
		swap4();
	if(!ins.compare(0, 5, "SWAP5"))
		swap5();
	if(!ins.compare(0, 4, "TERM"))
		term();
	if(!ins.compare(0, 3, "INC"))
		inc();
	if(!ins.compare(0, 3, "NEG"))
		neg();
	if(!ins.compare(0, 3, "ADD"))
		add();
	if(!ins.compare(0, 3, "DIV"))
		div();
	if(!ins.compare(0, 4, "MULT"))
		mult();
	if(!ins.compare(0, 4, "COMP"));
		comp();
}

void VM::swap(unsigned char &a, unsigned char &b) // notice this is not an instruction, but a helper
{
	unsigned char temp=a;
	a=b;
	b=temp;
}

/*INSTRUCTION SET STARTS HERE*/

void VM::nop(void)
{
	return;
}

void VM::jmp(void)
{
	ip=r2;
}

void VM::jmpif(void)
{
	if(r1==0)
	{
		jmp();
	}
}

void VM::load1(int literal)
{
	r1=literal;
}

void VM::load2(int literal)
{
	r2=literal;
}

void VM::store(void)
{
	memory[r2]=r1;
}

void VM::load(void)
{
	r1=memory[r2];
}

void VM::swap2(void)
{
	swap(r1,r2); 
}

void VM::swap3(void)
{
	swap(r1, r3);
}

void VM::swap4(void)
{
	swap(r1, r4);
}

void VM::swap5(void)
{
	swap(r1, r5);
}

void VM::term(void)
{
	finished=true;
}

void VM::inc(void)
{
	r1++;
}

void VM::neg(void)
{
	r1=-r1;
}

void VM::add(void)
{
	r1+=memory[r2];
}

void VM::div(void)
{
	if(memory[r2])
	{
		r1/=memory[r2];
	}
	else
	{
		r1=0; //because i can!
	}
}

void VM::mult(void)
{
	r1*=memory[r2];
}

void VM::comp(void)
{
	if(r1<0)
	{
		r1=-1;
	}
	else if(r1>0)
	{
		r1=1;
	}
	else
	{
		r1=0;
	}
}
