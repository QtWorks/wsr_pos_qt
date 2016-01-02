#ifndef ORDERITEMWIDGET_H
#define ORDERITEMWIDGET_H

#include <QWidget>
#include "OrderItemButton.h"
#include "../DiscountPanel/TabButton.h"

class OrderItemWidget : public QWidget
{
		Q_OBJECT

	private:
		DISCOUNT_TYPE mDiscountType;
		uint mDiscountValue;
		QWidget *mParent;
		QList<OrderItem*> mOrderItemList;
		QList<OrderItemButton*> mOrderItemButtonList;

		void setDiscountPrice(uint price);
		void setDiscountPercent(uint percent);
	public:
		OrderItemWidget(QWidget* parent = 0);
		~OrderItemWidget();
		void paintEvent(QPaintEvent *);
		uint getTotalPrice();
		uint getTotalPercent();
		uint getSubTotalPrice();
		uint getDiscountPrice();
		uint getDiscountPercent();
		uint getEnuriPrice();
		uint getEnuriPercent();
		void removeAll();
	signals:
		void changeOrder();
	public slots:
		void setDiscount(TabButton::TYPE type, uint value);
		void addItem(Item* item);
		void setEnuriPrice(uint price);
		void onChangeOrderItem(OrderItemButton* order_item_button);
		void refreshButtonList();
};

#endif // ORDERITEMWIDGET_H
