#include "ksostring.h"
#include "node.h"
#include <stdlib.h>
using namespace std;
/*
* function			默认长度，空字符串
* return   ksostring	ksostring类
*/
KsoString::KsoString()
{
	m_headNode = nullptr;
	m_tailNode = nullptr;
	m_count = 0;
}

/*
* function			可以用字符串初始化ksostring
* param    s		字符串
* return   ksostring   ksostring类
*/
KsoString::KsoString(const char* s)
{  
	setlocale(LC_ALL, "chs");
	m_headNode = nullptr;
	m_tailNode = nullptr;
	m_count = 0;
	for ( int i = 0; s[i]; i++)
	{
		if ((int)s[i] < 0)				//如果是中文字符，处理一下
		{
			PushChar(CharToWchar(s[i], s[i + 1]));//窄字符转为宽字符
			i++;
		}
		else
			PushChar((char)s[i]);
	}
}
/*
* function			可以用ksostring对象初始化ksostring
* param    str		ksostring对象
* return   ksostring   ksostring类
*/
KsoString::KsoString(const KsoString& str)
{
	m_count = 0;
	m_headNode = nullptr;
	m_tailNode = nullptr;
	Node* temp = str.m_headNode;
	for (int i = 0; i < str.m_count; i++)
	{
		temp->c ? PushChar(temp->c) : PushChar(temp->w);
		temp = temp->next;
	}
	delete temp;
}
/*
* function			析构函数
*/
KsoString::~KsoString()
{
	Clear();
	if (m_headNode)
		delete m_headNode;
	if (m_tailNode)
		delete m_tailNode;
}
/*
* function			添加一个窄字符到最后
* param    ch		字符
* return		    无
*/
void KsoString::PushChar(char ch)
{
	Node* node = new Node((int)ch);
	if (IsEmpty())
	{
		m_headNode = node;
		m_tailNode = node;
	}
	else
	{
		m_tailNode->next = node;
		node->pre = m_tailNode;
		m_tailNode = node;	
	}
	m_count++;
}
/*
* function			添加一个宽字符到最后
* param    ch		字符
* return		    无
*/
void KsoString::PushChar(wchar_t wch)
{
	Node* node = new Node((int)wch);
	if (IsEmpty())
	{
		m_headNode = node;
		m_tailNode = node;
	}
	else
	{
		m_tailNode->next = node;
		node->pre = m_tailNode;
		m_tailNode = node;
	}
	m_count++;
}
/*
* function			输出字符串
*/
void KsoString::PrintStr() {
	Node* temp = m_headNode;
	while (temp)
	{
		if (temp->c)
			cout << temp->c;
		else
			wcout << temp->w;
		temp = temp->next;
	}
	cout << endl;
}
/*
* function			窄字符转化为宽字符
* param    ch1		第一个字节
* param    ch2		第二个字节
* return		    返回一个宽字符
*/
wchar_t KsoString::CharToWchar(char ch1, char ch2)
{
	setlocale(LC_ALL, "");
	char buf[3] = "";
	sprintf_s(buf, "%c%c", ch1, ch2);
	size_t convertedChars = 0;
	setlocale(LC_ALL, "chs");
	const char* source = buf;
	size_t charNum = sizeof(buf) + 1;
	wchar_t* dest = new wchar_t[charNum];
	mbstowcs_s(&convertedChars, dest, charNum, source, _TRUNCATE);
	return dest[0];
 }
