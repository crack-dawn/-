cmake_minimum_required(VERSION 3.10)

project(export_dll)


# 将编译器选项设置为 32 位
set(CMAKE_C_FLAGS "-m32")
set(CMAKE_CXX_FLAGS "-m32")
set(CMAKE_EXE_LINKER_FLAGS "-m32")

# 设置编译选项
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 添加头文件搜索路径
list(APPEND INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/utils"

    "${CMAKE_CURRENT_SOURCE_DIR}/lib"

    "${CMAKE_CURRENT_SOURCE_DIR}/my_libs"

    "${CMAKE_CURRENT_SOURCE_DIR}/my_skills"

    "${CMAKE_CURRENT_SOURCE_DIR}"
    )


file(GLOB UTILS
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
    )
source_group("utils" FILES ${UTILS})
 


file(GLOB MY_SKILLS
    "${CMAKE_CURRENT_SOURCE_DIR}/my_skills/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/my_skills/*.h"

)
source_group("my_skills" FILES ${MY_SKILLS})
 


file(GLOB_RECURSE  MY_LIBS
     "${CMAKE_CURRENT_SOURCE_DIR}/my_libs/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/my_libs/*.cpp"
    )
source_group("my_libs" FILES ${MY_LIBS})
 



list(APPEND  ALL_SOURCE_FILES 
        ${MY_SKILLS}
        ${MY_LIBS}
        ${UTILS} 
    )

# 添加要编译为动态库的目标， 为其添加依赖源文件
add_library(TargetDLL SHARED ${ALL_SOURCE_FILES} )

# 设置添加依赖源文件 公共包含目录
target_include_directories(TargetDLL  PUBLIC  ${INCLUDE_DIR} )

# 设置链接的外部库文件的路径
link_directories(${CMAKE_SOURCE_DIR}/lib)
# 链接外部依赖库
target_link_libraries(TargetDLL PUBLIC ${CMAKE_SOURCE_DIR}/lib/worldmodel_lib.lib)




# 设置dll动态库的输出名称
set_target_properties(TargetDLL PROPERTIES OUTPUT_NAME "hiahia")

# 外部调用的函数需要设置为导出函数
set_target_properties(TargetDLL PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


# 设置编译为库类型的 TargetDLL 的属性 生成目录
set_target_properties(TargetDLL PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build_output  # 动态库         这里我需要的是最后的 DLL 动态库文件
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build_output  # 可执行文件
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build_output  # 静态库
)


# mkdir build 
# cd build  
# cmake ..               <path-to-cmake>\cmake.exe -G "Visual Studio 12 2013" <path-to-source>
# ls 查看生成目录
#











# # 打印 INCLUDE_DIR 变量的值
# message("INCLUDE_DIR:" ${INCLUDE_DIR})



# include_directories(inc)
# include_directories(src)
# include_directories(utils)
# include_directories(./)

# # 定义需要编译的源文件列表
# set(ALL_SOURCE_FILES
#     my_main/my_simple_demo.cpp
    # utils/ball.h
    # utils/basevision.h
    # utils/constants.h
    # utils/FilteredObject.h
    # utils/game_state.h
    # utils/historylogger.h
    # utils/matchstate.h
    # utils/maths.cpp
    # utils/maths.h
    # utils/PlayerTask.h
    # utils/referee_commands.h
    # utils/robot.h
    # utils/singleton.h
    # utils/util.h
    # utils/vector.h
    # utils/worldmodel.h
# )


# # 定义需要编译的源文件列表
# file(GLOB SRC_FILES
#      "${CMAKE_CURRENT_SOURCE_DIR}/my_main/*.h"
#      "${CMAKE_CURRENT_SOURCE_DIR}/my_main/*.cpp"

#      "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h"
#      "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"

#      "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h"
#      "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.cpp"

#      "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
#      "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"

#      "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
# )
