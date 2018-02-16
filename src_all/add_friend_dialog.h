#ifndef ADD_FRIEND_DIALOG_H
#define ADD_FRIEND_DIALOG_H

#include <QWidget>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qevent.h>
#include <qpainter.h>

# pragma execution_character_set("utf-8")
class add_friend_dialog : public QWidget
{
	Q_OBJECT

public:
	add_friend_dialog(QWidget *parent = 0);
	~add_friend_dialog();
	public slots:
	void ok_handle();
	void cancle_handle();
protected:



private:
	void setconnect();
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	int check_num_is_legal(QString name);
	QPushButton *ok, *cancel;
	QTextEdit *line;
	QTextEdit *textedit;
	QString number, input;
	QPoint windowPos, mousePos, dPos;
	QPushButton *chat_record_button;
	
};

#endif // ADD_FRIEND_DIALOG_H
