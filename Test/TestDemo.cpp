#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <list>
using namespace std;

class Util
{
public:
	int getRandomNumber(int start, int end)
	{
		/*default_random_engine engine(time(nullptr));
		uniform_int_distribution<unsigned> uniform(start, end);*/

		return 0;
	}
};

int main()
{
	srand((unsigned)time(NULL));
	list<int>::iterator it;//迭代器  
	list<int> l;//定义链表，保存生成的随机数  
	int begin, end;//数字范围  
	int sum;//随机数个数  
	cout << "输入数字范围（[n,m]）:";
	cin >> begin >> end;
	cout << "输入随机数个数:";
	cin >> sum;
	if ((end<0) || (begin<0) || (begin >end) || (sum>end))//起始范围必须大于0,且随机数个数小于等于最大数字范围  
	{
		cout << "范围错误";
		cout << endl;
		system("pause");
		return 0;
	}
	else
	{
		while (l.size() < sum)
		{
			l.push_back(rand() % (end - begin + 1) + begin);
			l.sort();//排序  
			l.unique();//去除相邻的重复随机数中的第一个  
		}
		cout << "结果：";
	}
	for (it = l.begin(); it != l.end(); it++)
	{
		cout << *it << ' ';
	}

	system("pause");

	return 0;
}