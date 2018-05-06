#include "recorder.h"

#include <QAudioRecorder>
#include <QFile>
#include <QUrl>
#include <QTimer>

#include <QDebug>

Recorder::Recorder()
    : m_audioRecorder(new QAudioRecorder(this))
{
    setupAudioRecorder();

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

void Recorder::setupAudioRecorder()
{
    auto inputs = m_audioRecorder->audioInputs();
    auto codecs = m_audioRecorder->supportedAudioCodecs();
    auto containers = m_audioRecorder->supportedContainers();
    auto sampleRates = m_audioRecorder->supportedAudioSampleRates();

    qDebug() << this << "setupAudioRecorder() -- inputs:\n" << inputs << "\n"
             << "codecs:\n" << codecs << "\n"
             << "containers:\n" << containers << "\n"
             << "sampleRates:\n" << sampleRates << "\n";

    QString input = inputs.value(0);
    QString codec = codecs.value(0);
    QString container = containers.value(0);
    int sampleRate = sampleRates.value(0);

    qDebug() << this << "setupAudioRecorder() -- input:" << input << "\n"
             << "codec:" << codec << "\n"
             << "container:" << container << "\n"
             << "sampleRate:" << sampleRate << "\n";

    QAudioEncoderSettings settings;
    settings.setCodec(codec);
    settings.setSampleRate(sampleRate);

    m_audioRecorder->setAudioInput(input);
    m_audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);

//    QAudioEncoderSettings settings;
//    // assuming this to be supported on all OSes no matter what
//    // ..would in fact be incorrect :)
//    // -- as capitalization (reportedly) matters (on Linux), see:
//    // https://forum.qt.io/topic/42541/recording-audio-using-qtaudiorecorder/3
//    settings.setCodec("audio/PCM");
//    settings.setQuality(QMultimedia::HighQuality);

//    m_audioRecorder->setAudioSettings(settings);
//    // not having this apparently gives people problems on Linux
//    // (see the link above)
//    m_audioRecorder->setContainerFormat("wav");
}
