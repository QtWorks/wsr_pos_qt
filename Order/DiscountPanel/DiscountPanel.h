#ifndef DISCOUNTPANEL_H
#define DISCOUNTPANEL_H

#include <QDialog>
#include <QLabel>
#include "NumPad.h"
#include "TabView.h"

class DiscountPanel : public QDialog
{
		Q_OBJECT
	public:
		typedef enum
		{
			DISCOUNT,
			DEPOSIT,
			ENURI,
		} TYPE;

	private:
		TYPE mType;
		TabButton::TYPE mTabType;

		uint mValue;

		QLabel *mLabelTitle;
		TabView *mTabView;
		QLabel *mLabelValue;
		NumPad *mNumPad;

	public:
		DiscountPanel(QWidget *parent = 0, TYPE type = DISCOUNT);
	private:
		void setStyle();
	signals:
		void discount(uint value);
		void discount(TabButton::TYPE type, uint value);
	public slots:
		void onTabTypeChanged(TabButton::TYPE type);
		void onNumButtonPressed(NUM_BUTTON num_button);
};

#endif // DISCOUNTPANEL_H
