#pragma once
#include"node.h"
//���������Ƶĵ�����
class KsoIter
{
public:
	typedef  Node value_type;
	typedef  Node& reference;
	typedef  Node* pointer;
	KsoIter(pointer p = nullptr) :Iter(p) {}
	//�������������ܣ�����++ /ǰ��++/ȡֵ*
	KsoIter& operator++()//ǰ����������
	{
		Iter = Iter->next;
		return *this;
	}
	KsoIter operator++(int)//������������
	{
		KsoIter tmp = *this;
		++(*this);
		return tmp;
	}
	int operator*() //�����ã�����ȡ������ָ���Ԫ��
	{
		return Iter->c? Iter->c: Iter->w;
	}
private:
	pointer Iter;
};
