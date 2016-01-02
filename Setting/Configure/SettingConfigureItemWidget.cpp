#include "SettingConfigureItemWidget.h"

#define LABEL_POSITION_X	20
#define LABEL_POSITION_Y	20
#define LABEL_POSITION_W	70
#define LABEL_POSITION_H	35

#define VERTICAL_GAP		10
#define LABEL_DATA_GAP		50

#define DATA_POSITION_X		LABEL_POSITION_X + LABEL_POSITION_W + LABEL_DATA_GAP
#define DATA_POSITION_Y		LABEL_POSITION_Y
#define DATA_POSITION_W		200
#define DATA_POSITION_H		LABEL_POSITION_H

SettingConfigureItemWidget::SettingConfigureItemWidget(QWidget *parent) : QWidget(parent)
{
	mDataManager = DataManager::getInstance();

	mLabelCategory.setParent(this);
	mLabelName.setParent(this);
	mLabelPrice.setParent(this);
	mLabelDiscount.setParent(this);
#if ENABLE_PRINT
	mLabelPrint.setParent(this);
	mLabelPrintTogether.setParent(this);
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mLabelColor.setParent(this);
	mLabelSubItemList.setParent(this);
#endif

	mDataCategory.setParent(this);
	mDataName.setParent(this);
	mDataPrice.setParent(this);
	mDataDiscount.setParent(this);
#if ENABLE_PRINT
	mDataPrint.setParent(this);
	mDataPrintTogether.setParent(this);
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mDataColor.setParent(this);
	mDataSubItemList.setParent(this);
#endif
	mUpdateButton.setParent(this);
	mDeleteButton.setParent(this);
	mCancelButton.setParent(this);

	mLabelCategory.setText("카테고리");
	mLabelName.setText("이름");
	mLabelPrice.setText("가격");
	mLabelDiscount.setText("할인");
#if ENABLE_PRINT
	mLabelPrint.setText("출력");
	mLabelPrintTogether.setText("모아찍기");
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mLabelColor.setText("버튼색상");
	mLabelSubItemList.setText("하위 상품");
#endif
	mUpdateButton.setText("수정");
	mDeleteButton.setText("삭제");
	mCancelButton.setText("취소");

	mLabelCategory.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 1) + (VERTICAL_GAP * 0), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataCategory.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 1) + (VERTICAL_GAP * 0), DATA_POSITION_W, DATA_POSITION_H);

	mLabelName.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 2) + (VERTICAL_GAP * 1), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataName.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 2) + (VERTICAL_GAP * 1), DATA_POSITION_W, DATA_POSITION_H);

	mLabelPrice.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 3) + (VERTICAL_GAP * 2), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataPrice.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 3) + (VERTICAL_GAP * 2), DATA_POSITION_W, DATA_POSITION_H);

	mLabelDiscount.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 4) + (VERTICAL_GAP * 3), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataDiscount.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 4) + (VERTICAL_GAP * 3), DATA_POSITION_W, DATA_POSITION_H);
#if ENABLE_PRINT
	mLabelPrint.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 5) + (VERTICAL_GAP * 4), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataPrint.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 5) + (VERTICAL_GAP * 4), DATA_POSITION_W, DATA_POSITION_H);

	mLabelPrintTogether.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 6) + (VERTICAL_GAP * 5), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataPrintTogether.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 6) + (VERTICAL_GAP * 5), DATA_POSITION_W, DATA_POSITION_H);
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mLabelColor.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 7) + (VERTICAL_GAP * 6), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataColor.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 7) + (VERTICAL_GAP * 6), DATA_POSITION_W, DATA_POSITION_H);

	mLabelSubItemList.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 8) + (VERTICAL_GAP * 7), LABEL_POSITION_W, LABEL_POSITION_H);
	mDataSubItemList.setGeometry(DATA_POSITION_X, (DATA_POSITION_H * 8) + (VERTICAL_GAP * 7), DATA_POSITION_W, DATA_POSITION_H);
#endif
	mUpdateButton.setGeometry(LABEL_POSITION_X, (LABEL_POSITION_H * 5) + (VERTICAL_GAP * 4), 100, 100);
	mDeleteButton.setGeometry(LABEL_POSITION_X + 160 + 20, (LABEL_POSITION_H * 5) + (VERTICAL_GAP * 4), 100, 100);
	mCancelButton.setGeometry(LABEL_POSITION_X + 160 + 20 + 160 + 20, (LABEL_POSITION_H * 5) + (VERTICAL_GAP * 4), 100, 100);

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(12);

	mLabelCategory.setFont(font);
	mLabelName.setFont(font);
	mLabelPrice.setFont(font);
	mLabelDiscount.setFont(font);
