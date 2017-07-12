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
					cout << "第" << a + 1 << "个点的横坐标值无效,被置为0" << endl;
					rect[a][0] = 0;
				}
				if (rect[a][1] >= 0 && rect[a][1]<=20)
				{

				}
				else
				{
					cout << "第" << a + 1 << "个点的纵坐标值无效,被置为0" << endl;
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
					cout << "不能构成长方形！" << endl;
					exit(0);
				}
			}
			else
			{
				cout << "不能构成长方形！" << endl;
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
		//        cout<<"请输入第"<<i+1<<"个点的横纵坐标（大于0且小于20）,以空格分隔：";
		cin >> rect[i][0] >> rect[i][1];
	}

	Rectangle myRect(rect);
	cout << "长度为：" << myRect.length() << endl;
	cout << "宽度为：" << myRect.width() << endl;
	cout << "周长为：" << myRect.perimeter() << endl;
	cout << "面积为：" << myRect.area() << endl;

	if (myRect.square())
		cout << "此长方形是一个正方形" << endl;
	else
		cout << "此长方形不是一个正方形" << endl;

	return 0;
}
*/