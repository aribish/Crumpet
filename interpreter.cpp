#include <iostream>
#include <fstream>
#include <string>

#define STACK_MAX 256

using std::string;
using std::ifstream;

int main(int argc, char** argv) {
	short int reg_a = 1;
	short int reg_b = 0;
	short int sp = 0; // stack pointer
	short int bm = 0; // bookmark
	short int stack[STACK_MAX];
	std::string code;

	// Check console arguments
	if(argc < 2) {
		std::cout << "\x1b[31mSource Code File Not Supplied :/\n\x1b[0m";
		return 1;
	}
	else if(argc > 2) {
		std::cout << "\x1b[31mToo Many Arguments :/\n\x1b[0m";
	}

	// Read the source code
	std::ifstream f;
	f.open(argv[1]);

	char c;
	bool inComment = false;
	while( (c = f.get()) != EOF) {
		if(c == '(')
			inComment = true;
		if(c == ')') {
			inComment = false;
			continue;
		}
										 // 9 is the Tab Character
		if(c != ' ' && c != '\n' && c != 9 && !inComment)
			code += c;
	}
	f.close();

	if(inComment)
		std::cout << "\x1b[31mNon-Terminating Comment\n\x1b[0m";

	// Clear garbage from stack
	for(int i = 0; i < STACK_MAX; i++) {
		stack[i] = 0;
	}

	// Interpret the source code
	short int swap = 0;
	for(int i = 0; i < code.length(); i++) {
		#ifdef DEBUG
			std::cout << code[i] << ": Output: (";
		#endif

		switch(code[i]) {
			case '>': // Push
				stack[sp] = reg_a;

				if(sp < STACK_MAX - 1)
				sp++;
				break;
			case '<': // Pop
				reg_a = stack[sp - 1];
				stack[sp - 1] = 0;

				if(sp > 0)
					sp--;
				break;
			case '+': // Add a + b
				reg_a += reg_b;
				break;
			case '-': // Subtract a - b
				reg_a -= reg_b;
				break;
			case '~': // Swap a and b
				swap = reg_a;
				reg_a = reg_b;
				reg_b = swap;
				break;
			case '#': // Print a (int)
				std::cout << reg_a << '\n';
				break;
			case '!': // Print a (char)
				std::cout << (char) reg_a;
				break;
			case '*': // Set Bookmark
				bm = i;
				break;
			case '=': // JE (a, b) -> *
				if(reg_a == reg_b)
					i = bm;
				break;
			default: // NOOOOOO!!!!!!!!!!!!!!!!!!
				std::cout << "\x1b\n[31mInvalid Instruction: \'" << code[i] << "\'\x1b[0m\n";
				return 1;
				break;
		}

		#ifdef DEBUG
		std::cout << ") Reg A: " << reg_a << " Reg B: " << reg_b << " Stack:\n";
		for(int j = 0; j < STACK_MAX; j++) {
			printf("%04x ", stack[j]);

			if((j + 1) % 16 == 0) std::cout << '\n';
		}
		std::cout << "Press Enter to Continue\n";
		std::cin.get();
		#endif
	}

	return 0;
}

// TODO IMPLEMENT STEP-BY-STEP DEBUGGER OPTION WITH STRACK TRACES
