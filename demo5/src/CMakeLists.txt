# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

#指定了生成.so的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 指定生成 calc 链接库 默认.a静态库，指定SHARED可设置生成动态库,指定STATIC可设置生成静态库
add_library (calc SHARED ${DIR_LIB_SRCS})

# 指定 MathFunctions 库的安装路径 
install (TARGETS calc DESTINATION lib)
install (FILES "${PROJECT_SOURCE_DIR}/include/head.h" DESTINATION include)
