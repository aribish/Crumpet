#include <iostream>
#include <fstream>
#include <string>

#define STACK_MAX 256

using std::string;
using std::ifstream;

int main(int argc, char** argv) {
	int reg_a = 1;
	int reg_b = 0;
	int sp = 0; // stack pointer
	int bm = 0; // bookmark
	int stack[STACK_MAX];
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
										 // V - Tab Character
		if(c != ' ' && c != '\n' && && c != 9 && !inComment)
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
	int swap = 0;
	for(int i = 0; i < code.length(); i++) {
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
		std::cout << code[i] << ": a = " << reg_a << ", b = " << reg_b << ", s[0] = " << stack[0] << ", s[1] = " << stack[1] << ", s[2] = " << stack[2] << ", s[3] = " << stack[3] << ", s[4] = " << stack[4] << '\n';
		#endif
	}

	return 0;
}
