#include <iostream>

using namespace std;

class test{
	private:
		string name;
		int num;
	public: //Access specifier
		test(int lu){
			this->num = lu;
			cout<<"class created"<<endl;
		}
		~test(){	//deconstructor (overloading not allowed)
			cout<<"dead"<<endl;
		}
		void testy(){
			cout<<name<<endl;
		}
		void setname(string name){
			this->name = name;
		}
};

int operator/(int a){
	return a*a;
}

int main(){
	//using new() we create test* 
	test t(1);//object tells which function to use
	t.setname("rushi");
	t.testy();
	//delete(t); cannot be called on test, needs test*
	//cout<<"called using delete"<<endl;
	return 0;
}
