#include<iostream>

using namespace std;
/*
Precedence
1. left side class
2. right side pointed to object(if downcasting)
3. Its own virtual function
*/
//Abstract class is a class with a pure virtual function
class Parent{
	//default is private
	public:
		Parent(){
			cout<<"I am parent"<<endl;
		}
		~Parent(){
			cout<<"Parent dead"<<endl;
		}
		virtual void eat(){}
		virtual void fart(){
			cout<<"Farty"<<endl;
		}
		virtual void fu(){cout<<"fu"<<endl;}
		virtual void zzz()=0;	//pure virtual funtion, has to be implemented in the child or its object cannot be declared
								//also we cannot declare pure Parent object anymore as it does not define zzz, we need to use downcasting
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
		void zzz(){
			cout<<"sleep"<<endl;
		}
		void fu(){
			cout<<"thu"<<endl;
		}
};

int main(){
	//Parent p0;
	//p0.eat();	//does nothing
	/*       SET 1
	//prints parents constructor then its own constructor
	Child *c1 = new Child();
	Child c2;
	c1->eat();
	c2.eat();
	//Child *c3 = new Parent();	no upcasting in c++
	Parent *p1 = new Child(); //downcasting, calls both parent and child constructors
	p1->eat();	//when virtual it calls child function cheat
	//prints its own deconstructor then parents deconstructor
	//c1 does not call its own deconstructor due to new() operator
	delete(c1);//this will call c1 deconstructor
	delete(p1);//does not call child deconstructor
	/**/
	/*			SET 2*/
	GrandChild g1;
	g1.eat();
	g1.fart();	//can call parent functions
	Parent *p2 = new GrandChild();
	p2->eat();	//when virtual it calls Grandchild function	grcheat
	p2->fart(); //empty undefined virtual functions do not give error
	p2->fu();
	delete(p2);
	/**/
	//If the child does not define the virtual funtion it will call parent virtual funtion
	//virtual function gives us an option of overriding
	//GrandChild g2;
	//g2.fart();
}
