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
		ui.label->setText("�������ܱ�����");
		ui.label_2->setText("�������");
		this->setWindowTitle("�����ܱ�");
	}
	else
	{
		ui.label->setText("������ԭ����");
		ui.label_2->setText("������������");
		this->setWindowTitle("�ı�����");
	}
	ui.pushButton->setText("ȷ��");
	ui.pushButton_2->setText("ȡ��");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_handle()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(cancle_handle()));
}
void change_passwd_dialog::ok_handle()
{
	QString old = ui.lineEdit->text();
	QString ne = ui.lineEdit_2->text();
	
	if (old.isEmpty() || ne.isEmpty())
	{
		QMessageBox::warning(this, "����", "��Ϣ������д����");
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
