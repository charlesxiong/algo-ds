
/**
 * C++��split����
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
 * ��C(n,k)�������
 * ���ټ����������������
 */

long long comb_k_of_n(int n,int k) {
	long long res = 1;
	for(int i = 1;i <= k;i++)
		res *= (n - k + i) / i;
	return res;

}

/**
 *������չ��
 *��������ǰ�����жϱȵ���С��û�г��ֹ�������
 * ���Կ���һ���ռ����ڿ��ٴ洢12!���ڵı�ʾ
��* �����ж�ĳ�����ǵڶ��ٸ�������
��* ��abcdfegh...����С������ֵ��������ǵڼ���
 */
long long sum[13] = {1,1,2,6,24,120,
	720,5040,40320,362880,3628800,39916800,479001600};

long long getPertNum(string a) {
	long long cnt = 0;
	for(int i = 0;;i < 12;i++) {
		long long tmp = 0;
		/*���������Ƿ��и�С������*/
		for(int j = i + 1;j < 12;j++) {
			if(a[j] < a[i]) tmp++;
		}
		cnt += tmp * sum[12 - i - 1];
	}
	return cnt + 1;
}


/**
 * ѡ���3�к͵�4�е����ݣ������µĵڶ��н�������ȥ��
 *��Ȼ�󰴶���ֶ�����,�����awk�������ֶ�
��* cat xxx | cut -d ' ' -f 3,4 | sort -k2 | uniq -c
 * | sort -k3 -k1 -r | awk '{print $2,$3}' > xxx.txt
 *
 */


