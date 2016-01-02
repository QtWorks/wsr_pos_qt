#ifndef PRINTER_H
#define PRINTER_H

#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QDateTime>

class printer : public QWidget
{
	Q_OBJECT
public:
	printer();
public slots:
	void print(QPrinter *printer);
};

#endif // PRINTER_H
