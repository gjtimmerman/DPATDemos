using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Composite
{
    public abstract class Expression
    {
        public abstract int Evaluate();
        public abstract string Print();
    }

    public class AtomicExpression: Expression
    {
        public AtomicExpression(int v)
        {
            value = v;
        }
        public override int Evaluate()
        {
            return value;
        }
        public override string Print()
        {
            return value.ToString();
        }
        private int value;
    }

    public abstract class UnaryExpression: Expression
    {

    }

    public class MinusExpression: UnaryExpression
    {
        public MinusExpression (Expression expr)
        {
            innerExpression = expr;
        }
        public override int Evaluate()
        {
            return -innerExpression.Evaluate();
        }
        public override string Print()
        {
            return "-" + innerExpression.Print();
        }
        private Expression innerExpression;
    }

    public abstract class BinaryExpression: Expression
    {

    }

    public class AddExpression: BinaryExpression
    {
        public AddExpression(Expression l, Expression r)
        {
            left = l;
            right = r;
        }
        public override int Evaluate()
        {
            return left.Evaluate() + right.Evaluate();
        }
        public override string Print()
        {
            return left.Print() + "+" + right.Print();
        }
        private Expression left;
        private Expression right;
    }
    class Program
    {
        static void Main(string[] args)
        {
            Expression outerExpr = new AddExpression(new MinusExpression(new AtomicExpression(3)), new AtomicExpression(5));
            Console.Write(outerExpr.Print() + "=");
            Console.WriteLine(outerExpr.Evaluate());
        }
    }
}
