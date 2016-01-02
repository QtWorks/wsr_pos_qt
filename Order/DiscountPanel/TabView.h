#ifndef TABVIEW_H
#define TABVIEW_H

#include "TabButton.h"

class TabView : public QWidget
{
		Q_OBJECT

	private:
		TabButton *mButtonPercent;
		TabButton *mButtonPrice;
		TabButton *mButtonCustom;

	public:
		TabView(QWidget* parent = 0);
		void setGeometry(int x, int y, int w, int h);
		void select(TabButton::TYPE tab_type);

	signals:
		void click(TabButton::TYPE tab_type);

	public slots:
		void onClick(TabButton::TYPE tab_type);
};

#endif // TABVIEW_H
