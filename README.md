## git clone 本项目后
1. 进入 source/， 在这个目录下会看到一个`CMakeLists.txt`文件，
2. 打开你的windows 命令行工具， 输入 `cmake --version`, 确保已经安装较新的cmake工具。
3. 进入到build/目录，里面已经事先用cmake构建了项目的vs2013方案。
   
------如果你已经安装vs2013可以直接打开解决方案使用，如果默认是`debug`模式，请改为`Release`模式

------下面步骤是 使用cmake构建这个项目的简单步骤：

1. 在source目录下，新建一个自己的文件夹， 比如说 mkdir ok,cd ok，创建并进入到这个文件夹； 这个文件夹后续会存放cmake构建生成的项目
2. 检测cmake工具是否安装
   + 在命令行工具中运行 `cmake --version` ，确保cmake已经安装
   + 在source/ok 这个文件夹内，命令行工具中运行 `cmake  -G "Visual Studio 12 2013"  -DCMAKE_BUILD_TYPE=Release  ..`, 
        - -G "Visual Studio 12 2013"   指定生辰vs2013的解决方案
        - -DCMAKE_BUILD_TYPE=Release   对性能进行优化的版本
        - .. 表示path-to-source，也就是`CMakeLists.txt` 所在的相对当前文件夹的相对路径      
   +  依次完成上面步骤，构建完成，

3. 最后我把生成DLL的目录设置在了 `source/build_output`这个文件夹内， 如果需要变更，请更改`CMakeLists.txt`的

```cmake
# 85行位置的 OUTPUT_DIRECTORY 
set(OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/build_output
)
```

4. Release 模式下进行生成任务才会成功。