#if ENABLE_PRINT
	mLabelPrint.setFont(font);
	mLabelPrintTogether.setFont(font);
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mLabelColor.setFont(font);
	mLabelSubItemList.setFont(font);
#endif

	mDataCategory.setFont(font);
	mDataName.setFont(font);
	mDataPrice.setFont(font);
	mDataDiscount.setFont(font);
#if ENABLE_PRINT
	mDataPrint.setFont(font);
	mDataPrintTogether.setFont(font);
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mDataColor.setFont(font);
	mDataSubItemList.setFont(font);
#endif
	mUpdateButton.setFont(font);

	setCategory();
#if ENABLE_COLOR_SUB_CATEGORY
	setSubItem();
#endif

	connect(&mUpdateButton, SIGNAL(clicked()), this, SLOT(updateItem()));
	connect(&mDeleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
	connect(&mCancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

SettingConfigureItemWidget::~SettingConfigureItemWidget()
{

}

void SettingConfigureItemWidget::setCategory()
{
	mCategoryList = mDataManager->getCategoryList();

	for(int i = 0; i < mCategoryList.size() ; i++)
	{
		Category* category = mCategoryList.at(i);
		mDataCategory.addItem(category->getName());
	}
}
#if ENABLE_COLOR_SUB_CATEGORY
void SettingConfigureItemWidget::setColor()
{

}

void SettingConfigureItemWidget::setSubItem()
{

	QStandardItemModel* treeModel = mDataSubItemList.model();

	QList<Item*> item_list = mDataManager->getItemList();

	QStandardItem* standard_item = new QStandardItem("없음");
	treeModel->appendRow(standard_item);
	standard_item->setCheckable(true);

	for(int i = 0; i < item_list.size() ; i++)
	{
		Item* item = item_list.at(i);

		if(item->getSubItemList().size() == 0)
		{
			QStandardItem* standard_item = new QStandardItem(item->getName());
			treeModel->appendRow(standard_item);
			standard_item->setCheckable(true);
		}
	}

	mDataSubItemList.SetupCompleter();
}
#endif
void SettingConfigureItemWidget::loadItem(Item *item)
{
	mItem = item;

	for(int i = 0 ; i < mCategoryList.size() ; i++)
	{
		if(mItem->getCategoryId() == mCategoryList.at(i)->getId())
		{
			mDataCategory.setCurrentIndex(i);
		}
	}

	mDataName.setText(mItem->getName());
	mDataPrice.setText(QString::number(mItem->getPrice()));
	mDataDiscount.setChecked(mItem->supportDiscountItem());
#if ENABLE_PRINT
	mDataPrint.setChecked(mItem->supportPrint());
	mDataPrintTogether.setChecked(mItem->supportPrintTogether());
#endif
}

void SettingConfigureItemWidget::updateItem()
{
	if(mItem->getName() != mDataName.text()
			|| mItem->getPrice() != mDataPrice.text().toUInt()
			|| mItem->supportDiscountItem() != mDataDiscount.isChecked()
#if ENABLE_PRINT
			|| mItem->supportPrint() != mDataPrint.isChecked()
			|| mItem->supportPrintTogether() != mDataPrintTogether.isChecked()
#endif
		)
	{
		mItem->setName(mDataName.text());
		mItem->setPrice(mDataPrice.text().toUInt());
		mItem->setSupportDiscountItem(mDataDiscount.isChecked());

		mDataManager->insertItem(mItem);
	}

	resetData();
	emit refresh();
}

void SettingConfigureItemWidget::deleteItem()
{
	mDataManager->deleteItem(mItem);
	resetData();
	emit refresh();
}

void SettingConfigureItemWidget::cancel()
{
	resetData();
	emit refresh();
}


void SettingConfigureItemWidget::resetData()
{
	mDataCategory.setCurrentIndex(0);
	mDataName.setText("");
	mDataPrice.setText("");
	mDataDiscount.setChecked(false);
#if ENABLE_PRINT
	mDataPrint.setParent(this);
	mDataPrintTogether.setParent(this);
#endif
#if ENABLE_COLOR_SUB_CATEGORY
	mDataColor.setParent(this);
	mDataSubItemList.setParent(this);
#endif
}
