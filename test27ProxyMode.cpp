/***
意图：为其他对象提供一种代理以控制对这个对象的访问

实用性：
在需要用比较通用和复杂的对象指针代替简单的指针的时候使用代理模式

1 远程代理：为一个对象在不同的地址空间提供局部代表，这样可以隐藏
一个对象存在于不同地址空间的事实。
2 虚拟代理：是根据需要创建开销很大的对象，通过它来存放实例化需要很长时间
的真实对象。
3 安全代理：用来控制真实对象访问的权限。
4 智能指针：取代了简单的指针，它在访问对象时执行一些附加操作。
***/
#include <iostream>

using namespace std;

class Girl
{
public:
	Girl(char* name=""):mName(name){};
	char* getName()
	{
		return mName;
	}
	~Girl();
private:
	char* mName;	
};


class GiveGift
{
public:
	virtual	void GiveDolls() =0;
	virtual void GiveFlowers() =0;
	virtual void GiveChocolate() =0;
};

class Puisuit:public GiveGift
{
public:
	Puisuit(Girl mm):mGirl(mm){};
	virtual void GiveDolls()
	{
		cout<<"送"<<mGirl.getName()<<"玩具"<<endl;
	}

	virtual void GiveFlowers()
	{
		cout<<"送"<<mGirl.getName<<"鲜花"<<endl;
	}
	virtual void GiveChocolate()
	{
		cout<<"送"<<mGirl.getName()<<"巧克力"<<endl;
	}

private:
	Girl mGirl;	
};




class Proxy:public GiveGift
{
	Proxy(Girl mm)
	{
		mPuisuit = new Puisuit(mm);

	}

	virtual void GiveDolls()
	{
		mPuisuit->GiveDolls();
	}
	virtual void GiveFlowers()
	{
		mPuisuit->GiveFlowers();
	}
	virtual void GiveChocolate()
	{
		mPuisuit->GiveChocolate();
	}

private:
	Puisuit* mPuisuit;	
};

int main(int argc, char const *argv[])
{
	Girl mm("xiao juan");
	Proxy pro(mm);
	pro.GiveChocolate();
	pro.GiveDolls();
	pro.GiveFlowers();


	return 0;
}