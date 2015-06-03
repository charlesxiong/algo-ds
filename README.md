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



# Generics-C: 基于泛型C实现的各种数据结构

-----

它实现的数据结构,如图下(待扩充):
![数据结构](https://github.com/charlesxiong/algo-ds/blob/master/generics-java/images/Selection_036.png)

每个文件夹对应实现不同的功能，例如有基础结构、查找、排序、字符串、图论等。

对于每一个数据结构，它含有3个文件。以二叉查找树为例：

- [bst.h](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.h) ：头文件定义其数据结构和API
- [bst.c](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c) ：实现二叉查找树的各种操作: 
- [bst_test.c](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst_test.c) ：测试二叉查找树的操作和时间消耗(测试用例并不全面): 

注意：在实现后务必使用[Valgrind](http://valgrind.org/docs/manual/quick-start.html)工具检查程序内存使用是否存在问题,命令如下:

```
valgrind --leak-check=yes program arg1 arg2 ...
```
-----

**Utils**

它提供了必要的计时操作和常见的基础数据结构，以下均是基于泛型的C实现:

- [计时器](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/timer.c) 
- [动态数组](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/dynarr.c)
- [单链表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/linklist.c)
- [双向链表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/dlinklist.c)
- [栈](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/stack.c)
- [队列](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/queue.c)
- [二叉树](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bintree.c)
- [位示图](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bitmap.c)


-----

**Sort**

它提供了常见的插入排序(直接插入排序、折半插入排序、希尔排序)、交换排序(冒泡排序、快速排序)、选择排序(简单选择排序、堆排序)、二路归并排序等比较排序，还包括了一些非基于比较的排序算法如计数排序、基数排序、桶排序等。

- [排序]()



-----

**Search**

它主要是以不同的数据结构实现查询操作，例如以树结构为形式的查找树、以链表为形式的跳跃表、以数组或链表为形式的散列表等等。主要实现有:

- [二分查找](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/binsearch.c)
- [二叉查找树](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c)
- [散列表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/hashtbl.c)
- [AVL树]()
- [2-3树]()
- [红黑树]()
- [跳跃表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/skiplist.c)
- [Trie树]()
- [数字查找树]()
- [基数排序树]()
- [最小堆]()
- [最大堆]()
- [并查集](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/uf.c)


-----

**String**

