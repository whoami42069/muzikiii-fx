#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

namespace muzikiii {

// Parameter IDs - matching Muzikiii Tone.js parameter names
namespace ParamIDs {
    // Reverb
    inline const juce::String reverbEnabled  { "reverb_enabled" };
    inline const juce::String reverbDecay    { "reverb_decay" };
    inline const juce::String reverbPreDelay { "reverb_predelay" };
    inline const juce::String reverbWet      { "reverb_wet" };

    // Delay
    inline const juce::String delayEnabled   { "delay_enabled" };
    inline const juce::String delayTime      { "delay_time" };
    inline const juce::String delayFeedback  { "delay_feedback" };
    inline const juce::String delayWet       { "delay_wet" };

    // EQ
    inline const juce::String eqEnabled       { "eq_enabled" };
    inline const juce::String eqLow           { "eq_low" };
    inline const juce::String eqMid           { "eq_mid" };
    inline const juce::String eqHigh          { "eq_high" };
    inline const juce::String eqLowFrequency  { "eq_low_freq" };
    inline const juce::String eqHighFrequency { "eq_high_freq" };

    // Distortion
    inline const juce::String distEnabled     { "dist_enabled" };
    inline const juce::String distAmount      { "dist_amount" };
    inline const juce::String distOversample  { "dist_oversample" };
    inline const juce::String distWet         { "dist_wet" };

    // Chorus
    inline const juce::String chorusEnabled   { "chorus_enabled" };
    inline const juce::String chorusRate      { "chorus_rate" };
    inline const juce::String chorusDelay     { "chorus_delay" };
    inline const juce::String chorusDepth     { "chorus_depth" };
    inline const juce::String chorusWet       { "chorus_wet" };

    // Compressor
    inline const juce::String compEnabled     { "comp_enabled" };
    inline const juce::String compThreshold   { "comp_threshold" };
    inline const juce::String compRatio       { "comp_ratio" };
    inline const juce::String compAttack      { "comp_attack" };
    inline const juce::String compRelease     { "comp_release" };
    inline const juce::String compKnee        { "comp_knee" };
}

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

} // namespace muzikiii
