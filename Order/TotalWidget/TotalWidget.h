#ifndef TOTALWIDGET_H
#define TOTALWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "DataManager/OrderItem.h"
#include "StyleSheet.h"

class TotalWidget : public QWidget
{
		Q_OBJECT
	private:
		uint mSubTotalPrice;
		uint mDepositPrice;
		uint mDiscountPrice;
		uint mDiscountPercent;
		int mTotalPrice;

		QLabel *mLabelTotalInfo;
		QLabel	*mLabelTotalInfo_SubTotal_Text;
		QLabel	*mLabelTotalInfo_SubTotal;
		QLabel	*mLabelTotalInfo_Deposit_Text;
		QLabel	*mLabelTotalInfo_Deposit;
		QLabel	*mLabelTotalInfo_Discount_Text;
		QLabel	*mLabelTotalInfo_Discount;
		QLabel	*mLabelTotalInfo_Total;

		QPushButton *mButtonDeposit;
		QPushButton *mButtonDiscount;
		QPushButton *mButtonOrder;
		QPushButton *mButtonCancel;

	private:
		void refreshValue();
	public:
		TotalWidget(QWidget *parent = 0);
		void paintEvent(QPaintEvent *);
	signals:
		void clickDeposit();
		void clickDiscount();
		void clickOrder();
		void clickCancel();
	public slots:
		void setSubtotal(uint sub_total);
		void setDeposit(uint deposit);
		void setDiscount(uint discount_price, uint discount_percent);
		void setTotal(uint total_price);
};

#endif // TOTALWIDGET_H
