# gdb学习笔记

```
Something I hope you know before go into the coding~
First, please watch or star this repo, I'll be more happy if you follow me.
Bug report, questions and discussion are welcome, you can post an issue or pull a request.
```

## 目录

# gdb小技巧

- [gdb小技巧](#gdb小技巧)   
   - [信息显示](#信息显示)   
      - [gdb版本信息](#gdb版本信息)   
      - [gdb许可证显示](#gdb许可证显示)   
      - [启动不显示版本信息](#启动不显示版本信息)   
      - [gdb退出时不显示提示信息](#gdb退出时不显示提示信息)   
      - [关闭gdb信息显示分页功能](#关闭gdb信息显示分页功能)   
   - [变量](#变量)   
      - [罗列所有全局/静态变量](#罗列所有全局静态变量)   
      - [设置变量](#设置变量)   
   - [字符串](#字符串)   
      - [打印ASCII和宽字符字符串](#打印ascii和宽字符字符串)   
      - [改变字符串的值](#改变字符串的值)   
   - [函数](#函数)   
      - [罗列所有函数](#罗列所有函数)   
      - [单步步入和单步步出](#单步步入和单步步出)   
      - [强行调试不带调试信息的函数](#强行调试不带调试信息的函数)   
      - [优雅退出正在调试的函数](#优雅退出正在调试的函数)   
      - [暴力退出正在执行的函数](#暴力退出正在执行的函数)   
      - [暴力执行函数](#暴力执行函数)   
      - [打印函数汇编代码](#打印函数汇编代码)   
      - [显示执行堆栈](#显示执行堆栈)   
      - [显示当前寄存器信息](#显示当前寄存器信息)   
      - [显示当前栈帧信息](#显示当前栈帧信息)   
      - [显示尾调用函数信息](#显示尾调用函数信息)   
   - [断点](#断点)   
   - [观察点](#观察点)   
   - [捕获点](#捕获点)   
   - [打印显示信息](#打印显示信息)   
   - [多进程/多线程](#多进程多线程)   
   - [core dump文件](#core-dump文件)   
   - [汇编](#汇编)   
   - [改变程序执行](#改变程序执行)   
   - [信号](#信号)   
   - [共享库](#共享库)   
   - [脚本](#脚本)   
   - [源文件](#源文件)   
   - [图形化界面显示](#图形化界面显示)   
   - [其他](#其他)   
      - [记录gdb操作日志](#记录gdb操作日志)   

参考:

* [100个gdb小技巧GitBook](https://wizardforcel.gitbooks.io/100-gdb-tips/content/)
- [100个gdb小技巧GitHub](https://github.com/hellogcc/100-gdb-tips)
- [GDB在线手册](https://sourceware.org/gdb/onlinedocs/gdb)
- [GDB命令卡片](https://github.com/hellogcc/100-gdb-tips/blob/master/refcard.pdf)
- [GDB dashboard](https://github.com/cyrus-and/gdb-dashboard)
- [Gdbinit for OS X, iOS and others - x86, x86_64 and ARM](https://github.com/gdbinit/Gdbinit)
- [dotgdb：关于底层调试和反向工程的gdb脚本集](https://github.com/dholm/dotgdb)
- [gdb调试内核(内核提供了gdb脚本在scripts/gdb目录下)](https://www.kernel.org/doc/html/v4.12/dev-tools/gdb-kernel-debugging.html)


授权许可通告：
```
100个gdb小技巧 官方文档，使用的是GNU Free Documentation License。
```


## 信息显示

### gdb版本信息

```
show version -- Show what version of GDB this is
```

```
(gdb) show version
GNU gdb (GDB) Red Hat Enterprise Linux 8.2-18.el8
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb)
```

### gdb许可证显示

```
show copying -- Conditions for redistributing copies of GDB
```

```
(gdb) show copying    
                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

                            Preamble

  The GNU General Public License is a free, copyleft license for
software and other kinds of works.

....省略一亿个单词

  Later license versions may give you additional or different
permissions.  However, no additional obligations are imposed on any
author or copyright holder as a result of your choosing to follow a
later version.
```

### 启动不显示版本信息

```
[root@Rocky ~]# gdb
GNU gdb (GDB) Red Hat Enterprise Linux 8.2-18.el8
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb)
```

如果想要在```~/.gdbinit```文件中配置该功能，则需要高版本，低版本暂时不支持。

The `startup-quietly` option was recently added to the 11.x branch of GDB ([Release notes](https://sourceware.org/git/gitweb.cgi?p=binutils-gdb.git;a=blob_plain;f=gdb/NEWS;hb=gdb-11.1-release)).

低版本唯一规避方法是增加```-q/--scilent```

```shell
[root@Rocky ~]# gdb --silent
(gdb)
[root@Rocky ~]# gdb -q
(gdb)
[root@Rocky ~]#
```

另外，可以在bashrc中将gdb命令alias一下

```
[root@Rocky ~]# echo 'alias gdb="gdb -q"' >> ~/.bashrc
[root@Rocky ~]# source ~/.bashrc
[root@Rocky ~]# alias gdb
alias gdb='gdb -q'
[root@Rocky ~]# gdb
(gdb)
```

### gdb退出时不显示提示信息

当进入调试状态（程序属于运行状态时）退出会提示确认

```
(gdb) start
Temporary breakpoint 1 at 0x4005ae: file main.c, line 12.
Starting program: /data/gdb.git/code/add/a.out

Temporary breakpoint 1, main () at main.c:12
12		result = add(1,2);
(gdb) q
A debugging session is active.

	Inferior 1 [process 25632] will be killed.

Quit anyway? (y or n)
```

可以通过配置规避，当然，直接在gdb命令行输入能起到临时规避的效果。

```shell
echo "set confirm off" >> ~/.gdbinit
```



### 关闭gdb信息显示分页功能



若gdb输出的而信息较多的情况下，例如罗列所有函数、罗列所有变量，在内核中数以万计，gdb会采用分页进行显示

```
All defined variables:

File arch/x86/ia32/audit.c:
8:      unsigned int ia32_chattr_class[19];
3:      unsigned int ia32_dir_class[15];
18:     unsigned int ia32_read_class[10];
23:     unsigned int ia32_signal_class[4];
13:     unsigned int ia32_write_class[22];

File arch/x86/ia32/syscall_ia32.c:
18:     const sys_call_ptr_t ia32_sys_call_table[359];

--Type <RET> for more, q to quit, c to continue without paging--

```



若要关闭分页，当然，直接在gdb命令行输入能起到临时规避的效果。

```
echo "set pagination off" >> ~/.gdbinit
```

此时所有内容都会打到前台，有好有坏，看你需求



## 变量

### 罗列所有全局/静态变量

```
info variables # 显示全部
info variables [REGEX] # 模糊搜索
```

```
(gdb) info variables
All defined variables:

File main.c:
3:	int result;

Non-debugging symbols:
0x0000000000400678  _IO_stdin_used
0x0000000000400680  __dso_handle
0x000000000040068c  __GNU_EH_FRAME_HDR
0x00000000004007d4  __FRAME_END__
0x0000000000600e00  __frame_dummy_init_array_entry
0x0000000000600e00  __init_array_start
0x0000000000600e08  __do_global_dtors_aux_fini_array_entry
0x0000000000600e08  __init_array_end
0x0000000000600e10  _DYNAMIC
0x0000000000601000  _GLOBAL_OFFSET_TABLE_
0x0000000000601020  __data_start
0x0000000000601020  data_start
0x0000000000601024  __bss_start
0x0000000000601024  _edata
0x0000000000601024  completed
0x0000000000601028  __TMC_END__
0x0000000000601030  _end
```

### 设置变量

样例程序

```c
#include <stdio.h>

int result;

int add(int a, int b)
{
	return a+b;
}

int main()
{
	result = add(1,2);
	printf("%d\n", result);
}
```

* 在函数内部，可设置局部变量

* 全局变量、静态变量任意时候都可以设置
* 设置语法```set var VARName=VARValue```，例如：

```
(gdb) break add
(gdb) c
(gdb) step
(gdb) p	a                                                                           4		05df
$1 = 1
(gdb) p	b
$2 = 2
(gdb) set var a=100
(gdb) p	a
$3 = 100
(gdb) s
(gdb) s
main () at main.c:12
(gdb) s
(gdb) s
102
(gdb)

```

还有很多set语法方式

```
set {type}address=expr # 例如 set {int}0x801234 = 123
set var $rax=99  # 设置寄存器值
```


## 字符串

字符串其实本身也是变量，是常量

### 打印ASCII和宽字符字符串



* x/s 可以打印字符串
* p stringVariable 也可以打印字符串

样例程序：

```
#include <stdio.h>

int main(void)
{
	char p1[] = "nicyou";
	char *p2 = "yifengyou";
	printf("p1 is %s, p2 is %s\n", p1, p2);
	return 0;
}
```



```
(gdb) x/s p1
+x/s p1
0x7fffffffd8b1:	"nicyou"
(gdb) p	p1
+p p1
$1 = "nicyou"
(gdb) p	sizeof(p1)
+p sizeof(p1)
$2 = 7
(gdb) x/ws p1
+x/ws p1
0x7fffffffd8b1:	U"\x7963696e畯"
(gdb) x/hs p1
+x/hs p1
0x7fffffffd8b1:	u"楮祣畯"
(gdb)
```





### 改变字符串的值

**只能小于或同等大小，不能超过现有容量**

样例程序:

```
#include <stdio.h>

int main(void)
{
	char p1[] = "nicyou";
	char *p2 = "yifengyou";
	printf("p1 is %s, p2 is %s\n", p1, p2);
	return 0;
}
```



```
set var p1="abc"
set main::p1="abc"
set {char[4]}0x80477a4="abc"
```





```
(gdb) s
(gdb) p	p1
$1 = "nicyou"
(gdb) set p1="tencent"
Too many array elements
(gdb) set p1="nicyyf"
(gdb) p	p1
$2 = "nicyyf"
(gdb)
```






## 函数

### 罗列所有函数

```
info functions  # 罗列全部
info functions [REGX] # 模糊搜索
```

```
(gdb) info functions
All defined functions:

File main.c:
3:	int add(int, int);
8:	int main();

Non-debugging symbols:
0x0000000000400468  _init
0x00000000004004a0  printf@plt
0x00000000004004b0  .annobin_elf_init.c.exit
0x00000000004004b0  .annobin_elf_init.c.hot
0x00000000004004b0  .annobin_elf_init.c.startup
0x00000000004004b0  .annobin_elf_init.c.unlikely
0x00000000004004b0  .annobin_elf_init.c_end.exit
```

如果不带调试信息，则

```
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x00000000004004a0  printf@plt
(gdb)
```



### 单步步入和单步步出

* next（简写n）是单步步出，遇到函数不会进入调试而是执行完在下一个执行点停住
* step（简写s）是单步步入，遇到函数会跳进函数里面停住
* nexti、stepi是针对汇编的单步步入he单步步出



### 强行调试不带调试信息的函数

默认step会进入函数内部，但是对于不带debuginfo的函数会跳过，需要配置一下

```
echo "set step-mode on" >> ~/.gdbinit
```

可以jump进该函数，没有源代码，只能做汇编级别的调试

```
(gdb) s
+s
0x00007ffff7a799b0 in printf ()	from /lib64/libc.so.6
(gdb) s
+s
0x00007ffff7a799b4 in printf ()	from /lib64/libc.so.6
(gdb) s
+s
0x00007ffff7a799bb in printf ()	from /lib64/libc.so.6
(gdb) s
+s
0x00007ffff7a799c0 in printf ()	from /lib64/libc.so.6
(gdb)
```



### 优雅退出正在调试的函数

当处于函数内部某个断点时，若要跳出当前函数，则用**finish（简写fin）**即可

该指令执行完当前函数并且返回，打印返回值，然后等待下一个调试命令

样例程序：

```
#include <stdio.h>

int result;

int add(int a, int b)
{
	return a+b;
}

int main()
{
	result = add(1,2);
	printf("%d\n", result);
}
```



```
(gdb) s
+s
add (a=1, b=2) at main.c:7
(gdb) finish
+finish
Run till exit from #0  add (a=1, b=2) at main.c:7
main ()	at main.c:12
Value returned is $1 = 3
(gdb)
```

### 暴力退出正在执行的函数

上面讲了如何优雅退出，还有一种暴力退出

在函数中调试，使用return命令可直接返回，不会继续执行该函数后续代码逻辑。

当然，还可用```return expression```指定函数的返回值。

样例程序：

```
#include <stdio.h>

int result;

int add(int a, int b)
{
	return a+b;
}

int main()
{
	result = add(1,2);
	printf("%d\n", result);
}
```



```
+start
Temporary breakpoint 2 at 0x4005ae: file main.c, line 12.
Starting program: /data/gdb.git/code/add/a.out

Temporary breakpoint 2, main () at main.c:12
+s
add (a=1, b=2) at main.c:7
+return 1000000
#0  main () at main.c:12
+s
+s
0x00007ffff7a799b0 in printf () from /lib64/libc.so.6
+fin
Run till exit from #0  0x00007ffff7a799b0 in printf () from /lib64/libc.so.6
0x00000000004005da in main () at main.c:13
+n
```

这里，返回值需要考虑参数类型、数量等？如果瞎JB造一堆参数，是否会造成堆栈不平衡？

```
(gdb) s
+s
add (a=1, b=2) at main.c:7
(gdb) return 1,2,3,4,5,6,7,8,9
+return 1,2,3,4,5,6,7,8,9
#0  main () at main.c:12
(gdb) n
+n
(gdb) n
+n
9
```

看样子是被截断了，坑位数量就那些，喂再多数据也是白搭，会被截断。那么如果不给返回值会咋滴？其实返回值是预先分配了空间的，但是空间值不一定初始化过哟，因此可能是不确定的返回值。这里看编译器了呢，像golang这种不会偷懒的强类型，一定是类型零值。

```
(gdb) s
+s
add (a=1, b=2) at main.c:7
(gdb) return
+return
#0  main () at main.c:12
(gdb) n
+n
(gdb) n
+n
4195754
(gdb)
```

### 暴力执行函数



样例程序：

```
#include <stdio.h>

int global = 1;

int func(void)
{
	return (++global);
}

int main(void)
{
	int a = 0;
	a = func();
	printf("%d\n", a);
	return 0;
}
```





```
(gdb) call func()
+call func()
$1 = 2
+call func()
$2 = 3
+call func()
$3 = 4
+call func()
$4 = 5
(gdb) fin
+fin
Run till exit from #0  func () at main.c:7
0x00000000004005c5 in main () at main.c:13
Value returned is $5 = 6
(gdb) n
+n
(gdb) n
+n
6
(gdb)
```

这里函数参数，仍然有堆栈平衡风险，因此调试工具已经安排好了，如果你给够，他就用你的，如果你给不够，它就用默认的。这样不至于造成编译器崩溃，但是程序运行的合理性，需要用户自己把握，这是一把双刃剑。

```
+start
Temporary breakpoint 1 at 0x4005b9: file main.c, line 12.
Starting program: /data/gdb.git/code/function/a.out

Temporary breakpoint 1, main () at main.c:12
+call func(1,2,3)
$1 = 2
...
+call func(1,2,3)
$24 = 25
+s
+s
func () at main.c:7
+fin
Run till exit from #0  func () at main.c:7
0x00000000004005c5 in main () at main.c:13
Value returned is $25 = 26
+n
+n
+n
+n
0x00007ffff7a44cf3 in __libc_start_main () from /lib64/libc.so.6
+q

```



### 打印函数汇编代码

很常用

```
disassemble FUNCTION
dissas FUNCTION
```



* FUNCTION必须精准匹配，否则找不到，模糊搜索也没有意义，如果有一亿个你看一辈子也看不完。



```
(gdb) disas func
+disas func
Dump of assembler code for function func:
   0x0000000000400596 <+0>:	push   rbp
   0x0000000000400597 <+1>:	mov    rbp,rsp
   0x000000000040059a <+4>:	mov    eax,DWORD PTR [rip+0x200a84]        # 0x601024 <global>
   0x00000000004005a0 <+10>:	add    eax,0x1
   0x00000000004005a3 <+13>:	mov    DWORD PTR [rip+0x200a7b],eax        # 0x601024 <global>
   0x00000000004005a9 <+19>:	mov    eax,DWORD PTR [rip+0x200a75]        # 0x601024 <global>
   0x00000000004005af <+25>:	pop    rbp
   0x00000000004005b0 <+26>:	ret    
End of assembler dump.
(gdb)
```



### 显示执行堆栈

```
backtrace
bt            # 显示所有堆栈
bt N          # 显示开头N个堆栈
bt -N         # 显示结尾N个堆栈
bt full N     # 显示开头N个堆栈及其局部变量
bt full -N    # 显示结尾N个堆栈及其局部变量
```



```
(gdb) bt 1
+bt 1
#0  func () at main.c:8
(More stack frames follow...)
(gdb) bt full 1
+bt full 1
#0  func () at main.c:8
No locals.
(More stack frames follow...)
```





### 显示当前寄存器信息

区分info和show，show其实主要用来显示gdb相关的信息，info用来显示目标程序相关信息。

```
info registers
i r
```



### 显示当前栈帧信息

```

info frame
i f
```

显示当前PC指针所在函数的堆栈信息

```
(gdb) i	f   
+i f
Stack level 0, frame at	0x7fffffffd8b0:
 rip = 0x40059a	in func	(main.c:7); saved rip =	0x4005c5
 called by frame at 0x7fffffffd8d0
 source language c.
 Arglist at 0x7fffffffd8a0, args:
 Locals at 0x7fffffffd8a0, Previous frame's sp is 0x7fffffffd8b0
 Saved registers:
  rbp at 0x7fffffffd8a0, rip at	0x7fffffffd8a8
(gdb)
```



### 显示尾调用函数信息



```
echo "set debug entry-values 1" >> ~/.gdbinit
```

尾调用栈有什么作用？



```
(gdb) i	f
+i f
tailcall: initial:
Stack level 0, frame at	0x7fffffffd8b0:
 rip = 0x40058a	in a (main.c:5); saved rip = 0x4005be
 called by frame at 0x7fffffffd8c0
 source language c.
 Arglist at 0x7fffffffd898, args:
 Locals at 0x7fffffffd898, Previous frame's sp is 0x7fffffffd8b0
 Saved registers:
  rip at 0x7fffffffd8a8
(gdb)
```







## 断点

## 观察点

## 捕获点

## 打印显示信息

## 多进程/多线程

## core dump文件


## 汇编


## 改变程序执行


## 信号


## 共享库

## 脚本


## 源文件

## 图形化界面显示

## 其他



### 记录gdb操作日志

参考：<https://sourceware.org/gdb/onlinedocs/gdb/Logging-Output.html>

```
echo "set logging on" >> ~/.gdbinit
echo "set logging file gdb.txt" >> ~/.gdbinit
echo "set logging overwrite off" >> ~/.gdbinit # 不覆写，采用追加方式
echo "set logging redirect off" >> ~/.gdbinit # 不做重定向，写入到终端和日志
echo "set trace-commands on" >> ~/.gdbinit
```

可以用show命令查看当前日志状态：

```
(gdb) show logging
Currently logging to "gdb.txt".
Logs will be appended to the log file.
Output will be logged and displayed.
```

当我打开日志，懵了，为什么命令不写进去，只有命令执行结果。。

```
[root@Rocky /data/gdb.git/code/string]# cat gdb.txt
$1 = "nicyou"
$2 = "abcdef"
Too many array elements
$3 = "abcdef"
$4 = 0x400678 "yifengyou"
```

后来找到<https://stackoverflow.com/questions/37530271/how-to-include-gdb-commands-in-logging-file>

还需要打开另一个选项

```shell
echo "set trace-commands on" >> ~/.gdbinit
```

类似于shell脚本中的```set -x```，屏幕和日志都会多输出一些内容，其中'+'开头的就是命令，例如：

```
+p $p1
$2 = void
+p p1
$3 = "nicyou"
+p p2
$4 = 0x0
+s
+p p2
$5 = 0x400678 "yifengyou"
```

另寻它法

```
gdb a.out |& tee backtrace.log
```

则能正常获取所有内容，例如：

```
[root@Rocky /data/gdb.git/code/string]# cat backtrace.log
Reading symbols from a.out...done.
(gdb) start
Temporary breakpoint 1 at 0x40059e: file main.c, line 5.
Starting program: /data/gdb.git/code/string/a.out

Temporary breakpoint 1, main () at main.c:5
5		char p1[] = "nicyou";
(gdb) n
6		char *p2 = "yifengyou";
(gdb) p p1
$1 = "nicyou"
(gdb) set var p1="123"
(gdb) p p1
$2 = "123\000\000\000"
(gdb) n
7		printf("p1 is %s, p2 is %s\n", p1, p2);
(gdb) finish
"finish" not meaningful in the outermost frame.
(gdb)
"finish" not meaningful in the outermost frame.
(gdb) quit

```

但是，如果是带```--tui```则无法tee重定向

```
[root@Rocky /data/gdb.git]# gdb --tui a.out |& tee log.txt
Cannot enable the TUI when output is not a terminal
```

















---
