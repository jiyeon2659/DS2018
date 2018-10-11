#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <fstream>

using namespace std;

template<typename T>
class Stack {
private:
	int top;
	int capacity;
public:
	T *str;

	Stack(int capacity) {
		str = new T[capacity];
		top = -1;
		for (int i = 0; i<capacity; i++)
			str[i] = 0;
	}

	~Stack() { delete[] str; }

	void push(T data, bool two) {
		this->str[++top] = data;
		if (two == false)
			this->str[++top] = ' ';
	}

	T pop() {
		T data = this->str[top--];
		return data;
	}

	T top_() {
		char data = this->str[top];
		return data;
	}

	bool isEmpty() {
		return (this->top == -1);
	}

	int getSize() {
		return this->top + 1;
	}
};

bool IsDigit(char digit) {
	if (digit >= '0' && digit <= '9') return true;
	if (digit >= 'a' && digit <= 'z') return true;
	if (digit >= 'A' && digit <= 'Z') return true;
	return false;
}

bool IsOperator(char op) {
	switch (op) {
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
	return true;
}

bool Precedence(char lhs, char rhs) {
	if (lhs == '*' || lhs == '/')
		return true;
	return false;
}

int ApplyOperator(char op, int operand1, int operand2) {
	switch (op) {
	case '+':
		return operand1 + operand2;
	case '-':
		return operand1 - operand2;
	case '*':
		return operand1 * operand2;
	case '/':
		return operand1 / operand2;
	default:
		return -1;
	}
}


string InfixToPostfix(string infix) {
	int capacity = infix.length();
	Stack<char> postfix(capacity * 2);
	Stack<char> stack(capacity);
	string post;
	int a;

	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == ' ') {
			continue;
		}
		else if (IsDigit(infix[i])) {
			while (IsDigit(infix[i])) {
				if (IsDigit(infix[i + 1]))
					postfix.push(infix[i], true);
				else {
					postfix.push(infix[i], false);
				}
				i++;
			}
			--i;
		}
		else if (IsOperator(infix[i])) {
			if (stack.isEmpty()) {
				stack.push(infix[i], true);
			}
			else {
				while (!stack.isEmpty()) {
					if (Precedence(infix[i], stack.top_())) {
						stack.push(infix[i], true);
						break;
					}
					else {
						postfix.push(stack.top_(), false);
						stack.pop();
						if (stack.isEmpty()) {
							stack.push(infix[i], true);
							break;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < stack.getSize(); i++) {
		postfix.push(stack.top_(), false);
		stack.pop();
	}

	post = postfix.str;
	return post;
}

int calculate(string postfix) {
	Stack<int> cal(postfix.length());
	int re;
	string check;
	for (int i = 0; i < postfix.length(); i++) {
		char current = postfix[i];
		char future = postfix[i + 1];
		if (current == ' ') continue;
		else if (IsDigit(current)) {
			while (IsDigit(postfix[i])) {
				check += postfix[i];
				i++;
			}
			int num = atoi(check.c_str());
			cal.push(num, true);
			check = "";
			--i;
		}

		if (IsOperator(postfix[i])) {
			int temp2 = cal.pop(), temp1 = cal.pop();
			re = ApplyOperator(postfix[i], temp1, temp2);
			cal.push(re, true);
		}
	}
	return re;
}

int main() {
	ifstream fin;
	ofstream fout;

	string infix;
	string postfix;
	int result;

	fin.open("stack.inp");
	fin.clear();
	getline(fin, infix);
	cout << infix << endl;

	Stack<char> stack(infix.length());

	postfix = InfixToPostfix(infix);
	result = calculate(postfix);

	fout.open("stack.out");
	if (fout.is_open()) {
		fout << result << endl;
		cout << postfix << endl << result << endl;
	}

	return 0;

	/*
	string infix;
	cout << "Infix notation: \t";
	getline(cin, infix);
	string postfix;
	int result;
	Stack<char> stack(infix.length());
	try {
	postfix = InfixToPostfix(infix);
	result = calculate(postfix);
	}
	catch (const std::runtime_error&  e) {
	cout << "Incorrect expression syntax!" << endl;
	return 0;
	}
	cout << "Postfix notation: \t" << postfix << endl;
	cout << "Result :          \t" << result << endl;

	return 0;
	*/
}


