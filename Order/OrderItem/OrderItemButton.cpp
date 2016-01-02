#include <QStyleOption>
#include <QPainter>
#include "OrderItemButton.h"
#include "StyleSheet.h"

OrderItemButton::OrderItemButton(QWidget *parent, OrderItem *order_item) : QWidget(parent), mOrderItem(order_item)
{
	mLabelTitle = new QLabel(this);
	mLabelUnitPrice = new QLabel(this);
	mButtonAmountDecrease = new QToolButton(this);
	mLabelAmount = new QLabel(this);
	mButtonAmountIncrease = new QToolButton(this);
	mLabelSubTotalPrice = new QLabel(this);
	mButtonDiscount = new QPushButton(this);
	mLabelTotalPrice = new QLabel(this);

	mButtonAmountDecrease->setStyleSheet(PUSH_BUTTON_STYLE_SHEET_1(GRASS, GRASS_DARK));
	mButtonDiscount->setStyleSheet(PUSH_BUTTON_STYLE_SHEET_1(GRASS, GRASS_DARK));
	setStyleSheet(PUSH_BUTTON_STYLE_SHEET_2(3, SHOPKEEP_ORDER_ITEM, SHOPKEEP_ORDER_ITEM));

	mLabelTitle->setGeometry(LABEL_TITLE_X, LABEL_TITLE_Y, LABEL_TITLE_W, LABEL_TITLE_H);
	mButtonAmountDecrease->setGeometry(BUTTON_AMOUNT_DECREASE_X, BUTTON_AMOUNT_DECREASE_Y, BUTTON_AMOUNT_DECREASE_W, BUTTON_AMOUNT_DECREASE_H);
	mLabelAmount->setGeometry(LABEL_AMOUNT_X, LABEL_AMOUNT_Y, LABEL_AMOUNT_W, LABEL_AMOUNT_H);
	mButtonAmountIncrease->setGeometry(BUTTON_AMOUNT_INCREASE_X, BUTTON_AMOUNT_INCREASE_Y, BUTTON_AMOUNT_INCREASE_W, BUTTON_AMOUNT_INCREASE_H);
	mLabelUnitPrice->setGeometry(LABEL_UNIT_PRICE_X, LABEL_UNIT_PRICE_Y, LABEL_UNIT_PRICE_W, LABEL_UNIT_PRICE_H);
	mLabelSubTotalPrice->setGeometry(LABEL_SUB_TOTAL_PRICE_X, LABEL_SUB_TOTAL_PRICE_Y, LABEL_SUB_TOTAL_PRICE_W, LABEL_SUB_TOTAL_PRICE_H);
	mButtonDiscount->setGeometry(LABEL_DISCOUNT_X, LABEL_DISCOUNT_Y, LABEL_DISCOUNT_W, LABEL_DISCOUNT_H);
	mLabelTotalPrice->setGeometry(LABEL_TOTAL_PRICE_X, LABEL_TOTAL_PRICE_Y, LABEL_TOTAL_PRICE_W, LABEL_TOTAL_PRICE_H);

	qDebug("BUTTON_AMOUNT_DECREASE_X:%d", BUTTON_AMOUNT_DECREASE_X);
	qDebug("BUTTON_AMOUNT_DECREASE_W:%d", BUTTON_AMOUNT_DECREASE_W);
	qDebug("LABEL_AMOUNT_X:%d", LABEL_AMOUNT_X);
	qDebug("LABEL_AMOUNT_W:%d", LABEL_AMOUNT_W);
	qDebug("BUTTON_AMOUNT_INCREASE_X:%d", BUTTON_AMOUNT_INCREASE_X);
	qDebug("BUTTON_AMOUNT_INCREASE_W:%d", BUTTON_AMOUNT_INCREASE_W);


	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(12);
	mLabelTitle->setFont(font);
	mLabelAmount->setFont(font);
	mLabelUnitPrice->setFont(font);
	mLabelSubTotalPrice->setFont(font);
	mButtonDiscount->setFont(font);
	mLabelTotalPrice->setFont(font);

	mLabelTitle->setStyleSheet("background-color: rgba(10,0,0,50%)");
	mButtonAmountDecrease->setText("<");
	mLabelAmount->setStyleSheet("qproperty-alignment: 'AlignCenter'; background-color: rgba(0,20,0,50%)");
	mButtonAmountIncrease->setText(">");
	mButtonAmountIncrease->setStyleSheet(TOOL_BUTTON_STYLE_SHEET_2());
	mLabelUnitPrice->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,0,30,50%)");
	mLabelSubTotalPrice->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(50,0,0,50%)");
	//	mLabelDiscount->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,50,0,50%)");
	mLabelTotalPrice->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,0,50,50%)");

	refreshData();

	connect(mButtonAmountDecrease, SIGNAL(clicked()), this, SLOT(decreaseAmount()));
	connect(mButtonAmountIncrease, SIGNAL(clicked()), this, SLOT(increaseAmount()));
	connect(mButtonDiscount, SIGNAL(clicked()), this, SLOT(showDiscountPanel()));
}

void OrderItemButton::refreshData()
{
	mLabelTitle->setText(mOrderItem->getItem()->getName());
	mLabelAmount->setText(QString::number(mOrderItem->getAmount()));
	mLabelUnitPrice->setText(QLocale(QLocale::Korean).toString(mOrderItem->getItem()->getPrice()));
	mLabelSubTotalPrice->setText(QLocale(QLocale::Korean).toString(mOrderItem->getSubTotalPrice()));
	mButtonDiscount->setText(QLocale(QLocale::Korean).toString(mOrderItem->getDiscountPercent()));
	mLabelTotalPrice->setText(QLocale(QLocale::Korean).toString(mOrderItem->getTotalPrice()));

	update();

	emit changeOrderItem(this);
}

bool OrderItemButton::compareItem(Item* item)
{
	if(mOrderItem->getItem() == item)
	{
		return true;
	}

	return false;
}


void OrderItemButton::increaseAmount(uint amount)
{
	mOrderItem->increaseItem(amount);
	refreshData();
}

void OrderItemButton::decreaseAmount(uint amount)
{
	mOrderItem->decreaseItem(amount);
	refreshData();
}

void OrderItemButton::showDiscountPanel()
{
	DiscountPanel *dp = new DiscountPanel(this, DiscountPanel::DISCOUNT);
	dp->show();

	connect(dp, SIGNAL(discount(TabButton::TYPE,uint)), this, SLOT(setDiscount(TabButton::TYPE,uint)));
}

void OrderItemButton::setDiscount(TabButton::TYPE type, uint value)
{
	switch(type)
	{
		case TabButton::PRICE:
		{
			getOrderItem()->setDiscountPrice(value);
			break;
		}
		case TabButton::PERCENT:
		{
			getOrderItem()->setDiscountPercent(value);
			break;
		}
		case TabButton::CUSTOM:
		{
			break;
		}
	}

	refreshData();
}

OrderItem* OrderItemButton::getOrderItem()
{
	return mOrderItem;
}

void OrderItemButton::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
