#要点
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
1. 并行设备的硬件寄存器，
2. 一个中断服务子程序中会访问到的非自动变量（Non-automatic variables),可以使用关键区保护
3. 多线程应用中被几个任务共享的变量，可以关闭系统调度

# 函数指针
```c
int (*fun)(int a, int b); // 声明函数指针 
```

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
const char * p;   // p is a pointer to const char;
char const * p;   // 同上,因为C++里面没有const*的运算符，所以const只能属于前面的类型。
```
#### C++标准规定，const关键字放在类型或变量名之前等价的。

结论：
```c
char * const cp     // 定义一个指向字符的指针常数，即const指针
const char* p       // 定义一个指向字符常数的指针
char const* p       // 等同于const char* p
const char **       // 是一个指向指针的指针，那个指针又指向一个字符串常量。   
char **             // 也是一个指向指针的指针，那个指针又指向一个字符串变量。
```

|  数据类型      | 16位平台  | 32位平台 | 64位平台 |
| -------------|:---------:|:------:|:------:|
| char         | 1 字节     | 1 字节 |  1 字节 |
| pointer      | 2 字节     | 4 字节 |  8 字节 |
| short        | 2 字节     | 2 字节 |  2 字节 |
| int          | 2 字节     | 4 字节 |  4 字节 |
| float        | 4 字节     | 4 字节 |  4 字节 |
| double       | 8 字节     | 8 字节 |  8 字节 |
| long         | 4 字节     | 4 字节 |  8 字节 |
| long long    | 8 字节     | 8 字节 |  8 字节 |

## linux c题目
### 1：printf返回值
```c
#include <stdio.h>
int main() {
  int i = 43;
  printf("%d\n", printf("%d", printf("%d", i)));
  return 0;
}
```
输出：4321
printf返回值是输出字符的个数（不包括字符串结尾\x00）

### 1：enum枚举类型
```c
#include <stdio.h>
int main() {
  enum color{
    RED,
    BLUE,
    GREEN = -2,
    YELLOW,
    PINK
  };
  printf("%d %d\n", BLUE, PINK);
  return 0;
}
```
输出：1 0
enum默认是从0开始的，所以RED = 0， BLUE = 1， GREEN = -2， YELLOW = -1， PINK = 0；
### 对(-1.2345)取整是（-1）
### 可变参数函数
```c
#include "stdarg.h"

char buf[512] = {0};

int func(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);
}
```
### main函数的返回值
1. 0 表示程序正常退出
2. 负数表示程序异常退出

### 浮点数存储方式
1. float 占用4个字节，32bits

<table style="text-align:center">
   <tr>
      <td>符号位</td>
      <td width="150">指数位</td>
      <td width="300">尾数部分</td>
   </tr>
   <tr>
      <td>1 bits</td>
      <td>8 bits</td>
      <td>23 bits</td>
   </tr>
</table>

2. double 占用8字节，64bits

<table style="text-align:center">
   <tr>
      <td>符号位</td>
      <td width="150">指数位</td>
      <td width="300">尾数部分</td>
   </tr>
   <tr>
      <td>1 bits</td>
      <td>11 bits</td>
      <td>52 bits</td>
   </tr>
</table>

## 链表操作
```c
////////////////////////////////////////////
//单链表的初始化，建立，插入，查找，删除。//
//Author:Wang Yong                        //
//Date: 2010.8.19                         //
////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
////////////////////////////////////////////
//定义结点类型
typedef struct Node
{
    ElemType data;              //单链表中的数据域
    struct Node *next;          //单链表的指针域
}Node,*LinkedList;
////////////////////////////////////////////
//单链表的初始化
LinkedList LinkedListInit()
{
    Node *L;
    L = (Node *)malloc(sizeof(Node));   //申请结点空间
    if(L == NULL)                       //判断是否有足够的内存空间
        printf("申请内存空间失败/n");
    L->next = NULL;                  //将next设置为NULL,初始长度为0的单链表
}
////////////////////////////////////////////
//单链表的建立1，头插法建立单链表
LinkedList LinkedListCreatH()
{
    Node *L;
    L = (Node *)malloc(sizeof(Node));   //申请头结点空间
    L->next = NULL;                      //初始化一个空链表
    
    ElemType x;                         //x为链表数据域中的数据
    while(scanf("%d",&x) != EOF)
    {
        Node *p;
        p = (Node *)malloc(sizeof(Node));   //申请新的结点
        p->data = x;                     //结点数据域赋值
        p->next = L->next;                    //将结点插入到表头L-->|2|-->|1|-->NULL
        L->next = p; 
    }
    return L;
}
////////////////////////////////////////////
//单链表的建立2，尾插法建立单链表
LinkedList LinkedListCreatT()
{
    Node *L;
    L = (Node *)malloc(sizeof(Node));   //申请头结点空间
    L->next = NULL;                  //初始化一个空链表
    Node *r;
    r = L;                          //r始终指向终端结点，开始时指向头结点
    ElemType x;                         //x为链表数据域中的数据
    while(scanf("%d",&x) != EOF)
    {
        Node *p;
        p = (Node *)malloc(sizeof(Node));   //申请新的结点
        p->data = x;                     //结点数据域赋值
        r->next = p;                 //将结点插入到表头L-->|1|-->|2|-->NULL
        r = p;
    }
    r->next = NULL;
    
    return L;
}
////////////////////////////////////////////
//单链表的插入，在链表的第i个位置插入x的元素
LinkedList LinkedListInsert(LinkedList L,int i,ElemType x)
{  
    Node *pre;                      //pre为前驱结点
    pre = L;
    int tempi = 0;
    for (tempi = 1; tempi < i; tempi++)
        pre = pre->next;                 //查找第i个位置的前驱结点
    Node *p;                                //插入的结点为p
    p = (Node *)malloc(sizeof(Node));
    p->data = x;
    p->next = pre->next;
    pre->next = p;

    return L;
}
////////////////////////////////////////////
//单链表的删除，在链表中删除值为x的元素
LinkedList LinkedListDelete(LinkedList L,ElemType x)
{
    Node *p,*pre;                   //pre为前驱结点，p为查找的结点。
    p = L->next;
    while(p->data != x)              //查找值为x的元素
    {
        pre = p;
        p = p->next;
    }
    pre->next = p->next;          //删除操作，将其前驱next指向其后继。
    free(p);
    return L;
}
/////////////////////////////////////////////
int main()
{
    LinkedList list,start;
/*  printf("请输入单链表的数据：");
    list = LinkedListCreatH();
    for(start = list->next; start != NULL; start = start->next)
        printf("%d ",start->data);
    printf("/n");
*/  printf("请输入单链表的数据：");
    list = LinkedListCreatT();
    for(start = list->next; start != NULL; start = start->next)
        printf("%d ",start->data);
    printf("/n");
    int i;
    ElemType x;
    printf("请输入插入数据的位置：");
    scanf("%d",&i);
    printf("请输入插入数据的值：");
    scanf("%d",&x);
    LinkedListInsert(list,i,x);
    for(start = list->next; start != NULL; start = start->next)
        printf("%d ",start->data);
    printf("/n");
    printf("请输入要删除的元素的值：");
    scanf("%d",&x);
    LinkedListDelete(list,x); 
    for(start = list->next; start != NULL; start = start->next)
        printf("%d ",start->data);
    printf("/n");

    return 0;
}
```
