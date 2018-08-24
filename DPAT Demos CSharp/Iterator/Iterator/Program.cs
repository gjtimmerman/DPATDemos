using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Iterator
{
    public enum SexType { Male, Female};
    public class Person
    {
        public string Name;
        public DateTime DateOfBirth;
        public SexType Sex; 
        internal Person[] children;
        public IEnumerator<Person> GetEnumerator()
        {
            return new PersonIterator(this);
        }
    }
    internal class ReturnNode
    {
        internal ReturnNode(Person person, int numChild)
        {
            ancestor = person;
            next = numChild;
        }
        internal Person ancestor;
        internal int next;
    }
    public class PersonIterator : IEnumerator<Person>
    {
        private Person dummy = new Person() { children = new Person[1] };
        public PersonIterator(Person first)
        {
            dummy.children[0] = first;
            current = dummy;
        }
        private LinkedList<ReturnNode> backTrail = new LinkedList<ReturnNode>();
        private Person current;

        public Person Current => current;

        object IEnumerator.Current => current;

        public void Dispose()
        {
            backTrail.Clear();
            backTrail = null;
        }

        public bool MoveNext()
        {
            if (current.children != null && current.children.Length > 0)
            {
                ReturnNode rn = new ReturnNode(current, 1);
                backTrail.AddFirst(rn);
                current = current.children[0];
                return true;
            }
            else
            {
                while ((backTrail.Count > 0) && !(backTrail.First.Value.ancestor.children.Length > backTrail.First.Value.next))
                {
                    backTrail.RemoveFirst();
                }
                if (backTrail.Count > 0)
                {
                    current = backTrail.First.Value.ancestor.children[backTrail.First.Value.next++];
                    return true;
                }
                else
                {
                    current = null;
                    return false;
                }
            }
        }

        public void Reset()
        {
            current = dummy;
            backTrail.Clear();
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Person root = new Person();
            root.Name = "Root";
            root.DateOfBirth = DateTime.Now;
            root.Sex = SexType.Male;
            root.children = new Person[5];

            for (int i = 0; i < 5; i++)
            {
                root.children[i] = new Person();
                root.children[i].Name = "Child:" + i;
                root.children[i].DateOfBirth = DateTime.Now;
                root.children[i].Sex = (SexType)(i % 2);
                root.children[i].children = new Person[i+1];
                for (int j = 0; j < i+1; j++ )
                {
                    root.children[i].children[j] = new Person();
                    root.children[i].children[j].Name = "GrandChild:" + i*j;
                    root.children[i].children[j].DateOfBirth = DateTime.Now;
                    root.children[i].children[j].Sex = (SexType)(i % 2);
                    if (j % 2 == 0)
                    {
                        root.children[i].children[j].children = new Person[1];
                        root.children[i].children[j].children[0] = new Person();
                        root.children[i].children[j].children[0].Name = "GrandGrandChild";
                        root.children[i].children[j].children[0].DateOfBirth = DateTime.Now;
                        root.children[i].children[j].children[0].Sex = SexType.Female;
                    }

                }
            }
            
            foreach(Person p in root)
            {
                Console.WriteLine($"Person: {p.Name}, Dob: {p.DateOfBirth}, Sex: {p.Sex}, Number of Children: {((p.children==null) ? 0 : p.children.Length)}");
            }
        }

    }
}
