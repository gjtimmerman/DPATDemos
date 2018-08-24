package composite;

abstract class Expression
{
    public abstract int Evaluate();
    public abstract String Print();
}

class AtomicExpression extends Expression
{
    public AtomicExpression(int v)
    {
        value = v;
    }
    @Override
    public int Evaluate()
    {
        return value;
    }
    @Override
    public String Print()
    {
        return new Integer(value).toString();
    }
    private int value;
}

abstract class UnaryExpression extends Expression
{

}

class MinusExpression extends UnaryExpression
{
    public MinusExpression (Expression expr)
    {
        innerExpression = expr;
    }
    @Override
    public int Evaluate()
    {
        return -innerExpression.Evaluate();
    }
    @Override
    public String Print()
    {
        return "-" + innerExpression.Print();
    }
    private Expression innerExpression;
}

abstract class BinaryExpression extends Expression
{

}

class AddExpression extends BinaryExpression
{
    public AddExpression(Expression l, Expression r)
    {
        left = l;
        right = r;
    }
    @Override
    public int Evaluate()
    {
        return left.Evaluate() + right.Evaluate();
    }
    @Override
    public String Print()
    {
        return left.Print() + "+" + right.Print();
    }
    private Expression left;
    private Expression right;
}


public class MainClass {

	public static void main(String[] args) {
        Expression outerExpr = new AddExpression(new MinusExpression(new AtomicExpression(3)), new AtomicExpression(5));
        System.out.print(outerExpr.Print() + "=");
        System.out.println(outerExpr.Evaluate());

	}

}
