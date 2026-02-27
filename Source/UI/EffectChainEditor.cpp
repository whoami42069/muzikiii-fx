#include "EffectChainEditor.h"
#include "../Parameters/ParameterLayout.h"
#include "CustomLookAndFeel.h"

namespace muzikiii {

EffectChainEditor::EffectChainEditor(juce::AudioProcessorValueTreeState& apvts)
{
    // Reverb
    reverbSlot = std::make_unique<EffectSlot>(
        "Reverb", apvts, ParamIDs::reverbEnabled,
        juce::StringArray { ParamIDs::reverbDecay, ParamIDs::reverbPreDelay, ParamIDs::reverbWet },
        juce::StringArray { "Decay", "Pre-Delay", "Mix" });
    addAndMakeVisible(*reverbSlot);

    // Delay
    delaySlot = std::make_unique<EffectSlot>(
        "Delay", apvts, ParamIDs::delayEnabled,
        juce::StringArray { ParamIDs::delayTime, ParamIDs::delayFeedback, ParamIDs::delayWet },
        juce::StringArray { "Time", "Feedback", "Mix" });
    addAndMakeVisible(*delaySlot);

    // EQ
    eqSlot = std::make_unique<EffectSlot>(
        "EQ", apvts, ParamIDs::eqEnabled,
        juce::StringArray { ParamIDs::eqLow, ParamIDs::eqMid, ParamIDs::eqHigh,
                            ParamIDs::eqLowFrequency, ParamIDs::eqHighFrequency },
        juce::StringArray { "Low", "Mid", "High", "Low Freq", "High Freq" });
    addAndMakeVisible(*eqSlot);

    // Distortion
    distortionSlot = std::make_unique<EffectSlot>(
        "Distortion", apvts, ParamIDs::distEnabled,
        juce::StringArray { ParamIDs::distAmount, ParamIDs::distWet },
        juce::StringArray { "Amount", "Mix" });
    addAndMakeVisible(*distortionSlot);

    // Chorus
    chorusSlot = std::make_unique<EffectSlot>(
        "Chorus", apvts, ParamIDs::chorusEnabled,
        juce::StringArray { ParamIDs::chorusRate, ParamIDs::chorusDelay,
                            ParamIDs::chorusDepth, ParamIDs::chorusWet },
        juce::StringArray { "Rate", "Delay", "Depth", "Mix" });
    addAndMakeVisible(*chorusSlot);

    // Compressor
    compressorSlot = std::make_unique<EffectSlot>(
        "Compressor", apvts, ParamIDs::compEnabled,
        juce::StringArray { ParamIDs::compThreshold, ParamIDs::compRatio,
                            ParamIDs::compAttack, ParamIDs::compRelease, ParamIDs::compKnee },
        juce::StringArray { "Threshold", "Ratio", "Attack", "Release", "Knee" });
    addAndMakeVisible(*compressorSlot);

    slots = { reverbSlot.get(), delaySlot.get(), eqSlot.get(),
              distortionSlot.get(), chorusSlot.get(), compressorSlot.get() };
}

void EffectChainEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(CustomLookAndFeel::bgColour));
}

void EffectChainEditor::resized()
{
    auto bounds = getLocalBounds().reduced(8);
    int slotHeight = bounds.getHeight() / 6;

    for (auto* slot : slots)
    {
        slot->setBounds(bounds.removeFromTop(slotHeight).reduced(0, 2));
    }
}

} // namespace muzikiii
