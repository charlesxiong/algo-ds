# Introduction
**����C��Javaʵ�ֵ����ݽṹ���㷨��Ҫ��Ϊ5��:**��
* �������ݽṹ(��̬���顢����ջ�����е�)
* �ֵ���ṹ(�����������AVL�������������ϣ��B-��)
* �����㷨(���š������򡢹鲢�����)
* �ַ����㷨(Digital Search Tree��Trie������׺������׺���顢AC�Զ�����KMP��ƥ������㷨��������ʽ��)
* ͼ�㷨(DFS��BFS����С�����������·��)

---

**����C++ʵ�ֵ��㷨��Ʋ�����Ҫ��Ϊ���¼���:**
* �ݹ�����β���
* ��̬�滮�㷨
* ̰���㷨
* ���ݷ�
* ��֧�޽編
* �����㷨
* ���Թ滮���������㷨
* �����㷨

---

# Implementation in C

��ʵ�ֵ����ݽṹ,��ͼ��(������):

![���ݽṹ](https://github.com/charlesxiong/algo-ds/blob/master/generics-java/images/Selection_036.png)

ÿ���ļ��ж�Ӧʵ�ֲ�ͬ�Ĺ��ܣ������л����ṹ�����ҡ������ַ�����ͼ�۵ȡ�

����ÿһ�����ݽṹ��������3���ļ����Զ��������Ϊ����

- [bst.h](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.h) ��ͷ�ļ����������ݽṹ��API
- [bst.c](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c) ��ʵ�ֶ���������ĸ��ֲ���: 
- [bst_test.c](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst_test.c) �����Զ���������Ĳ�����ʱ������(������������ȫ��): 

ע�⣺��ʵ�ֺ����ʹ��[Valgrind](http://valgrind.org/docs/manual/quick-start.html)���߼������ڴ�ʹ���Ƿ��������,��������:

```
valgrind --leak-check=yes program arg1 arg2 ...
```
-----

**Utils**

���ṩ�˱�Ҫ�ļ�ʱ�����ͳ����Ļ������ݽṹ�����¾��ǻ��ڷ��͵�Cʵ��:

- [��ʱ��](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/timer.c) 
- [��̬����](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/dynarr.c)
- [������](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/linklist.c)
- [˫������](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/dlinklist.c)
- [ջ](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/stack.c)
- [����](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/queue.c)
- [������](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bintree.c)
- [λʾͼ](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bitmap.c)
- [��������](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bigint.c)


-----

**Sort**

���ṩ�˳����Ĳ�������(ֱ�Ӳ��������۰��������ϣ������)����������(ð�����򡢿�������)��ѡ������(��ѡ�����򡢶�����)����·�鲢����ȱȽ����򣬻�������һЩ�ǻ��ڱȽϵ������㷨��������򡢻�������Ͱ����ȡ�

- [����](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/sort.c)


-----

**Search**

����Ҫ���Բ�ͬ�����ݽṹʵ�ֲ�ѯ���������������ṹΪ��ʽ�Ĳ�������������Ϊ��ʽ����Ծ�������������Ϊ��ʽ��ɢ�б�ȵȡ���Ҫʵ����:

- [���ֲ���](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/binsearch.c)
- [���������](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c)
- [ɢ�б�](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/hashtbl.c)
- [��Ծ��](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/skiplist.c)
- [��С��](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/minheap.c)
- [����]()
- [���鼯](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/uf.c)
- [AVL��]()
- [2-3��]()
- [�����]()
- [���ֲ�����]()
- [����������]()


-----

**String**
- [Trie��](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/string/trie.cpp)

----

# Implementation in Java

---

# Algorithm Design


---

**�ο�����:**
- [Algorithms,4th Edition](http://algs4.cs.princeton.edu/home/)
- [Algorithm Design](http://www.amazon.cn/%E5%A4%A7%E5%AD%A6%E8%AE%A1%E7%AE%97%E6%9C%BA%E6%95%99%E8%82%B2%E5%9B%BD%E5%A4%96%E8%91%97%E5%90%8D%E6%95%99%E6%9D%90%E7%B3%BB%E5%88%97-%E7%AE%97%E6%B3%95%E8%AE%BE%E8%AE%A1-%E5%85%8B%E8%8E%B1%E5%9B%A0%E4%BC%AF%E6%A0%BC/dp/B00AX3NRKY/ref=pd_sim_14_1?ie=UTF8&refRID=1KKT6S2ASJSDYVW7MHQ5)
- [List of data structures](http://en.wikipedia.org/wiki/List_of_data_structures)
- [The lesser known but useful data structures](http://stackoverflow.com/questions/500607/what-are-the-lesser-known-but-useful-data-structures?page=1&tab=votes#tab-top)
- [The Archive of Interesting Code](http://www.keithschwarz.com/interesting/)
- [NOCOW](http://www.nocow.cn/index.php/NOCOW%E5%9C%B0%E5%9B%BE)


