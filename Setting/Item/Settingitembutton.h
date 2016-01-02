#ifndef SETTING_ITEM_BUTTON_H
#define SETTING_ITEM_BUTTON_H

#include <QPushButton>
#include <QLocale>
#include "DataManager/Item.h"

class SettingItemButton : public QPushButton
{
    Q_OBJECT

private:
	Item *mItem;

public:
    SettingItemButton(QWidget *parent = 0, Item *item = 0);
    ~SettingItemButton();
protected slots:
	void onClicked();
	void checkClicked(Item *item);
signals:
	void clicked(Item* item);
public slots:
	void refresh(Item *item);
};

#endif // SETTING_ITEM_BUTTON_H
