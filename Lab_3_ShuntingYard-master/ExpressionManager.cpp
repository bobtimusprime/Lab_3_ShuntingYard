#include "ExpressionManager.h"
#include "Syntax_error.h"
#include <stack>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>



using namespace std;

bool ExpressionManager::isBalanced(string expression) {

	stack<char> exStack;
	for (int i = 0; i < expression.size(); i++) {
		if (isOperator(expression[i])) {
			if (isPair(exStack.top(), expression[i])) {
				exStack.pop();
			}
			else {
				exStack.push(expression[i]);
			}
		}
	}
	if (exStack.size() == 0) { return true; }
	return false;
}

string ExpressionManager::postfixToInfix(string postfixExpression) {

}

string ExpressionManager::postfixEvaluate(string postfixExpression) {

	//Make sure the stack is empty
	while (!operand_stack.empty()) {
		operand_stack.pop();
	}

	istringstream tokens(postfixExpression);
	char next_char;

	while (tokens >> next_char) {
		if (isNumber(next_char)) {
			tokens.putback(next_char);
			int value;
			tokens >> value;
			operand_stack.push(value);
		}
		else if (isOperator(next_char)) {
			int result = eval_op(next_char);
			operand_stack.push(result);
		}
		else {
			throw Syntax_Error("Invalid character encountered");
		}
	}
	if (!operand_stack.empty()) {
		int answer = operand_stack.top();
		operand_stack.pop();
		if (operand_stack.empty()){
			return to_string(answer);
		}
		else{
			throw Syntax_Error("Stack should be empty");
			
		}
	}
	else {
		throw Syntax_Error("Stack is empty");
	}

}

string ExpressionManager::infixToPostfix(string infixExpression) {
	postfix = "";
	while (!operand_stack.empty()){
		operand_stack.pop();
	}
	istringstream infix_tokens(infixExpression);
	std::string next_token;

	while (infix_tokens >> next_token){
		if (isalnum(next_token[0])){
			postfix += next_token;
			postfix += " ";
		}
		else if (isOperator(next_token[0])){
			process_operator(next_token[0]);
		}
		else{
			//cout << "Unexpected Character Encountered" << endl;
			throw Syntax_Error("Unexpected Character Encountered");
		}
	}

	while (!operand_stack.empty()){
		char op = operand_stack.top();
		operand_stack.pop();
		if (isLeftParen(op)) {
			//cout << "Unmatched open parenthesis" << endl;
			throw Syntax_Error("Unmatched open parenthesis");
		}
		postfix += op;
		postfix += " ";
	}
	return postfix;
}

void ExpressionManager::process_operator(char op){
	if (operand_stack.empty() || isLeftParen(op)){
		if (isRightParen(op)){
			//cout << "Unmatched close parenthesis" << endl;
			throw Syntax_Error("Unmatched close parenthesis");
		}
		operand_stack.push(op);
	}
	else{
		if (precedence(op) > precedence(operand_stack.top())){
			operand_stack.push(op);
		}
		else{
			while (!operand_stack.empty()
				&& !isLeftParen(operand_stack.top()) 
				&& (precedence(op) <= precedence(operand_stack.top()))){
				postfix += operand_stack.top();
				postfix += " ";
				operand_stack.pop();
			}
			if (isRightParen){
				if (!operand_stack.empty() && isLeftParen(operand_stack.top())){
					operand_stack.pop();
				}
				else{
					//cout << "Unmatched close parentheses" << endl;
					throw Syntax_Error("Unmatched close parenthesis");
				}
			}
			else{
				operand_stack.push(op);
			}
		}
	}
}

bool ExpressionManager::isLeftParen(char t) {
	if (t == '(' || t == '[' || t == '{') { return true; }
	return false;
}

bool ExpressionManager::isRightParen(char t) {
	if (t == ')' || t == ']' || t == '}') { return true; }
	return false;
}
bool ExpressionManager::isLeftBracket(char t) {
	if (t == '[') { return true; }
	return false;
}

bool ExpressionManager::isRightBracket(char t) {
	if (t == ']') { return true; }
	return false;
}
bool ExpressionManager::isLeftBrace(char t) {
	if (t == '{') { return true; }
	return false;
}

bool ExpressionManager::isRightBrace(char t) {
	if (t == '}') { return true; }
	return false;
}

bool ExpressionManager::isPair(char left, char right) {
	if (isLeftParen(left) && isRightParen(right)) { return true; }
	if (isLeftBracket(left) && isRightBracket(right)) { return true; }
	if (isLeftBrace(left) && isRightBrace(right)) { return true; }
	return false;
}

bool ExpressionManager::isOperator(char t) {
	if (t == '+' || t == '-' || t == '*' || t == '/' || t == '^') { return true; }
	return false;
}

bool ExpressionManager::isNumber(char t) {
	return isdigit(t); //This works in VS 2013 but not 2017
}

int ExpressionManager::precedence(char oper) {
	if (oper == ')' || oper == ']' || oper == '}') {
		return 3;
	}
	else if (oper == '*' || oper == '/' || oper == '%') {
		return 2;
	}
	else if (oper == '+' || oper == '-') {
		return 1;
	}
	else {
		return 0;
	}

}

int ExpressionManager::eval_op(char op){
	/*Deprecated
	if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");
		*/
	int rhs = operand_stack.top();
	operand_stack.pop();
	/*Deprecated
	if (operand_stack.empty())
	throw Syntax_Error("Stack is empty");
	*/
	int lhs = operand_stack.top();
	operand_stack.pop();
	int result = 0;
	switch (op) {
	case '+': result = lhs + rhs;
		break;
	case '-': result = lhs - rhs;
		break;
	case '*': result = lhs * rhs;
		break;
	case '/': result = lhs / rhs;
		break;
	case '%': result = lhs % rhs;
		break;
	}

	return result;
}
