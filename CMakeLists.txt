cmake_minimum_required(VERSION 4.2)
project(bookkeepings)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# MSVC 构建请指向 msvc2017_64（MSVC 编译器只能链接 MSVC 编译的 Qt）
# MinGW 构建请改成 mingw53_32，或用 -DCMAKE_PREFIX_PATH=... 覆盖
set(CMAKE_PREFIX_PATH "D:/qt/5.9.6/msvc2017_64" CACHE PATH "Qt 安装路径")

# 源码是 UTF-8 编码，MSVC 默认按 GBK 读会报 C4819/C2001，必须加 /utf-8
if (MSVC)
    add_compile_options(/utf-8)
endif ()

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        sql
        network
)

add_executable(bookkeepings main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        po/employee.cpp
        po/employee.h
        dialog/employeedialog.cpp
        dialog/employeedialog.h
        dialog/employeedialog.ui
        dao/DatabaseManager.cpp
        dao/DatabaseManager.h
        dao/EmployeeDao.cpp
        dao/EmployeeDao.h
        po/Result.cpp
        po/Result.h
        po/QueryPage.cpp
        po/QueryPage.h
        po/processs.cpp
        po/processs.h
        dao/ProcessDao.cpp
        dao/ProcessDao.h
        po/bag.cpp
        po/bag.h
        dialog/bag.cpp
        dialog/bag.h
        dialog/bag.ui
        dao/bagDao.cpp
        dao/bagDao.h
        dialog/bagprocessdialog.cpp
        dialog/bagprocessdialog.h
        dialog/bagprocessdialog.ui
        dao/BagProcessDao.cpp
        dao/BagProcessDao.h
        po/BagProcess.cpp
        po/BagProcess.h
        customDelegateImage/ImageDelegate.cpp
        customDelegateImage/ImageDelegate.h
        po/order.cpp
        po/order.h
        po/orderDetail.cpp
        po/orderDetail.h
        dialog/orderdialog.cpp
        dialog/orderdialog.h
        dialog/orderdialog.ui
        dao/OrderDao.cpp
        dao/OrderDao.h
        customDelegateImage/ComboxDelegate.cpp
        customDelegateImage/ComboxDelegate.h
        dao/OrderDeatilDao.cpp
        dao/OrderDeatilDao.h
        dialog/orderprocessdialog.cpp
        dialog/orderprocessdialog.h
        dialog/orderprocessdialog.ui
        dialog/employeesalarydialog.cpp
        dialog/employeesalarydialog.h
        dialog/employeesalarydialog.ui
        vo/OrderDetailtem.cpp
        vo/OrderDetailtem.h
        vo/EmployeeOrderSummary.cpp
        vo/EmployeeOrderSummary.h
        vo/EmployeeMonthSalary.cpp
        vo/EmployeeMonthSalary.h
        network/NetworkManager.cpp
        network/NetworkManager.h
        network/OSSClient.cpp
        network/OSSClient.h

)
target_link_libraries(bookkeepings
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Network
)

target_include_directories(bookkeepings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Sql Network)
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
        # OpenSSL SSL 库（HTTPS 需要）
        foreach (SSL_LIB libeay32 ssleay32)
            if (EXISTS "${QT_INSTALL_PATH}/bin/${SSL_LIB}.dll")
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${QT_INSTALL_PATH}/bin/${SSL_LIB}.dll"
                        "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
            endif ()
        endforeach (SSL_LIB)
    endif ()
endif ()
