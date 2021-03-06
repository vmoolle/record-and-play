#ifndef RECORDER_H
#define RECORDER_H

#include "iaudio.h"

class QAudioRecorder;

class Recorder: public IAudio
{
    Q_OBJECT
public:
    Recorder();
    ~Recorder();

    QString target() const;
    void setTarget(const QString& target);

    void toggle();
    bool running() const;

private:
    void setupAudioRecorder();

    QAudioRecorder* m_audioRecorder;

    QString m_target;
    bool m_running = false;
};

#endif // RECORDER_H
