/**
*********************************************
2016 Autumn DataStructure
SNU Dept. of Electrical & Computer Engineering
2014-13261
Han-Byul Kim
*********************************************
Rev. log.
2016.09.28 : List Structure
2016.10.02 : Text input with input checking
**/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "List.h"
#include "ListRow.h"
#include "Stack.h"

// Read line
std::string CleanLine(const std::string& n);
// Forming Matrix List
void CheckMatrix(std::string& command, bool* matlist);
// converting infix to postfix
void postfixCalculator(std::string& command, ListRow* Matrix);
int getWeight(char oper);
// Forming Matrix Structure
ListRow& MakeMatrix(char MatName);
// calculator
char calculation(char a, char b, char symbol);
ListRow MatCalculation(char a, ListRow b, char symbol);
List RowCalculation(char a, List b, char symbol);
void main() {
	std::string command;
	ListRow Matrix[26];
	bool matlist[26] = { 0 }; // A:65 ~ Z:90

	// Command input
	std::cout << "Input expression: ";
	std::cin >> command;

	CheckMatrix(command, matlist);

	// Forming Matrix
	for (int i = 0; i < 26; i++){
		if (matlist[i] == 1){
			// Cleanline function
			// original : CleanLine((char)(i + 65));
			/************************/
			char MatName = (char)(i + 65);
			std::string filename;
			std::stringstream ss;
			std::string str, cleanstr;
			double x;
			int point_count = 0;

			// Forming Filename
			ss << MatName;
			ss << ".txt";
			ss >> filename;
			ss.clear();

			std::ifstream file(filename);
			std::cout << "matrix " << MatName << " file: " << filename << std::endl;

			if (file) { // Same as Try Catch Exception

				while (!file.eof()) {
					std::string temp;
					std::getline(file, str);
					List* Row = new List();

					// Clean each line.
					cleanstr = CleanLine(str);

					// Pass the cleaned-up string into a stringstream, to parse out the data elements.
					ss.clear();
					ss << cleanstr;

					// Stringstream will parse directly on whitespace.
					while (!ss.eof()) {
						ss >> temp;					// TODO: Type compatibility checking.
						x = std::stod(temp);

						// Put to List(making nth row)
						Row->add(x);
					}

					Matrix[i].add(Row);

					++point_count;
				}
			}
			else {
				std::cout << "Wrong File!" << std::endl;
				//	delete Mat;
				//	return '\0';
			}
			/****************/
		}
	}

	std::cout << std::endl;
	std::cout << "Infix Expression :: " << command << std::endl;
	postfixCalculator(command, Matrix);

	system("pause");
}

std::string CleanLine(const std::string& n){
	std::string cleanline;
	char* char_line = (char*)n.c_str(); // Non-const cast required.

	char* token = NULL;
	char* context = NULL;
	char  delims[] = " ,\t\n";

	// During the first read, establish the char string and get the first token.
	token = strtok_s(char_line, delims, &context);

	// While there are any tokens left in "char_line"...
	while (token != NULL)
	{
		// Accumulate the tokens.
		cleanline += token;
		cleanline += ' ';

		// NOTE: NULL, function just re-uses the context after the first read.
		token = strtok_s(NULL, delims, &context);
	}

	return cleanline;
}

void CheckMatrix(std::string& command, bool* matlist){
	for (char& c : command){
		if (c >= 65 && c <= 90){
			matlist[c - 65] = 1;
		}
		if (c >= 97 && c <= 122){
			matlist[c - 97] = 1;
		}
	}
}

char calculation(char a, char b, char symbol){
	switch (symbol){
	//case '(': return 100;
	//case ')': return -1;
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	case '^': return a ^ b;
	default: return 0;
	}
}

