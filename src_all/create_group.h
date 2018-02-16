#ifndef CREATE_GROUP_H
#define CREATE_GROUP_H

#include <QWidget>
#include <qlineedit.h>
#include <qpushbutton.h>

class create_group : public QWidget
{
	Q_OBJECT

public:
	create_group(QWidget *parent);
	~create_group();

private:
	QLineEdit *edit;
	QPushButton *ok, *cancle;

	
};

#endif // CREATE_GROUP_H
