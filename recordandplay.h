#ifndef RECORDANDPLAY_H
#define RECORDANDPLAY_H

#include <QObject>

#include "iaudio.h"

class RecordAndPlay: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool recording READ recording NOTIFY recordingChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)

signals:
    void recordingChanged();
    void playingChanged();

public:
    RecordAndPlay(IAudio& recorder, IAudio& player);
    ~RecordAndPlay();

    bool recording() const;
    bool playing() const;

    Q_INVOKABLE void requestRecordingToggle();
    Q_INVOKABLE void requestPlayingToggle();

private:
    enum State { Recording, Playing, Idle };

    void toggleState(State state, bool doToggle=true);
    void setNewTargetFileName();

    IAudio& m_recorder;
    IAudio& m_player;

    State m_state = Idle;
    QString m_targetFileName;
};

#endif // RECORDANDPLAY_H
