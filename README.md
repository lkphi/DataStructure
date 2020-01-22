# DataStructure
## 介绍
本项目根据浙江大学数据结构与算法，采用c++ 泛型编程编写代码，并实现了一部分的课程相关作业。
本项目主要分为两个部分，[代码](https://github.com/lkphi/DataStructure/tree/master/DataStructure)和[课件](https://github.com/lkphi/DataStructure/tree/master/课件)，课件是浙江大学数据结构与算法的课件，代码中的```test.txt```是习题测试的测试用例

To-Do：

- [ ]1. 将加入红黑树，B+树数据结构;
- [ ]2. 加入异常的类型判断，并集成到Exception.h里
- [ ]3. 增加更多的测试用例
## 目录
- [线性表](##线性表)
- [堆栈](##堆栈)
- [队列](##队列)
- [二叉树](##二叉树)
- [二叉搜索树和平衡二叉树](##二叉搜索树和平衡二叉树)
- [堆](#堆)
- [集合](#集合)
- [图](#图)
- [排序](#排序)
- [散列表](#散列查找)
- [KMP算法](#KMP算法)

## 线性表
只编写了链表存储对象的线性表，实现了主要的操作，并将其应用到多项式上，实现了多项式的加减乘运算。

详见 ```LinearList.h``` 、```Polygon.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test Linear List``` 部分
### 课件内容
* 2.1线性表及其实现
* 2.4应用实例--多项式加法运算
* 习题选讲-Reversing Linked List
* 小白专场：一元多项式的加法乘法实现
## 堆栈
实现了堆栈的主要操作，采用了数组和链表的方式存储对象。

详见 ```Stack.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test stack```和```#pragma region test Stack``` 部分
### 课件内容
* 2.2堆栈 
## 队列
提取出了队列的主要操作到接口文件```queueService.h```，实现了循环队列、单端队列和双端队列，
其中双端队列是用链表的方式存储数据，后续考虑加上采用数组形式的双端队列，
单端队列是用链表实现，循环队列是用数组实现

详见 ```QueueService.h```、```Queue.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test LoopQueue```、```#pragma region test test Queue```和```#pragma regiontest Dequue``` 部分
### 课件内容
* 2.3队列
## 二叉树
实现了二叉树的基本操作，二叉树同构的判断，详见```Tree.h```。

测试程序详见```DataStructure.cpp```中的```#pragma region test binarytree```和```#pragma region test binary tree Isomorphic```部分
### 课件内容
* 3.1 树与树的表示
* 3.2 二叉树及存储结构
* 3.3 二叉树的遍历
* 小白专场：树的同构
## 二叉搜索树和平衡二叉树
先由二分查找法和比例查找法引出二叉搜索树，然后借由二叉搜索树引出了平衡二叉树，
实现了二分查找法、比例查找法、二叉搜索树和平衡二叉树的基本操作。

详见```Search.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test BinSearchTree```和```#pragma region test BinarySearch```部分
### 课件内容
* 4.1 二叉搜索树
* 4.2 平衡二叉树
* 习题选讲-Complete Binary Search Tree
* 小白专场：是否同一棵二叉搜索树
## 堆
堆结构可以解决从优先队列中获取优先级最高的任务，
哈弗曼编码广泛应用于通讯和数据传输中，哈夫曼树能有效地解决哈夫曼编码问题，
实现了堆、哈弗曼树、哈夫曼编码的基本操作

详见```Heap.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test heap```部分
### 课件内容
* 5.1堆
* 5.2哈夫曼树与哈夫曼编码
* 习题选讲-Huffman Codes
* 小白专场：堆中的路径
## 集合
等价类划分的问题可以以树形式的并查集的方法实现，集合的数据结构能很好的实现

详见```Set.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test set```部分部分
### 课件内容
* 5.3 集合及运算
## 图
实现了图的存储，以及遍历表的方法，采用邻接矩阵和邻接表的方式存储，实现了DFS、BFS的大体算法结构。
解决最短路径、最小生成树问题和拓扑排序问题。

详见```Graph.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test graph```、```#pragma regionsave 007```
```#pragma region six degrees of separation 六度空间```、```#pragma region test key Path```、
```#pragma regiontest travel Plan```和```#pragma regionHarryPotter Test```部分
### 课件内容
* 6-1图
* 6-2图的遍历
* 6-3应用实例：拯救007
* 6-4六度空间
* 7-1最短路径问题
* 8-1最小生成树
* 8-2拓扑排序
* 习题选讲-Tree Traversals Again
* 习题选讲-旅游规划
* 小白专场：哈利•波特的考试
* 小白专场：如何建立图
## 排序
实现了冒泡排序、插入排序、希尔排序、选择排序、堆排序、归并排序、
快速排序、桶排序、物理排序、表排序、基数排序算法

详见```Sort.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test sort```和 ```#pragma region Insert or Merge```部分
### 课件内容
* 9-1简单排序
* 9-2希尔排序
* 9-3堆排序
* 9-4归并排序
* 10-1快速排序
* 10-2表排序
* 10-3基数排序
* 10-4排序算法的比较
* 习题选讲-Sort with Swap
## 散列表
实现了散列表的基本操作

详见```HashTable.h```

测试程序详见```DataStructure.cpp```中的```#pragma region 电话狂人```和 ```#pragma region Hard Version```部分
### 课件内容
* 11.1散列表
* 11.2散列函数的构造方法
* 11.3冲突处理方法
* 11.4散列表的性能分析
* 11.5应用实例(词频统计）
* 习题选讲-Hashing-Hard Version
* 小白专场：电话聊天狂人
## KMP算法
串的模式匹配

详见```Kmp.h```

测试程序详见```DataStructure.cpp```中的```#pragma region test KMP```部分
### 课件内容
* KMP

