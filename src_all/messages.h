#ifndef MESSAGES_H
#define MESSAGES_H
#include "qmainstackwidget.h"
#include "widget_.h"
#include <string>
using namespace std;
#include <QWidget>
#include <qgroupbox.h>
#include <qboxlayout.h>
class qmainstackwidget;
class widget_;
static map<string, widget_*>message_come;
class messages : public QWidget
{
	Q_OBJECT

public:
	messages(QWidget *parent);
	void handle_group_message(string time____ ,widget_ *wi, string name_, int type, string sender, string text, string imag, string image_name, string group_name);
	//void message_come(string sender, string text, string time);
	void message_text_image_com(string sender);
	//�˴�����������Ҫ������ΪĬ��¼������wav��ʽ��ֻ��Ҫ�ں���ӡ�wav����
	
	~messages();

private:
	bool isexitinwidgetofmessage(string sender);
	void insert_widget_handle(int type, string sender);
	QVBoxLayout *friend_layout;
	QGroupBox *groupbox;
	
};

#endif // MESSAGES_H
