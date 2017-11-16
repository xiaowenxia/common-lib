## linux进程间通讯方式
1. 管道（Pipe）及有名管道（named pipe）
2. 信号（Signal）
3. 报文（Message）队列（消息队列）：
4. 共享内存
5. 信号量（semaphore）
6. 套接口（Socket）
## 经典排序算法
1. 快速
2. 希尔
3. 冒泡
4. 插入
5. 堆
6. 归并 
## 简单的makefile
```makefile
CROSS_COMPILE=/opt/4.5.1/bin/arm-linux-

CC=$(CROSS_COMPILE)gcc

AS=$(CROSS_COMPILE)as

LD=$(CROSS_COMPILE)ld


CFLAGS=-g -Wall

LIBS=-lpthread

all:main


main:main.o gsm_gprs.o socket.o telosb.o wifi.o 
	
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

main.o: main.c gsm_gprs.h option.h telosb.h
	
	$(CC) $(CFLAGS) -c $<

gsm_gprs.o:gsm_gprs.c gsm_gprs.h socket.h

	$(CC) $(CFLAGS) -c $<

socket.o:socket.c socket.h option.h

	$(CC) $(CFLAGS) -c $<

telosb.o: telosb.c telosb.h option.h

	$(CC) $(CFLAGS) -c $<

wifi.o: wifi.c wifi.h option.h

	$(CC) $(CFLAGS) -c $<

clean:
	
	-rm main -f *\.o *\*~ *~
```

### insmod rmmode 加载 卸载模块
### 内存申请函数
1. calloc
2. malloc
3. realloc
### gcc 编译过程：
预处理，编译，汇编，连接
### 文件系统
fat ntfs ext2 ext3 ext4 jfs
### linux 常用的系统调用函数
fork（创建进程） exit（终止进程）pause sleep usleep
### 僵尸进程产生原因和回收
  ps指令怎么查看僵尸进程
### 以下文件的作用
/var/log/boot.log 系统引导日志
/var/log/dmesg    系统核心启动日志
/var/log/messages 核心系统日志
/var/log/maillog  邮件系统日志
/var/log/xferlog  FTP系统日志
/var/log/syslog   系统出问题的日志
/var/log/secure   安全信息和系统登录与网络连接的信息
/var/log/wtmp     登录记录
/var/spool/clientmqueue
/proc/interrupts
/etc/fstab        Linux内核引导时,从文件/etc/fstab 中读取要加载的文件系统.
### /proc 目录
```sh
proc文件系统是一个伪文件系统，它只存在内存当中。
/proc/buddyinfo   每个内存区中的每个order有多少块可用，和内存碎片问题有关
/proc/cmdline     启动时传递给kernel的参数信息
/proc/cpuinfo     cpu的信息
/proc/crypto      内核使用的所有已安装的加密密码及细节
/proc/devices     已经加载的设备并分类
/proc/dma         已注册使用的ISA DMA频道列表
/proc/execdomains Linux内核当前支持的execution domains
/proc/fb          帧缓冲设备列表，包括数量和控制它的驱动
/proc/filesystems 内核当前支持的文件系统类型
/proc/interrupts  x86架构中的每个IRQ中断数
/proc/iomem       每个物理设备当前在系统内存中的映射
/proc/ioports     一个设备的输入输出所使用的注册端口范围
/proc/kcore       代表系统的物理内存，存储为核心文件格式，里边显示的是字节数，等于RAM大小加上4kb
/proc/kmsg        记录内核生成的信息，可以通过/sbin/klogd或/bin/dmesg来处理
/proc/loadavg     根据过去一段时间内CPU和IO的状态得出的负载状态，与uptime命令有关
/proc/locks       内核锁住的文件列表
/proc/mdstat      多硬盘，RAID配置信息(md=multiple disks)
/proc/meminfo     RAM使用的相关信息
/proc/misc        其他的主要设备(设备号为10)上注册的驱动
/proc/modules     所有加载到内核的模块列表
/proc/mounts      系统中使用的所有挂载
/proc/mtrr        系统使用的Memory Type Range Registers (MTRRs)
/proc/partitions  分区中的块分配信息
/proc/pci         系统中的PCI设备列表
/proc/slabinfo    系统中所有活动的 slab 缓存信息
/proc/stat        所有的CPU活动信息
/proc/sysrq-trigger 使用echo命令来写这个文件的时候，远程root用户可以执行大多数的系统请求关键命令，就好像在本地终端执行一样。要写入这个文件，需要把/proc/sys/kernel/sysrq不能设置为0。这个文件对root也是不可读的
/proc/uptime      系统已经运行了多久
/proc/swaps       交换空间的使用情况
/proc/version     Linux内核版本和gcc版本
/proc/bus         系统总线(Bus)信息，例如pci/usb等
/proc/driver      驱动信息
/proc/fs          文件系统信息
/proc/ide         ide设备信息
/proc/irq         中断请求设备信息
/proc/net         网卡设备信息
/proc/scsi        scsi设备信息
/proc/tty         tty设备信息
/proc/net/dev     显示网络适配器及统计信息
/proc/vmstat      虚拟内存统计信息
/proc/vmcore      内核panic时的内存映像
/proc/diskstats   取得磁盘信息
/proc/schedstat   kernel调度器的统计信息
/proc/zoneinfo    显示内存空间的统计信息，对分析虚拟内存行为很有用
#### 以下是/proc目录中进程N的信息
/proc/N           pid为N的进程信息
/proc/N/cmdline   进程启动命令
/proc/N/cwd       链接到进程当前工作目录
/proc/N/environ   进程环境变量列表
/proc/N/exe       链接到进程的执行命令文件
/proc/N/fd        包含进程相关的所有的文件描述符
/proc/N/maps      与进程相关的内存映射信息
/proc/N/mem       指代进程持有的内存，不可读
/proc/N/root      链接到进程的根目录
/proc/N/stat      进程的状态
/proc/N/statm     进程使用的内存的状态
/proc/N/status    进程状态信息，比stat/statm更具可读性
/proc/self        链接到当前正在运行的进程
```
### fopen的参数有：
1. r 以只读方式打开文件，该文件必须存在。
2. r+ 以可读写方式打开文件，该文件必须存在。
3. rb+ 读写打开一个二进制文件，允许读写数据，文件必须存在。
4. w 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
5. w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
6. a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）
7. a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）
8. wb 只写打开或新建一个二进制文件；只允许写数据。
9. wb+ 读写打开或建立一个二进制文件，允许读和写。
10. ab+ 读写打开一个二进制文件，允许读或在文件末追加数据。
11. wx 创建文本文件,只允许写入数据.[C11]
12. wbx 创建一个二进制文件,只允许写入数据.[C11]
13. w+x 创建一个文本文件,允许读写.[C11]
14. wb+x 创建一个二进制文件,允许读写.[C11]
15. w+bx 和"wb+x"相同[C11]
16. 以x结尾的模式为独占模式,文件已存在或者无法创建(一般是路径不正确)都会导致fopen失败.文件以操作系统支持的独占模式打开.[C11]

