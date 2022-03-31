#include <iostream>
#include <locale>           //setlocale������localeͷ�ļ��ж���
#include "ksostring.h"
#include"ksoiter.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "chs");
	const char* strTest = "201921098401�����ַ���";
	KsoString ksoStr1;				//�չ��캯��
	KsoString ksoStr2(strTest);		//�ַ���ָ�빹��KsoString
	ksoStr2.PrintStr();				//��ӡ
	KsoString ksoStr3(ksoStr2);		//�������
	ksoStr3.PrintStr();
	ksoStr2.Insert(0, L'��');		//������ַ�
	ksoStr2.PrintStr();
	ksoStr2.Insert(1, 'A');			//����խ�ַ�
	ksoStr2.PrintStr();
	//ksoStr2.Insert(1, 1);			//����int
	//ksoStr2.Insert(1, 3.14);		//����double
	ksoStr2.Delete(1);				//ɾ���ַ�
	ksoStr2.PrintStr();
	ksoStr2.PushChar(L'׷');		//׷�ӿ��ַ�
	ksoStr2.PrintStr();
	ksoStr2.PushChar('B');			//׷��խ�ַ�
	ksoStr2.PrintStr();
	//ksoStr2.PushChar(1);			//׷��int
	//ksoStr2.PushChar(3.14);		//׷��double
	cout << ksoStr2.Count()<<endl;	//�ַ�����
	ksoStr2.Clear();				//����ַ���
	ksoStr2.PrintStr();
	cout << ksoStr2.IsEmpty()<<endl;//�ַ����Ƿ�Ϊ��
	for (int i = 0; i < ksoStr3.Count(); i++)
	{
		if (ksoStr3[i] > 255)
			wcout << (wchar_t)ksoStr3[i];//�����ȡ
		else
			cout << (char)ksoStr3[i];
	}
	cout << endl;
	ksoStr1 = ksoStr3;				//=���������
	ksoStr1.PrintStr();
	ksoStr1 = "�����ַ���201921098401"; //=���������
	ksoStr1.PrintStr();
	KsoIter ksoIter1(ksoStr3.GetNode(0));	//��ʼ��������KsoIter
	for (int i = 0; i < ksoStr3.Count(); i++)//�����������ַ���
	{
		if (*ksoIter1 > 255)
			wcout << (wchar_t)*ksoIter1;
		else
			cout << (char)*ksoIter1;
		ksoIter1++;
	}
	cout << endl;
	KsoIter ksoIter2(ksoStr3.GetNode(0));
	wcout << (wchar_t)*ksoIter2++;		//����++
	wcout << (wchar_t)*++ksoIter2;		//ǰ��++
}