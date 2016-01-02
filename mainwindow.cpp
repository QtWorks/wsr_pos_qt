#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataManager/DataManager.h"
#include <StyleSheet.h>
#include "Order/DiscountPanel/DiscountPanel.h"
#define TOTAL_WIDTH		1280
#define TOTAL_HEIGHT	1024
#include "Order/DiscountPanel/TabView.h"

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
    setGeometry(100, 100, TOTAL_WIDTH, TOTAL_HEIGHT);

	setItemWidget();
	setOrderItemWidget();
	setTotalWidget();

    connect(mItemWidget, SIGNAL(itemSelected(Item*)), mOrderItemWidget, SLOT(addItem(Item*)));

	connect(mOrderItemWidget, SIGNAL(changeOrder()), this, SLOT(onChangeOrder()));

//	connect(this, SIGNAL(changedOrderItem(QList<OrderItem*>)), mOrderItemWidget, SLOT(onChangeOrderItem(QList<OrderItem*>)));
//	connect(this, SIGNAL(changedOrderItem(QList<OrderItem*>)), mTotalWidget, SLOT(onChangeOrderItem(QList<OrderItem*>)));

	connect(mTotalWidget, SIGNAL(clickDeposit()), this, SLOT(showDepositPanel()));
	connect(mTotalWidget, SIGNAL(clickDiscount()), this, SLOT(showDiscountPanel()));
    connect(mTotalWidget, SIGNAL(clickOrder()), this, SLOT(showOrderPanel()));
    connect(mTotalWidget, SIGNAL(clickCancel()), this, SLOT(clearAll()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setItemWidget()
{
	DataManager *dm = DataManager::getInstance();

    mItemWidget = new ItemWidget(this, dm->getItemList());
    mItemWidget->setGeometry(0, 400, 1280, 624);
    mItemWidget->setStyleSheet(WIDGET_STYLE_SHEET_1(SHOPKEEP_ITEM, SHOPKEEP_ITEM_DARK));

    mItemWidget->show();
}

void MainWindow::setOrderItemWidget()
{
	mOrderItemWidget = new OrderItemWidget(this);
	mOrderItemWidget->setGeometry(0, 0, 900, 450);
	mOrderItemWidget->setStyleSheet(WIDGET_STYLE_SHEET_1(SHOPKEEP_ORDER_ITEM_WIDGET, SHOPKEEP_ORDER_ITEM_WIDGET));
	mOrderItemWidget->show();
}

void MainWindow::setTotalWidget()
{
	mTotalWidget = new TotalWidget(this);
	mTotalWidget->setGeometry(900, 0, 380, 450);
	mTotalWidget->setStyleSheet(WIDGET_STYLE_SHEET_1(SHOPKEEP_TOTAL_WIDGET, SHOPKEEP_TOTAL_WIDGET_DARK));
}

void MainWindow::onChangeOrder()
{
	mTotalWidget->setSubtotal(mOrderItemWidget->getSubTotalPrice());
	mTotalWidget->setDiscount(mOrderItemWidget->getDiscountPrice(), mOrderItemWidget->getDiscountPercent());
	mTotalWidget->setTotal(mOrderItemWidget->getTotalPrice());
}

void MainWindow::showDepositPanel()
{
	DiscountPanel *dp = new DiscountPanel(this, DiscountPanel::DEPOSIT);
	dp->show();

	connect(dp, SIGNAL(discount(uint)), mTotalWidget, SLOT(setDeposit(uint)));
}

void MainWindow::showDiscountPanel()
{
	DiscountPanel *dp = new DiscountPanel(this, DiscountPanel::DISCOUNT);
	dp->show();

	connect(dp, SIGNAL(discount(TabButton::TYPE, uint)), mOrderItemWidget, SLOT(setDiscount(TabButton::TYPE, uint)));
}

void MainWindow::clearAll()
{
	mTotalWidget->setDeposit(0);
	mOrderItemWidget->removeAll();
}

void MainWindow::showOrderPanel()
{

}