### 硬链接 和 符号链接(软连接)
#### 硬链接
1. 硬链接直接指向文件的i节点
2. 硬链接和原文件的i节点是一样的
3. 硬链接文件显示的大小是跟原文件是一样的
4. 硬连接不能链接目录文件。
```sh
ln file2 /home/longcheng/file2hard
```
#### 软连接
软连接则是建立了一个新文件，这个文件指向链接的文件，i节点不一样
```sh
ln -s file2 /home/longcheng/file2hard
```
### linux内核子系统
1. 进程管理
2. 内存管理
3. I/O管理
4. 文件系统管理
### 进程几种状态
1. 运行态
2. 就绪态
3. 阻塞态
### 文件系统组成
1. <strong>超级块</strong>：存放文件系统本身的信息，比如记录了每个区域的大小，或未被使用的磁盘块的信息。（不同版本稍有差别）
2. <strong>i-节点表</strong>：每个文件都有其属性，大小，最近修改时间等等，这些被存储在ino_t 的结构体中，所有的i-节点都有一样的大小，i-节点表就是这样一些节点的列表。（表中的每个i-节点都通过位置来标志，例如标志为2的i-节点位于文件系统i-节点表中的第3个位置 ）
3. <strong>数据块</strong>：存放文件内容，因为块的大小一定，所以有时一个文件会分布在多个磁盘上。
### i 节点
i 节点是一个64字节长的表,表中包含了文件的相关信息,其中有文件的大小、文件所有者、文件的存取许可方式以及文件的类型等重要信息.
### Linux 系统关机命令
1. Shutdown   命令安全地将系统关机。
2. Halt       就是调用shutdown -h。
3. Reboot     工作过程差不多跟halt一样﹐不过它是引发主机重启
4. Poweroff   就是halt的软链接而已
5. Init       所有进程的祖先﹐它的进程号始终为1﹐init 0为关机﹐init1为重启。