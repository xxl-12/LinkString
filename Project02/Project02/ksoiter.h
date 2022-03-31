#pragma once
#include"node.h"
//针对链表设计的迭代器
class KsoIter
{
public:
	typedef  Node value_type;
	typedef  Node& reference;
	typedef  Node* pointer;
	KsoIter(pointer p = nullptr) :Iter(p) {}
	//迭代器基本功能，后置++ /前置++/取值*
	KsoIter& operator++()//前置自增运算
	{
		Iter = Iter->next;
		return *this;
	}
	KsoIter operator++(int)//后置自增运算
	{
		KsoIter tmp = *this;
		++(*this);
		return tmp;
	}
	int operator*() //解引用，即获取迭代器指向的元素
	{
		return Iter->c? Iter->c: Iter->w;
	}
private:
	pointer Iter;
};
