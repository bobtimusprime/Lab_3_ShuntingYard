#pragma once
#include "ExpressionManagerInterface.h"
#include <string>
#include <stack>

class ExpressionManager : public ExpressionManagerInterface
{
public:
	ExpressionManager() {};
	~ExpressionManager() {};
	/*
	* Checks whether an expression is balanced on its parentheses
	*
	* - The given expression will have a space between every number or operator
	*
	* @return true if expression is balanced
	* @return false otherwise
	*/

	bool isBalanced(string expression);

	/**
	* Converts a postfix expression into an infix expression
	* and returns the infix expression.
	*
	* - The given postfix expression will have a space between every number or operator.
	* - The returned infix expression must have a space between every number or operator.
	* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix expression.
	* otherwise, return the correct infix expression as a string.
	*/
	string postfixToInfix(string postfixExpression);

	/*
	* Evaluates a postfix expression returns the result as a string
	*
	* - The given postfix expression will have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix Expression
	* otherwise, return the correct evaluation as a string
	*/
	string postfixEvaluate(string postfixExpression);

	/*
	* Converts an infix expression into a postfix expression
	* and returns the postfix expression
	*
	* - The given infix expression will have a space between every number or operator.
	* - The returned postfix expression must have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if infixExpression is not a valid infix expression.
	* otherwise, return the correct postfix expression as a string.
	*/
	string infixToPostfix(string infixExpression);

	bool isLeftParen(char t); // (
	bool isRightParen(char t); // )
	bool isLeftBracket(char t); // [
	bool isRightBracket(char t); // ]
	bool isLeftBrace(char t); // {
	bool isRightBrace(char t); // }
	bool isPair(char left, char right); //The two are complementary
	bool isOperator(char t);
	bool isNumber(char t);
	int precedence(char oper);
	int eval_op(char op);
	void process_operator(char op);

private:
	stack<int> operand_stack;
	std::string postfix;
};