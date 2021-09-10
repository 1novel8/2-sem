#include <iostream>

using namespace std;

int inputInt();
int fibonacci(int);
char inputChoise(int, int);

int main() {
	int num = -1, value = -1;
	while (true) {

		char choise = inputChoise(value, num);
		switch (choise) {
		case '1': {
			num = inputInt();
			value = fibonacci(num);
			break;
		}
		case '0':
			return 0;
			break;
		}
	}
}

int inputInt() {
	while (true) {
		int a;
		cout << "Enter a number in the Fibonacci sequence\n";
		cin >> a;
		if ( cin.peek() != '\n' || a < 0) {
			system("cls");
			cout << "!!!!!!!!!!!!!!!!!!!!!!!!!\nInvalid value entered\n!!!!!!!!!!!!!!!!!!!!!!!!!\n";
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
			return a;
	}
}

char inputChoise(int value, int num) {
	while (true) {
		char ch;

		if (value != -1) {
			cout << "Current [" << num << "] = " << value << endl;
		}
		cout << "Choose action\n";
		cout << "1 - Find out the value by the number in the Fibonacci sequence\n";
		cout << "0 - Exit\n";
		cin >> ch;
		system("cls");
		if ( cin.peek() != '\n' || (ch!='1' && ch!='0')) {
			system("cls");
			cout << "!!!\nInvalid value entered\n!!!\n";
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
			return ch;
	}
}

int fibonacci(int num) {
	if (num ==0)
		return 0;
	if (num==1)
		return 1;
	else
		return fibonacci(num - 1) + fibonacci(num-2);
}