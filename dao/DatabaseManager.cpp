//
// Created by 114514 on 2026/7/29.
//

#include "DatabaseManager.h"

#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QThread>

QThreadStorage<QSqlDatabase> DatabaseManager::s_databases;

QMutex DatabaseManager::s_mutex;

bool DatabaseManager::initialize() {
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() {
    if (s_databases.hasLocalData() && s_databases.localData().isOpen()) {
        return s_databases.localData();
    }
    QMutexLocker locker(&s_mutex);
    QString connName=buildConnectionName();
    if (QSqlDatabase::contains(connName)) {
        QSqlDatabase::removeDatabase(connName);
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connName);
    QString appDir = QCoreApplication::applicationDirPath();
    // QString dbPath = QDir(appDir).filePath("../db/bookkeepings.db");

    db.setDatabaseName("D:/furthre/qt/bookkeepings/db/bookkeepings.db");
    if (!db.open()) {
        qCritical() << "线程" << QThread::currentThreadId() << "数据库打开失败:" << db.lastError().text();
        return QSqlDatabase();
    }
    s_databases.setLocalData(db);
    locker.unlock();
    return db;
}

void DatabaseManager::close() {
    if (s_databases.hasLocalData()) {
        QString connName=buildConnectionName();
        s_databases.localData().close();
        s_databases.setLocalData(QSqlDatabase());
        QSqlDatabase::removeDatabase(connName);
    }
}

bool DatabaseManager::isOpen() {
    return s_databases.hasLocalData() && s_databases.localData().isOpen();
}


QString DatabaseManager::buildConnectionName() {
    return QString("bookkeepings_conn_%1")
    .arg(reinterpret_cast<quintptr>(QThread::currentThreadId()),0,16);
}
