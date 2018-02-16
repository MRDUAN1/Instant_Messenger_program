#include "detailfriendss.h"
#include "tool_widget.h"
extern struct _my_information my_information;
extern map<string, friend_information*> friend_detail;
detailfriendss::detailfriendss(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	tool_widget *tool_hp = new tool_widget(this);
	tool_hp->setGeometry(this->width() - tool_hp->width(), 0, tool_hp->width(), tool_hp->height());
	
}

detailfriendss::~detailfriendss()
{

}
int detailfriendss::change_(QString name, QString telephone_, QString birthday_, QString mymaxim_, string picture, QString account__, QString image_name)
{
	ui.label_6->setText(name);
	ui.label_7->setText(account__);
	ui.label_8->setText(birthday_);
	ui.label_9->setText(telephone_);
	ui.label_10->setText(mymaxim_);
	ui.label_12->setText(name);
	ui.label_13->setText(account__);
	QFont ft;
	ft.setPointSize(15);
	ui.label_12->setFont(ft);
	return 1;

}
void detailfriendss::paintEvent(QPaintEvent *event)
{
	QBitmap bitmap(this->size());
	QPainter painter(&bitmap);
	painter.fillRect(bitmap.rect(), Qt::white);
	painter.setBrush(QColor(0, 0, 0));
	painter.setRenderHint(QPainter::Antialiasing);//平滑
	painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawRoundedRect(this->rect(), 10, 10);
	this->setMask(bitmap);//可设置不同的形


}
void detailfriendss::mousePressEvent(QMouseEvent *event)
{
	this->windowPos = this->pos();                // 获得部件当前位置
	this->mousePos = event->globalPos();     // 获得鼠标位置
	this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}

void detailfriendss::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - this->dPos);
}
