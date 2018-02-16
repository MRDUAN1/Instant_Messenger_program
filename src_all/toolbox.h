#ifndef TOOLBOX_H
#define TOOLBOX_H
#include "widget_.h"
#include "protobuf_client.h"
#include <QToolBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QString>
#include <qdatetime.h>
#include <qtimer.h>
#include <string>
using namespace std;

class widget_;
class protobuf_client;
class toolbox : public QToolBox
{
public:
	toolbox(QWidget *parent = 0);
	void add_widget(QPixmap _pix, QString _text, string id_____, int palce, string isonline);
	enum{
		good_friend = 0,
		strange,
		balack

	};
	/*��j��ֵ�Ҳ�Ϊ0ʱ,ֻ���ƶ�,��j��ֵʱ��ɾ��*/
	void remove_widget(int i, QWidget *, int j = 0);
	void move_widget(int i, int j, QWidget *);
	//1Ϊ��¼0Ϊ�ǳ�
	void renovate_loin_exit(string id, int i);
	

private:
	protobuf_client *protobuf_cli;
	QGroupBox *my_friend;
	QGroupBox *stranger;
	QGroupBox *balacklist;
	QGroupBox *group_;
	QVBoxLayout *friend_layout;
	QVBoxLayout *stranger_layout;
	QVBoxLayout *balacklist_layout;
	QVBoxLayout *_group;
	

};

#endif // TOOLBOX_H
