#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

class global : public QObject
{
	Q_OBJECT

public:
	global(QObject *parent);
	~global();

private:
	
};

#endif // GLOBAL_H
