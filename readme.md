![](https://img-blog.csdnimg.cn/20210118221347395.gif)

<font color=#888888 size=4 face="华文楷体">
来源：微信公众号「编程学习基地」
</font>

### 一、初识cmake

cmake集中开源，跨平台，能够管理大型项目，简化编译构建过程和编译过程，高效率，可扩展于一体，简单而强大的项目构建工具

### 二，安装cmake

> 一般不需要安装，cmake目前已经成为各大Linux发行版提供的组件，所以，需要自己动手安装的可能性很小。如果你使用的操作系统(比如Windows或者某些Linux版本)没有提供cmake或者包含的版本较旧，建议你直接从cmake官方网站下载安装。
>
> cmake官网：https://cmake.org/download/

### 三、初试cmake – cmake的helloworld

Hello world，世界 你好

一个最简单的例子Helloworld来演练一下cmake的完整构建过程

**1、准备工作：**

> 本节对应的源代码所在目录：[Demo1](#)。

新建一个 demo1 文件，目录结构如下

~~~c
[root@ecs-x-medium-2-linux-20200312093025 cmake]# pwd
/root/cmake
[root@ecs-x-medium-2-linux-20200312093025 cmake]# tree
.
└── demo1

1 directory, 0 files
~~~

所有的cmake练习都会放在/root/cmake的子目录下

在demo1目录新建main.c和CMakeLists.txt (注意文件名大小写)：

**main.c**

~~~c
#include <stdio.h>
int main()
{
   printf("Hello World!\n");
   return 0;
}
~~~

**CmakeLists.txt**

~~~cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (demo1)

# 指定生成目标  将名为 main.c 的源文件编译成一个名称为 Demo 的可执行文件。
add_executable(demo main.c)
~~~

CMakeLists.txt 的语法比较简单，由命令、注释和空格组成，其中命令是不区分大小写的。符号 `#` 后面的内容被认为是注释。命令由命令名称、小括号和参数组成，参数之间使用空格进行间隔。

对于上面的 CMakeLists.txt 文件，依次出现了几个命令：

1. `cmake_minimum_required`：指定运行此配置文件所需的 CMake 的最低版本；
2. `project`：参数值是 `demo1`，该命令表示项目的名称是 `demo1` 。
3. `add_executable`： 将名为 [main.c](http://main.cc/) 的源文件编译成一个名称为 Demo 的可执行文件

**2、开始构建**

所有的文件创建完成后，demo1目录中应该存在main.c和CMakeLists.txt两个文件,如下所示

~~~
[root@ecs-x-medium-2-linux-20200312093025 cmake]# tree
.
└── demo1
    ├── CMakeLists.txt
    └── main.c

1 directory, 2 files
~~~

**编译项目**

之后，在 demo1 目录执行 `cmake .` ，得到 Makefile 后再使用 `make` 命令编译得到 Demo1 可执行文件。

~~~shell
[root@ecs-x-medium-2-linux-20200312093025 demo1]# ls
CMakeLists.txt  main.c
[root@ecs-x-medium-2-linux-20200312093025 demo1]# cmake .
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/demo1
[root@ecs-x-medium-2-linux-20200312093025 demo1]# make
Scanning dependencies of target demo
[100%] Building C object CMakeFiles/demo.dir/main.c.o
Linking C executable demo
[100%] Built target demo
[root@ecs-x-medium-2-linux-20200312093025 demo1]# ./demo 
Hello World!
~~~

**3、清理工程：**

跟经典的autotools系列工具一样，运行:

> make clean

即可对**构建结果**进行清理

### 四、内部构建 与 外部构建

上面的例子展示的是“内部构建”，相信看到生成的临时文件比你的代码文件还要多的时候，估计这辈子你都不希望再使用内部构建！

对于cmake，内部编译上面已经演示过了，它生成了一些无法自动删除的中间文件，所以，引出了我们对外部编译的探讨，外部编译的过程如下：

(1)、新建build目录

(2)、进入build目录，运行 `cmake ..` (注意,..代表父目录)查看一下build目录，就会发现了生成了编译需要的Makefile以及其他的中间文件。

(3)、运行make构建工程，就会在当前目录(build目录)中获得目标文件demo。

上述过程就是所谓的out-of-source外部编译，一个最大的好处是，对于原有的工程没有任何影响，所有动作全部发生在编译目录。通过这一点，也足以说服我们全部采用外部编译方式构建工程。

~~~shell
[root@ecs-x-medium-2-linux-20200312093025 demo1]# mkdir build
[root@ecs-x-medium-2-linux-20200312093025 demo1]# tree
.
├── build
├── CMakeLists.txt
└── main.c

1 directory, 2 files
[root@ecs-x-medium-2-linux-20200312093025 demo1]# cd build
[root@ecs-x-medium-2-linux-20200312093025 build]# cmake ..
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/demo1/build
[root@ecs-x-medium-2-linux-20200312093025 build]# make
Scanning dependencies of target demo
[100%] Building C object CMakeFiles/demo.dir/main.c.o
Linking C executable demo
[100%] Built target demo
[root@ecs-x-medium-2-linux-20200312093025 build]# ./demo 
Hello World!
~~~

### 五、多个源文件

#### 同一目录，多个源文件

> 本节对应的源代码所在目录：[Demo2](#)。

先看下目录结构,代码是makefile里面的测试文件，简单的调用加减乘除函数

~~~c
[root@ecs-x-medium-2-linux-20200312093025 demo2]# tree ..
..
└── demo2
    ├── add.c
    ├── CMakeLists.txt
    ├── div.c
    ├── head.h
    ├── main.c
    ├── mult.c
    └── sub.c

1 directory, 7 files
~~~

这个时候，CMakeLists.txt 可以改成如下的形式：

~~~cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (demo2)

# 查找目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(demo ${DIR_SRCS})
~~~

唯一的改动只是在 `add_executable` 命令中增加了一个 `DIR_SRCS` 变量。这样写的好处就是如果源文件很多，把所有源文件的名字都加进去将是一件烦人的工作。更省事的方法是使用 `aux_source_directory` 命令，该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名。其语法如下：

```
aux_source_directory(<dir> <variable>)
```

这样，CMake 会将当前目录所有源文件的文件名赋值给变量 `DIR_SRCS` ，再指示变量 `DIR_SRCS` 中的源文件需要编译成一个名称为 demo 的可执行文件。

我们还是使用外部编译

~~~shell
[root@ecs-x-medium-2-linux-20200312093025 demo2]# ls
add.c  CMakeLists.txt  div.c  head.h  main.c  mult.c  sub.c
[root@ecs-x-medium-2-linux-20200312093025 demo2]# mkdir build
[root@ecs-x-medium-2-linux-20200312093025 demo2]# cd build/
[root@ecs-x-medium-2-linux-20200312093025 build]# cmake ..
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/demo1/build
[root@ecs-x-medium-2-linux-20200312093025 build]# make
Scanning dependencies of target demo
[ 20%] Building C object CMakeFiles/demo.dir/mult.c.o
[ 40%] Building C object CMakeFiles/demo.dir/sub.c.o
[ 60%] Building C object CMakeFiles/demo.dir/main.c.o
[ 80%] Building C object CMakeFiles/demo.dir/div.c.o
[100%] Building C object CMakeFiles/demo.dir/add.c.o
Linking C executable demo
[100%] Built target demo
[root@ecs-x-medium-2-linux-20200312093025 build]# ./demo 
a = 20,b = 12
a + b = 32
a - b = 8
a * b = 240
a / b = 12
~~~

运行profect完美,简单又强大。

#### 多个目录，多个源文件

> 本节对应的源代码所在目录：[Demo3](#)。

目录构建如下

~~~c
[root@ecs-x-medium-2-linux-20200312093025 demo3]# tree
.
├── CMakeLists.txt
├── include
│   └── head.h
├── lib
│   └── libcalc.so
├── main.c
└── src
    ├── add.c
    ├── CMakeLists.txt
    ├── div.c
    ├── mult.c
    └── sub.c
3 directories, 9 files
~~~

对于这种情况，需要分别在项目根目录 demo3 和 src 目录里各编写一个 CMakeLists.txt 文件。

为了方便，我们可以先将 src 目录里的文件编译成静态库或者动态库再由 main 函数调用

**根目录makefile**

~~~cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (calc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 是否使用自己的 LIBCALC 库
option (USE_MYCALC
	   "Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if (USE_MYCALC)
  # 添加 头文件路径
  include_directories ("${PROJECT_SOURCE_DIR}/include")
  # 添加 math 子目录    指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理 
  add_subdirectory (src)
  set (EXTRA_LIBS ${EXTRA_LIBS} calc)
endif (USE_MYCALC)

# 查找当前目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable (demo ${DIR_SRCS})
# 添加链接库
target_link_libraries (demo  ${EXTRA_LIBS})
~~~

该文件添加了下面的内容: 

第10行，定义变量 `USE_MYCALC`,默认为`ON`

第18行，使用命令 `add_subdirectory` 指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理 。

第28行，使用命令 `target_link_libraries` 指明可执行文件 demo 需要连接一个名为 calc 的链接库 。

**子目录中的 CMakeLists.txt**

~~~cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

#指定了生成.so的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 指定生成 calc 链接库 默认.a静态库，指定SHARED可设置生成动态库,指定STATIC可设置生成静态库
add_library (calc SHARED ${DIR_LIB_SRCS})
~~~

同样，我们还是使用外部编译

~~~c
[root@ecs-x-medium-2-linux-20200312093025 demo3]# ls
CMakeLists.txt  include  lib  main.c  src
[root@ecs-x-medium-2-linux-20200312093025 demo3]# mkdir build
[root@ecs-x-medium-2-linux-20200312093025 demo3]# cd build/
[root@ecs-x-medium-2-linux-20200312093025 build]# cmake ..
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/cmake/demo3/build
[root@ecs-x-medium-2-linux-20200312093025 build]# make
Scanning dependencies of target calc
[ 20%] Building C object src/CMakeFiles/calc.dir/mult.c.o
[ 40%] Building C object src/CMakeFiles/calc.dir/sub.c.o
[ 60%] Building C object src/CMakeFiles/calc.dir/div.c.o
[ 80%] Building C object src/CMakeFiles/calc.dir/add.c.o
Linking C shared library ../../lib/libcalc.so
[ 80%] Built target calc
Scanning dependencies of target demo
[100%] Building C object CMakeFiles/demo.dir/main.c.o
Linking C executable demo
[100%] Built target demo
[root@ecs-x-medium-2-linux-20200312093025 build]# ldd demo 
	linux-vdso.so.1 =>  (0x00007ffc815d8000)
	libcalc.so => /root/cmake/demo3/lib/libcalc.so (0x00007f6880a80000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f68806b2000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f6880c82000)
~~~

使用ldd查看链接库的位置，发现`libcalc.so`在我们指定的`lib`目录。

### 六、自定义编译选项

> 本节对应的源代码所在目录：[Demo4](#)。

CMake 允许为项目增加编译选项，从而可以根据用户的环境和需求选择最合适的编译方案。

例如，可以将 calc 库设为一个可选的库，如果该选项为 `ON` ，就使用该库定义的函数来进行运算。否则就调用标准库中的运算符进行操作。

还是之前的代码，在此基础上进行增删。

**修改 CMakeLists 文件**

我们要做的第一步是在顶层的 CMakeLists.txt 文件中添加该选项：

~~~cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (calc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)

# 是否使用自己的 LIBCALC 库
option (USE_MYCALC
	   "Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if (USE_MYCALC)
  # 添加 头文件路径
  include_directories ("${PROJECT_SOURCE_DIR}/include")
  # 添加 math 子目录    指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理 
  add_subdirectory (src)
  set (EXTRA_LIBS ${EXTRA_LIBS} calc)
endif (USE_MYCALC)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable (demo ${DIR_SRCS})
# 添加链接库
target_link_libraries (demo  ${EXTRA_LIBS})
~~~

其中：

1. 第10行的 `configure_file` 命令用于加入一个配置头文件 config.h ，这个文件由 CMake 从 [config.h.in](http://config.h.in/) 生成，通过这样的机制，将可以通过预定义一些参数和变量来控制代码的生成。
2. 第16行的 `option` 命令添加了一个  `USE_MYCALC`选项，并且默认值为 `ON` 。
3. 第20行根据  `USE_MYCALC`变量的值来决定是否使用我们自己编写的 calc库。

**修改 [main.c]文件**，让其根据 `USE_MYCALC` 值来决定是否调用标准库还是 calc 库：

~~~c
#include<stdio.h>
#include<config.h>

#ifdef USE_MYCALC
#include"head.h"
#endif
int main()
{
	int a = 20;
	int b = 12;
	printf("a = %d,b = %d\n",a,b);
#ifdef USE_MYCALC
	printf("use my calc\n");
	printf("a + b = %d\n",add(a,b));
	printf("a - b = %d\n",subtract(a,b));
	printf("a * b = %d\n",multiply(a,b));
	printf("a / b = %lf\n",divide(a,b));
#else
	printf("not use my clac\n");
	printf("a + b = %d\n",a + b);
	printf("a - b = %d\n",a - b);
	printf("a * b = %d\n",a * b);
	printf("a / b = %d\n",a / b);
#endif
	return 0;
}
~~~

**编写 [config.h.in]文件**

上面的程序值得注意的是第2行，这里引用了一个 config.h 文件，这个文件预定义了 `USE_MYCALC` 的值。但我们并不直接编写这个文件，为了方便从 CMakeLists.txt 中导入配置，我们编写一个 [config.h.in](http://config.h.in/) 文件，内容如下：

```cmake
#cmakedefine USE_MYCALC
```

这样 CMake 会自动根据 CMakeLists 配置文件中的设置自动生成 config.h 文件。

#### 自定义编译项目

同样使用外部编译，为了便于交互式的选择该变量的值，可以使用`cmake -i` 命令（也可以使用  `ccmake` 命令，该命令会提供一个会话式的交互式配置界面）：

~~~shell
[root@ecs-x-medium-2-linux-20200312093025 demo4]# ls
CMakeLists.txt  config.h.in  include  lib  main.c  src
[root@ecs-x-medium-2-linux-20200312093025 demo4]# mkdir build
[root@ecs-x-medium-2-linux-20200312093025 demo4]# cd build/
[root@ecs-x-medium-2-linux-20200312093025 build]# cmake -i ..
Would you like to see advanced options? [No]:
Please wait while cmake processes CMakeLists.txt files....



Variable Name: CMAKE_BUILD_TYPE
Description: Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.
Current Value: 
New Value (Enter to keep current value): 

Variable Name: CMAKE_INSTALL_PREFIX
Description: Install path prefix, prepended onto install directories.
Current Value: /usr/local
New Value (Enter to keep current value): 

Variable Name: USE_MYCALC
Description: Use provided math implementation
Current Value: ON
New Value (Enter to keep current value): OFF

Please wait while cmake processes CMakeLists.txt files....

CMake complete, run make to build project.
~~~

上面是交互命令，有提示让你输入选项，回车默认不修改，可设置`OFF`和`ON`，

从中可以找到刚刚定义的 `USE_MYCALC` 选项，在选项中设置`OFF`，make一下运行如下

~~~shell
[root@ecs-x-medium-2-linux-20200312093025 build]# make
Scanning dependencies of target demo
[100%] Building C object CMakeFiles/demo.dir/main.c.o
Linking C executable demo
[100%] Built target demo
[root@ecs-x-medium-2-linux-20200312093025 build]# ./demo 
a = 20,b = 12
not use my clac
a + b = 32
a - b = 8
a * b = 240
a / b = 1
~~~

可以将定义的 `USE_MYCALC` 选项，在选项中设置`ON`，重新，make一下运行如下

~~~shell
[root@ecs-x-medium-2-linux-20200312093025 build]# ./demo 
a = 20,b = 12
use my calc
a + b = 32
a - b = 8
a * b = 240
a / b = 1.666667
~~~

### 七、定制安装规则

> 本节对应的源代码所在目录：[Demo5](#)。

首先先在 子目录下的CMakeLists.txt 文件里添加下面两行：

~~~cmake
# 指定 MathFunctions 库的安装路径 
install (TARGETS calc DESTINATION lib)
install (FILES "${PROJECT_SOURCE_DIR}/include/head.h" DESTINATION include)
~~~

指明 calc 库的安装路径。之后同样修改根目录的 CMakeLists 文件，在末尾添加下面几行：

~~~c
# 指定安装路径
install (TARGETS demo DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
~~~

通过上面的定制，生成的 demo 文件和 calc 函数库 libcalc.so 文件将会被复制到 `/usr/local/bin` 中，而 head.h 和生成的 config.h 文件则会被复制到 `/usr/local/include` 中。

### 八、支持 gdb

> 本节对应的源代码所在目录：[Demo5](#)。

让 CMake 支持 gdb 的设置也很容易，只需要指定 `Debug` 模式下开启 `-g` 选项：

```cmake
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")
```

之后可以直接对生成的程序使用 gdb 来调试。

另外提一下，`CFLAGS` 是预先设置的变量。

| 命令       | 意义                      |
| :--------- | :------------------------ |
| `CFLAGS`   | C语言编译器参数。         |
| `CXXFLAGS` | C++语言编译器参数。       |
| `CPPFLAGS` | C预处理器参数             |
| `LDFLAGS`  | 链接器参数。（如：`ld` ） |