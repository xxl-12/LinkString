#pragma once
//节点类
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
	Node* next;   //后继节点
	Node* pre;    //前驱节点
	char c;
	wchar_t w;
	friend class KsoString;
	friend class KsoIter;
};

