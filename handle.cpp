#include "handle.h"

void handle(int argsCount, char** argsVariable) { //main processing
	int w = 1, h = 1;
	bool flag = 1;
	if (argsCount == 6) {
		if (checkNum(argsVariable[3]) && checkNum(argsVariable[5])) {
			if ((string)argsVariable[2] == "-h" && (string)argsVariable[4] == "-w") w = parseInt(argsVariable[3]), h = parseInt(argsVariable[5]);
			else if ((string)argsVariable[4] == "-h" && (string)argsVariable[2] == "-w") w = parseInt(argsVariable[5]), h = parseInt(argsVariable[3]);
			else flag = 0;
		}
		else flag = 0;
	}
	else if (argsCount == 4) {
		if (checkNum(argsVariable[3])) {
			if ((string)argsVariable[2] == "-h") h = parseInt(argsVariable[3]);
			else if ((string)argsVariable[2] == "-w") w = parseInt(argsVariable[3]);
			else flag = 0;
		}
		else flag = 0;
	}
	else flag = 0;
	
	if (!flag) cout << "Syntax Error!" << '\n';
	else {
		bool (*func)(char*, int w, int h) = bmpSplit;
		if (func(argsVariable[1], w, h)) cout << "successful!" << '\n';
		else cout << "Failed!" << '\n';
	}
}

int parseInt(char* s) {
	int res = 0;
	for (int i = 0; i < strlen(s); i++)
		(res *= 10) += s[i] - '0';
	return res;
}

bool checkNum(char* s) {
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] > '9' && s[i] < '0') return 0;
	}
	return 1;
}
