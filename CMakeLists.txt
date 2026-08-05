cmake_minimum_required(VERSION 4.2)

project(bookkeepings)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


list(APPEND CMAKE_PREFIX_PATH "D:/qt/5.9.6/msvc2017_64")



file(GLOB_RECURSE BOOKKEEPING_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
# 排除构建目录（Qt Creator 的 build/、CLion 的 cmake-build-*）和
# AUTOMOC/AUTOUIC 生成的 _autogen 目录，避免把 moc/ui 临时文件当源码编译
list(FILTER BOOKKEEPING_SOURCES EXCLUDE REGEX "/(cmake-build-[^/]*|build)/|_autogen/")
# 源码是 UTF-8 编码，MSVC 默认按 GBK 读会报 C4819/C2001，必须加 /utf-8
if (MSVC)
    add_compile_options(/utf-8)
endif ()

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        sql
        network
        PrintSupport
        REQUIRED
)
find_package(alibabacloud_oss_v2 REQUIRED)

add_executable(bookkeepings ${BOOKKEEPING_SOURCES})
target_link_libraries(bookkeepings
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
        Qt5::PrintSupport
        alibabacloud_oss_v2::oss

)

target_include_directories(bookkeepings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "D:/qt/5.9.6/msvc2017_64")
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Sql Network PrintSupport)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
    # SQLite 驱动插件
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlite${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/bearer/")
    if (EXISTS "${QT_INSTALL_PATH}/plugins/bearer/qgenericbearer${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/bearer/qgenericbearer${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/bearer/")
        # OpenSSL SSL 库
    endif ()
        foreach (SSL_LIB libeay32 ssleay32)
            if (EXISTS "D:/furthre/qt/toolkit/OpenSSL/${SSL_LIB}.dll")
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "D:/furthre/qt/toolkit/OpenSSL/${SSL_LIB}.dll"
                        "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
            endif ()
        endforeach (SSL_LIB)




