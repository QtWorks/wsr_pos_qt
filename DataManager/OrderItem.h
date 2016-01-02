#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QObject>
#include "Item.h"

typedef enum
{
	DISCOUNT_TYPE_NONE,
	DISCOUNT_TYPE_PERCENT,
	DISCOUNT_TYPE_PRICE,
	DISCOUNT_TYPE_CUSTOM,
} DISCOUNT_TYPE;

class OrderItem : public QObject
{
	Q_OBJECT

private:
	Item *mItem;
	uint mAmount;
	uint mSubTotalPrice;
	DISCOUNT_TYPE mDiscountType;
	uint mDiscountPrice;
	uint mDiscountPercent;
	uint mEnuriPrice;
	uint mEnuriPercent;
	uint mTotalPrice;

	void recalculation();
public:
	OrderItem(Item *item = 0);
	Item* getItem();
	uint getAmount();
	void increaseItem(uint amount = 1);
	void decreaseItem(uint amount = 1);
	void increaseDiscountPercent(uint discount = 10);
	void decreaseDiscountPercent(uint discount = 10);
	void setDiscountPrice(uint price);
	void setDiscountPercent(uint discount = 10);
	void setEnuriPrice(uint price);
	uint getTotalPrice();
	uint getSubTotalPrice();
	uint getDiscountPercent();
	uint getDiscountPrice();
	uint getEnuriPrice();
	uint getEnuriPercent();

signals:
	void changed();
};

#endif // ORDERITEM_H
