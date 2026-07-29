//
// Created by 114514 on 2026/7/29.
//

#ifndef BOOKKEEPINGS_BAGPROCESSDIALOG_H
#define BOOKKEEPINGS_BAGPROCESSDIALOG_H

#include <QDialog>

#include "po/processs.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class bagprocessdialog;
}

QT_END_NAMESPACE

class bagprocessdialog : public QDialog {
    Q_OBJECT

public:
    explicit bagprocessdialog(QWidget *parent = nullptr);

    ~bagprocessdialog() override;
    void setComboxData(const QVector<processs>& processes);
private:
    Ui::bagprocessdialog *ui;

public:
    processs current_process() const;

};


#endif //BOOKKEEPINGS_BAGPROCESSDIALOG_H
