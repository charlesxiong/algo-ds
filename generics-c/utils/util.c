
/**
 * C++中split函数
 *
 */
vector<string> split(string s,string delim) {
	vector<string> res;
	size_t last = 0;
	size_t idx = s.find_first_of(delim,last);
	while(idx != string::npos) {
		res.push_back(s.substr(last,idx - last));
		last = idx + 1;
		idx = s.find_first_of(delim,last);
	}

	if(idx - last > 0) {
		res.push_back(s.substr(last,idx - last));
	}
	return res;
}


/**
 *
 * 求C(n,k)的组合数
 * 快速计算出组合数避免溢出
 */

long long comb_k_of_n(int n,int k) {
	long long res = 1;
	for(int i = 1;i <= k;i++)
		res *= (n - k + i) / i;
	return res;

}

/**
 *　康托展开
 *　分析当前数，判断比当数小且没有出现过的数字
 * 可以开辟一个空间用于快速存储12!以内的表示
　* 用于判断某个数是第多少个有序数
　* 如abcdfegh...按由小到大的字典序排序是第几个
 */
long long sum[13] = {1,1,2,6,24,120,
	720,5040,40320,362880,3628800,39916800,479001600};

long long getPertNum(string a) {
	long long cnt = 0;
	for(int i = 0;;i < 12;i++) {
		long long tmp = 0;
		/*遍历后者是否有更小的数字*/
		for(int j = i + 1;j < 12;j++) {
			if(a[j] < a[i]) tmp++;
		}
		cnt += tmp * sum[12 - i - 1];
	}
	return cnt + 1;
}


/**
 * 选择第3列和第4列的内容，按照新的第二列进行排序去重
 *　然后按多个字段排序,最后用awk输出多个字段
　* cat xxx | cut -d ' ' -f 3,4 | sort -k2 | uniq -c
 * | sort -k3 -k1 -r | awk '{print $2,$3}' > xxx.txt
 *
 */


