
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
   - [函数](#函数)   
      - [罗列所有函数](#罗列所有函数)   
   - [变量](#变量)   
      - [罗列所有全局/静态变量](#罗列所有全局静态变量)   
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
[root@rocky-clion ~]# gdb
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
[root@rocky-clion ~]# gdb --silent
(gdb)
[root@rocky-clion ~]# gdb -q
(gdb)
[root@rocky-clion ~]#
```

另外，可以在bashrc中将gdb命令alias一下

```
[root@rocky-clion ~]# echo 'alias gdb="gdb -q"' >> ~/.bashrc
[root@rocky-clion ~]# source ~/.bashrc
[root@rocky-clion ~]# alias gdb
alias gdb='gdb -q'
[root@rocky-clion ~]# gdb
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



### 改变字符串的值

只能小于或同等大小，不能超过现有容量

样例程序

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
[root@rocky-clion /data/gdb.git/code/string]# cat gdb.txt 
$1 = "nicyou"
$2 = "abcdef"
Too many array elements
$3 = "abcdef"
$4 = 0x400678 "yifengyou"
```

后来找到<https://stackoverflow.com/questions/37530271/how-to-include-gdb-commands-in-logging-file>

发现需要打开一个选项

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
[root@rocky-clion /data/gdb.git/code/string]# cat backtrace.log 
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
(gdb) n
8		return 0;
(gdb) n
9	}
(gdb) n
0x00007ffff7a44cf3 in __libc_start_main () from /lib64/libc.so.6
(gdb) n
Single stepping until exit from function __libc_start_main,
which has no line number information.
p1 is 123, p2 is yifengyou
[Inferior 1 (process 27206) exited normally]
(gdb) n
The program is not being run.
(gdb) quit
[root@rocky-clion /data/gdb.git/code/string]# cat backtrace.log 
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
(gdb) n
8		return 0;
(gdb) n
9	}
(gdb) n
0x00007ffff7a44cf3 in __libc_start_main () from /lib64/libc.so.6
(gdb) n
Single stepping until exit from function __libc_start_main,
which has no line number information.
p1 is 123, p2 is yifengyou
[Inferior 1 (process 27206) exited normally]
(gdb) n
The program is not being run.
(gdb) quit

```

但是，如果是带```--tui```则无法tee重定向

```
[root@rocky-clion /data/gdb.git]# gdb --tui a.out |& tee log.txt
Cannot enable the TUI when output is not a terminal
```

















---
