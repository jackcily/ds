#include<iostream>
#include<cmath>
using namespace std;
class Rectangle
{
private:
	double x;
	double y;
	double z;
public:
	Rectangle(double rect[4][2])
	{
		int a;
			for (a = 0; a < 4; a++)
			{
				if (rect[a][0] >= 0 && rect[a][0]<=20)
				{

				}
				else
				{
					cout << "��" << a + 1 << "����ĺ�����ֵ��Ч,����Ϊ0" << endl;
					rect[a][0] = 0;
				}
				if (rect[a][1] >= 0 && rect[a][1]<=20)
				{

				}
				else
				{
					cout << "��" << a + 1 << "�����������ֵ��Ч,����Ϊ0" << endl;
					rect[a][1] = 0;
				}
			}
			if (fabs(rect[0][0] - rect[1][0]) ==fabs( rect[2][0] - rect[3][0]))
			{
				x = fabs(rect[0][0] - rect[1][0]);
				if (fabs(rect[0][1] - rect[2][1]) ==fabs( rect[1][1] - rect[3][1]))
				{
					y = fabs(rect[0][1] - rect[2][1]);
					if (y > x)
					{
						z = y;
						y = x;
						x = z;
					}
				}
				else
				{
					cout << "���ܹ��ɳ����Σ�" << endl;
					exit(0);
				}
			}
			else
			{
				cout << "���ܹ��ɳ����Σ�" << endl;
				exit(0);
			}
	}
	double length()
	{
		return x;
	}
	double width()
	{
		return y;
	}
	double perimeter()
	{
		return 2 * (x + y);
	}
	double area()
	{
		return x*y;
	}
	int square()
	{
		if (x == y)
			return 1;
		else
			return 0;
	}
};
/*int main()
{
	double rect[4][2];
	int i;

	for (i = 0; i<4; i++)
	{
		//        cout<<"�������"<<i+1<<"����ĺ������꣨����0��С��20��,�Կո�ָ���";
		cin >> rect[i][0] >> rect[i][1];
	}

	Rectangle myRect(rect);
	cout << "����Ϊ��" << myRect.length() << endl;
	cout << "���Ϊ��" << myRect.width() << endl;
	cout << "�ܳ�Ϊ��" << myRect.perimeter() << endl;
	cout << "���Ϊ��" << myRect.area() << endl;

	if (myRect.square())
		cout << "�˳�������һ��������" << endl;
	else
		cout << "�˳����β���һ��������" << endl;

	return 0;
}
*/