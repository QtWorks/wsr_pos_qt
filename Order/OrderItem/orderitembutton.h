#ifndef ORDERITEMBUTTON_H
#define ORDERITEMBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QLocale>
#include "DataManager/OrderItem.h"
#include "../DiscountPanel/DiscountPanel.h"

#define BUTTON_W					900
#define BUTTON_H					50

#define BUTTON_GAP					20
#define BUTTON_ICON_GAP				5

#define LABEL_TITLE_X				0
#define LABEL_TITLE_Y				0
#define LABEL_TITLE_W				240
#define LABEL_TITLE_H				BUTTON_H

#define BUTTON_AMOUNT_DECREASE_X	LABEL_TITLE_X + BUTTON_GAP + LABEL_TITLE_W
#define BUTTON_AMOUNT_DECREASE_Y	15
#define BUTTON_AMOUNT_DECREASE_W	20
#define BUTTON_AMOUNT_DECREASE_H	20

#define LABEL_AMOUNT_X				BUTTON_AMOUNT_DECREASE_X + BUTTON_ICON_GAP + BUTTON_AMOUNT_DECREASE_W
#define LABEL_AMOUNT_Y				0
#define LABEL_AMOUNT_W				40
#define LABEL_AMOUNT_H				BUTTON_H

#define BUTTON_AMOUNT_INCREASE_X	LABEL_AMOUNT_X + BUTTON_ICON_GAP + LABEL_AMOUNT_W
#define BUTTON_AMOUNT_INCREASE_Y	15
#define BUTTON_AMOUNT_INCREASE_W	20
#define BUTTON_AMOUNT_INCREASE_H	20

#define LABEL_UNIT_PRICE_X			BUTTON_AMOUNT_INCREASE_X + BUTTON_GAP + BUTTON_AMOUNT_INCREASE_W
#define LABEL_UNIT_PRICE_Y			0
#define LABEL_UNIT_PRICE_W			60
#define LABEL_UNIT_PRICE_H			BUTTON_H

#define LABEL_SUB_TOTAL_PRICE_X		LABEL_UNIT_PRICE_X + BUTTON_GAP + LABEL_UNIT_PRICE_W
#define LABEL_SUB_TOTAL_PRICE_Y		0
#define LABEL_SUB_TOTAL_PRICE_W		80
#define LABEL_SUB_TOTAL_PRICE_H		BUTTON_H

#define LABEL_DISCOUNT_X			LABEL_SUB_TOTAL_PRICE_X + BUTTON_ICON_GAP + LABEL_SUB_TOTAL_PRICE_W
#define LABEL_DISCOUNT_Y			0
#define LABEL_DISCOUNT_W			80
#define LABEL_DISCOUNT_H			BUTTON_H

#define LABEL_TOTAL_PRICE_X			LABEL_DISCOUNT_X + BUTTON_GAP + LABEL_DISCOUNT_W
#define LABEL_TOTAL_PRICE_Y			0
#define LABEL_TOTAL_PRICE_W			80
#define LABEL_TOTAL_PRICE_H			BUTTON_H

class OrderItemButton : public QWidget
{
	Q_OBJECT
private:
	OrderItem *mOrderItem;

	QLabel	*mLabelTitle;
	QLabel	*mLabelUnitPrice;
	QLabel	*mLabelAmount;
	QLabel	*mLabelSubTotalPrice;
	QPushButton	*mButtonDiscount;
	QLabel	*mLabelTotalPrice;

	QToolButton	*mButtonAmountIncrease;
	QToolButton	*mButtonAmountDecrease;

	QToolButton	*mButtonDelete;

public:
	OrderItemButton(QWidget *parent = 0, OrderItem *order_item = new OrderItem());
	bool compareItem(Item* item);
	OrderItem* getOrderItem();
	void paintEvent(QPaintEvent *);

signals:
	void changeOrderItem(OrderItemButton* order_item_button);

public slots:
	void increaseAmount(uint amount = 1);
	void decreaseAmount(uint amount = 1);
	void showDiscountPanel();
	void setDiscount(TabButton::TYPE type, uint value);
	void refreshData();
};

#endif // ORDERITEMBUTTON_H
