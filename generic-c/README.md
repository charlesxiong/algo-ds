-----

**基于泛型C实现各种数据结构**

它实现的数据结构,如图下(待扩充):
![数据结构](https://github.com/charlesxiong/algo-ds/blob/master/java/images/Selection_036.png)

每个文件夹对应实现不同的功能，例如有查找、排序、基础结构、字符串、图论等。

对于每一个数据结构，它含有3个文件。以二叉查找树为例：

- 头文件定义数据结构和使用接口:  [bst.h](https://github.com/charlesxiong/algo-ds/blob/master/generic-c/search/bst.h)
-  实现二叉查找树的各种操作: [bst.c](https://github.com/charlesxiong/algo-ds/blob/master/generic-c/search/bst.c)
-  测试二叉查找树的操作和时间消耗(测试用例并不全面): [bst_test.c](https://github.com/charlesxiong/algo-ds/blob/master/generic-c/search/bst_test.c)



-----

**Utils**

它提供了必要的计时操作和常见的基础数据结构，以下均是基于泛型的C实现:

- [计时器](https://github.com/charlesxiong/algo-ds/blob/master/generic-c/utils/timer.c) 
- [动态数组](http://)
- [单链表](http://)
- [双向链表](http://)
- [栈](http://)
- [队列](http://)
- [位示图](http://)
- [并查集](http://)

-----

**Search**

它主要是以不同的数据结构实现查询操作，例如以树结构为形式的查找树、以链表为形式的跳跃表、以数组或链表为形式的散列表等等。主要实现有:

- [二分查找](https://github.com/charlesxiong/algo-ds/blob/master/generic-c/search/binsearch.c)
- [二叉查找树](https://github.com/charlesxiong/algo-ds/blob/master/generic-c/search/bst.c)
- 散列表
- 跳跃表
- AVL树