/*
* function			插入字符
* param    index    要插入的位置
* param    ch		要插入的窄字符
* return		    无
*/
void KsoString::Insert(int index, char ch)
{
	index = index < 0 ? 0 : index > m_count ? m_count : index;//下标范围
	if(IsEmpty() || index == m_count)    //如果是空的，则直接全部尾添加即可,或者插入的位置是最后一个
	{
		PushChar(ch);
	}
	else if (index==0)
	{
		Node* node = new Node(ch);
		node->next = m_headNode;
		m_headNode->pre = node;
		m_headNode = node;
		m_count++;
	}
	else
	{
		Node* cur = GetNode(index)->pre;
		Node* node = new Node(ch); 
		node->next = cur->next;    
		cur->next = node;
		node->next->pre = node;     
		node->pre = cur;
		m_count++;
	}
}
/*
* function			插入字符
* param    index    要插入的位置
* param    ch		要插入的宽字符
* return		    无
*/
void KsoString::Insert(int index, wchar_t wch)
{
	index = index < 0 ? 0 : index > m_count ? m_count : index;//下标范围
	if (IsEmpty() || index == m_count)    //如果是空的，则直接全部尾添加即可,或者插入的位置是最后一个
	{
		PushChar(wch);
	}
	else if (index == 0)
	{
		Node* node = new Node(wch);
		node->next = m_headNode;
		m_headNode->pre = node;
		m_headNode = node;
		m_count++;
	}
	else
	{
		Node* cur = GetNode(index)->pre;
		Node* node = new Node(wch);
		node->next = cur->next;
		cur->next = node;
		node->next->pre = node;
		node->pre = cur;
		m_count++;
	}
	
}
/*
* function			删除指定位置字符
* param    index	删除的位置
* return		    删除失败返回-1
*/
int KsoString::Delete(int index)
{
	if (IsEmpty())
		return -1;
	if (index < 0 || index > m_count - 1)
		return -1;
	if (m_count==1)
	{
		Node* cur = m_headNode;
		m_headNode = nullptr;
		m_tailNode = nullptr;
		m_count--;
		delete cur;
	}
	else if (index==0)
	{
		Node* cur = m_headNode;
		cur->next->pre = nullptr;
		m_headNode = cur->next;
		m_count--;
		delete cur;
	}
	else if (index==m_count-1)
	{
		Node* cur = m_tailNode;
		cur->pre->next = nullptr;
		m_headNode = cur->pre;
		m_count--;
		delete cur;
	}
	else
	{
		Node* cur = GetNode(index);
		cur->pre->next = cur->next;
		cur->next->pre = cur->pre;
		m_count--;
		delete cur;
	}
	return 1;
}
/*
* function			获取index位置的那个节点
* param    index	起始位置
* return		    返回起始节点
*/
Node* KsoString::GetNode(int index)
{
	Node* cur = nullptr;
	//分半遍历
	if (index > m_count / 2)
	{
		cur = m_tailNode;
		for (int i = m_count - 1; i > index; i--, cur = cur->pre); 
	}
	else
	{
		cur = m_headNode;
		for (int i = 0; i < index; i++, cur = cur->next); 
	}
	return cur;
}
/*
* function			获取字符串大小
* return   int      返回字符串大小
*/
int KsoString::Count()
{
	return m_count;
}
/*
* function			重载[]运算符
* param    index     元素位置
* return		    返回该字符
*/
int KsoString::operator [](int index)
{
	if (index < 0 || index >= m_count)
		return 0;
	Node* node = GetNode(index);
	return node->c ? node->c : node->w;
}

/*
* function			重载=号运算符
* param    str      KsoString&
* return		    KsoString类
*/

KsoString& KsoString::operator =(const KsoString& str)
{
	Clear();
	Node* temp = str.m_headNode;
	for (int i = 0; i < str.m_count; i++)
	{
		temp->c ? PushChar(temp->c) : PushChar(temp->w);
		temp = temp->next;
	}
	return *this;
}

/*
* function			重载=号运算符
* param    str      const char*
* return		    KsoString类
*/
KsoString& KsoString::operator =(const char* str)
{
	Clear();
	for (int i = 0; str[i]; i++)
	{
		if ((int)str[i] < 0)				//如果是中文字符，处理一下
		{
			PushChar(CharToWchar(str[i], str[i + 1]));//窄字符转为宽字符
			i++;
		}
		else
			PushChar((char)str[i]);
	}
	return *this;
}
/*
* function			清空字符串
* return		    无
*/
void KsoString::Clear()
{
	int len = m_count;
	for (int i = 0; i < len; i++)
	{
		Delete(0);
	}
}
/*
* function			是否为空
* return   bool     空返回true
*/
bool KsoString::IsEmpty()
{
	return m_count ? false : true;
}

