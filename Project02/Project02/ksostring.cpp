#include "ksostring.h"
#include "node.h"
#include <stdlib.h>
using namespace std;
/*
* function			Ĭ�ϳ��ȣ����ַ���
* return   ksostring	ksostring��
*/
KsoString::KsoString()
{
	m_headNode = nullptr;
	m_tailNode = nullptr;
	m_count = 0;
}

/*
* function			�������ַ�����ʼ��ksostring
* param    s		�ַ���
* return   ksostring   ksostring��
*/
KsoString::KsoString(const char* s)
{  
	setlocale(LC_ALL, "chs");
	m_headNode = nullptr;
	m_tailNode = nullptr;
	m_count = 0;
	for ( int i = 0; s[i]; i++)
	{
		if ((int)s[i] < 0)				//����������ַ�������һ��
		{
			PushChar(CharToWchar(s[i], s[i + 1]));//խ�ַ�תΪ���ַ�
			i++;
		}
		else
			PushChar((char)s[i]);
	}
}
/*
* function			������ksostring�����ʼ��ksostring
* param    str		ksostring����
* return   ksostring   ksostring��
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
* function			��������
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
* function			���һ��խ�ַ������
* param    ch		�ַ�
* return		    ��
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
* function			���һ�����ַ������
* param    ch		�ַ�
* return		    ��
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
* function			����ַ���
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
* function			խ�ַ�ת��Ϊ���ַ�
* param    ch1		��һ���ֽ�
* param    ch2		�ڶ����ֽ�
* return		    ����һ�����ַ�
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
* function			�����ַ�
* param    index    Ҫ�����λ��
* param    ch		Ҫ�����խ�ַ�
* return		    ��
*/
void KsoString::Insert(int index, char ch)
{
	index = index < 0 ? 0 : index > m_count ? m_count : index;//�±귶Χ
	if(IsEmpty() || index == m_count)    //����ǿյģ���ֱ��ȫ��β��Ӽ���,���߲����λ�������һ��
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
* function			�����ַ�
* param    index    Ҫ�����λ��
* param    ch		Ҫ����Ŀ��ַ�
* return		    ��
*/
void KsoString::Insert(int index, wchar_t wch)
{
	index = index < 0 ? 0 : index > m_count ? m_count : index;//�±귶Χ
	if (IsEmpty() || index == m_count)    //����ǿյģ���ֱ��ȫ��β��Ӽ���,���߲����λ�������һ��
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
* function			ɾ��ָ��λ���ַ�
* param    index	ɾ����λ��
* return		    ɾ��ʧ�ܷ���-1
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
* function			��ȡindexλ�õ��Ǹ��ڵ�
* param    index	��ʼλ��
* return		    ������ʼ�ڵ�
*/
Node* KsoString::GetNode(int index)
{
	Node* cur = nullptr;
	//�ְ����
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
* function			��ȡ�ַ�����С
* return   int      �����ַ�����С
*/
int KsoString::Count()
{
	return m_count;
}
/*
* function			����[]�����
* param    index     Ԫ��λ��
* return		    ���ظ��ַ�
*/
int KsoString::operator [](int index)
{
	if (index < 0 || index >= m_count)
		return 0;
	Node* node = GetNode(index);
	return node->c ? node->c : node->w;
}

/*
* function			����=�������
* param    str      KsoString&
* return		    KsoString��
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
* function			����=�������
* param    str      const char*
* return		    KsoString��
*/
KsoString& KsoString::operator =(const char* str)
{
	Clear();
	for (int i = 0; str[i]; i++)
	{
		if ((int)str[i] < 0)				//����������ַ�������һ��
		{
			PushChar(CharToWchar(str[i], str[i + 1]));//խ�ַ�תΪ���ַ�
			i++;
		}
		else
			PushChar((char)str[i]);
	}
	return *this;
}
/*
* function			����ַ���
* return		    ��
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
* function			�Ƿ�Ϊ��
* return   bool     �շ���true
*/
bool KsoString::IsEmpty()
{
	return m_count ? false : true;
}

