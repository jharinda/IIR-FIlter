/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IIRFilterAudioProcessor::IIRFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),treeState(*this, nullptr),
    iirFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100,defaultFilterCutoff,defaultFilterResonance))
#endif
{
    juce::NormalisableRange<float> filterCutoffRange(minFilterCutoff, maxFilterCutoff);
    filterCutoffRange.setSkewForCentre(1000.0f);

    juce::NormalisableRange<float> filterResonanceRange(minFilterResonance, maxFilterResonance);
    juce::NormalisableRange<float> filterTypeMenuRange(minFilterTypeMenu, maxFilterTypeMenu);
    juce::NormalisableRange<float> filterGainFactorRange(minFilterGainFactor, maxFilterGainFactor);

    treeState.createAndAddParameter(filterCutoffId, filterCutoffName, filterCutoffName, filterCutoffRange, defaultFilterCutoff, nullptr, nullptr);
    treeState.createAndAddParameter(filterResonanceId, filterResonanceName, filterResonanceName, filterResonanceRange, defaultFilterResonance, nullptr, nullptr);
    treeState.createAndAddParameter(filterTypeMenuId, filterTypeMenuName, filterTypeMenuName, filterTypeMenuRange, defaultFilterTypeMenu, nullptr, nullptr);
    treeState.createAndAddParameter(filterGainFactorId, filterGainFactorName, filterGainFactorName, filterGainFactorRange, defaultFilterGainFactor, nullptr, nullptr);

    treeState.state = juce::ValueTree("Tree");
}

IIRFilterAudioProcessor::~IIRFilterAudioProcessor()
{
}

//==============================================================================
const juce::String IIRFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IIRFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IIRFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IIRFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IIRFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IIRFilterAudioProcessor::getNumPrograms()
{
    return 1;   
}

int IIRFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IIRFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String IIRFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void IIRFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void IIRFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    juce::dsp::ProcessSpec spec;
    
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getNumOutputChannels();
    spec.sampleRate = lastSampleRate;
    
    updateFilter();
    iirFilter.reset();
    iirFilter.prepare(spec);
}

void IIRFilterAudioProcessor::updateFilter()
{
    int filterChoice = *treeState.getRawParameterValue(filterTypeMenuId);
    float cutoff = *treeState.getRawParameterValue(filterCutoffId);
    float resonance = *treeState.getRawParameterValue(filterResonanceId);

    if (filterChoice == 0)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeAllPass(lastSampleRate, cutoff);

    }

    if (filterChoice == 1)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, cutoff, resonance);
    }

    if (filterChoice == 2)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }

   if (filterChoice == 3)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }

    if (filterChoice == 4)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }
    if (filterChoice == 5)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }
    if (filterChoice == 6)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }
    if (filterChoice == 7)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }
    if (filterChoice == 8)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }
    if (filterChoice == 9)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }
    if (filterChoice == 10)
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, resonance);
    }

}


void IIRFilterAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IIRFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void IIRFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    /*for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());*/

    
    updateFilter();
    juce::dsp::AudioBlock<float> block(buffer);
    iirFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool IIRFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* IIRFilterAudioProcessor::createEditor()
{
    return new IIRFilterAudioProcessorEditor (*this);
}

//==============================================================================
void IIRFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IIRFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IIRFilterAudioProcessor();
}
