#include "ParameterLayout.h"

namespace muzikiii {

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // ============ Reverb ============
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID { ParamIDs::reverbEnabled, 1 }, "Reverb Enabled", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::reverbDecay, 1 }, "Reverb Decay",
        juce::NormalisableRange<float>(0.1f, 30.0f, 0.01f, 0.3f), 2.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::reverbPreDelay, 1 }, "Reverb Pre-Delay",
        juce::NormalisableRange<float>(0.0f, 0.1f, 0.001f), 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::reverbWet, 1 }, "Reverb Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.3f));

    // ============ Delay ============
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID { ParamIDs::delayEnabled, 1 }, "Delay Enabled", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::delayTime, 1 }, "Delay Time",
        juce::NormalisableRange<float>(0.0f, 5.0f, 0.001f, 0.4f), 0.25f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::delayFeedback, 1 }, "Delay Feedback",
        juce::NormalisableRange<float>(0.0f, 0.9f, 0.01f), 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::delayWet, 1 }, "Delay Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.3f));

    // ============ EQ ============
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID { ParamIDs::eqEnabled, 1 }, "EQ Enabled", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::eqLow, 1 }, "EQ Low",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::eqMid, 1 }, "EQ Mid",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::eqHigh, 1 }, "EQ High",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::eqLowFrequency, 1 }, "EQ Low Freq",
        juce::NormalisableRange<float>(60.0f, 800.0f, 1.0f, 0.5f), 300.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::eqHighFrequency, 1 }, "EQ High Freq",
        juce::NormalisableRange<float>(800.0f, 12000.0f, 1.0f, 0.5f), 3000.0f));

    // ============ Distortion ============
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID { ParamIDs::distEnabled, 1 }, "Distortion Enabled", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::distAmount, 1 }, "Distortion Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID { ParamIDs::distOversample, 1 }, "Distortion Oversample",
        juce::StringArray { "None", "2x", "4x" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::distWet, 1 }, "Distortion Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    // ============ Chorus ============
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID { ParamIDs::chorusEnabled, 1 }, "Chorus Enabled", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::chorusRate, 1 }, "Chorus Rate",
        juce::NormalisableRange<float>(0.1f, 10.0f, 0.01f, 0.5f), 1.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::chorusDelay, 1 }, "Chorus Delay",
        juce::NormalisableRange<float>(2.0f, 20.0f, 0.1f), 3.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::chorusDepth, 1 }, "Chorus Depth",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.7f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::chorusWet, 1 }, "Chorus Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    // ============ Compressor ============
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID { ParamIDs::compEnabled, 1 }, "Compressor Enabled", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::compThreshold, 1 }, "Comp Threshold",
        juce::NormalisableRange<float>(-60.0f, 0.0f, 0.1f), -24.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::compRatio, 1 }, "Comp Ratio",
        juce::NormalisableRange<float>(1.0f, 20.0f, 0.1f, 0.5f), 4.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::compAttack, 1 }, "Comp Attack",
        juce::NormalisableRange<float>(0.0001f, 1.0f, 0.0001f, 0.3f), 0.003f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::compRelease, 1 }, "Comp Release",
        juce::NormalisableRange<float>(0.001f, 1.0f, 0.001f, 0.3f), 0.25f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::compKnee, 1 }, "Comp Knee",
        juce::NormalisableRange<float>(0.0f, 40.0f, 0.1f), 10.0f));

    return { params.begin(), params.end() };
}

} // namespace muzikiii
