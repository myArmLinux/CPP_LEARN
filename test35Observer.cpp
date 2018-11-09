#include <iostream>
#include <list>


using namespace std;

class Observer
{
public:
	Observer(){}
	virtual ~Observer(){}
	virtual void Update(){}
};

class Blog
{
public:
	Blog(){}
	virtual ~Blog(){}
	void Attach(Observer *obser){m_observers.push_back(obser);}
	void Remove(Observer *obser){m_observers.remove(obser);}
	void Notify()
	{
		list<Observer*>::iterator iter = m_observers.begin();
		for (; iter != m_observers.end(); iter++)
		{
			/* code */
			(*iter)->Update();
		}
	}
	virtual void SetStatus(string s){m_status = s;}
	virtual string GetStatus(){return m_status;}

private:
	list<Observer* > m_observers;

protected:
	string m_status;
};

class BlogCSDN:public Blog
{
private:
	string m_name;
public:
	BlogCSDN(string name):m_name(name){}
	~BlogCSDN(){}
	void SetStatus(string s){m_status = "CSDN 通知:"+m_name+s;}
	string GetStatus(){return m_status;}	
};

class ObserverBlog:public Observer
{
private:
	string m_name;
	Blog *m_blog;

public:
	ObserverBlog(string name, Blog *blog):m_name(name),m_blog(blog){}
	~ObserverBlog(){}
	void Update()
	{
		string status = m_blog->GetStatus();
		cout<<m_name<<"--------"<<status<<endl;
	}	
};

int main(int argc, char const *argv[])
{
	Blog *blog = new BlogCSDN("wangxin");
	Observer *obser1 = new ObserverBlog("seanwon", blog);
	blog->Attach(obser1);
	blog->SetStatus("observer code demo");
	blog->Notify();
	delete blog;
	delete obser1;
	return 0;
}












