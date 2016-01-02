#ifndef TABVIEWBUTTON_H
#define TABVIEWBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "StyleSheet.h"

class TabButton : public QPushButton
{
		Q_OBJECT
	public:
		typedef enum
		{
			PRICE,
			PERCENT,
			CUSTOM,
		} TYPE;

	private:
		TYPE mType;
		QLabel *mLabelText;
		QLabel *mLabelSelection;

	public:
		TabButton(QWidget *parent = 0, QString name="", TYPE type=PERCENT);
		void setNormal();
		void setSelect();
		void setGeometry(int x, int y, int w, int h);

	signals:
		void click(TabButton::TYPE type);

	private slots:
		void onClick();
};

#endif // TABVIEWBUTTON_H
