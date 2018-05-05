#ifndef PLAYER_H
#define PLAYER_H

#include "iaudio.h"

class QMediaPlayer;

class Player: public IAudio
{
    Q_OBJECT
public:
    Player();
    ~Player();

    QString target() const;
    void setTarget(const QString& target);

    void toggle();
    bool running() const;

    double playbackRate() const;
    void setPlaybackRate(double rate);

private:
    QMediaPlayer* m_mediaPlayer;

    QString m_target;
    bool m_running = false;
};

#endif // PLAYER_H
