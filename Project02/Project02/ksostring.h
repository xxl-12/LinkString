#pragma once
#include "node.h"
#include <iostream>

class KsoString
{
public:
	KsoString();											    //Ĭ�Ͽչ��캯��
	KsoString(const char* s);									//����ָ���ַ�����ʼ��
	KsoString(const KsoString& c);								//�������캯��
	~KsoString();
	void PushChar(char ch);								//����ַ�������
	void PushChar(wchar_t wch);
	bool IsEmpty();										//�ַ����Ƿ�Ϊ��
	wchar_t CharToWchar(char ch1, char ch2);			//CharתWchar
	void Insert(int index, char ch);					//����խ�ַ�
	void Insert(int index, wchar_t wch);				//������ַ�
	Node* GetNode(int index);							//���Ҹ���λ�õĽڵ�
	int Delete(int index);								//ɾ���ַ�
	int Count();										//��ȡ�ַ�����
	void Clear();										//����ַ���
	int operator [](int index);							//����[]�����
	KsoString& operator =(const KsoString& s);          //����=������� 
	KsoString& operator =(const char* s);				//����=�������
	void PrintStr();									//��ӡ�ַ���
private:
	Node* m_headNode;
	Node* m_tailNode;
	int m_count;
};


