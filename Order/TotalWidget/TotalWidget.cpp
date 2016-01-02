#include "TotalWidget.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

TotalWidget::TotalWidget(QWidget *parent) : QWidget(parent), mSubTotalPrice(0), mDepositPrice(0), mDiscountPrice(0), mDiscountPercent(0), mTotalPrice(0)
{
	mLabelTotalInfo = new QLabel(this);
	mLabelTotalInfo_SubTotal_Text = new QLabel(mLabelTotalInfo);
	mLabelTotalInfo_SubTotal = new QLabel(mLabelTotalInfo);
	mLabelTotalInfo_Deposit_Text = new QLabel(mLabelTotalInfo);
	mLabelTotalInfo_Deposit = new QLabel(mLabelTotalInfo);
	mLabelTotalInfo_Discount_Text = new QLabel(mLabelTotalInfo);
	mLabelTotalInfo_Discount = new QLabel(mLabelTotalInfo);
	mLabelTotalInfo_Total = new QLabel(mLabelTotalInfo);
	mButtonDeposit = new QPushButton(this);
	mButtonDiscount = new QPushButton(this);
	mButtonOrder = new QPushButton(this);
	mButtonCancel = new QPushButton(this);

	mLabelTotalInfo->setGeometry(20, 25, 340, 230);
	mButtonDeposit->setText("선금");
	mButtonDeposit->setGeometry(20, 275, 160, 65);
	mButtonDiscount->setText("할인");
	mButtonDiscount->setGeometry(200, 275, 160, 65);
	mButtonOrder->setText("계산");
	mButtonOrder->setGeometry(20, 360, 160, 65);
	mButtonCancel->setText("취소");
	mButtonCancel->setGeometry(200, 360, 160, 65);

	mLabelTotalInfo_SubTotal_Text->setGeometry(40, 20, 100, 30);
	mLabelTotalInfo_SubTotal->setGeometry(140, 20, 160, 30);
	mLabelTotalInfo_Deposit_Text->setGeometry(40, 60, 100, 30);
	mLabelTotalInfo_Deposit->setGeometry(140, 60, 160, 30);
	mLabelTotalInfo_Discount_Text->setGeometry(40, 100, 100, 30);
	mLabelTotalInfo_Discount->setGeometry(140, 100, 160, 30);
	mLabelTotalInfo_Total->setGeometry(40, 140, 260, 70);

	mLabelTotalInfo->setStyleSheet(WIDGET_STYLE_SHEET_2(5, SHOPKEEP_TOTAL, SHOPKEEP_TOTAL_DARK));
	mButtonDeposit->setStyleSheet(PUSH_BUTTON_STYLE_SHEET_1(SHOPKEEP_DEPOSIT, SHOPKEEP_DEPOSIT_DARK));
	mButtonDiscount->setStyleSheet(PUSH_BUTTON_STYLE_SHEET_1(SHOPKEEP_DEPOSIT, SHOPKEEP_DEPOSIT_DARK));
	mButtonOrder->setStyleSheet(PUSH_BUTTON_STYLE_SHEET_1(SHOPKEEP_ORDER, SHOPKEEP_ORDER_DARK));
	mButtonCancel->setStyleSheet(PUSH_BUTTON_STYLE_SHEET_1(SHOPKEEP_DEPOSIT, SHOPKEEP_DEPOSIT_DARK));

	mLabelTotalInfo_SubTotal_Text->setText("합계");
	mLabelTotalInfo_SubTotal_Text->setStyleSheet("background-color: rgba(0,0,0,0%); color: #FFFFFF;");
	mLabelTotalInfo_SubTotal->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,0,0,0%); color: #FFFFFF;");
	mLabelTotalInfo_Deposit_Text->setText("선금");
	mLabelTotalInfo_Deposit_Text->setStyleSheet("background-color: rgba(0,0,0,0%); color: #FFFFFF;");
	mLabelTotalInfo_Deposit->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,0,0,0%); color: #FFFFFF;");
	mLabelTotalInfo_Discount_Text->setText("할인");
	mLabelTotalInfo_Discount_Text->setStyleSheet("background-color: rgba(0,0,0,0%); color: #FFFFFF;");
	mLabelTotalInfo_Discount->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,0,0,0%); color: #FFFFFF;");
	mLabelTotalInfo_Total->setStyleSheet("qproperty-alignment: 'AlignCenter | AlignRight'; background-color: rgba(0,0,0,0%); color: #FFFFFF;");

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(14);
	mButtonDeposit->setFont(font);
	mButtonDiscount->setFont(font);
	mButtonOrder->setFont(font);
	mButtonCancel->setFont(font);
	mLabelTotalInfo_SubTotal_Text->setFont(font);
	mLabelTotalInfo_SubTotal->setFont(font);
	mLabelTotalInfo_Deposit_Text->setFont(font);
	mLabelTotalInfo_Deposit->setFont(font);
	mLabelTotalInfo_Discount_Text->setFont(font);
	mLabelTotalInfo_Discount->setFont(font);

	QFont font2;
	font2.setFamily(QString("맑은 고딕"));
	font2.setPointSize(24);
	mLabelTotalInfo_Total->setFont(font2);

	connect(mButtonDeposit, SIGNAL(clicked()), this, SIGNAL(clickDeposit()));
	connect(mButtonDiscount, SIGNAL(clicked()), this, SIGNAL(clickDiscount()));
	connect(mButtonOrder, SIGNAL(clicked()), this, SIGNAL(clickOrder()));
	connect(mButtonCancel, SIGNAL(clicked()), this, SIGNAL(clickCancel()));
}

void TotalWidget::setSubtotal(unsigned int sub_total)
{
	mSubTotalPrice = sub_total;
	refreshValue();
}

void TotalWidget::setDeposit(unsigned int deposit)
{
	mDepositPrice = deposit;
	refreshValue();
}

void TotalWidget::setDiscount(unsigned int discount_price, unsigned int discount_percent)
{
	mDiscountPrice = discount_price;
	mDiscountPercent = discount_percent;
	refreshValue();
}

void TotalWidget::setTotal(unsigned int total_price)
{

	update();
}

void TotalWidget::refreshValue()
{
	mTotalPrice = mSubTotalPrice - mDepositPrice - mDiscountPrice;
	mLabelTotalInfo_SubTotal->setText(QLocale(QLocale::Korean).toString(mSubTotalPrice));
	mLabelTotalInfo_Deposit->setText(QLocale(QLocale::Korean).toString(mDepositPrice));
	mLabelTotalInfo_Discount->setText(QLocale(QLocale::Korean).toString(mDiscountPrice) + " (" + QString::number(mDiscountPercent) + "%)");
	mLabelTotalInfo_Total->setText(QLocale(QLocale::Korean).toString(mTotalPrice));
}

void TotalWidget::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
