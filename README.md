# Algorithms and Data Structures

This repository contains most basic algorithms and data structures using generic method implementation in c , which provides unit testing , functional and time complexity tests to guarantee that there are less obvious bugs .

-----

# Introduction
There are a lot of useful references for the implementations . Here is the reference list which helps me a lot .
- [Algorithms,4th Edition](http://algs4.cs.princeton.edu/home/)
- [List of data structures](http://en.wikipedia.org/wiki/List_of_data_structures)
- [The lesser known but useful data structures](http://stackoverflow.com/questions/500607/what-are-the-lesser-known-but-useful-data-structures?page=1&tab=votes#tab-top)
- [The Archive of Interesting Code](http://www.keithschwarz.com/interesting/)
- [NOCOW](http://www.nocow.cn/index.php/NOCOW%E5%9C%B0%E5%9B%BE)



# Generics-C: ���ڷ���Cʵ�ֵĸ������ݽṹ

-----

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


-----

**Sort**

���ṩ�˳����Ĳ�������(ֱ�Ӳ��������۰��������ϣ������)����������(ð�����򡢿�������)��ѡ������(��ѡ�����򡢶�����)����·�鲢����ȱȽ����򣬻�������һЩ�ǻ��ڱȽϵ������㷨��������򡢻�������Ͱ����ȡ�

- [����]()



-----

**Search**

����Ҫ���Բ�ͬ�����ݽṹʵ�ֲ�ѯ���������������ṹΪ��ʽ�Ĳ�������������Ϊ��ʽ����Ծ�������������Ϊ��ʽ��ɢ�б�ȵȡ���Ҫʵ����:

- [���ֲ���](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/binsearch.c)
- [���������](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c)
- [ɢ�б�](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/hashtbl.c)
- [AVL��]()
- [2-3��]()
- [�����]()
- [��Ծ��](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/skiplist.c)
- [Trie��]()
- [���ֲ�����]()
- [����������]()
- [��С��]()
- [����]()
- [���鼯](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/uf.c)


-----

**String**

