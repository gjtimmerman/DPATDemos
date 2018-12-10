package visitor;

abstract class NodeVisitor
{
    public abstract void VisitAtomicExpression(AtomicExpression ae);
    public abstract void VisitMinusExpression(MinusExpression me);
    public abstract void VisitAddExpression(AddExpression ae);
}

class EvaluateVisitor extends NodeVisitor
{
    private int result;
    public int getResult() {
		return result;
	}

	public void setResult(int result) {
		this.result = result;
	}

	@Override
	public void VisitAddExpression(AddExpression ae)
    {
        ae.left.Accept(this);
        int resl = getResult();
        ae.right.Accept(this);
        int resr = getResult();
        setResult(resl + resr); 
    }

	@Override
    public void VisitAtomicExpression(AtomicExpression ae)
    {
        setResult(ae.value);
    }

	@Override
    public void VisitMinusExpression(MinusExpression me)
    {
        me.innerExpression.Accept(this);
        setResult( -getResult());
    }
}
class PrintVisitor extends NodeVisitor
{
    private String result;
    public String getResult() {
		return result;
	}

	public void setResult(String result) {
		this.result = result;
	}
	
	@Override
    public void VisitAddExpression(AddExpression ae)
    {
        ae.left.Accept(this);
        String resl = getResult();
        ae.right.Accept(this);
        String resr = getResult();
        setResult(resl + "+" + resr);
    }

	@Override
    public void VisitAtomicExpression(AtomicExpression ae)
    {
        setResult(new Integer(ae.value).toString());
    }

	@Override
    public void VisitMinusExpression(MinusExpression me)
    {
        me.innerExpression.Accept(this);
        String res = getResult();
        setResult("-" + res);

    }
}
abstract class Expression
{
    public abstract void Accept(NodeVisitor nv);

}

class AtomicExpression extends Expression
{
    public AtomicExpression(int v)
    {
        value = v;
    }
    
    @Override
    public void Accept(NodeVisitor nv)
    {
        nv.VisitAtomicExpression(this);
    }
    
    int value;
}

abstract class UnaryExpression extends Expression
{

}

class MinusExpression extends UnaryExpression
{
    public MinusExpression(Expression expr)
    {
        innerExpression = expr;
    }
    
    @Override
    public void Accept(NodeVisitor nv)
    {
        nv.VisitMinusExpression(this);
    }
    Expression innerExpression;
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
    public void Accept(NodeVisitor nv)
    {
        nv.VisitAddExpression(this);
    }
    Expression left;
    Expression right;
}


public class MainClass {

	public static void main(String[] args) {
        Expression myExpr = new AddExpression(new MinusExpression(new AtomicExpression(3)), new MinusExpression(new AtomicExpression(7)));
        EvaluateVisitor myEvaluate = new EvaluateVisitor();
        myExpr.Accept(myEvaluate);
        System.out.println(myEvaluate.getResult());
        PrintVisitor myPrint = new PrintVisitor();
        myExpr.Accept(myPrint);
        System.out.println(myPrint.getResult());

	}

}
