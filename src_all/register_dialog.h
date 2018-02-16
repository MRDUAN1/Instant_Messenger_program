#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qbitmap.h>
#include <qevent.h>
#include <qbytearray.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <memory>
#include <stdio.h>
#include "tool_widget.h"
#include "protobuf_client.h"
#include <fstream>

class register_dialog : public QWidget
{
	Q_OBJECT

public:
	register_dialog(QWidget *parent);
	~register_dialog();

private:
	QWidget *wid;
	protobuf_client *_protobuf;
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event); 
	void mouseMoveEvent(QMouseEvent *event);
	void create_widget();
	void set_widget_layout();
	void set_style_layout();
	void set_connect();
	void deal_message_image(string &image_name);
	tool_widget *toolwidge;
	protobuf_client *client;
	QLineEdit *lineedit_account, *lineeddit_passwd, *lineedit_passwdagaing, *line_telphone, *line_birthday;
	QTextEdit *text_mymaxim;
	QLabel *account, *passwd, *passwd_again, *telphone, *birthday, *mymaxim, *photo;
	QPushButton *ok, *cancel, *help;
	QLabel *chose_picture, *picture;
	QPushButton *file_dialog;
	QPoint windowPos, mousePos, dPos;
	QString string_account, string_passwd, string_passwdagaing, string_telphone, string_birthday, string_mymaxim;
	string str_image; //图片的内容
	string _filename; //图片的文件名字
	string _filename_all; //图片的绝对地址
	QHBoxLayout *hlayout;
public slots:
void ok_handle();
void cancel_handel();
void help_handel();
void file_dialog_signal();


};

#endif // REGISTER_DIALOG_H
