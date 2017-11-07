#面试复习要点
1. c基础知识
2. 数据结构（链表 hash表 排序算法 设计模式等）
3. 外设（串口 网口 i2s i2c spi sdio等）
4. ARM cortex-m0 m3 m4 A8等芯片架构
5. 操作系统（内存管理 进程管理 实时性要求 任务间通讯等）
6. tcpip协议栈（tcpip模型 分层结构 ip tcp udp icmp igmp tftp http ftp等协议）
7. linux 多线程 多进程通讯 
8. bash命令 shell makefile python github go javascript


# volatile
volatile 指出变量是随时可能发生变化的，每次使用它的时候必须从变量的地址中读取，因而编译器生成的汇编代码会重新从变量的地址读取数据。
1. 并行设备的硬件寄存器
2. 一个中断服务子程序中会访问到的非自动变量（Non-automatic variables)
3. 多线程应用中被几个任务共享的变量

# const要点
## const T
定义一个常量，声明的同时必须进行初始化。一旦声明，这个值将不能被改变。
```c
const int constInt = 10;        //正确
constInt = 20;                  //错误，常量值不可被改变
const int constInt3;            //错误，未被初始化
```

## const T*
指向常量的指针，不能用于改变其所指向的对象的值。
```c
const int i = 5;
const int i2 = 10;
const int* pInt = &i;           //正确，指向一个const int对象，即i的地址
//*pInt = 10;                   //错误，不能改变其所指缶的对象
pInt = &i2;                     //正确，可以改变pInt指针本身的值,此时pInt指向的是i2的地址
const int* p2 = new int(8);     //正确，指向一个new出来的对象的地址
delete p2;                      //正确
//int* pInt = &i;               //错误，i是const int类型，类型不匹配，不能将const int * 初始化为int *
int nValue = 15;
const int * pConstInt = &nValue;    //正确，可以把int *赋给const int *，但是pConstInt不能改变其所指向对象的值，即nValue
*pConstInt = 40;                    //错误，不能改变其所指向对象的值
```
## const int* 与int* const的区别
指针本身就是一种对象，把指针定义为常量就是常量指针，也就是int* const的类型，也可以写成int *const，声明时必须初始化。
```c
int nValue = 10;
int* const p = &nValue;
int *const p2 = &nValue;
const int* 指针指向的对象不可以改变，但指针本身的值可以改变；int* const 指针本身的值不可改变，但其指向的对象可以改变。
int nValue1 = 10;
int nValue2 = 20;
int* const constPoint = &nValue1;
//constPoint = & nValue2;           //错误，不能改变constPoint本身的值
*constPoint = 40;                   //正确，可以改变constPoint所指向的对象，此时nValue1 = 40


const int nConstValue1 = 5;
const int nConstValue2 = 15;
const int* pPoint = &nConstValue1;
//*pPoint  = 55;                    //错误，不能改变pPoint所指向对象的值
pPoint = &nConstValue2;             //正确，可以改变pPoint指针本身的值，此时pPoint邦定的是nConstValue2对象，即pPoint为nConstValue2的地址
```
const int* const 是一个指向常量对象的常量指针，即不可以改变指针本身的值，也不可以改变指针指向的对象。
```c
const int nConstValue1 = 5;
const int nConstValue2 = 15;
const int* const pPoint = &nConstValue1;
//*pPoint  = 55;                    //错误，不能改变pPoint所指向对象的值
//pPoint = &nConstValue2;           //错误，不能改变pPoint本身的值
```
## 助记方法
#### 把一个声明从右向左读。( * 读成 pointer to )
```c
char * const cp;  // cp is a const pointer to char
const char * p; // p is a pointer to const char;
char const * p; // 同上,因为C++里面没有const*的运算符，所以const只能属于前面的类型。
```
#### C++标准规定，const关键字放在类型或变量名之前等价的。
```c
结论：
char * const cp     : 定义一个指向字符的指针常数，即const指针
const char* p       : 定义一个指向字符常数的指针
char const* p       : 等同于const char* p
const   char   **是一个指向指针的指针，那个指针又指向一个字符串常量。   
char   **也是一个指向指针的指针，那个指针又指向一个字符串变量。
```