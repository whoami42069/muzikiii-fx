#include "CustomLookAndFeel.h"

namespace muzikiii {

CustomLookAndFeel::CustomLookAndFeel()
{
    // Set colour scheme
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colour(bgColour));
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(highlightColour));
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(accentColour));
    setColour(juce::Slider::thumbColourId, juce::Colour(textColour));
    setColour(juce::Label::textColourId, juce::Colour(textColour));
    setColour(juce::ToggleButton::tickColourId, juce::Colour(highlightColour));
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colour(mutedTextColour));
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                          juce::Slider&)
{
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(4.0f);
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto centreX = bounds.getCentreX();
    auto centreY = bounds.getCentreY();
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Background arc
    juce::Path bgArc;
    bgArc.addCentredArc(centreX, centreY, radius - 2.0f, radius - 2.0f,
                         0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(juce::Colour(accentColour));
    g.strokePath(bgArc, juce::PathStrokeType(3.0f, juce::PathStrokeType::curved,
                                               juce::PathStrokeType::rounded));

    // Value arc
    juce::Path valueArc;
    valueArc.addCentredArc(centreX, centreY, radius - 2.0f, radius - 2.0f,
                            0.0f, rotaryStartAngle, angle, true);
    g.setColour(juce::Colour(highlightColour));
    g.strokePath(valueArc, juce::PathStrokeType(3.0f, juce::PathStrokeType::curved,
                                                  juce::PathStrokeType::rounded));

    // Thumb dot
    juce::Point<float> thumbPoint(
        centreX + (radius - 8.0f) * std::cos(angle - juce::MathConstants<float>::halfPi),
        centreY + (radius - 8.0f) * std::sin(angle - juce::MathConstants<float>::halfPi));
    g.setColour(juce::Colour(textColour));
    g.fillEllipse(juce::Rectangle<float>(6.0f, 6.0f).withCentre(thumbPoint));
}

void CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
                                          bool shouldDrawButtonAsHighlighted, bool)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);
    auto toggleWidth = 36.0f;
    auto toggleHeight = 18.0f;
    auto toggleBounds = juce::Rectangle<float>(toggleWidth, toggleHeight)
                            .withCentre({ bounds.getX() + toggleWidth / 2.0f + 4.0f, bounds.getCentreY() });

    // Track
    auto trackColour = button.getToggleState() ? juce::Colour(highlightColour) : juce::Colour(accentColour);
    if (shouldDrawButtonAsHighlighted)
        trackColour = trackColour.brighter(0.1f);
    g.setColour(trackColour);
    g.fillRoundedRectangle(toggleBounds, toggleHeight / 2.0f);

    // Thumb
    float thumbX = button.getToggleState()
                       ? toggleBounds.getRight() - toggleHeight + 2.0f
                       : toggleBounds.getX() + 2.0f;
    g.setColour(juce::Colour(textColour));
    g.fillEllipse(thumbX, toggleBounds.getY() + 2.0f, toggleHeight - 4.0f, toggleHeight - 4.0f);

    // Label text
    auto textBounds = bounds.withLeft(toggleBounds.getRight() + 8.0f);
    g.setColour(juce::Colour(textColour));
    g.setFont(14.0f);
    g.drawText(button.getButtonText(), textBounds, juce::Justification::centredLeft);
}

} // namespace muzikiii
