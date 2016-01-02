#include "OrderItemWidget.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

OrderItemWidget::OrderItemWidget(QWidget *parent) : QWidget(parent)
{
	QLabel *title = new QLabel(this);
	QLabel *amount = new QLabel(this);
	QLabel *unit_price = new QLabel(this);
	QLabel *subtotal = new QLabel(this);
	QLabel *discount = new QLabel(this);
	QLabel *total = new QLabel(this);

	title->setText("항목");
	amount->setText("수량");
	unit_price->setText("단가");
	subtotal->setText("합계");
	discount->setText("할인");
	total->setText("총계");

	title->setGeometry(LABEL_TITLE_X, LABEL_TITLE_Y, LABEL_TITLE_W, LABEL_TITLE_H);
	amount->setGeometry(LABEL_AMOUNT_X, LABEL_AMOUNT_Y, LABEL_AMOUNT_W, LABEL_AMOUNT_H);
	unit_price->setGeometry(LABEL_UNIT_PRICE_X, LABEL_UNIT_PRICE_Y, LABEL_UNIT_PRICE_W, LABEL_UNIT_PRICE_H);
	subtotal->setGeometry(LABEL_SUB_TOTAL_PRICE_X, LABEL_SUB_TOTAL_PRICE_Y, LABEL_SUB_TOTAL_PRICE_W, LABEL_SUB_TOTAL_PRICE_H);
	discount->setGeometry(LABEL_DISCOUNT_X, LABEL_DISCOUNT_Y, LABEL_DISCOUNT_W, LABEL_DISCOUNT_H);
	total->setGeometry(LABEL_TOTAL_PRICE_X, LABEL_TOTAL_PRICE_Y, LABEL_TOTAL_PRICE_W, LABEL_TOTAL_PRICE_H);



//	title->setGeometry(40, 0, 380, 50);
//	amount->setGeometry(420, 0, 50, 50);
//	unit_price->setGeometry(470, 0, 100, 50);
//	subtotal->setGeometry(570, 0, 100, 50);
//	discount->setGeometry(670, 0, 100, 50);
//	total->setGeometry(770, 0, 110, 50);

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(12);

	title->setFont(font);
	amount->setFont(font);
	unit_price->setFont(font);
	subtotal->setFont(font);
	discount->setFont(font);
	total->setFont(font);

	amount->setAlignment(Qt::AlignCenter);
	unit_price->setAlignment(Qt::AlignCenter);
	subtotal->setAlignment(Qt::AlignCenter);
	discount->setAlignment(Qt::AlignCenter);
	total->setAlignment(Qt::AlignCenter);
}

OrderItemWidget::~OrderItemWidget()
{

}

void OrderItemWidget::paintEvent(QPaintEvent *)
{
	 QStyleOption opt;
	 opt.init(this);
	 QPainter p(this);
	 style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void OrderItemWidget::addItem(Item* item)
{
	bool find_item = false;

	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		if(mOrderItemButtonList.at(i)->compareItem(item) == true)
		{
			find_item = true;
			mOrderItemButtonList.at(i)->increaseAmount();
		}
	}

	if(find_item == false)
	{
		OrderItemButton *order_item_button = new OrderItemButton(this, new OrderItem(item));
		mOrderItemButtonList.append(order_item_button);

		connect(order_item_button, SIGNAL(changeOrderItem(OrderItemButton*)), this, SLOT(onChangeOrderItem(OrderItemButton*)));

		refreshButtonList();
	}

	emit changeOrder();
}

void OrderItemWidget::setDiscount(TabButton::TYPE type, uint value)
{
	switch(type)
	{
		case TabButton::PRICE:
		{
			setDiscountPrice(value);
			break;
		}
		case TabButton::PERCENT:
		{
			setDiscountPercent(value);
			break;
		}
		case TabButton::CUSTOM:
		{
			break;
		}
	}

	refreshButtonList();
}

