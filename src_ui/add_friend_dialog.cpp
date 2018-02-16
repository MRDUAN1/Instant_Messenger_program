#include "add_friend_dialog.h"
#include "protobuf_client.h"
#include <qpushbutton.h>
#include <qfont.h>
#include <qmessagebox.h>
extern protobuf_client *pro;
extern networkn *net;
extern struct _my_information my_information;
extern map<string, friend_information*> friend_detail;
add_friend_dialog::add_friend_dialog(QWidget *parent)
	: QWidget(parent)
{
	this->setFixedSize(300, 200);
	
	this->setStyleSheet("background-color:rgb(232,252,232)");
	QFont font("Times", 12, QFont::Bold);
	ok = new QPushButton(this);
	ok->setStyleSheet("QPushButton{border: 2px solid #8f8f91;border-radius: 6px;background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,stop : 0 #f6f7fa, stop: 1 #dadbde);min-width: 80px;}\
					  					  					  QPushButton:pressed{background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,stop : 0 #dadbde, stop: 1 #f6f7fa);}\
															  QPushButton:flat{border: none;}\
															  QPushButton:default {	border-color: navy;	}");		
	ok->setText("发送");
	ok->setGeometry(20, 150, 90, 30);
	cancel = new QPushButton(this);
	cancel->setGeometry(180, 150, 90, 30);
	cancel->setText("取消");
	cancel->setStyleSheet("QPushButton{border: 2px solid #8f8f91;border-radius: 6px;background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,stop : 0 #f6f7fa, stop: 1 #dadbde);min-width: 80px;}\
						  					  					  					  QPushButton:pressed{background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,stop : 0 #dadbde, stop: 1 #f6f7fa);}\
																					  															  QPushButton:flat{border: none;}\
																																				  															  															  QPushButton:default {	border-color: navy;	}");
	line = new QTextEdit(this);
	line->setFont(font);
	line->setStyleSheet("QLineEdit {\
							border: 2px solid gray;\
								border - radius: 10px;\
								padding: 0 8px;\
								background: yellow;\
									selection - background - color: darkgray;\
									}");
	line->setGeometry(50, 10, 190, 20);
	textedit = new QTextEdit(this);
	
	textedit->setFont(font);

	textedit->setGeometry(50, 50, 190, 90);
	setconnect();
	this->show();
}

add_friend_dialog::~add_friend_dialog()
{

}
void add_friend_dialog::setconnect()
{
	connect(ok, SIGNAL(clicked()), this, SLOT(ok_handle()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(cancle_handle()));
}
void add_friend_dialog::ok_handle()
{
	if (!check_num_is_legal(line->toPlainText())) return;
	QString account = line->toPlainText();
	QString account_info = textedit->toPlainText();
	pro->query_add_friend(account, account_info);
	//net->write()	
}
void add_friend_dialog::cancle_handle()
{
	this->close();
}
int add_friend_dialog::check_num_is_legal(QString name)
{
	QByteArray ba = name.toLatin1();
	const char *s = ba.data();
	int num = 0;
	if (name.isEmpty())
	{
		QMessageBox::warning(this, "错误", "好友的账号不能为空");
		line->clear();
		return 0;
	}
	while (*s && *s >= '0'&& *s <= '9')
	{
		s++;
		num++;
	}
	if (*s)
	{
		QMessageBox::warning(this, "格式错误", "必需全为数字");
		line->clear();
		return 0;
	}
	if (num != 10)
	{
		QMessageBox::warning(this, "格式错误", "账号位数为10位");
		line->clear();
		return 0;
	}
	return 1;
}
void add_friend_dialog::paintEvent(QPaintEvent *event)
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
void add_friend_dialog::mousePressEvent(QMouseEvent *event)
{
	this->windowPos = this->pos();                // 获得部件当前位置
	this->mousePos = event->globalPos();     // 获得鼠标位置
	this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}

void add_friend_dialog::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - this->dPos);
}
