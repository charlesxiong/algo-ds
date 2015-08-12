#include "trie.h"

void Trie::delete_trie_node(trie_node_t *root) {
	for(int i = 0;i < R;i++) {
		if(root->next[i] != NULL) {
			delete_trie_node(root->next[i]);
		}
	}
	delete root;
}

void Trie::insert(string word) {
	trie_node_t *cur = root;
	auto iter = word.begin();
	while(iter != word.end()) {
		int index = *iter - ALPHA;
		if(cur->next[index] == NULL) {
			cur->next[index] = new trie_node_t();
			size++;
		}
		cur = cur->next[index]; 
		++iter; /*移到下一个字符*/
	}
	cur->is_str = true;
	//cur->count++;
}

bool Trie::find(string word) {
	trie_node_t *cur = root;
	auto iter = word.begin();
	while(iter != word.end() && cur) {
		cur = cur->next[*iter - ALPHA];
		++iter;
	}
	return (cur != NULL && cur->is_str == true);
}

/**
 * 用递归思路更为简单
 * 先查找到该字符串对应的结点，将其值设为空
 * 如果结点还有非空子链接，不作任何事；
 * 如果所有链接全为空，删除该结点并且
 * 如果使得它的父节点的所有链接也均为空，就需要递归向上删除父节点
 */
trie_node_t* Trie::remove_trie_word(trie_node_t *root,string word,int d) {
	if(root == NULL) return NULL;

	/*继续查找到对应的结点*/
	if(d == static_cast<int>(word.length())) {
		root->is_str = false;
	} else {
		int index = word[d] - ALPHA;
		root->next[index] = remove_trie_word(root->next[index],word,d + 1); 
	}

	/*向上删除发现是字符串的标记，该结点递归返回*/
	if(root->is_str == true) return root; 

	/*如果不是字符串标记但是有非空子链接，该结点递归返回; 否则删除该结点*/
	int i;
	for(i = 0;i < R;i++) {
		if(root->next[i] != NULL)
			return root;
	}
	if(i == R) {
		delete root;
	}
	return NULL;
}

void Trie::remove(string word) {
	root = remove_trie_word(root,word,0);
}

bool Trie::contains_prefix(string pre) {
	trie_node_t *cur = root;
	auto iter = pre.begin();
	while(iter != pre.end() && cur) {
		cur = cur->next[*iter - ALPHA];
		++iter;
	}
	return (cur != NULL);
}

/**
 * 收集所有从匹配前缀字符串所对应的字典树的字符串
 */
void Trie::collect_string(trie_node_t *root,string pre,vector<string>& res) {
	if(root == NULL) return;
	if(root->is_str == true) res.push_back(pre);
	for(int i = 0;i < R;i++){
		char c = ALPHA + i;
		collect_string(root->next[i],pre + c,res);
	}
}

vector<string> Trie::keys_with_prefix(string pre) {
	vector<string>  res;

	/*第一步: 首先看前缀是否存在并返回对应的单词查找树如果不存在*/
	trie_node_t *cur = root;
	auto iter = pre.begin();
	while(iter != pre.end() && cur) {
		cur = cur->next[*iter - ALPHA];
		++iter;
	}

	/*第二步: 收集匹配前缀的字符串*/
	collect_string(cur,pre,res);
	return res;
}

/*找出所有的字符串,且已经排序好*/
vector<string> Trie::keys_all() {
	return keys_with_prefix("");
}


/**
 * 找出匹配模式串pat的字符串
 * 如果模式中含有通配符.需要递归调用所有的子树
 * 其他字符只需要处理指定字符的子树
 * 不考虑超过模式串长度的字符串，并未考虑星号通配符
 */

void Trie::collect_string_pat(trie_node_t *root,string pre,string pat,vector<string>& res) {
	if(root == NULL) return;
	auto d = pre.length();
	if(d == pat.length() && root->is_str == true) res.push_back(pre);
	if(d == pat.length()) return; //不作处理

	char cur = pat[d];//取当前字符
	/*若是通配符，所有的字符都要考虑；否则只需考虑对应字符*/
	if(cur == '.') {
		for(int i = 0;i < R;i++) {
			char c = ALPHA + i;
			collect_string_pat(root->next[i],pre + c,pat,res); 
		}
	} else {
		int index = cur - ALPHA;
		collect_string_pat(root->next[index],pre + cur,pat,res);
	}
}

vector<string> Trie::keys_that_match(string pat) {
	vector<string> res;
	collect_string_pat(root,"",pat,res);
	return res;
}

/** 
 * 找到给定字符串的前缀中最长的字符串
 * 最长前缀匹配的可能情形
 * 例如在字符串she,shells中分别查找
 * she,shell,shellsort,shelters中最长的前缀串，分别对应如下情况
 *　被查找的字符串结束且该结点是字符串末尾
 * 被查找的字符串结束且该结点不是字符串末尾
 * 查找在空链接时结束(正常结束)，返回之前最近的一个字符串
 * 查找在空链接时结束(字符不匹配时)，返回之前最近的一个字符串
 */
string Trie::longest_prefix_of(string word) {
	trie_node_t *cur = root;
	auto iter = word.begin();
	int len = 0;
	while(iter != word.end() && cur) {
		cur = cur->next[*iter - ALPHA];
		if(cur == NULL) break;
		if(cur->is_str == true) {
			len = iter - word.begin() + 1;
		}
		++iter;
	}
	return word.substr(0,len);
}





