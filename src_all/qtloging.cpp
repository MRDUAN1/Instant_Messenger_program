#include "qtloging.h"

qtloging::qtloging(QWidget *parent)
	: QWidget(parent)
{
	
	label = new QLabel(this);
	QPixmap pix("2.png");
	QSize rect = pix.size();
	QWidget *widget = new QWidget(this);
	widget->setGeometry(0, 0, this->width(), this->height() / 2);
	widget->setStyleSheet("background-color:rgb(232, 245, 252);");
	for (int i = 1; i <= 8; i++)
	{
		vector_pix.push_back(QPixmap(QString("%d").arg(i)));
	}
	
	this->setFixedSize(parent->size());
	
	QTimer *time;
	time = new QTimer;
	time->setInterval(500);
	time->start();
	connect(time, SIGNAL(timeout()), this, SLOT(timeout_handle()));
}

qtloging::~qtloging()
{

}
void qtloging::paintEvent(QPaintEvent *event)
{
	QBitmap bitmap(this->size());
	QPainter painter(&bitmap);
	painter.fillRect(bitmap.rect(), Qt::white);
	painter.setBrush(QColor(0, 0, 0));
	painter.setRenderHint(QPainter::Antialiasing);//平滑
	painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawRoundedRect(this->rect, 5, 5);
	this->setMask(bitmap);//可设置不同的形
}
void qtloging::timeout_handle()
{
	QPainter painter_1(this);
	if (i > 8) i = 0;
	i++;
	label->setFixedSize(rect.width(), rect.height());
	label->setPixmap(vector_pix[i]);
	label->setGeometry(this->width() / 2 - 5, this->height() / 2 + 20, label->width(), label->height());
	
	
}

