#include "recorder.h"

#include <QAudioRecorder>
#include <QFile>
#include <QUrl>
#include <QTimer>

#include <QDebug>

Recorder::Recorder()
    : m_audioRecorder(new QAudioRecorder(this))
{
    QAudioEncoderSettings settings;
    // assuming this to be supported on all OSes no matter what
    settings.setCodec("audio/pcm");
    settings.setQuality(QMultimedia::HighQuality);

    m_audioRecorder->setAudioSettings(settings);
    // not having this apparently gives people problems on Linux, i.e.:
    // https://forum.qt.io/topic/42541/recording-audio-using-qtaudiorecorder/3
    m_audioRecorder->setContainerFormat("wav");

    connect(m_audioRecorder, &QAudioRecorder::statusChanged, this, [this](){
        auto status = m_audioRecorder->status();
        auto err    = m_audioRecorder->error();

        qDebug() << this << "Recorder() / m_audioRecorder / statusChanged(), status:" << status
                 << "error:" << err;

        if (m_running) {
            if (err != QAudioRecorder::NoError) {
                m_running = false;
                emit error(m_audioRecorder->errorString());
            }
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
    if (m_target == target)
        return;

    m_target = target;

    // Can't open output location

    // will be an empty URL at least on Windows right after being set
    //
    // quoting the (terrible :)) docs:
    //
    // The location can be relative or empty; in this case the recorder uses the system specific
    // place and file naming scheme. After recording has stated, QMediaRecorder::outputLocation()
    // returns the actual output location.
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
