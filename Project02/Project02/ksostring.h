#pragma once
#include "node.h"
#include <iostream>

class KsoString
{
public:
	KsoString();											    //默认空构造函数
	KsoString(const char* s);									//可用指定字符串初始化
	KsoString(const KsoString& c);								//拷贝构造函数
	~KsoString();
	void PushChar(char ch);								//添加字符到后面
	void PushChar(wchar_t wch);
	bool IsEmpty();										//字符串是否为空
	wchar_t CharToWchar(char ch1, char ch2);			//Char转Wchar
	void Insert(int index, char ch);					//插入窄字符
	void Insert(int index, wchar_t wch);				//插入宽字符
	Node* GetNode(int index);							//查找给定位置的节点
	int Delete(int index);								//删除字符
	int Count();										//获取字符个数
	void Clear();										//清空字符串
	int operator [](int index);							//重载[]运算符
	KsoString& operator =(const KsoString& s);          //重载=号运算符 
	KsoString& operator =(const char* s);				//重载=号运算符
	void PrintStr();									//打印字符串
private:
	Node* m_headNode;
	Node* m_tailNode;
	int m_count;
};


