#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace muzikiii {

class EffectSlot : public juce::Component
{
public:
    EffectSlot(const juce::String& effectName,
               juce::AudioProcessorValueTreeState& apvts,
               const juce::String& enabledParamId,
               const juce::StringArray& paramIds,
               const juce::StringArray& paramLabels);

    ~EffectSlot() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::String name;

    juce::ToggleButton enableToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enableAttachment;

    struct ParamControl
    {
        std::unique_ptr<juce::Slider> slider;
        std::unique_ptr<juce::Label> label;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    };

    std::vector<ParamControl> paramControls;
};

} // namespace muzikiii
