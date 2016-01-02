#include "settingwidget.h"
#include <StyleSheet.h>
#define TOTAL_WIDTH		1280
#define TOTAL_HEIGHT	1024

SettingWidget::SettingWidget(QWidget *parent) :
	QWidget(parent)
{
	mDataManager = DataManager::getInstance();

	setGeometry(100, 100, TOTAL_WIDTH, TOTAL_HEIGHT);
	setConfigureWidget();
	setItemWidget();

	connect(mSettingConfigureWidget, SIGNAL(refresh()), this, SLOT(refresh()));
	connect(mSettingItemWidget, SIGNAL(itemSelected(Item*)), mSettingConfigureWidget, SLOT(loadItem(Item*)));
}

SettingWidget::~SettingWidget()
{

}

void SettingWidget::setConfigureWidget()
{
	mSettingConfigureWidget = new SettingConfigureItemWidget(this);
	mSettingConfigureWidget->setGeometry(0, 0, 1280, 600);

	mSettingConfigureWidget->show();
}

void SettingWidget::setItemWidget()
{
	mSettingItemWidget = new SettingItemWidget(this, mDataManager->getItemList());
	mSettingItemWidget->setGeometry(0, 400, 1280, 624);
	mSettingItemWidget->setStyleSheet(WIDGET_STYLE_SHEET_1(SHOPKEEP_ITEM, SHOPKEEP_ITEM_DARK));

	mSettingItemWidget->show();
}

void SettingWidget::refresh()
{
	mSettingItemWidget->refresh(mDataManager->getItemList());
}
