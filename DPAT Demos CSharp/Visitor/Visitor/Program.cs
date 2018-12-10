using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visitor
{
    public abstract class NodeVisitor
    {
        public abstract void VisitAtomicExpression(AtomicExpression ae);
        public abstract void VisitMinusExpression(MinusExpression me);
        public abstract void VisitAddExpression(AddExpression ae);
    }
    public class EvaluateVisitor : NodeVisitor
    {
        public int Result { get; set; }
        public override void VisitAddExpression(AddExpression ae)
        {
            ae.left.Accept(this);
            int resl = Result;
            ae.right.Accept(this);
            int resr = Result;
            Result = resl + resr; 
        }

        public override void VisitAtomicExpression(AtomicExpression ae)
        {
            Result = ae.value;
        }

        public override void VisitMinusExpression(MinusExpression me)
        {
            me.innerExpression.Accept(this);
            Result = -Result;
        }
    }
    public class PrintVisitor : NodeVisitor
    {
        public string Result { get; set; }
        public override void VisitAddExpression(AddExpression ae)
        {
            ae.left.Accept(this);
            string resl = Result;
            ae.right.Accept(this);
            string resr = Result;
            Result = resl + "+" + resr;
        }

        public override void VisitAtomicExpression(AtomicExpression ae)
        {
            Result = ae.value.ToString();
        }

        public override void VisitMinusExpression(MinusExpression me)
        {
            me.innerExpression.Accept(this);
            string res = Result;
            Result = "-" + res;

        }
    }
    public abstract class Expression
    {
        public abstract void Accept(NodeVisitor nv);

    }

    public class AtomicExpression : Expression
    {
        public AtomicExpression(int v)
        {
            value = v;
        }
        public override void Accept(NodeVisitor nv)
        {
            nv.VisitAtomicExpression(this);
        }
        internal int value;
    }

    public abstract class UnaryExpression : Expression
    {

    }

    public class MinusExpression : UnaryExpression
    {
        public MinusExpression(Expression expr)
        {
            innerExpression = expr;
        }
        public override void Accept(NodeVisitor nv)
        {
            nv.VisitMinusExpression(this);
        }
        internal Expression innerExpression;
    }

    public abstract class BinaryExpression : Expression
    {

    }

    public class AddExpression : BinaryExpression
    {
        public AddExpression(Expression l, Expression r)
        {
            left = l;
            right = r;
        }
        public override void Accept(NodeVisitor nv)
        {
            nv.VisitAddExpression(this);
        }
        internal Expression left;
        internal Expression right;
    }

    class Program
    {
        static void Main(string[] args)
        {
            Expression myExpr = new AddExpression(new MinusExpression(new AtomicExpression(3)), new MinusExpression(new AtomicExpression(7)));
            EvaluateVisitor myEvaluate = new EvaluateVisitor();
            myExpr.Accept(myEvaluate);
            Console.WriteLine(myEvaluate.Result);
            PrintVisitor myPrint = new PrintVisitor();
            myExpr.Accept(myPrint);
            Console.WriteLine(myPrint.Result);
        }
    }
}
