#include "trie.h"
#include <iostream>
#include <queue>
#include <string>

int main() {
	Trie tree;
	tree.insert("word");
	tree.insert("by");
	tree.insert("sea");
	tree.insert("sells");
	tree.insert("she");
	tree.insert("shells");
	tree.insert("the");
	tree.insert("shore");
	tree.insert("shellsort");

	cout << "所有存在的字符串" << endl;
	vector<string>  res1 = tree.keys_all();
	for(auto s : res1)
		cout << s << " ";
	cout << endl;
	cout << endl;
	cout << "所有存在的字符串" << endl;
	tree.remove("shellsort");
	vector<string>  res4 = tree.keys_all();
	for(auto s : res4)
		cout << s << " ";
	cout << endl;

	
	cout << "测试是否存在该字符串" << endl;
	cout << tree.find("shells") << endl;
	cout << tree.find("hello") << endl;
	cout << tree.contains_prefix("wo") << endl;
	cout << endl;
	cout << "以字符串'sh'开头的所有字符串" << endl;
	vector<string>  res = tree.keys_with_prefix("sh");
	for(auto s : res)
		cout << s << " ";
	cout << endl;
	cout << endl;
	
	cout << endl;
	cout << "匹配'.he'的所有字符串" << endl;
	vector<string>  res2 = tree.keys_that_match(".he");
	for(auto s : res2)
		cout << s << " ";
	cout << endl;
	cout << endl;
	cout << "匹配's..'的所有字符串" << endl;
	vector<string>  res3 = tree.keys_that_match("s..");
	for(auto s : res3)
		cout << s << " ";
	cout << endl;
	
	cout << endl;
	cout << "最长的前缀字符串" << endl;
	string s1 = tree.longest_prefix_of("she");
	string s2 = tree.longest_prefix_of("shell");
	string s3 = tree.longest_prefix_of("shellsort");
	string s4 = tree.longest_prefix_of("shelters");
	cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
	return 0;
}