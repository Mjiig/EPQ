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
		std::string line=programtext.substr(last, next-last);
		program.push_back(compile(line));
		last=next+1;
		next=programtext.find('\n', last);
	}
	program.push_back(compile(programtext.substr(last, next)));
	
	r1=r2=r3=r4=r5=0;
	for(int i=0; i<256;i++)
	{
		memory[i]=0;
	}

	finished=false;
	ip=0;
	steps=0;
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
	while(!finished && ip<program.size() && steps<100000) //This limit is less than I'd like, but necessary to get high enough performance
	{
		exec(program[ip]);
		ip++;
		steps++;
	}
}

unsigned int VM::compile(std::string ins)
{
	unsigned int ret;

	if(!ins.compare(0, 5, "LOAD1"))
	{
		int literal=atoi(ins.substr(6).c_str());
		ret= 0 | (literal << 8);
	}
	else if(!ins.compare(0, 5, "LOAD2"))
	{
		int literal=atoi(ins.substr(6).c_str());
		ret= 1 | (literal << 8);
	}
	else if(!ins.compare(0, 3, "NOP"))
		ret=2;
	else if(!ins.compare(0, 5, "JMPIF"))
		ret=3;
	else if(!ins.compare(0, 3, "JMP"))
		ret=4;
	else if(!ins.compare(0, 5, "STORE"))
		ret=5;
	else if(!ins.compare(0, 4, "LOAD"))
		ret=6;
	else if(!ins.compare(0, 5, "SWAP2"))
		ret=7;
	else if(!ins.compare(0, 5, "SWAP3"))
		ret=8;
	else if(!ins.compare(0, 5, "SWAP4"))
		ret=9;
	else if(!ins.compare(0, 5, "SWAP5"))
		ret=10;
	else if(!ins.compare(0, 4, "TERM"))
		ret=11;
	else if(!ins.compare(0, 3, "INC"))
		ret=12;
	else if(!ins.compare(0, 3, "ADD"))
		ret=13;
	else if(!ins.compare(0, 3, "SUB"))
		ret=14;
	else if(!ins.compare(0, 3, "DIV"))
		ret=15;
	else if(!ins.compare(0, 4, "MULT"))
		ret=16;
	else
		ret=2; //If we don't know what the user wants, assume NOP, though this should never happen

	return ret;
}
void VM::exec(unsigned int ins)
{
	switch(ins & 0xFF)
	{
	case 0:
		load1(ins >> 8);
		break;
	case 1:
		load2(ins >> 8);
		break;
	case 2:
		nop();
		break;
	case 3:
		jmpif();
		break;
	case 4:
		jmp();
		break;
	case 5:
		store();
		break;
	case 6:
		load();
		break;
	case 7:
		swap2();
		break;
	case 8:
		swap3();
		break;
	case 9:
		swap4();
		break;
	case 10:
		swap5();
		break;
	case 11:
		term();
		break;
	case 12:
		inc();
		break;
	case 13:
		add();
		break;
	case 14:
		sub();
		break;
	case 15:
		div();
		break;
	case 16:
		mult();
		break;
	}
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
	ip=r2-1;
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

void VM::add(void)
{
	r1+=memory[r2];
}

void VM::sub(void)
{
	r1-=memory[r2];
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