void OrderItemWidget::setDiscountPercent(uint percent)
{
	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		OrderItem* order_item = mOrderItemButtonList.at(i)->getOrderItem();
		order_item->setDiscountPercent(percent);
	}
}

void OrderItemWidget::setDiscountPrice(uint price)
{
	uint sub_total_price = getSubTotalPrice();
	uint total_discount_price = 0;

	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		OrderItem* order_item = mOrderItemButtonList.at(i)->getOrderItem();

		if(i != mOrderItemButtonList.size() - 1)
		{
			uint discount_price = order_item->getSubTotalPrice() * (((uint)((float)price / sub_total_price * 100)) / (float) 100.0 );
			order_item->setDiscountPrice(discount_price);
			total_discount_price = total_discount_price + discount_price;
		}
		else
		{
			order_item->setDiscountPrice(price - total_discount_price);
		}
	}
}

void OrderItemWidget::setEnuriPrice(uint price)
{
	uint sub_total_price = getSubTotalPrice();
	uint total_enuri_price = 0;

	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		OrderItem* order_item = mOrderItemButtonList.at(i)->getOrderItem();

		if(i != mOrderItemButtonList.size() - 1)
		{
			uint enuri_price = order_item->getSubTotalPrice() * (((uint)((float)price / sub_total_price * 100)) / (float) 100.0 );
			order_item->setEnuriPrice(enuri_price);
			total_enuri_price = total_enuri_price + enuri_price;
		}
		else
		{
			order_item->setEnuriPrice(price - total_enuri_price);
		}
	}
}

void OrderItemWidget::onChangeOrderItem(OrderItemButton* order_item_button)
{
	int index = mOrderItemButtonList.indexOf(order_item_button);

	if(index > -1)
	{
		if(order_item_button->getOrderItem()->getAmount() <= 0)
		{
			delete mOrderItemButtonList.takeAt(index);
			refreshButtonList();
		}

		emit changeOrder();
	}
	else
	{
		qDebug("OrderItemButton Remove Failed. No such OrderItemButton in the list");
	}
}

void OrderItemWidget::refreshButtonList()
{
	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		mOrderItemButtonList.at(i)->setGeometry(50, i * 50 + 50, 800, 50);
		mOrderItemButtonList.at(i)->refreshData();
		mOrderItemButtonList.at(i)->show();
	}
}

uint OrderItemWidget::getTotalPrice()
{
	uint total_price = 0;

	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		OrderItem* order_item = mOrderItemButtonList.at(i)->getOrderItem();
		total_price = total_price + order_item->getTotalPrice();
	}

	return total_price;
}

uint OrderItemWidget::getTotalPercent()
{
	uint total_price = getTotalPrice();
	uint sub_total_price = getSubTotalPrice();

	return total_price / sub_total_price * 100.0;
}

uint OrderItemWidget::getSubTotalPrice()
{
	uint sub_total_price = 0;

	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		OrderItem* order_item = mOrderItemButtonList.at(i)->getOrderItem();
		sub_total_price = sub_total_price + (order_item->getItem()->getPrice() * order_item->getAmount());
	}

	return sub_total_price;
}

uint OrderItemWidget::getDiscountPrice()
{
	uint discount = 0;

	for(int i = 0 ; i < mOrderItemButtonList.size() ; i++)
	{
		OrderItem* order_item = mOrderItemButtonList.at(i)->getOrderItem();
		discount = discount + order_item->getDiscountPrice();
	}

	return discount;
}

uint OrderItemWidget::getDiscountPercent()
{
	uint sub_total_price = getSubTotalPrice();
	uint discount_price = getDiscountPrice();

	if(discount_price != 0)
	{
		return (float)discount_price / sub_total_price * 100;
	}
	else
	{
		return 0;
	}
}

void OrderItemWidget::removeAll()
{
	while(!mOrderItemButtonList.isEmpty())
	{
		delete mOrderItemButtonList.at(0)->getOrderItem();
		delete mOrderItemButtonList.takeAt(0);
	}

	refreshButtonList();
	emit changeOrder();
}
