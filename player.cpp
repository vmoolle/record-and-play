#include "player.h"

#include <QDebug>

Player::Player()
{

}

Player::~Player()
{

}

QString Player::target() const
{
    return m_target;
}

void Player::setTarget(const QString& target)
{

}

void Player::toggle()
{
    m_running = !m_running;
    qDebug() << this << "toggle(), running:" << m_running;
}

bool Player::running() const
{
    return m_running;
}

