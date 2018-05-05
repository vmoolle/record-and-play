#include "recorder.h"

#include <QAudioRecorder>
#include <QUrl>

#include <QDebug>

Recorder::Recorder()
    : m_audioRecorder(new QAudioRecorder(this))
{
    QAudioEncoderSettings settings;
    settings.setCodec("audio/pcm");
    settings.setQuality(QMultimedia::HighQuality);

    m_audioRecorder->setAudioSettings(settings);

    connect(m_audioRecorder, &QAudioRecorder::statusChanged, this, [this](){
        auto status = m_audioRecorder->status();
        auto err    = m_audioRecorder->error();

        qDebug() << this << "Recorder() / m_audioRecorder / statusChanged(), status:" << status
                 << "error:" << err;

        if (err != QAudioRecorder::NoError) {
            emit error(m_audioRecorder->errorString());
        }
    });
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
    m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(target));
}

void Recorder::toggle()
{
    m_running = !m_running;
    qDebug() << this << "toggle(), running:" << m_running;

    if (m_running) {
        m_audioRecorder->record();
    } else {
        m_audioRecorder->stop();
    }
}

bool Recorder::running() const
{
    return m_running;
}
