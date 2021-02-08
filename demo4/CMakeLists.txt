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
