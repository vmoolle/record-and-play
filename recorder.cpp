#include "recorder.h"

#include <QDebug>

Recorder::Recorder()
{

}

Recorder::~Recorder()
{

}

QString Recorder::target() const
{
    return m_target;
}

void Recorder::setTarget(const QString& target)
{

}

void Recorder::toggle()
{
    m_running = !m_running;
    qDebug() << this << "toggle(), running:" << m_running;
}

bool Recorder::running() const
{
    return m_running;
}
