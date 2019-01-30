// Visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace Visitor
{
	class Expression;
	class AtomicExpression;
	class MinusExpression;
	class AddExpression;

	class NodeVisitor
	{
	public:
		virtual void VisitAtomicExpression(AtomicExpression *ae) = 0;
		virtual void VisitMinusExpression(MinusExpression *me) = 0;
		virtual void VisitAddExpression(AddExpression *ae) = 0;
	};

	class EvaluateVisitor : public NodeVisitor
	{
	public:
		int getResult()
		{
			return result;
		}
		virtual void VisitAddExpression(AddExpression *ae) override;

		virtual void VisitAtomicExpression(AtomicExpression *ae) override;

		virtual void VisitMinusExpression(MinusExpression *me);
	private:
		int result;
	};

	class PrintVisitor : public NodeVisitor
	{
	public:
		string getResult()
		{
			return result;
		}

		virtual void VisitAtomicExpression(AtomicExpression *ae) override;

		virtual void VisitMinusExpression(MinusExpression *me) override;
		virtual void VisitAddExpression(AddExpression *ae) override;
	private:
		string result;
	};

	class Expression
	{
	public:
		virtual void Accept(NodeVisitor *nv) = 0;
		virtual ~Expression()
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
		virtual void Accept(NodeVisitor *nv) override
		{
			nv->VisitAtomicExpression(this);
		}
		int value;
	};

	class UnaryExpression : public Expression
	{
	public:
		Expression *innerExpression;
		virtual ~UnaryExpression() override;

	};

	class MinusExpression : public UnaryExpression
	{
	public:
		MinusExpression(Expression *expr)
		{
			innerExpression = expr;
		}
		virtual void Accept(NodeVisitor *nv) override
		{
			nv->VisitMinusExpression(this);
		}
	};

	class BinaryExpression : public Expression
	{
	public:
		Expression *left;
		Expression *right;
		virtual ~BinaryExpression() override;
	};

	class AddExpression : public BinaryExpression
	{
	public:
		AddExpression(Expression *l, Expression *r)
		{
			left = l;
			right = r;
		}
		virtual void Accept(NodeVisitor *nv) override
		{
			nv->VisitAddExpression(this);
		}
	};
}

namespace Visitor
{ 
	void PrintVisitor::VisitAddExpression(AddExpression *ae)
	{
		ae->left->Accept(this);
		string resl = result;
		ae->right->Accept(this);
		string resr = result;
		result = resl + "+" + resr;
	}
	void PrintVisitor::VisitAtomicExpression(AtomicExpression *ae)
	{
		result = to_string(ae->value);
	}
	void PrintVisitor::VisitMinusExpression(MinusExpression *me)
	{
		me->innerExpression->Accept(this);
		string res = result;
		result = "-" + res;

	}
	void EvaluateVisitor::VisitAddExpression(AddExpression *ae)
	{
		ae->left->Accept(this);
		int resl = result;
		ae->right->Accept(this);
		int resr = result;
		result = resl + resr;
	}
	void EvaluateVisitor::VisitAtomicExpression(AtomicExpression *ae)
	{
		result = ae->value;
	}
	void EvaluateVisitor::VisitMinusExpression(MinusExpression *me)
	{
		me->innerExpression->Accept(this);
		result = -result;
	}
	UnaryExpression::~UnaryExpression()
	{
		delete innerExpression;
	}
	BinaryExpression::~BinaryExpression()
	{
		delete left;
		delete right;
	}
}


int main()
{
	using namespace Visitor;
	Expression *myExpr = new AddExpression(new MinusExpression(new AtomicExpression(3)), new MinusExpression(new AtomicExpression(7)));
	EvaluateVisitor *myEvaluate = new EvaluateVisitor();
	myExpr->Accept(myEvaluate);
	cout << myEvaluate->getResult() << endl;
	PrintVisitor *myPrint = new PrintVisitor();
	myExpr->Accept(myPrint);
	cout << myPrint->getResult() << endl;
	delete myExpr;
	delete myPrint;
	delete myEvaluate;
	return 0;
}

