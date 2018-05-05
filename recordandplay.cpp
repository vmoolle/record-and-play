#include "recordandplay.h"

#include <QCoreApplication>
#include <QDir>

#include <QDebug>

RecordAndPlay::RecordAndPlay(const QString& targetFileName, IAudio &recorder, IAudio &player)
    : m_recorder(recorder),
      m_player(player)
{
    Q_ASSERT(!m_recorder.running());
    Q_ASSERT(!m_player.running());

    connect(&m_recorder, &IAudio::finished, this, [this](){
        qDebug() << this << "RecordAndPlay() / m_recorder / finished()";
        toggleState(Idle, false);
    });
    connect(&m_recorder, &IAudio::error, this, [this](const QString& message){
        qDebug() << this << "RecordAndPlay() / m_recorder / error(), message:" << message;
        toggleState(Idle, false);
    });

    connect(&m_player, &IAudio::finished, this, [this](){
        qDebug() << this << "RecordAndPlay() / m_player / finished()";
        toggleState(Idle, false);
    });
    connect(&m_player, &IAudio::error, this, [this](const QString& message){
        qDebug() << this << "RecordAndPlay() / m_player / error(), message:" << message;
        toggleState(Idle, false);
    });

    QString target = QDir(QCoreApplication::applicationDirPath()).filePath(targetFileName);
    m_recorder.setTarget(target);
    m_player.setTarget(target);
}

RecordAndPlay::~RecordAndPlay()
{

}

bool RecordAndPlay::recording() const
{
    return m_state == Recording;
}

bool RecordAndPlay::playing() const
{
    return m_state == Playing;
}

void RecordAndPlay::requestRecordingToggle()
{
    if (m_state != Recording) {
        toggleState(Recording);
    } else {
        toggleState(Idle);
    }
}

void RecordAndPlay::requestPlayingToggle()
{
    if (m_state != Playing) {
        toggleState(Playing);
    } else {
        toggleState(Idle);
    }
}

void RecordAndPlay::toggleState(RecordAndPlay::State state, bool doToggle)
{
    bool wasRecording = recording();
    bool wasPlaying   = playing();

    if (m_state != state) {
        m_state = state;

        if (recording() != wasRecording) {
            if (doToggle) m_recorder.toggle();
            emit recordingChanged();
        }
        if (playing() != wasPlaying) {
            if (doToggle) m_player.toggle();
            emit playingChanged();
        }
    }
}
