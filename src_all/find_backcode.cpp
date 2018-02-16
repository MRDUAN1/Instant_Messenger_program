#include "find_backcode.h"
#include "protobuf_client.h"
#include <qmessagebox.h>
extern protobuf_client *pro;
find_backcode::find_backcode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.label->setText("������Ҫ�һص��˺�");
	ui.label_2->setText("����������ܱ�����");
	ui.label_3->setText("����������ܱ���");
	ui.pushButton->setText("ȷ��");
	ui.pushButton_2->setText("ȡ��");
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
		QMessageBox::warning(this, "����", "��Ϣ������д����");
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
