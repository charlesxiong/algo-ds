#ifndef _TRIE_TREE_H_
#define _TRIE_TREE_H_

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

/** 
 * R表示字符集的基，字符的种类数－单个结点所含有的最大子树个数
 * ALPHA表示设定字符集的起始字符,比如小写字母字符集起始为'a',数字字符集开始为'0'
 */
#define R 26
#define ALPHA 'a'

/**
 * is_str标记当前字符是否位于串的末尾
 * count表示该单词出现的次数
　* next数组表示指向各子树的指针
 */
struct trie_node_t {
	bool is_str;
	trie_node_t *next[R];
	trie_node_t(): is_str(false) {
		memset(next,0,sizeof(next));
	} 
};

/**
 * Trie树的用途
 * 统计和排序大量的字符串，如结点上设置计数域，用于进行文本字符串的词频统计
 * 用于查找Trie树中某字符串是否存在前缀串、最长前缀串等等
 * 也可用作查找树，键为字符集R的字符串，对应的值可以根据需求设置，如次数，
 */
class Trie {
public:

	Trie():root(new trie_node_t()),size(1) {}

	~Trie() {
		delete_trie_node(root);
	}

	void insert(string word);

	bool find(string word);

	void remove(string word);

	/*是否含有前缀串pre*/
	bool contains_prefix(string pre);

	/*找出所有以pre开头的字符串*/
	vector<string> keys_with_prefix(string pre);

	/*找出所有的字符串*/
	vector<string> keys_all();

	/*找出匹配模式串pat的字符串*/
	vector<string> keys_that_match(string pat);

	/*找到给定字符串的前缀中最长的字符串*/
	string longest_prefix_of(string word);

private:
	trie_node_t *root;
	int size;

private:
	void delete_trie_node(trie_node_t *root);
	trie_node_t* remove_trie_word(trie_node_t *root,string word,int d);
	void collect_string(trie_node_t *root,string pre,vector<string>& res);
	void collect_string_pat(trie_node_t *root,string pre,string pat,vector<string>& res);
};


#endif