#include "change_passwd_dialog.h"
#include "protobuf_client.h"
#include <qmessagebox.h>
extern protobuf_client *pro;
change_passwd_dialog::change_passwd_dialog(QWidget *parent, bool is_protect_)
	: QWidget(parent)
{
	is_protect = is_protect_;
	ui.setupUi(this);
	if (is_protect)
	{
		ui.label->setText("请输入密保问题");
		ui.label_2->setText("请输入答案");
		this->setWindowTitle("设置密保");
	}
	else
	{
		ui.label->setText("请输入原密码");
		ui.label_2->setText("请输入新密码");
		this->setWindowTitle("改变密码");
	}
	ui.pushButton->setText("确认");
	ui.pushButton_2->setText("取消");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_handle()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(cancle_handle()));
}
void change_passwd_dialog::ok_handle()
{
	QString old = ui.lineEdit->text();
	QString ne = ui.lineEdit_2->text();
	
	if (old.isEmpty() || ne.isEmpty())
	{
		QMessageBox::warning(this, "警告", "消息必须填写完整");
		return;
	}
	if (!is_protect)
		pro->change_passwd_name(old.toStdString(), ne.toStdString());
	else
		pro->change_passwd_name(old.toStdString(), ne.toStdString(), true);
	this->close();
	return;

}
void change_passwd_dialog::cancle_handle()
{
	this->close();
}

change_passwd_dialog::~change_passwd_dialog()
{

}
