#include "OrderItem.h"

OrderItem::OrderItem(Item *item) : QObject(0)
{
	mItem = item;
	mAmount = 1;
	mSubTotalPrice = mItem->getPrice();
	mTotalPrice = mItem->getPrice();
	mDiscountPrice = 0;
	mDiscountPercent = 0;
	mEnuriPrice = 0;
	mEnuriPercent = 0;

	mDiscountType = DISCOUNT_TYPE_NONE;
}

Item* OrderItem::getItem()
{
	return mItem;
}

uint OrderItem::getAmount()
{
	return mAmount;
}

void OrderItem::increaseItem(uint amount)
{
	mAmount = mAmount + amount;
	recalculation();
}

void OrderItem::decreaseItem(uint amount)
{
	if(mAmount > 0)
	{
		mAmount = mAmount - amount;
	}

	recalculation();
}

void OrderItem::increaseDiscountPercent(uint discount)
{
	mDiscountPercent = mDiscountPercent + discount;

	if(mDiscountPercent > 100)
	{
		mDiscountPercent = 100;
	}

	recalculation();
}

void OrderItem::decreaseDiscountPercent(uint discount)
{
	if(mDiscountPercent <= discount)
	{
		mDiscountPercent = 0;
	}
	else
	{
		mDiscountPercent = mDiscountPercent - discount;
	}

	recalculation();
}

void OrderItem::setDiscountPrice(uint price)
{
	mDiscountType = DISCOUNT_TYPE_PRICE;
	mDiscountPrice = price;
	recalculation();
}

void OrderItem::setDiscountPercent(uint discount)
{
	mDiscountType = DISCOUNT_TYPE_PERCENT;

	if(discount > 100)
	{
		mDiscountPercent = 100;
	}
	else
	{
		mDiscountPercent = discount;
	}

	recalculation();
}

void OrderItem::setEnuriPrice(uint price)
{
	mEnuriPrice = price;
	recalculation();
}

uint OrderItem::getTotalPrice()
{
	return mTotalPrice;
}

uint OrderItem::getSubTotalPrice()
{
	return mSubTotalPrice;
}

uint OrderItem::getDiscountPercent()
{
	return mDiscountPercent;
}

uint OrderItem::getDiscountPrice()
{
	return mDiscountPrice;
}

uint OrderItem::getEnuriPrice()
{
	return mEnuriPrice;
}

uint OrderItem::getEnuriPercent()
{
	return mEnuriPercent;
}

void OrderItem::recalculation()
{
	mSubTotalPrice = mItem->getPrice() * mAmount;

	switch(mDiscountType)
	{
		case DISCOUNT_TYPE_PERCENT:
		{
			if(mDiscountPercent != 0)
			{
				mDiscountPrice = (float)mDiscountPercent * mSubTotalPrice / 100.0;
			}
			else
			{
				mDiscountPrice = 0;
			}

			break;
		}
		case DISCOUNT_TYPE_PRICE:
		{
			if(mDiscountPrice != 0)
			{
				mDiscountPercent = (float)mDiscountPrice / mSubTotalPrice * 100;
			}
			else
			{
				mDiscountPercent = 0;
			}

			break;
		}
		case DISCOUNT_TYPE_CUSTOM:
		{
			break;
		}
		default:
		{
			mDiscountPrice = 0;
			mDiscountPercent = 0;
			break;
		}
	}

	mEnuriPercent = (float)mEnuriPrice / mSubTotalPrice * 100;
	mTotalPrice = mSubTotalPrice - mDiscountPrice - mEnuriPrice;

	emit changed();
}
