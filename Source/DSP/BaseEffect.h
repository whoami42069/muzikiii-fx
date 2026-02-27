#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace muzikiii {

class BaseEffect
{
public:
    virtual ~BaseEffect() = default;

    virtual void prepare(const juce::dsp::ProcessSpec& spec) = 0;
    virtual void process(juce::dsp::AudioBlock<float>& block) = 0;
    virtual void reset() = 0;
    virtual void updateParameters() = 0;

    void setEnabled(bool shouldBeEnabled) { enabled = shouldBeEnabled; }
    bool isEnabled() const { return enabled; }

protected:
    bool enabled = false;
};

} // namespace muzikiii
