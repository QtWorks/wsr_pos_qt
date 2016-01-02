#ifndef ITEM_H
#define ITEM_H

#include <QList>
#include <QtSql/QtSql>
#include "Category.h"

typedef unsigned int ITEM_ID;

class Item
{
private:
    CATEGORY_ID mCategoryId;
    ITEM_ID mId;
	QString mName;
	QString mHint;
    unsigned int mPrice;
	bool mDiscount;
	bool mPrint;
	bool mPrintTogether;
    unsigned int mPositionX;
    unsigned int mPositionY;
    unsigned int mColor;
	QList<ITEM_ID> mSubItemList;

public:
	explicit Item(CATEGORY_ID category_id = 0, ITEM_ID id = 0, QString name = QString(), QString hint = QString(), unsigned int price = 0, bool discount = true, bool print = true, bool print_together = false, uint position_x = 0, uint position_y = 0, uint color = 0, QList<ITEM_ID> sub_item_list = QList<ITEM_ID>());
	~Item();

    CATEGORY_ID getCategoryId();
    ITEM_ID getId();
	QString getName();
	QString getHint();
    unsigned int getPrice();
	bool supportDiscountItem();
	bool supportPrint();
	bool supportPrintTogether();
    unsigned int getPositionX();
    unsigned int getPositionY();
    unsigned int getColor();
    QList<ITEM_ID> getSubItemList();

	void setCategoryId(CATEGORY_ID id);
	void setName(QString name);
	void setHint(QString hint);
	void setPrice(unsigned int price);
	void setSupportDiscountItem(bool discount);
	void setSupportPrint(bool print);
	void setSupportPrintTogether(bool print_together);
	void setPositionX(unsigned int x);
	void setPositionY(unsigned int y);
	void setColor(unsigned int color);
	void setSubItemList(QList<ITEM_ID> sub_item_list);
};

#endif // ITEM_H
