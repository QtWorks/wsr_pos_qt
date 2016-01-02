#ifndef SETTINGCONFIGUREITEMWIDGET_H
#define SETTINGCONFIGUREITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include "../../DataManager/DataManager.h"
#include "TreeComboBox.h"
#include "ConfigureButton.h"
#include <QStandardItem>

#define ENABLE_PRINT				0
#define ENABLE_COLOR_SUB_CATEGORY	0

class SettingConfigureItemWidget : public QWidget
{
	Q_OBJECT

private:
	QLabel	mLabelCategory;
	QLabel  mLabelName;
	QLabel  mLabelPrice;
	QLabel  mLabelDiscount;
#if ENABLE_PRINT
	QLabel  mLabelPrint;
	QLabel  mLabelPrintTogether;
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	QLabel  mLabelColor;
	QLabel  mLabelSubItemList;
#endif

	QComboBox	mDataCategory;
	QLineEdit	mDataName;
	QLabel		mDataPrice;
	QCheckBox	mDataDiscount;
#if ENABLE_PRINT
	QCheckBox	mDataPrint;
	QCheckBox	mDataPrintTogether;
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	QComboBox	mDataColor;
	StandardTreeComboBox	mDataSubItemList;
#endif

	ConfigureButton	mUpdateButton;
	ConfigureButton	mDeleteButton;
	ConfigureButton	mCancelButton;

	DataManager *mDataManager;
	QStandardItemModel *mItemModel;

	QList<Category*>	mCategoryList;
	QList<Item*>		mItemList;

	Item		*mItem;

	void resetData();

public:
	SettingConfigureItemWidget(QWidget *parent);
	~SettingConfigureItemWidget();

	void setCategory();
#if ENABLE_COLOR_SUB_CATEGORY
	void setColor();
	void setSubItem();
#endif

signals:
	void refresh();

public slots:
	void loadItem(Item *item);
	void updateItem();
	void deleteItem();
	void cancel();
};

#endif // SETTINGCONFIGUREITEMWIDGET_H
