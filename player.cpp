#include "player.h"

#include <QMediaPlayer>
#include <QDebug>

Player::Player()
    : m_mediaPlayer(new QMediaPlayer(this))
{
    connect(m_mediaPlayer, &QMediaPlayer::stateChanged, this, [this](){
        auto state = m_mediaPlayer->state();
        auto err   = m_mediaPlayer->error();

        qDebug() << this << "Player() / m_mediaPlayer / stateChanged(), state:" << state
                 << "error:" << err
                 << "m_running:" << m_running;

        if (m_running) {
            // note, how the error would not be reported from here if it is discovered
            // after the state changes (the docs do not seem to give any guarantees on the ordering
            // here, and errors are not treated in the special way -- except for logging --
            // in this application either)
            if (err != QMediaPlayer::NoError) {
                m_running = false;
                emit error(m_mediaPlayer->errorString());
            } else if (state == QMediaPlayer::StoppedState) {
                m_running = false;
                emit finished();
            }
        }
    });
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
    if (m_target == target)
        return;

    m_target = target;

    // see comment in Recorder::setTarget()
    // in case this piece of logic displays issues with apparently-empty URLs
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(target));
}

void Player::toggle()
{
    m_running = !m_running;

    if (m_running) {
        m_mediaPlayer->play();
    } else {
        m_mediaPlayer->stop();
    }
}

bool Player::running() const
{
    return m_running;
}

double Player::playbackRate() const
{
    return m_mediaPlayer->playbackRate();
}

void Player::setPlaybackRate(double rate)
{
    m_mediaPlayer->setPlaybackRate(rate);
}
