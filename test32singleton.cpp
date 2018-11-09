/**
些时候，允许自由创建某个类的实例没有意义，还可能造成系统性能下降。
如果一个类始终只能创建一个实例，则这个类被称为单例类，这种模式就
被称为单例模式。
一般建议单例模式的方法命名为：getInstance()，这个方法的返回类型肯
定是单例类的类型了。getInstance方法可以有参数，这些参数可能是创建
类实例所需要的参数，当然，大多数情况下是不需要的.

优缺点：
减少创建实例所带来的系统开销
便于系统跟踪单个实例的生命周期、实例状态等。
**/

public singleton
{
public:
	static singleton* getInstance();
private:
	int someth;
}

singleton* singleton::getInstance()
{
	static singleton instance;
	return &instance;
}