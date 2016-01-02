#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QtWidgets>
#include "Item/SettingItemWidget.h"
#include "Configure/SettingConfigureItemWidget.h"
#include "../DataManager/DataManager.h"

class SettingWidget : public QWidget
{
	Q_OBJECT
private:
	DataManager* mDataManager;

public:
	explicit SettingWidget(QWidget *parent = 0);
	~SettingWidget();

private:
	SettingConfigureItemWidget *mSettingConfigureWidget;
	SettingItemWidget *mSettingItemWidget;

	void setConfigureWidget();
	void setItemWidget();

public slots:
	void refresh();

};

#endif // SETTINGWIDGET_H
