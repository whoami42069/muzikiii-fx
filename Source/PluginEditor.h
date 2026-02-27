#pragma once

#include "PluginProcessor.h"
#include "UI/EffectChainEditor.h"
#include "UI/CustomLookAndFeel.h"

namespace muzikiii {

class MuzikiiiFXEditor : public juce::AudioProcessorEditor
{
public:
    explicit MuzikiiiFXEditor(MuzikiiiFXProcessor& processor);
    ~MuzikiiiFXEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MuzikiiiFXProcessor& audioProcessor;
    CustomLookAndFeel customLookAndFeel;
    EffectChainEditor chainEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MuzikiiiFXEditor)
};

} // namespace muzikiii
