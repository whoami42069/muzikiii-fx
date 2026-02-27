#include "PluginEditor.h"

namespace muzikiii {

MuzikiiiFXEditor::MuzikiiiFXEditor(MuzikiiiFXProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , chainEditor(p.getAPVTS())
{
    setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(chainEditor);
    setSize(600, 720);
    setResizable(true, true);
    setResizeLimits(400, 500, 1200, 1400);
}

MuzikiiiFXEditor::~MuzikiiiFXEditor()
{
    setLookAndFeel(nullptr);
}

void MuzikiiiFXEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(CustomLookAndFeel::bgColour));

    // Header
    auto headerBounds = getLocalBounds().removeFromTop(40).toFloat();
    g.setColour(juce::Colour(CustomLookAndFeel::surfaceColour));
    g.fillRect(headerBounds);

    g.setColour(juce::Colour(CustomLookAndFeel::highlightColour));
    g.setFont(juce::Font(20.0f, juce::Font::bold));
    g.drawText("Muzikiii FX", headerBounds.reduced(12.0f, 0.0f), juce::Justification::centredLeft);

    g.setColour(juce::Colour(CustomLookAndFeel::mutedTextColour));
    g.setFont(12.0f);
    g.drawText("v1.0.0", headerBounds.reduced(12.0f, 0.0f), juce::Justification::centredRight);

    // Separator line
    g.setColour(juce::Colour(CustomLookAndFeel::accentColour).withAlpha(0.3f));
    g.drawHorizontalLine(40, 0.0f, static_cast<float>(getWidth()));
}

void MuzikiiiFXEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(41); // Header
    chainEditor.setBounds(bounds);
}

} // namespace muzikiii
