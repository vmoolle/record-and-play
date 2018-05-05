#include "recordandplay.h"

#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QUuid>

#include <QDebug>

const QString targetFileNamePrefix = "record-and-play";

RecordAndPlay::RecordAndPlay(IAudio &recorder, IAudio &player)
    : m_recorder(recorder),
      m_player(player)
{
    Q_ASSERT(!m_recorder.running());
    qDebug() << "*** m_player.running():" << m_player.running();
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
            if (doToggle) {
                if (recording()) {
                    setNewTargetFileName();
                    m_recorder.setTarget(m_targetFileName);
                }
                m_recorder.toggle();
            }
            emit recordingChanged();
        }
        if (playing() != wasPlaying) {
            if (doToggle) {
                if (playing()) {
                    m_player.setTarget(m_targetFileName);
                }
                m_player.toggle();
            }
            emit playingChanged();
        }
    }
}

void RecordAndPlay::setNewTargetFileName()
{
    QString targetFileName = QString("%1-%2-%3.wav").arg(targetFileNamePrefix)
            .arg(QDateTime::currentMSecsSinceEpoch())
            .arg(QUuid::createUuid().toString());

    m_targetFileName = QDir(QCoreApplication::applicationDirPath()).filePath(targetFileName);
    qDebug() << this << "setNewTargetFileName() -- switching to target:" << m_targetFileName;
}
