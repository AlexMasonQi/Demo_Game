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
	list<int>::iterator it;//������  
	list<int> l;//���������������ɵ������  
	int begin, end;//���ַ�Χ  
	int sum;//���������  
	cout << "�������ַ�Χ��[n,m]��:";
	cin >> begin >> end;
	cout << "�������������:";
	cin >> sum;
	if ((end<0) || (begin<0) || (begin >end) || (sum>end))//��ʼ��Χ�������0,�����������С�ڵ���������ַ�Χ  
	{
		cout << "��Χ����";
		cout << endl;
		system("pause");
		return 0;
	}
	else
	{
		while (l.size() < sum)
		{
			l.push_back(rand() % (end - begin + 1) + begin);
			l.sort();//����  
			l.unique();//ȥ�����ڵ��ظ�������еĵ�һ��  
		}
		cout << "�����";
	}
	for (it = l.begin(); it != l.end(); it++)
	{
		cout << *it << ' ';
	}

	system("pause");

	return 0;
}