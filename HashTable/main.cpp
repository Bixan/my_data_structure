#include <iostream>
#include "CHashTable.h"
#include <unordered_map>
#include <string>
using namespace std;

int main()
{
#if 1
	CHashTable hash;
	hash.Insert(1, 1.1);
	hash.Insert(2, 2.2);
	hash.Insert(3, 3.3);
	hash.Insert(4, 4.4);
	hash.Insert(5, 5.5);
	hash.Insert(6, 6.6);
	hash.Insert(7, 7.7);
	hash.Insert(8, 8.8);
	hash.Insert(9, 9.9);
	hash.Insert(17, 17.17);
	hash.Insert(25, 25.25);

	
	cout << hash.Find(4) << endl;
	cout << hash[17] << endl;
	hash[17] = 17.71;
	cout << hash[17] << endl;

	cout << hash[18] << endl;
	hash[18] = 18.18;
	cout << hash[18] << endl;

	hash.Remove(1);
	hash.Remove(17);
#endif // 测试

#if 0
	unordered_map<string, string> map;
	map.insert({ "张三", "001" });
	map.insert({ "李四", "002" });
	map.insert({ "张三", "003" });
	map.insert({ "王五", "004" });
	map.insert({ "哈哈", "005" });
	map.insert({ "嘻嘻", "006" });

	cout << map["张三"] << endl;
	cout << map["哈哈"] << endl;


	unordered_map<string, int> map1;
	map1.insert({ "张三", 20 });
	map1.insert({ "李四", 21 });
	map1.insert({ "张三", 22 });
	map1.insert({ "王五", 23 });
	map1.insert({ "哈哈", 34 });
	map1.insert({ "嘻嘻", 27 });

	cout << map1["张三"] << endl;
	cout << map1["哈哈"] << endl;



	unordered_map<int, string> map2;
	map2.insert({ 1, "张三" });
	map2.insert({ 2, "李四" });
	map2.insert({ 3, "张三" });
	map2.insert({ 4, "王五" });
	map2.insert({ 5, "哈哈" });
	map2.insert({ 6, "嘻嘻" });

	map2.erase(2);
	cout << map2[1] << endl;
	cout << map2[2] << endl;

	map2.find(2);

	cout << map2[7] << endl;

#endif // 0

	return 0;
}