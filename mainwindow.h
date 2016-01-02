#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "Order/Item/ItemWidget.h"
#include "Order/OrderItem/OrderItemWidget.h"
#include "Order/TotalWidget/TotalWidget.h"

class MainWindow : public QWidget
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
        ItemWidget *mItemWidget;
		OrderItemWidget *mOrderItemWidget;
		TotalWidget *mTotalWidget;

		QList<OrderItem*> mOrderItemList;

		void setItemWidget();
		void setOrderItemWidget();
		void setTotalWidget();

	signals:
		void changedOrderItem(QList<OrderItem*>);

	public slots:
		void showDepositPanel();
		void showDiscountPanel();
		void clearAll();
		void onChangeOrder();
        void showOrderPanel();
};

#endif // MAINWINDOW_H
