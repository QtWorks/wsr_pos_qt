#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include "ItemButton.h"
#include "DataManager/DataManager.h"

#define ITEM_BUTTON_WIDTH		100
#define ITEM_BUTTON_HEIGHT		100

#define PADDING_HORIZONTAL      30
#define PADDING_VERTICAL        30

#define ITEM_GAP_HORIZONTAL		20
#define ITEM_GAP_VERTICAL		10

#define ROW                     10
#define COL                     5

class ItemWidget : public QWidget
{
	Q_OBJECT

private:
	QWidget *mParent;
	QList<Item*> mItemList;
	QList<ItemButton*> *mItemButtonList;

public:
	ItemWidget(QWidget* parent = 0, QList<Item*> item_list = QList<Item*>());
	~ItemWidget();
    void setGeometry(int x, int y, int w, int h);
	void paintEvent(QPaintEvent *);
signals:
	void itemSelected(Item *item);
};

#endif // ITEMWIDGET_H