ListRow MatCalculation(char a, ListRow b, char symbol) {
	ListRow Mat;
	NodeRow* B;
	B = b.head;
	for (int i = 0; i < b.size; i++) {
		std::cout << "ok" << std::endl;
		B = B->next;
		List temp = RowCalculation(a, (*(B->n)), symbol);
		List* Row = new List();
		NodeEle* go = temp.head->next;
		std::cout << std::endl;
		for (int i = 0; i < temp.size; i++) {
			Row->add(go->n);
			std::cout <<"g"<< go->n<<std::endl;
			go = go->next;
		}
		Row->print();
		std::cout << "Rowprint" << std::endl;
		Mat.add(Row);
	}
	Mat.print();
	return Mat;
}
List RowCalculation(char a, List b, char symbol) {
	List Mat;
	a = a - 48;
	NodeEle* B;
	B = b.head;
	for (int i = 0; i < b.size; i++) {
		std::cout << "ok" << std::endl;
		B = B->next;
		Mat.add((double)a * B->n);
		std::cout << "Rowprint" << std::endl;
	}
	Mat.print();
	return Mat;
}

int getWeight(char* oper) {
	switch (*oper) {
	case '(': return 100;
	case ')': return -2;
	case '/':
	case '*': return 3;
	case '+':
	case '-': return 1;
	case '^': return 6;
	default:
		if (*oper >= 65 && *oper <= 90) // Alphabet uppercase
			return 0;
		else if (*oper >= 97 && *oper <= 122) { //Alphabet lowercase
			*oper -= 32;
			return 0;
		}
		else
			return -1; // number
	}
}

