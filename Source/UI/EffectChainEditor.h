#pragma once

#include "EffectSlot.h"

namespace muzikiii {

class EffectChainEditor : public juce::Component
{
public:
    EffectChainEditor(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    std::unique_ptr<EffectSlot> reverbSlot;
    std::unique_ptr<EffectSlot> delaySlot;
    std::unique_ptr<EffectSlot> eqSlot;
    std::unique_ptr<EffectSlot> distortionSlot;
    std::unique_ptr<EffectSlot> chorusSlot;
    std::unique_ptr<EffectSlot> compressorSlot;

    std::array<EffectSlot*, 6> slots;
};

} // namespace muzikiii
