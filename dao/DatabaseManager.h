//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_DATABASEMANAGER_H
#define BOOKKEEPINGS_DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

/**
 * 统一的数据库连接管理器
 *
 * 整个应用只维护一个数据库连接，所有 DAO 共享此连接。
 * 使用原则：
 *   1. 程序启动时调用 DatabaseManager::initialize() 一次
 *   2. 所有 QSqlQuery 必须传入 DatabaseManager::getDatabase() 作为第二个参数
 *      QSqlQuery query(DatabaseManager::getDatabase());
 *   3. 程序退出时调用 DatabaseManager::close()
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

    static const QString CONNECTION_NAME;
    static bool s_initialized;
};

#endif //BOOKKEEPINGS_DATABASEMANAGER_H
