// Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace Iterator
{
	enum SexType { Male, Female };
	class Person
	{
	public:
		string Name;
		SexType Sex;
		vector<Person*> children;
		~Person()
		{
			for (Person *p : children)
				delete p;
		}
	};
	class ReturnNode;
	class Family
	{
	public:
		class iterator
		{
		public:
			iterator(Person *first, Person *last)
			{
				dummy = last;
				current = first;
			}
			void moveNext();
			bool operator ==(iterator r)
			{
				return current == r.current;
			}
			bool operator != (iterator r)
			{
				return current != r.current;
			}
			Person *operator *()
			{
				return current;
			}
			class ReturnNode
			{
			public:
				ReturnNode(Person *person, int numChild)
				{
					ancestor = person;
					next = numChild;
				}
			private:
				Person *ancestor;
				unsigned int next;
				friend void Family::iterator::moveNext();
			};
		private:
			Person *dummy;
			Person *current;
			list<ReturnNode> backTrail;

		public:
			Person *operator++()
			{
				moveNext();
				return current;
			}
			Person *operator++(int)
			{
				Person *tmp = current;
				moveNext();
				return tmp;
			}
		};







		Family(Person *p) : root(p), dummy(new Person)
		{
		}
		Family::iterator begin()
		{
			return Family::iterator(root, dummy);
		}
		Family::iterator end()
		{
			return Family::iterator(dummy, dummy);
		}
		~Family()
		{
			delete dummy;
		}
	private:
		Person *root;
		Person *dummy;
	};



void Family::iterator::moveNext()
{
	if (current->children.size() > 0)
	{
		ReturnNode rn(current, 1);
		backTrail.push_front(rn);
		current = current->children[0];
	}
	else
	{
		while ((backTrail.size() > 0) && !(backTrail.front().ancestor->children.size() > backTrail.front().next))
		{
			backTrail.pop_front();
		}
		if (backTrail.size() > 0)
		{
			current = this->backTrail.front().ancestor->children[backTrail.front().next++];
		}
		else
		{
			current = dummy;
		}
	}
}
}

int main()
{
	using namespace Iterator;

	Person *root = new Person;
	root->Name = "Root";
	root->Sex = SexType::Male;

	for (int i = 0; i < 5; i++)
	{
		Person *tmp = new Person;
		tmp->Name = "Child:" + to_string(i);
		tmp->Sex = (SexType)(i % 2);
		root->children.push_back(tmp);

		for (int j = 0; j < i + 1; j++)
		{
			tmp = new Person;
			
			tmp->Name = "GrandChild:" + to_string(i*j);
			tmp->Sex = (SexType)(i % 2);
			root->children[i]->children.push_back(tmp);
			if (j % 2 == 0)
			{
				tmp = new Person;
				tmp->Name = "GrandGrandChild";
				tmp->Sex = SexType::Female;
				root->children[i]->children[j]->children.push_back(tmp);
			}

		}
	}
	Family myFamily(root);


	for(Person *p : myFamily)
	{
		cout << "Person: "<< p->Name << ", Sex: "<< p->Sex << ", Number of Children: "<< p->children.size() << endl;
	}
	delete root;
	return 0;
}

