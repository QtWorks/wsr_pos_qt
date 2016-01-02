#ifndef ITEM_BUTTON_H
#define ITEM_BUTTON_H

#include <QPushButton>
#include <QLocale>
#include "DataManager/Item.h"

#define WIDTH	100
#define HEIGHT	100

#define LABEL_NAME_W	100
#define LABEL_NAME_H	30
#define LABEL_NAME_X	((WIDTH - LABEL_NAME_W) / 2)
#define LABEL_NAME_Y	(((WIDTH / 2 ) - LABEL_NAME_H) / 2)

#define LABEL_PRICE_W	LABEL_NAME_W
#define LABEL_PRICE_H	LABEL_NAME_H
#define LABEL_PRICE_X	LABEL_NAME_X
#define LABEL_PRICE_Y	LABEL_NAME_Y + LABEL_NAME_H

class ItemButton : public QPushButton
{
    Q_OBJECT

private:
	Item *mItem;

public:
	ItemButton(QWidget *parent = 0, Item *item = 0);
	~ItemButton();
protected slots:
	void onClicked();
signals:
	void clicked(Item* item);
};

#endif // ITEM_BUTTON_H
