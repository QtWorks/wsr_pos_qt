#include "Item.h"

Item::Item(uint category_id, uint id, QString name, QString hint, uint price, bool discount, bool print, bool print_together, uint position_x, uint position_y, uint color, QList<uint> sub_item_list)
	: mCategoryId(category_id), mId(id), mName(name), mHint(hint), mPrice(price), mDiscount(discount), mPrint(print), mPrintTogether(print_together), mPositionX(position_x), mPositionY(position_y), mColor(color), mSubItemList(sub_item_list)
{

}

Item::~Item()
{

}

CATEGORY_ID Item::getCategoryId()
{
	return mCategoryId;
}

ITEM_ID Item::getId()
{
	return mId;
}

QString Item::getName()
{
	return mName;
}

QString Item::getHint()
{
	return mHint;
}

unsigned int Item::getPrice()
{
	return mPrice;
}

bool Item::supportDiscountItem()
{
	return mDiscount;
}

bool Item::supportPrint()
{
	return mPrint;
}

bool Item::supportPrintTogether()
{
	return mPrintTogether;
}

uint Item::getPositionX()
{
	return mPositionX;
}

uint Item::getPositionY()
{
	return mPositionY;
}

uint Item::getColor()
{
	return mColor;
}

QList<ITEM_ID> Item::getSubItemList()
{
	return mSubItemList;
}

void Item::setCategoryId(CATEGORY_ID id)
{
	mId = id;
}

void Item::setName(QString name)
{
	mName = name;
}

void Item::setHint(QString hint)
{
	mHint = hint;
}

void Item::setPrice(unsigned int price)
{
	mPrice = price;
}

void Item::setSupportDiscountItem(bool discount)
{
	mDiscount = discount;
}

void Item::setSupportPrint(bool print)
{
	mPrint = print;
}

void Item::setSupportPrintTogether(bool print_together)
{
	mPrintTogether = print_together;
}

void Item::setPositionX(unsigned int x)
{
	mPositionX = x;
}

void Item::setPositionY(unsigned int y)
{
	mPositionY = y;
}

void Item::setColor(unsigned int color)
{
	mColor = color;
}

void Item::setSubItemList(QList<ITEM_ID> sub_item_list)
{
	mSubItemList = sub_item_list;
}