void postfixCalculator(std::string& command, ListRow* Matrix){
	char* infixexp = new char[command.size()]; // Expression to char array
	char* postfixexp = new char[command.size()];
	strcpy(infixexp, command.c_str());

	// Displaying Postfix Expression

	Stack eq;
	char Infix_expression[100] = { NULL };
	char Postfix_expression[100] = { NULL };

	strcpy(Infix_expression, "(");
	strcat(Infix_expression, infixexp);
	strcat(Infix_expression, ")");

	char Symbol[5] = { NULL };
	char Temp[5] = { NULL };

	for (int count = 0; count<strlen(Infix_expression); count++) {
		Symbol[0] = Infix_expression[count];

		if (Symbol[0] == '(')
			eq.push(Symbol[0]);

		else if (Symbol[0] == ')') {
			Symbol[0] = eq.pop();

			while (Symbol[0] != '(') {
				strcat(Postfix_expression, Symbol);

				Symbol[0] = eq.pop();
			}
		}

		else if (Symbol[0] == '^' || Symbol[0] == '*' || Symbol[0] == '/' || Symbol[0] == '+' || Symbol[0] == '-') {
			if (Symbol[0] == '*' || Symbol[0] == '/') {
				Temp[0] = eq.pop();

				while (Temp[0] == '^' || Temp[0] == '*' || Temp[0] == '/') {
					strcat(Postfix_expression, Temp);
					Temp[0] = eq.pop();
				}
				eq.push(Temp[0]);
			}

			else if (Symbol[0] == '+' || Symbol[0] == '-') {
				Temp[0] = eq.pop();

				while (Temp[0] != '(') {
					strcat(Postfix_expression, Temp);
					Temp[0] = eq.pop();
				}
				eq.push(Temp[0]);
			}
			eq.push(Symbol[0]);
		}

		else
			strcat(Postfix_expression, Symbol);
	}

	std::cout << "Postfix Expression :: " << Postfix_expression << std::endl;
	std::cout << "Result : ";

	// Calculating Postfix Expression

	Stack number, symbol;
	int weight;
	char tempsym[5] = { NULL };
	
	// Main operation
	for (int idx = 0; idx < command.size(); idx++){
		tempsym[0] = infixexp[idx];
		weight = getWeight(&tempsym[0]);
		if (weight >= 100)
			symbol.push(tempsym[0]);
		else if (weight == 0 || weight == -1)
			number.push(tempsym[0]);
		else if (symbol.top != NULL && (symbol.top->n) > weight && symbol.top->n != '(') {
			if (tempsym[0] == ')') {
				char sym = symbol.pop();
				while (sym != '(') {
					char b = number.pop();
					char a = number.pop();
					if (a >= 65 && a <= 90 && b >= 65 && b <= 90) {
						switch (sym) {
						case '+': Matrix[a - 65] = Matrix[a - 65] + Matrix[b - 65]; break;
						case '-': Matrix[a - 65] = Matrix[a - 65] - Matrix[b - 65]; break;
						case '*': Matrix[a - 65] = Matrix[a - 65] * Matrix[b - 65]; break;
						}
					}
					else if (a >= 65 && a <= 90) {
						switch (sym) {
						case '*': 
							//Matrix[a - 65] = MatCalculation(b, Matrix[a - 65], sym);
							ListRow Mat;
							NodeRow* B;
							B = Matrix[a - 65].head;
							for (int i = 0; i < Matrix[a - 65].size; i++) {
								B = B->next;
								List temp = RowCalculation(b, (*(B->n)), sym);
								List* Row = new List();
								NodeEle* go = temp.head->next;
								std::cout << std::endl;
								for (int i = 0; i < temp.size; i++) {
									Row->add(go->n);
									go = go->next;
								}
								Row->print();
								Mat.add(Row);
							}
							Mat.print();
							Matrix[a - 65] = Mat;
							break;
						}
					}
					else if (b >= 65 && b <= 90) {
						switch (sym) {
						case '*': 
							//Matrix[a - 65] = MatCalculation(a, Matrix[b - 65], sym);
							ListRow Mat;
							NodeRow* B;
							B = Matrix[b - 65].head;
							for (int i = 0; i < Matrix[b - 65].size; i++) {
								B = B->next;
								List temp = RowCalculation(a, (*(B->n)), sym);
								List* Row = new List();
								NodeEle* go = temp.head->next;
								std::cout << std::endl;
								for (int i = 0; i < temp.size; i++) {
									Row->add(go->n);
									go = go->next;
								}
								Row->print();
								Mat.add(Row);
							}
							Mat.print();
							Matrix[a - 65] = Mat;
							break;
						}
					}
					number.push(a);
					sym = symbol.pop();
				}
			}
			else {
				while (symbol.top != NULL &&symbol.top->n > weight) {
					char b = number.pop();
					char a = number.pop();
					if (a >= 65 && a <= 90 && b >= 65 && b <= 90) {
						switch ('*') {
						case '+': Matrix[a - 65] = Matrix[a - 65] + Matrix[b - 65]; break;
						case '-': Matrix[a - 65] = Matrix[a - 65] - Matrix[b - 65]; break;
						case '*': Matrix[a - 65] = Matrix[a - 65] * Matrix[b - 65]; break;
						}
						symbol.pop();
					}
					else if (a >= 65 && a <= 90) {
						switch ('*') {
						case '*': 
							//Matrix[a - 65] = MatCalculation(b, Matrix[a - 65], '*'); ListRow Mat;
							ListRow Mat;
							NodeRow* B;
							B = Matrix[a - 65].head;
							for (int i = 0; i < Matrix[a - 65].size; i++) {
								B = B->next;
								List temp = RowCalculation(b, (*(B->n)), '*');
								List* Row = new List();
								NodeEle* go = temp.head->next;
								std::cout << std::endl;
								for (int i = 0; i < temp.size; i++) {
									Row->add(go->n);
									go = go->next;
								}
								Row->print();
								Mat.add(Row);
							}
							Mat.print();
							Matrix[a - 65] = Mat;
							break;
						}
						symbol.pop();
					}
					else if (b >= 65 && b <= 90) {
						switch ('*') {
						case '*': 
							//Matrix[a - 65] = MatCalculation(a, Matrix[b - 65], '*');
							ListRow Mat;
							NodeRow* B;
							B = Matrix[b - 65].head;
							for (int i = 0; i < Matrix[b - 65].size; i++) {
								B = B->next;
								List temp = RowCalculation(a, (*(B->n)), '*');
								List* Row = new List();
								NodeEle* go = temp.head->next;
								std::cout << std::endl;
								for (int i = 0; i < temp.size; i++) {
									Row->add(go->n);
									go = go->next;
								}
								Row->print();
								Mat.add(Row);
							}
							Mat.print();
							Matrix[a - 65] = Mat;
							break;
						}
						symbol.pop();
					}
				}
			}
		}
		else if (weight > 0 && weight < 100)
			symbol.push(tempsym[0]);
	}

	// Others operation
	while (symbol.size>0) {
		char b = number.pop();
		char a = number.pop();
		if (a >= 65 && a <= 90 && b >= 65 && b <= 90) {
			switch (symbol.top->n) {
			case '+': Matrix[a - 65] = Matrix[a - 65] + Matrix[b - 65]; break;
			case '-': Matrix[a - 65] = Matrix[a - 65] - Matrix[b - 65]; break;
			case '*': Matrix[a - 65] = Matrix[a - 65] * Matrix[b - 65]; break;
			}
			symbol.pop();
			Matrix[b - 65].print();
			Matrix[a - 65].print();
		}
		else if (a >= 65 && a <= 90) {
			switch ('*') {
			case '*':
				// MatCalculation Function
				// original:Matrix[a - 65] = MatCalculation(b, Matrix[a - 65], '*');
				/*****/
				ListRow Mat;
				NodeRow* B;
				B = Matrix[a - 65].head;
				for (int i = 0; i < Matrix[a - 65].size; i++) {
					B = B->next;
					List temp = RowCalculation(b, (*(B->n)), '*');
					List* Row = new List();
					NodeEle* go = temp.head->next;
					std::cout << std::endl;
					for (int i = 0; i < temp.size; i++) {
						Row->add(go->n);
						go = go->next;
					}
					Mat.add(Row);
				}
				Mat.print();
				Matrix[a - 65] = Mat;
				/*****/
				break;
			}
			symbol.pop();
		}
		else if (b >= 65 && b <= 90) {
			switch ('*') {
			case '*':
				// MatCalculation Function
				// original:Matrix[a - 65] = MatCalculation(a, Matrix[b - 65], '*');
				/*****/
				ListRow Mat;
				NodeRow* B;
				B = Matrix[b - 65].head;
				for (int i = 0; i < Matrix[b - 65].size; i++) {
					B = B->next;
					List temp = RowCalculation(a, (*(B->n)), '*');
					List* Row = new List();
					NodeEle* go = temp.head->next;
					std::cout << std::endl;
					for (int i = 0; i < temp.size; i++) {
						Row->add(go->n);
						go = go->next;
					}
					Row->print();
					Mat.add(Row);
				}
				Mat.print();
				/*****/
				Matrix[a - 65] = Mat;
				break;
			}
			symbol.pop();
		}
		Matrix[a - 65].print();
		number.push(a);
	}

	std::cout << "print answer" << std::endl;
	Matrix[number.pop() - 65].print();
}

ListRow& MakeMatrix(char MatName){
	ListRow Mat;
	std::string filename;
	std::stringstream ss;
	std::string str, cleanstr;
	double x;
	int point_count = 0;

	// Forming Filename
	ss << MatName;
	ss << ".txt";
	ss >> filename;
	ss.clear();

	std::ifstream file(filename);
	std::cout << "matrix " << MatName << " file: " << filename << std::endl;

	if (file){ // Same as Try Catch Exception

		while (!file.eof()) {
			std::string temp;
			std::getline(file, str);
			List* Row = new List();

			// Clean each line.
			cleanstr = CleanLine(str);

			// Pass the cleaned-up string into a stringstream, to parse out the data elements.
			ss.clear();
			ss << cleanstr;

			// Stringstream will parse directly on whitespace.
			while (!ss.eof()){
				ss >> temp;					// TODO: Type compatibility checking.
				x = std::stod(temp);

				// Put to List(making nth row)
				Row->add(x);
			}

			Mat.add(Row);

			++point_count;
		}
	}
	else{
		std::cout << "Wrong File!" << std::endl;
	//	delete Mat;
	//	return '\0';
	}

	return Mat;
}
#endif