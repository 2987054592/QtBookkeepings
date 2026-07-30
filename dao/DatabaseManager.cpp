//
// Created by 114514 on 2026/7/29.
//

#include "DatabaseManager.h"

#include <QSqlError>
#include <QDebug>

const QString DatabaseManager::CONNECTION_NAME = QStringLiteral("bookkeepings_conn");
bool DatabaseManager::s_initialized = false;

bool DatabaseManager::initialize() {
    if (s_initialized && getDatabase().isOpen()) {
        return true;
    }

    // 如果之前已经添加过同名连接，先移除
    if (QSqlDatabase::contains(CONNECTION_NAME)) {
        QSqlDatabase::removeDatabase(CONNECTION_NAME);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    db.setDatabaseName("bookkeepings.db");

    if (!db.open()) {
        qCritical() << "数据库打开失败:" << db.lastError().text();
        return false;
    }

    s_initialized = true;
    qInfo() << "数据库连接成功";
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() {
    return QSqlDatabase::database(CONNECTION_NAME);
}

void DatabaseManager::close() {
    if (s_initialized) {
        // 确保所有查询都已销毁后再关闭
        QSqlDatabase::database(CONNECTION_NAME).close();
        QSqlDatabase::removeDatabase(CONNECTION_NAME);
        s_initialized = false;
    }
}

bool DatabaseManager::isOpen() {
    return s_initialized && getDatabase().isOpen();
}
