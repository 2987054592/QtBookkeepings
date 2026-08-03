//
// Created by 114514 on 2026/8/3.
//

#include "worker.h"

#include <qset.h>

#include "dao/bagDao.h"
#include "dao/EmployeeDao.h"
#include "dao/OrderDao.h"
#include "dao/OrderDeatilDao.h"
#include "po/employee.h"
#include <qdebug.h>
worker::worker(QObject *parent) : QObject(parent) {

}

void worker::doFetchData(const CategoryType& categoryType, const TimeRangeType& timeRangeType) {
    ChartData data;
    if (categoryType==CategoryType::Employee) {
        //根据时间范围查询员工数据
        const auto & time = getTimeRangeTypeString(timeRangeType);
        const auto & order_by_time = OrderDao::getOrderByTime(time);
        if (!order_by_time.isOk) {
            return;
        }
        QSet<int> orderIds;
        for (const auto& o:order_by_time.data) {
            orderIds.insert(o.id);
        }
        const auto & order_detail_list_by_order_ids = OrderDeatilDao::getOrderDetailListByOrderIds(orderIds,-1);
        if (!order_detail_list_by_order_ids.isOk) {
            return;
        }

        QMap<int,double> employeeSales;
        for (const auto& o:order_detail_list_by_order_ids.data.values()) {
            for (orderDetail detail : o) {
                employeeSales[detail.employeeId]+=detail.real_price*detail.real_quantity/1000.0;
            }
        }
        QSet<int> employeeIds=employeeSales.keys().toSet();
        const auto & employeeList = EmployeeDao::getByIds(employeeIds);
        QMap<int, employee> empMap;
        if (!employeeList.isOk) {
            return;
        }
        for (const auto& e : employeeList.data) {
            empMap.insert(e.id, e);
        }
        for (const auto& [employeeId, earnings] : employeeSales.toStdMap()) {
            if (empMap.contains(employeeId)) {
                QString name = empMap.value(employeeId).name;
                data.barLabels.append(name);
                data.barValues.append(earnings);
                data.pieLabels.append(name);
                data.pieValues.append(earnings);
            }
        }

    }else if(categoryType==CategoryType::Package){
        //根据时间范围查询书包的热销数量
        const auto & time = getTimeRangeTypeString(timeRangeType);
        const auto & order_by_time = OrderDao::getOrderByTime(time);
        if (!order_by_time.isOk) {
            return;
        }
        //返回书包的名称，书包的销量
        QSet<int> bagIDs;
        for (const auto& o:order_by_time.data) {
            bagIDs.insert(o.bagId);
        }
        const auto & bagList = bagDao::getBagByids(bagIDs);
        QMap<int,QString> bagNameMap;
        for (const auto& b:bagList) {
            bagNameMap.insert(b.id,b.name);
        }
        QSet<int> orderIds;
        for (const auto& o:order_by_time.data) {
            orderIds.insert(o.id);
        }
        const auto & order_detail_list_by_order_ids = OrderDeatilDao::getOrderDetailListByOrderIds(orderIds,-1);
        if (!order_detail_list_by_order_ids.isOk) {
            return;
        }
        QMap<QString,int> bagCount;
        QMap<int,int> orderToBag;
        for (const auto& o:order_by_time.data) {
            orderToBag[o.id]=o.bagId;
        }
        for (auto it=order_detail_list_by_order_ids.data.begin();it!=order_detail_list_by_order_ids.data.end();it++) {
            int orderId=it.key();
            const auto& details=it.value();
            if (details.isEmpty()) {
                return;
            }
            int bagId=orderToBag[orderId];
            bagCount[bagNameMap.value(bagId)]+=details.first().real_quantity;
        }


        for (const auto& [bagName,count]:bagCount.toStdMap()) {
            data.barLabels.append(bagName);
            data.barValues.append(count);
            data.pieLabels.append(bagName);
            data.pieValues.append(count);
        }
    }
    qDebug() << "testdata" << data.barLabels<<data.barValues;
    emit dataFetched(data);
}

