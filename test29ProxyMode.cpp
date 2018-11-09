/***
游戏中通过代理来控制不同VIP玩家的游戏权限
***/

class Play
{
public:
	virtual void Play1()=0;
	virtual void Play2()=0;
	virtual void Play3()=0;
};

class Player:public Play
{
public:
	void Play1()
	{
		cout<<"zhanyi"<<endl;
	}
	void Play2()
	{
		cout<<"juntuan"<<endl;
	}
	void Play3()
	{
		cout<<"shenqi"<<endl;
	}
};

//不同vip玩家的代理
class ProxyPlayerVip0:Play
{
public:
	ProxyPlayerVip0()
	{
		mPlayer = new Player;
	};
	void Play1()
	{
		mPlayer->Play1();
	}
	void Play2()
	{
		cout<<"no right"<<endl;
	}
	void Play3()
	{
		cout<<"no right"<<endl;
	}
	~ProxyPlayerVip0();
	
private:
	Play* mPlayer;	
};


class ProxyPlayerVip1:Play
{
public:
	ProxyPlayerVip1()
	{
		mPlayer = new Player;
	};
	void Play1()
	{
		mPlayer->Play1();
	}
	void Play2()
	{
		mPlayer->Play2();
	}
	void Play3()
	{
		cout<<"no right "<<endl;
	}

	~ProxyPlayerVip1();
private:
	Play* mPlayer;
};

void main(int argc, char const *argv[])
{
	ProxyPlayerVip0 pro5;
	pro5.Play1();
	pro5.Play2();
	pro5.Play3();

	ProxyPlayerVip1 pro1;
	pro1.Play1();
	pro1.Play2();
	pro1.Play3();

	return 0;
}