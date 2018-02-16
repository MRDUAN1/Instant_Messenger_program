
#include "register_dialog.h"
#include <QByteArray>
#include <qboxlayout.h>
extern protobuf_client *protobuf_;
extern map<string, friend_information*> friend_detail;
extern struct _my_information my_information;
register_dialog::register_dialog(QWidget *parent)
	: QWidget()
{
	wid = parent;
	hlayout = new QHBoxLayout(this);
	
	this->setFixedSize(400, 190);
	toolwidge = new tool_widget(this);
	toolwidge->move(this->width() - toolwidge->width(), 0);
	create_widget();
	set_widget_layout();
	set_style_layout();
	set_connect();
	this->show();
	
}

register_dialog::~register_dialog()
{
	
	wid->show();
}
void register_dialog::paintEvent(QPaintEvent *event)
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
void register_dialog::create_widget()
{
	line_telphone = new QLineEdit(this);
	telphone = new QLabel(this);
	telphone->setText("请输入电话号码");
	telphone->hide();
	birthday = new QLabel(this);
	birthday->setText("你的生日");
	mymaxim = new QLabel(this);
	mymaxim->setText("你的格言");
	
	text_mymaxim = new QTextEdit(this);
	lineedit_account = new QLineEdit(this);
	line_birthday = new QLineEdit(this);
	line_birthday->hide();
	line_birthday->setStyleSheet("QLineEdit{border:1px solid gray;border-radius:5px;padding: 0 8px;selection-background-color:darkgray;}");
	
	lineeddit_passwd = new QLineEdit(this);
	lineedit_passwdagaing = new QLineEdit(this);
	
	QFont font;
	
	account = new QLabel(this); 
	account->setText("请输入你的名字");
	passwd = new QLabel(this);
	passwd->setText("请输入密码");
	passwd_again = new QLabel(this);
	passwd_again->setText("请再次核对密码");
	
	ok = new QPushButton(this);
	ok->setText("确定");
	cancel = new QPushButton(this);
	cancel->setText("取消");
	help = new QPushButton(this);
	help->setText("详细信息填写");
	chose_picture = new QLabel;
	chose_picture->setText("请选择图片");
	picture = new QLabel(this);
	
	file_dialog = new QPushButton(this);
	file_dialog->setText("选择图片");

	
}
void register_dialog::set_widget_layout()
{
	account->setGeometry(10, 30, 110, 15);
	lineedit_account->setGeometry(130, 30, 150, 25);
	passwd->setGeometry(10, 70, 110, 15);
	lineeddit_passwd->setGeometry(130, 70, 150, 25);
	passwd_again->setGeometry(10, 110, 110, 15);
	lineedit_passwdagaing->setGeometry(130, 110, 150, 25);
	help->move(10, 150);
	ok->move(150, 150);
	cancel->move(300, 150);
	chose_picture->setGeometry(250, 30, 110, 15);
	picture->setGeometry(290, 17, 100, 100);
	file_dialog->move(300, 110);
	
	line_telphone->setStyleSheet("QLineEdit{border:1px solid gray;border-radius:5px;padding: 0 8px;selection-background-color:darkgray;}");
	line_telphone->setGeometry(130, 200, 150, 25);
	line_telphone->hide();
	mymaxim->setGeometry(10, 229, 110, 15);
	text_mymaxim->setGeometry(20, 245, 300, 80);
	text_mymaxim->setFont(QFont("Times", 10, QFont::Black));

	text_mymaxim->setStyleSheet("QLineEdit{border:1px solid gray;border-radius:5px;padding: 0 8px;selection-background-color:darkgray;}");
	
	
	birthday->setGeometry(10, 150, 110, 15);
	birthday->hide();
	line_birthday->hide();
	line_birthday->setGeometry(130, 150, 150, 25); //原来是190

	
	
}
void register_dialog::set_style_layout()
{
	lineedit_passwdagaing->setStyleSheet("QLineEdit{border:1px solid gray;border-radius:5px;padding: 0 8px;selection-background-color:darkgray;}");
	lineedit_account->setStyleSheet("QLineEdit{border:1px solid gray;border-radius:5px;padding: 0 8px;selection-background-color:darkgray;}");
	lineeddit_passwd->setStyleSheet("QLineEdit{border:1px solid gray;border-radius:5px;padding: 0 8px;selection-background-color:darkgray;}");
	
	

}
void register_dialog::set_connect()
{
	connect(ok, SIGNAL(clicked()), this, SLOT(ok_handle()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(cancel_handel()));
	connect(help, SIGNAL(clicked()), this, SLOT(help_handel()));
	connect(file_dialog, SIGNAL(clicked()), this, SLOT(file_dialog_signal()));
	
}
void register_dialog::ok_handle()
{
	
	
	//_protobuf = new protobuf_client;
	string_account = lineedit_account->text();
	string_passwd = lineeddit_passwd->text();
	string_birthday = line_birthday->text();
	string_passwdagaing = lineedit_passwdagaing->text();
	string_telphone = line_telphone->text();
	string_mymaxim = text_mymaxim->toPlainText();
	if (string_account.isEmpty() && string_passwd.isEmpty() && string_passwdagaing.isEmpty())
	{
		QMessageBox::warning(this, "出错", "必填内容没有填完");
		return;
	}
	if (string_passwd != string_passwdagaing)
	{
		QMessageBox::warning(this, "出错", "密码不一致");
		return;
	}
	string string_image_name;
	if (_filename.empty())
	{
		str_image = "0";
		string_image_name = "0";
		protobuf_->make_register_message(string_account, string_passwd, string_telphone, string_birthday, string_mymaxim, str_image, string_image_name);
		return ;
	}
	
	deal_message_image(string_image_name);
	protobuf_->make_register_message(string_account, string_passwd, string_telphone, string_birthday, string_mymaxim, str_image, string_image_name);



}
void register_dialog::deal_message_image(string &image_name)
{
	FILE *file;
	char buf[1024] = { '\0' };
	//此处出现错误原因是mm只代表第一个数据char
	const char *mm = _filename.data();
	//_filename.data()
	QFileInfo in;
	in = QFileInfo(mm);
	//name_e代表文件名
	QString	nam_e = in.fileName();
	image_name = nam_e.toStdString();
	if ((file = fopen(_filename.data(), "rb+")) == NULL)
	{
		perror("file open");
		QMessageBox::warning(this, "打开文件失败", "图片文件不能正常打开");
		return;
	}

	while (!feof(file))
	{
		int len_ = fread(buf, 1, 1024, file);
		str_image.append(buf, 1024);
		memset(buf, '\0', 1024);
	}

}
void register_dialog::cancel_handel()
{
	this->close();
}
void register_dialog::help_handel()
{
	this->setFixedSize(400, 360); 
	telphone->setGeometry(10, 190, 110, 15);
	line_telphone->show();
	birthday->show();
	line_birthday->show();
	telphone->show();
	ok->move(150, 330);
	help->move(10, 330);
	cancel->move(300, 330);
	
}
void register_dialog::file_dialog_signal()
{
	

	str_image.clear();
	char buf[1024] = { '\0' };
	QString file_full, file_name;
	QString slcStr;
	QString fileName;
	fileName = QFileDialog::getOpenFileName(this,
		tr("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)"));
	if (slcStr.left(3) == "JPG")
	{
		if (fileName.right(4).toLower() != ".jpg")
		{
			fileName += ".jpg";
		}
	}
	if (slcStr.left(3) == "PNG")
	{
		if (fileName.right(4).toLower() != ".png")
		{
			fileName += ".png";
		}
	}
	if (slcStr.left(3) == "BMP")
	{
		if (fileName.right(4).toLower() != ".bmp")
		{
			fileName += ".bmp";
		}
	}
	_filename = fileName.toStdString();
	QPixmap pix;
	pix.load(fileName);
	pix = pix.scaled(100, 80, Qt::KeepAspectRatioByExpanding);
	picture->setPixmap(pix);
	
}
void register_dialog::mousePressEvent(QMouseEvent *event)
{
	this->windowPos = this->pos();                // 获得部件当前位置
	this->mousePos = event->globalPos();     // 获得鼠标位置
	this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}

void register_dialog::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - this->dPos);
}