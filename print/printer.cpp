#include "printer.h"

printer::printer()
{
	QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
	printer.setPageSize(QPrinter::A4);
	printer.setOrientation(QPrinter::Portrait);
	printer.setPageMargins (15,15,15,15,QPrinter::Millimeter);
	printer.setFullPage(true);
	printer.setOutputFileName("output.pdf");
	//printer.setOutputFormat(QPrinter::PdfFormat); //you can use native format of system usin QPrinter::NativeFormat
	printer.setOutputFormat(QPrinter::NativeFormat);

	QPrintPreviewDialog preview(&printer, this);
	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(print(QPrinter *)));
	preview.exec();
}

void printer::print(QPrinter *printer)
{
	// print the page
	QPainter painter(printer);
	int w = printer->pageRect().width();
	int h = printer->pageRect().height();
	QRect page(0, 0, w, h);

	painter.setFont(QFont("Tahoma",8));
	painter.drawText(200,200,"Test");

	printer->newPage();
	QFont font = painter.font();
	font.setPixelSize((w+h)/100);
	painter.setFont(font);
	painter.drawText(page, Qt::AlignBottom | Qt::AlignRight,
					 QDateTime::currentDateTime().
					 toString(Qt::DefaultLocaleShortDate));

	page.adjust(w/20, h/20, -w/20, -h/20);
}
