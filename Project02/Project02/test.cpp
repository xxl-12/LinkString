#include <iostream>
#include <locale>           //setlocale函数在locale头文件中定义
#include "ksostring.h"
#include"ksoiter.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "chs");
	const char* strTest = "201921098401我是字符串";
	KsoString ksoStr1;				//空构造函数
	KsoString ksoStr2(strTest);		//字符串指针构造KsoString
	ksoStr2.PrintStr();				//打印
	KsoString ksoStr3(ksoStr2);		//深拷贝构造
	ksoStr3.PrintStr();
	ksoStr2.Insert(0, L'插');		//插入宽字符
	ksoStr2.PrintStr();
	ksoStr2.Insert(1, 'A');			//插入窄字符
	ksoStr2.PrintStr();
	//ksoStr2.Insert(1, 1);			//插入int
	//ksoStr2.Insert(1, 3.14);		//插入double
	ksoStr2.Delete(1);				//删除字符
	ksoStr2.PrintStr();
	ksoStr2.PushChar(L'追');		//追加宽字符
	ksoStr2.PrintStr();
	ksoStr2.PushChar('B');			//追加窄字符
	ksoStr2.PrintStr();
	//ksoStr2.PushChar(1);			//追加int
	//ksoStr2.PushChar(3.14);		//追加double
	cout << ksoStr2.Count()<<endl;	//字符个数
	ksoStr2.Clear();				//清空字符串
	ksoStr2.PrintStr();
	cout << ksoStr2.IsEmpty()<<endl;//字符串是否为空
	for (int i = 0; i < ksoStr3.Count(); i++)
	{
		if (ksoStr3[i] > 255)
			wcout << (wchar_t)ksoStr3[i];//随机读取
		else
			cout << (char)ksoStr3[i];
	}
	cout << endl;
	ksoStr1 = ksoStr3;				//=运算符重载
	ksoStr1.PrintStr();
	ksoStr1 = "我是字符串201921098401"; //=运算符重载
	ksoStr1.PrintStr();
	KsoIter ksoIter1(ksoStr3.GetNode(0));	//初始化迭代器KsoIter
	for (int i = 0; i < ksoStr3.Count(); i++)//迭代器遍历字符串
	{
		if (*ksoIter1 > 255)
			wcout << (wchar_t)*ksoIter1;
		else
			cout << (char)*ksoIter1;
		ksoIter1++;
	}
	cout << endl;
	KsoIter ksoIter2(ksoStr3.GetNode(0));
	wcout << (wchar_t)*ksoIter2++;		//后置++
	wcout << (wchar_t)*++ksoIter2;		//前置++
}