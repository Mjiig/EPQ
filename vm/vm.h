#include <vector>
#include <string>

class VM
{
	unsigned char memory[256];
	unsigned char r1, r2, r3, r4, r5;
	std::vector<unsigned int> program; //a vector the compiled program
	size_t ip; //the instruction pointer
	int steps;

	void swap(unsigned char &a, unsigned char &b);
	void load_board(std::string board);
	void mainloop(void);
	void exec(unsigned int instruction);
	unsigned int compile(std::string ins);

	/*INSTRUCTION SET*/
	void nop(void);
	void jmp(void);
	void jmpif(void);
	void load1(int literal);
	void load2(int literal);
	void store(void);
	void load(void); //dont be confused, nothing to do with load1 or load2
	void swap2(void);
	void swap3(void);
	void swap4(void);
	void swap5(void);
	void term(void);
	void inc(void);
	void add(void);
	void sub(void);
	void div(void);
	void mult(void);

	public:
	bool finished; //indicates whether the program has called TERM or not
	VM(std::string init);
	unsigned char run(std::string state);

	friend class ExecTests; //For unit testing
	friend class InstructionTests;
	friend class ProgramTests;
	friend class CompileTests;
};
