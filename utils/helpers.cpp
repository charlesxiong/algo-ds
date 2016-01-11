#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;


/****************************************************************************************
 *
 * string split functions implementation  
 *
 ***************************************************************************************/
vector<string> split(string s,string delim) {
	vector<string> result;
	size_t start = 0;
	size_t idx = s.find_first_of(delim,start);

	while(idx != string::npos) {
		result.push_back(s.substr(start,idx - start));
		start = idx + 1;
		if(start == string::npos) {
			break;
		}
		idx = s.find_first_of(delim,start);
	}
	// two special conditions
	// start = 0,idx = s.end()
	// start = s.end(),it will stop searching
	if(idx - start > 0) 
		result.push_back(s.substr(start,idx - start));
	return result;
}

/**
 *
 * split_test(",",",");
 * split_test("a",",");
 * split_test("a,",",");
 * split_test("a,b",",");
 * split_test("abc",",");
 * split_test("abc,",",");
 * split_test("ab,cd",",");
 * split_test("ab,cd,",",");
 */
void split_test(string s,string delim) {
	vector<string> res = split(s,delim);
	for_each(res.begin(), res.end(), [](const string& s) { cout << s << " ";});
	cout << endl;
}
/**************************************************************************************/

int main() {
    
	return 0;
}
