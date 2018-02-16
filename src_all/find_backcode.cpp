#include "find_backcode.h"
#include "protobuf_client.h"
#include <qmessagebox.h>
extern protobuf_client *pro;
find_backcode::find_backcode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.label->setText("请输入要找回的账号");
	ui.label_2->setText("请输入你的密保问题");
	ui.label_3->setText("请输入你的密保答案");
	ui.pushButton->setText("确认");
	ui.pushButton_2->setText("取消");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_handle()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(cancle_handle()));
}
void find_backcode::ok_handle()
{
	QString id = ui.lineEdit->text();
	QString question = ui.lineEdit_2->text();
	QString answer = ui.lineEdit_3->text();
	if (id.isEmpty() || question.isEmpty() || answer.isEmpty())
	{
		QMessageBox::warning(this, "警告", "消息必须填写完整");
		return;
	}
	pro->find_passwd(id.toStdString(), question.toStdString(), answer.toStdString());
	return;
}
void find_backcode::cancle_handle()
{
	this->close();
}
find_backcode::~find_backcode()
{

}
