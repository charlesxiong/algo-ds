# 数据结构和算法(based on C)

* 基本数据结构(动态数组、链表、栈及队列等)
* 字典类结构(二叉查找树、AVL树、红黑树、哈希表、B-树)
* 排序算法(快排、堆排序、归并排序等)
* 字符串算法(Digital Search Tree、Trie树、后缀树、后缀数组、AC自动机、KMP等匹配查找算法、正则表达式等)
* 图算法(DFS、BFS、最小生成树、最短路径)

每个文件夹对应实现不同的功能，例如有基础结构、查找、排序、字符串、图论等。对于每一个数据结构，它含有3个文件。以二叉查找树为例：
- [bst.h](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.h) ：头文件定义其数据结构和API
- [bst.c](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c) ：实现二叉查找树的各种操作: 
- [bst_test.c](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst_test.c) ：测试二叉查找树的操作和时间消耗(测试用例并不全面): 

注意：在实现后务必使用[Valgrind](http://valgrind.org/docs/manual/quick-start.html)工具检查程序内存使用是否存在问题,命令如下:

```
valgrind --leak-check=yes program arg1 arg2 ...
```

## Utils
提供必要的计时操作和常见的基础数据结构:
- [计时器](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/timer.c) 
- [动态数组](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/dynarr.c)
- [单链表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/linklist.c)
- [双向链表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/dlinklist.c)
- [栈](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/stack.c)
- [队列](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/queue.c)
- [二叉树](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bintree.c)
- [位示图](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bitmap.c)
- [大数运算](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/bigint.c)


## Sort
提供常见的插入排序(直接插入排序、折半插入排序、希尔排序)、交换排序(冒泡排序、快速排序)、选择排序(简单选择排序、堆排序)、二路归并排序等比较排序方法，另外还包括一些基于非比较的排序算法如计数排序、基数排序、桶排序等。

- [排序](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/utils/sort.c)


## Search
以不同的数据结构实现查询操作，如以树结构为形式的查找树、以链表为形式的跳跃表、以数组或链表为形式的散列表等等。主要实现有:

- [二分查找](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/binsearch.c)
- [二叉查找树](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/bst.c)
- [散列表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/hashtbl.c)
- [跳跃表](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/skiplist.c)
- [最小堆](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/minheap.c)
- [最大堆]()
- [并查集](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/search/uf.c)
- [AVL树]()
- [2-3树]()
- [红黑树]()
- [数字查找树]()
- [基数排序树]()


## String
- [Trie树](https://github.com/charlesxiong/algo-ds/blob/master/generics-c/string/trie.cpp)


# 算法设计策略(based on C++)
* 递归与分治策略
* 动态规划算法
* 贪心算法
* 回溯法
* 分支限界法
* 概率算法
* 线性规划与网络流算法
* 近似算法


# 参考资料
- [List of data structures](http://en.wikipedia.org/wiki/List_of_data_structures)
- [The lesser known but useful data structures](http://stackoverflow.com/questions/500607/what-are-the-lesser-known-but-useful-data-structures?page=1&tab=votes#tab-top)
- [The Archive of Interesting Code](http://www.keithschwarz.com/interesting/)
- [NOCOW](http://www.nocow.cn/index.php/NOCOW%E5%9C%B0%E5%9B%BE)


