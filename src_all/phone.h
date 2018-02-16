#ifndef PHONE_H
#define PHONE_H

#include <QObject>

class phone : public QObject
{
	Q_OBJECT

public:
	phone(QObject *parent);
	~phone();

private:
	
};

#endif // PHONE_H
