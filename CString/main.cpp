#include <iostream>
#include "CString.h"

int main()
{
#if 0
	CString str1("Hello World");
	CString str2(str1);
	CString str3(str1);

	//cout << str1.GetString() << endl;
	cout << "str1��" << str1.GetString() << " StringLength��" << str1.GetStringLength() << endl;
	cout << "str2��" << str2.GetString() << " StringLength��" << str2.GetStringLength() << endl;
#endif //  ���Բ��Թ��������

#if 0
	CString str0("Hello");
	CString str1("World");
	//str.Append(" ");
	//str.Append(str1);

	//Append ���ض�������� str.Append(" ")����һ����ʱ����Append(str1);���ĵ�����ʱ�����޸ĵ����ݸ�strû�й�ϵ
	str0.Append(" ").Append(str1).Append("Test").Append("��������");

	//������ã�str.Append(" ") ��Ӱ��str����Append(str1)����Ӱ��str����  
#endif // 0 �����ַ���ƴ�� ->�൱��strcat


#if 0
	CString str1("Hello");
	str1.Copy("world");
	cout << "str1��" << str1.GetString() << " StringLength��" << str1.GetStringLength() << endl;
	str1.Copy("StrcpyTest");
	cout << "str1��" << str1.GetString() << " StringLength��" << str1.GetStringLength() << endl;
#endif // 0 �����ַ������� -> strcpy

#if 0
	CString str1("Hello World");
	str1.Find("Test");
#endif // 0 �����ڻ��������������ָ�����ַ���

#if 0
	CString str1("Test Hello World Test");
	std::cout << "��ǰ�������ڵ�����Ϊ��" << std::endl;
	std::cout << "str��" << str1.GetString() << " strlength��" << str1.GetStringLength() << std::endl;
	str1.ReverseFind("World");
#endif // 0 �����ڻ��������������ָ�����ַ���

#if 0
	CString str1("Hello");
	CString str2("hello");
	cout << "�滻ǰ�Ľ��Ϊ��" << endl;
	cout << "Str1��" << str1.GetString() << " strLength��" << str1.GetStringLength() << endl;
	str1.Replace(str1, str2);
	cout << "�滻��Ľ��Ϊ��" << endl;
	cout << "Str1��" << str1.GetString() << " strLength��" << str1.GetStringLength() << endl;
#endif // 0 �����ַ����滻 �� szStr �滻�� szDst

#if 0
	const char* StrTemp = "ileemi";
	int nStrLength = strlen(StrTemp);
	CString str1("HelloWorld");
	std::cout << "�滻ǰ�������ڵ�����Ϊ��" << std::endl;
	std::cout << "str1��" << str1.GetString() << " strlength��" << str1.GetStringLength() << std::endl;

	std::cout << "�滻�󻺳����ڵ�����Ϊ��" << std::endl;
	str1.Replace(nStrLength, StrTemp);			//nStrLength�����������洢���ַ����ֽڳ��ȣ��滻ʧ��
	std::cout << "str1��" << str1.GetString() << " strlength��" << str1.GetStringLength() << std::endl;
#endif // 0 �����滻 ָ�����ȵ��ַ�����ԭ���Ļ�����ȥ


#if 0
	CString str1("Hello World");
	std::cout << "��ȡǰ�������ڵ�����Ϊ��" << std::endl;
	std::cout << "str1��" << str1.GetString() << " strlength��" << str1.GetStringLength() << std::endl;
	int nMiddle = str1.GetStringLength() / 2;
	str1.Mid(nMiddle, 2);	//�ӻ������д洢���ַ����м俪ʼ����
	str1.Left(5);		//�ӻ������д洢���ַ�������࿪ʼ����
	str1.Right(5);		//�ӻ������д洢���ַ������Ҳ࿪ʼ����
	std::cout << "��ȡ�󻺳����ڵ�����Ϊ��" << std::endl;
	std::cout << "str1��" << str1.GetString() << " strlength��" << str1.GetStringLength() << std::endl;
#endif // 0 ���Ի������ڵ��ַ�����ȡ����


#if 0
	CString str("\r\n  Hello  world  \r\n");
	std::cout << "��ǰ�������ڵ�����Ϊ��" << std::endl;
	std::cout << "str��" << str.GetString() << " strlength��" << str.GetStringLength() << std::endl;
	str.Strip();
	std::cout << "������������ַ���ǰ�漰��������пո�tab���س���Ļ���������Ϊ��" << std::endl;
	std::cout << "str��" << str.GetString() << " strlength��" << str.GetStringLength() << std::endl;
#endif // 0 ����ȥ�����������ַ���ͷ����β���Ŀհ��ַ�


#if 0
	CString str;
	str.Format("%d %f %s", 666, 999.999, "Hello World");
	std::cout << "ʹ��Format�������������е����ݸ�ʽ����Ϊ��" << std::endl;
	std::cout << "str��" << str.GetString() << " strlength��" << str.GetStringLength() << std::endl;
#endif // 0  ���Խ��������е����ݸ�ʽ��(���㣬�����ȸ�ʽ��Ϊ�ַ���)


	/*
	Date��2020/05/14
	����CString�࣬���볣��Ա�������������¾�̬����
	*/

#if 0
	CString str1 = CString::ValueOf(true);
	cout << str1.GetString() << endl; //���true
	//cout << true << endl; //���1  
#endif // 0 ����static CString ValueOf(bool b);

	CString str1;
	//���ԣ����ַ� 'a' �� �ַ� "a" ����ʽ���
	cout << str1.ValueOf(true).GetString() << endl;
	cout << str1.ValueOf('a').GetString() << endl;
	cout << str1.ValueOf(99.99).GetString() << endl;
	cout << str1.ValueOf(99.99f).GetString() << endl;
	cout << str1.ValueOf(666).GetString() << endl;
	cout << str1.ValueOf(5201314l).GetString() << endl;
	cout << str1.ValueOf("HelloWorld").GetString() << endl;
	cout << str1.CopyValueOf("Hello World", 2, 5).GetString() << endl;
	cout << str1.FromFormat("%s %d %f %lf", "Hello World", 999, 66.66f, 2020.0514).GetString() << endl;

#if 0
	CString nVal;
	nVal = 999;
	cout << nVal << endl;

	CString str1("Hello");
	// ==
	bool bResual1 = (str1 == "Hello");
	cout << bResual1 << endl;

	// != 
	bool bResual2 = (str1 != "Hello");
	cout << bResual2 << endl;
	if (!("World" == str1))
	{
		cout << false << endl;
	};

	CString str2("Hello");
	CString str3("Apple");

	bool nResual3 = str2 > str3;
	cout << nResual3 << endl;
#endif //  �������������


	/*
	4.��CMyString��Ϊ������CMyString��Ĺ��캯����new�����ڴ档��������ڴ治�ɹ���
	����try����׳�һ��char�����쳣����catch��䲶����쳣��ͬʱ���쳣�������������
	����ʽ���ڴ��ڴ����ʧ����һ�쳣���д���Աȣ�����쳣������ŵ㡣
	*/

	//try
	//{
	//	CString str1("Hello World");
	//	CString str2(str1);
	//}
	//catch (const char* szError)
	//{
	//	cout << "�쳣���룺" << szError << endl;
	//}
	//catch (...)
	//{
	//	cout << "���������������ֵ" << endl;
	//}


	/*
	5.�ڵ�4��Ļ����ϣ����������±������[], ʹ֮�����ж��봦���±�Խ��Ĺ��ܡ�
	*/



	char szBuff[32] = "Hello World";
	CString ary(szBuff);
	try
	{
		ary[0] = 'h';
		ary[30] = 'w';
		cout << ary.GetString() << endl;
	}
	catch (const char* szError)
	{
		cout << "�쳣���룺" << szError << endl;
	}
	catch (...)
	{
		cout << "���������������ֵ" << endl;
	}
	cout << ary.GetString() << endl;



	//CString str;
	//CString str1("Hello World");
	//CString str2(str1);
	//CString str3(str);


	//str.Append("Hello").Append(" World").Append(str1);
	//str1.Append("Test");

	//char szBuff[] = "Hello World";
	//char* p0 = _strrev(szBuff);


	CString str("H:\\CR37\\c++\\17 ����\\CMyString\\CMyString.cpp");

	int nIdx = str.Find("ssss");
	nIdx = str.Find("CMyString");
	nIdx = str.ReverseFind("aaa");
	nIdx = str.ReverseFind("CMyString");

	CString strTmp = str.Mid(nIdx, 5);
	CString strTmp1 = str.Right(3);
	CString strTmp2 = str.Left(2);

	str.Replace("CMyString", "CString");
	nIdx = str.ReverseFind("CString");
	str.Replace(nIdx, "CString", "CMyString");

	CString strFmt;
	strFmt.Format("%s %d %lf %f %08x", "ileemi", 999, 99.66, 6.18f, 0xAAAAAAAA);

	cout << strFmt << endl;

	CString strTemp("\n\t\tdasds sds sdasd \t \t \t");
	strTemp.Strip();
	cout << strTemp << endl;
	return 0;
}