#ifndef RECORDANDPLAY_H
#define RECORDANDPLAY_H

#include <QObject>

class RecordAndPlay: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool recording READ recording NOTIFY recordingChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)

signals:
    void recordingChanged();
    void playingChanged();

public:
    RecordAndPlay();
    ~RecordAndPlay();

    bool recording() const;
    bool playing() const;

    Q_INVOKABLE void requestRecordingToggle();
    Q_INVOKABLE void requestPlayingToggle();

private:
    enum State { Recording, Playing, Idle };

    void setState(State state);

    State m_state = Idle;
};

#endif // RECORDANDPLAY_H
