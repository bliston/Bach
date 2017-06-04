/*
  ==============================================================================

    Chord.h
    Created: 3 Jun 2017 4:15:43pm
    Author:  blist

  ==============================================================================
*/

#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED
#include "../../BachCommon.h"
#include "../../Utils/MidiUtils.h"
#include "../Chord/ChordNameToMidiNotes.h"
#include "../Chord/MidiNotesToChordName.h"
namespace Bach {
	class Note {
	public:
		Note(int midi);
		Note(int midi, int vel);
		int getMidiNoteNumber(); // 48
		void setMidiNoteNumber(int midi);
		int getVelocity(); // 48
		void setVelocity(int vel);
		String getPitchClassWithOctave(); // A3
		String getPitchClass(); // A
		int getIntegerPitchClass(); // 0
		int getOctave(); // 4
	private:
		MidiUtils midiUtils;
		int midiNoteNumber;
		int velocity;
	};
}

#endif  // NOTE_H_INCLUDED
