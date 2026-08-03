//
// Created by 114514 on 2026/8/3.
//

#ifndef BOOKKEEPINGS_TIMERANGETYPE_H
#define BOOKKEEPINGS_TIMERANGETYPE_H
#include <QDateTime>

#include "../../../../qt/5.9.6/mingw53_32/include/QtCore/qmetatype.h"


enum class TimeRangeType {
    ThisMonth,
    LastThreeMonths,
    LastYear,
};
struct TimeRange {
    QString start;
    QString end;
};
Q_DECLARE_METATYPE(TimeRangeType)
inline TimeRange getTimeRangeTypeString(TimeRangeType timeRangeType) {
    QString end = QDateTime::currentDateTime().toString("yyyy-MM");
    switch (timeRangeType) {
        case TimeRangeType::ThisMonth:
            return {end,end};
        case TimeRangeType::LastThreeMonths:
            return {QDateTime::currentDateTime().addMonths(-3).toString("yyyy-MM"),end};
        case TimeRangeType::LastYear:
            return {QDateTime::currentDateTime().addYears(-1).toString("yyyy-MM"),end};
    }
    return {};
}

#endif //BOOKKEEPINGS_TIMERANGETYPE_H
