//
// Created by 114514 on 2026/8/3.
//

#ifndef BOOKKEEPINGS_CATEGORYTYPE_H
#define BOOKKEEPINGS_CATEGORYTYPE_H
#include <QString>

#include "../../../../qt/5.9.6/mingw53_32/include/QtCore/qmetatype.h"


enum class CategoryType {
    Package,
    Employee,
};
Q_DECLARE_METATYPE(CategoryType)
inline QString getCategoryTypeString(CategoryType categoryType) {
    switch (categoryType) {
        case CategoryType::Package:
            return "bag";
        case CategoryType::Employee:
            return "employee";
    }
    return nullptr;
}

#endif //BOOKKEEPINGS_CATEGORYTYPE_H
