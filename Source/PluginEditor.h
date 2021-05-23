/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class IIRFilterAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                       public juce::ComboBox::Listener
{
public:
    IIRFilterAudioProcessorEditor (IIRFilterAudioProcessor&);
    ~IIRFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    IIRFilterAudioProcessor& audioProcessor;

    juce::Slider filterCutoffDial;
    juce::Slider filterResonanceDial;
    juce::Slider filterGainFactorDial;

    juce::ComboBox filterTypeMenu;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeMenuValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IIRFilterAudioProcessorEditor)
};
