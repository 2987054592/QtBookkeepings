//
// Created by 114514 on 2026/7/28.
//

#ifndef BOOKKEEPINGS_RESULT_H
#define BOOKKEEPINGS_RESULT_H

#include <QString>
template <typename T>
class Result {
public:
    explicit Result() : isOk(false),message(""),data(T()){}
    explicit Result(bool isOk, const QString &message, const T &data) : isOk(isOk),message(message),data(data){}
    explicit Result(bool isOk, const QString &message) : isOk(isOk),message(message),data(T()){}
       static Result<T> success(const T &data) {
        return Result<T>(true,"",data);
    }
    static Result<T> success() {
        return Result<T>(true,T());
       }
    static Result<T> error(const QString &message) {
        return Result<T>(false,message,T());
    }
public:
    bool isOk;
    QString message;
    T data;
};



#endif //BOOKKEEPINGS_RESULT_H
