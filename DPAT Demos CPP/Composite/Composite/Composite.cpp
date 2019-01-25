// Composite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace Composite
{
	class Expression
	{
	public:
		virtual int Evaluate() = 0;
		virtual string Print() = 0;
		virtual ~Expression() = 0
		{
		}
	};

	class AtomicExpression : public Expression
	{
	public:
		AtomicExpression(int v)
		{
			value = v;
		}
		int Evaluate() override
		{
			return value;
		}
		string Print() override
		{
			return to_string(value);
		}
		~AtomicExpression()
		{
		}
	private:
		int value;
	};

	class UnaryExpression : public Expression
	{

	};

	class MinusExpression : public UnaryExpression
	{
	public:
		MinusExpression(Expression *expr)
		{
			innerExpression = expr;
		}
		int Evaluate() override
		{
			return -innerExpression->Evaluate();
		}
		string Print() override
		{
			return "-" + innerExpression->Print();
		}
		~MinusExpression()
		{
			delete innerExpression;
		}
	private:
		Expression *innerExpression;
	};

	class BinaryExpression : public Expression
	{

	};

	class AddExpression : public BinaryExpression
	{
	public:
		AddExpression(Expression *l, Expression *r)
		{
			left = l;
			right = r;
		}
		int Evaluate() override
		{
			return left->Evaluate() + right->Evaluate();
		}
		string Print() override
		{
			return left->Print() + "+" + right->Print();
		}
		~AddExpression()
		{
			delete left;
			delete right;
		}
	private:
		Expression *left;
		Expression *right;
	};
}


int main()
{
	using namespace Composite;

	Expression *outerExpr = new AddExpression(new MinusExpression(new AtomicExpression(3)), new AtomicExpression(5));
	cout << outerExpr->Print() + "=";
	cout << outerExpr->Evaluate() << endl;
	delete outerExpr;
	return 0;
}

