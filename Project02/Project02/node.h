#pragma once
//�ڵ���
class Node
{
public:
	Node(int ch = 0, Node* next = nullptr, Node* pre = nullptr)
		:c(0), w(0), next(next), pre(pre)
	{
		if (ch > 255)
			w = (wchar_t)ch;
		else
			c = (char)ch;
	}

private:
	Node* next;   //��̽ڵ�
	Node* pre;    //ǰ���ڵ�
	char c;
	wchar_t w;
	friend class KsoString;
	friend class KsoIter;
};

