#ifndef IAUDIO_H
#define IAUDIO_H

#include <QObject>

class IAudio: public QObject
{
    Q_OBJECT
signals:
    void finished();
    void error(QString message);

public:
    virtual QString target() const =0;
    virtual void setTarget(const QString& target) =0;

    virtual void toggle() =0;
    virtual bool running() const =0;
};

#endif // IAUDIO_H
