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
			/* Need to understand how this works better
			throw Syntax_Error("Invalid character encountered");
			*/
		}
	}
	if (!operand_stack.empty()) {
		int answer = operand_stack.top();
		operand_stack.pop();
		if (operand_stack.empty()){
			return to_string(answer);
		}
		else {
			/*Need to understand how this works better
			throw Syntax_Error("Stack should be empty");
			*/
		}
	}
	else {
		/*Need to understand how this works better
		throw Syntax_Error("Stack is empty");
		*/
	}

}

string ExpressionManager::infixToPostfix(string infixExpression) {

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
	return isdigit(t); //WHY IS THIS NOT WORKING?
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
