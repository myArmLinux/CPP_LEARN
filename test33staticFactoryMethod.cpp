/**
简单工厂模式是由一个工厂对象决定创建出哪一种产品类的实例。简单工厂模式
是工厂模式家族中最简单实用的模式，可以理解为是不同工厂模式的一个特殊实
现。

A实例调用B实例的方法，称为A依赖于B。如果使用new关键字来创建一个B实例
（硬编码耦合），然后调用B实例的方法。一旦系统需要重构：需要使用C类来
代替B类时，程序不得不改写A类代码。而用工厂模式则不需要关心B对象的实现、
创建过程。

优缺点：
使用简单工厂模式的优势：让对象的调用者和对象创建过程分离，当对象调用者
需要对象时，直接向工厂请求即可。从而避免了对象的调用者与对象的实现类以
硬编码方式耦合，以提高系统的可维护性、可扩展性。工厂模式也有一个小小的
缺陷：当产品修改时，工厂类也要做相应的修改。
**/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Output
{
public:
	int MAX_CACHE_LINE = 50;
	virtual void out()=0;
	virtual void getData(string msg)=0;
};

class MyPrinter1:public Output
{
public:
	void out()
	{
		cout<<"this is MyPrinter1!"<<endl;
	}
	void getData(string msg)
	{
		cout<<msg<<endl;
	}

private:

};

class MyPrinter2:public Output
{
public:
	void out()
	{
		cout<<"this is MyPrinter2!"<<endl;
	}
	void getData(string msg)
	{
		cout<<msg<<endl;
	}

private:

};


int main(int argc, char const *argv[])
{
	Output *instance1 =NULL;
	if(argc!=2)
	{
		cout<<"useage app [1/2]"<<endl;
		return -1;
	}

	switch (atoi(argv[1]))
	{
		case 1:
		{
			instance1 =new MyPrinter1();
			break;
		}
		case 2:
		{
			instance1 =new MyPrinter2();
			break;
		}
		default:
		{
			cout<<"exec err !"<<endl;
			return -1;
		}
	}
	instance1->out();
	return 0;
}

