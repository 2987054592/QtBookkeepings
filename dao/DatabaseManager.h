//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_DATABASEMANAGER_H
#define BOOKKEEPINGS_DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>


#include <QThreadStorage>
#include <QMutex>

/**
 * 统一的数据库连接管理器
 */
class DatabaseManager {
public:
    /// 初始化数据库连接（只应调用一次）
    static bool initialize();

    /// 获取共享的数据库连接引用
    static QSqlDatabase getDatabase();

    /// 关闭数据库连接
    static void close();

    /// 连接是否已打开
    static bool isOpen();

private:
    DatabaseManager() = default;

    static QThreadStorage<QSqlDatabase> s_databases;
    static QMutex s_mutex;
    static QString buildConnectionName();
};

#endif //BOOKKEEPINGS_DATABASEMANAGER_H
