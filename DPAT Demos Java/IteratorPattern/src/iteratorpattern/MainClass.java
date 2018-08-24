package iteratorpattern;

import java.time.LocalDate;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;

enum SexType { Male, Female};

class Person implements Iterable<Person>
{
    public String Name;
    public LocalDate DateOfBirth;
    public SexType Sex; 
    Person[] children;
    public Iterator<Person> iterator()
    {
        return new PersonIterator(this);
    }
}
class ReturnNode
{
    ReturnNode(Person person, int numChild)
    {
        ancestor = person;
        next = numChild;
    }
    Person ancestor;
    int next;
}
class PersonIterator implements Iterator<Person>
{
    private Person dummy = new Person();
    public PersonIterator(Person first)
    {
    	dummy.children = new Person[1];
        dummy.children[0] = first;
        current = dummy;
    }
    LinkedList<ReturnNode> backTrail = new LinkedList<>();
    private Person current;


	@Override
	public Person next() {
        if (current.children != null && current.children.length > 0)
        {
            ReturnNode rn = new ReturnNode(current, 1);
            backTrail.addFirst(rn);
            current = current.children[0];
            return current;
        }
        else
        {
            while ((backTrail.size() > 0) && !(backTrail.getFirst().ancestor.children.length > backTrail.getFirst().next))
            {
                backTrail.removeFirst();
            }
            if (backTrail.size() > 0)
            {
                current = backTrail.getFirst().ancestor.children[backTrail.getFirst().next++];
                return current;
            }
            else
            {
                current = null;
                throw new NoSuchElementException();
            }
        }
    }




	@Override
	public boolean hasNext() {
        if (current.children != null && current.children.length > 0)
        {
        	return true;
        }
        else
        {
        	Iterator<ReturnNode> tmp = backTrail.iterator();
        
            while (tmp.hasNext())
            {
            	ReturnNode tmpRN = tmp.next();
            	if (tmpRN.ancestor.children.length > tmpRN.next)
            		return true;
            }
        }
        	
		return false;
	}
}



public class MainClass {

	public static void main(String[] args) {
        Person root = new Person();
        root.Name = "Root";
        root.DateOfBirth = LocalDate.now();
        root.Sex = SexType.Male;
        root.children = new Person[5];

        for (int i = 0; i < 5; i++)
        {
            root.children[i] = new Person();
            root.children[i].Name = "Child:" + i;
            root.children[i].DateOfBirth = LocalDate.now();
            root.children[i].Sex = (i % 2 == 0) ? SexType.Male : SexType.Female;
            root.children[i].children = new Person[i+1];
            for (int j = 0; j < i+1; j++ )
            {
                root.children[i].children[j] = new Person();
                root.children[i].children[j].Name = "GrandChild:" + i*j;
                root.children[i].children[j].DateOfBirth = LocalDate.now();
                root.children[i].children[j].Sex = (i % 2 == 0) ? SexType.Male : SexType.Female;
                if (j % 2 == 0)
                {
                    root.children[i].children[j].children = new Person[1];
                    root.children[i].children[j].children[0] = new Person();
                    root.children[i].children[j].children[0].Name = "GrandGrandChild";
                    root.children[i].children[j].children[0].DateOfBirth = LocalDate.now();
                    root.children[i].children[j].children[0].Sex = SexType.Female;
                }

            }
        }
        
        for(Person p : root)
        {
            System.out.println("Person: " + p.Name + " +, Dob: " + p.DateOfBirth + ", Sex: " + p.Sex + ", Number of Children: " + ((p.children==null) ? 0 : p.children.length));
        }
    }

}
