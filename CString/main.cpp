#include <iostream>
#include "CString.h"

int main()
{
#if 0
	CString str1("Hello World");
	CString str2(str1);
	CString str3(str1);

	//cout << str1.GetString() << endl;
	cout << "str1：" << str1.GetString() << " StringLength：" << str1.GetStringLength() << endl;
	cout << "str2：" << str2.GetString() << " StringLength：" << str2.GetStringLength() << endl;
#endif //  测试测试构造和析构

#if 0
	CString str0("Hello");
	CString str1("World");
	//str.Append(" ");
	//str.Append(str1);

	//Append 返回对象的类型 str.Append(" ")创建一块临时对象，Append(str1);更改的是临时对象，修改的内容跟str没有关系
	str0.Append(" ").Append(str1).Append("Test").Append("哈哈哈哈");

	//添加引用，str.Append(" ") 将影响str本身，Append(str1)继续影响str本身  
#endif // 0 测试字符串拼接 ->相当于strcat


#if 0
	CString str1("Hello");
	str1.Copy("world");
	cout << "str1：" << str1.GetString() << " StringLength：" << str1.GetStringLength() << endl;
	str1.Copy("StrcpyTest");
	cout << "str1：" << str1.GetString() << " StringLength：" << str1.GetStringLength() << endl;
#endif // 0 测试字符串拷贝 -> strcpy

#if 0
	CString str1("Hello World");
	str1.Find("Test");
#endif // 0 测试在缓冲区中正向查找指定的字符串

#if 0
	CString str1("Test Hello World Test");
	std::cout << "当前缓冲区内的数据为：" << std::endl;
	std::cout << "str：" << str1.GetString() << " strlength：" << str1.GetStringLength() << std::endl;
	str1.ReverseFind("World");
#endif // 0 测试在缓冲区中逆向查找指定的字符串

#if 0
	CString str1("Hello");
	CString str2("hello");
	cout << "替换前的结果为：" << endl;
	cout << "Str1：" << str1.GetString() << " strLength：" << str1.GetStringLength() << endl;
	str1.Replace(str1, str2);
	cout << "替换后的结果为：" << endl;
	cout << "Str1：" << str1.GetString() << " strLength：" << str1.GetStringLength() << endl;
#endif // 0 测试字符串替换 将 szStr 替换成 szDst

#if 0
	const char* StrTemp = "ileemi";
	int nStrLength = strlen(StrTemp);
	CString str1("HelloWorld");
	std::cout << "替换前缓冲区内的数据为：" << std::endl;
	std::cout << "str1：" << str1.GetString() << " strlength：" << str1.GetStringLength() << std::endl;

	std::cout << "替换后缓冲区内的数据为：" << std::endl;
	str1.Replace(nStrLength, StrTemp);			//nStrLength超过缓冲区存储的字符串字节长度，替换失败
	std::cout << "str1：" << str1.GetString() << " strlength：" << str1.GetStringLength() << std::endl;
#endif // 0 测试替换 指定长度的字符串到原来的缓冲区去


#if 0
	CString str1("Hello World");
	std::cout << "提取前缓冲区内的数据为：" << std::endl;
	std::cout << "str1：" << str1.GetString() << " strlength：" << str1.GetStringLength() << std::endl;
	int nMiddle = str1.GetStringLength() / 2;
	str1.Mid(nMiddle, 2);	//从缓冲区中存储的字符串中间开始查找
	str1.Left(5);		//从缓冲区中存储的字符串最左侧开始查找
	str1.Right(5);		//从缓冲区中存储的字符串最右侧开始查找
	std::cout << "提取后缓冲区内的数据为：" << std::endl;
	std::cout << "str1：" << str1.GetString() << " strlength：" << str1.GetStringLength() << std::endl;
#endif // 0 测试缓冲区内的字符串提取功能


#if 0
	CString str("\r\n  Hello  world  \r\n");
	std::cout << "当前缓冲区内的数据为：" << std::endl;
	std::cout << "str：" << str.GetString() << " strlength：" << str.GetStringLength() << std::endl;
	str.Strip();
	std::cout << "清除缓冲区内字符串前面及后面的所有空格、tab、回车后的缓冲区数据为：" << std::endl;
	std::cout << "str：" << str.GetString() << " strlength：" << str.GetStringLength() << std::endl;
#endif // 0 测试去除缓冲区内字符串头部和尾部的空白字符


#if 0
	CString str;
	str.Format("%d %f %s", 666, 999.999, "Hello World");
	std::cout << "使用Format方法将缓冲区中的数据格式化后为：" << std::endl;
	std::cout << "str：" << str.GetString() << " strlength：" << str.GetStringLength() << std::endl;
#endif // 0  测试将缓冲区中的数据格式化(浮点，整数等格式化为字符串)


	/*
	Date：2020/05/14
	完善CString类，加入常成员函数，增加以下静态方法
	*/

#if 0
	CString str1 = CString::ValueOf(true);
	cout << str1.GetString() << endl; //输出true
	//cout << true << endl; //输出1  
#endif // 0 测试static CString ValueOf(bool b);

	CString str1;
	//测试：将字符 'a' 以 字符 "a" 的形式输出
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
#endif //  测试运算符重载


	/*
	4.以CMyString类为例，在CMyString类的构造函数中new分配内存。如果分配内存不成功，
	则用try语句抛出一个char类型异常，用catch语句捕获该异常。同时将异常处理机制与其它
	处理方式对内存内存分配失败这一异常进行处理对比，体会异常处理的优点。
	*/

	//try
	//{
	//	CString str1("Hello World");
	//	CString str2(str1);
	//}
	//catch (const char* szError)
	//{
	//	cout << "异常代码：" << szError << endl;
	//}
	//catch (...)
	//{
	//	cout << "接收其它错误代码值" << endl;
	//}


	/*
	5.在第4题的基础上，重载数组下标操作符[], 使之具有判断与处理下标越界的功能。
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
		cout << "异常代码：" << szError << endl;
	}
	catch (...)
	{
		cout << "接收其它错误代码值" << endl;
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


	CString str("H:\\CR37\\c++\\17 补课\\CMyString\\CMyString.cpp");

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