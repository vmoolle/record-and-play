#include "recordandplay.h"

RecordAndPlay::RecordAndPlay()
{

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
        setState(Recording);
    } else {
        setState(Idle);
    }
}

void RecordAndPlay::requestPlayingToggle()
{
    if (m_state != Playing) {
        setState(Playing);
    } else {
        setState(Idle);
    }
}

void RecordAndPlay::setState(RecordAndPlay::State state)
{
    bool wasRecording = recording();
    bool wasPlaying   = playing();

    if (m_state != state) {
        m_state = state;

        if (recording() != wasRecording)
            emit recordingChanged();
        if (playing() != wasPlaying)
            emit playingChanged();
    }
}
