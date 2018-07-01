#include<iostream>
#include<stdlib.h>
using namespace std;
 
class Parent{
	//default is private
	public:
		Parent(){
			cout<<"I am parent"<<endl;
		}
		~Parent(){
			cout<<"Parent dead"<<endl;
		}
		void eat(){
			cout<<"pareat"<<endl;
		}
		void fart(){
			cout<<"pfft"<<endl;
		}
};

class Child : public Parent{
	public:
		Child(){
			cout<<"I am child"<<endl;
		}
		~Child(){
			cout<<"Child dead"<<endl;
		}
		void eat(){
			cout<<"cheat"<<endl;
		}
};

class GrandChild : public Child{
	public:
		GrandChild(){
			cout<<"I am grandchild"<<endl;
		}
		~GrandChild(){
			cout<<"GrandChild dead"<<endl;
		}
		void eat(){
			cout<<"grcheat"<<endl;
		}
		
};

int main(){
	/*       SET 1
	//prints parents constructor then its own constructor
	Child *c1 = new Child();
	Child c2;
	c1->eat();
	c2.eat();
	//Child *c3 = new Parent();	no upcasting in c++
	Parent *p1 = new Child(); //downcasting, calls both parent and child constructors
	p1->eat();	//calls parent funtion
	//prints its own deconstructor then parents deconstructor
	//c1 does not call its own deconstructor due to new() operator
	delete(c1);//this will call c1 deconstructor
	delete(p1);//does not call child deconstructor
	*/
	/*			SET 2*/
	GrandChild g1;
	g1.eat();
	g1.fart();	//can call parent functions
	Parent *p2 = new GrandChild();
	p2->eat();
	//p2->fart(); cannot call child functions
	delete(p2);
	/**/
}
