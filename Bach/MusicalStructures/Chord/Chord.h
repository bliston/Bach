/*
  ==============================================================================

    Chord.h
    Created: 3 Jun 2017 4:15:43pm
    Author:  blist

  ==============================================================================
*/

#ifndef CHORD_H_INCLUDED
#define CHORD_H_INCLUDED
#include "../../BachCommon.h"
#include "../../Utils/MidiUtils.h"
#include "../Note/Note.h"
#include "ChordNameToMidiNotes.h"
#include "MidiNotesToChordName.h"
namespace Bach {
	class Chord {
	public:
		Chord();
		Chord(String chordName); // A#m7
		void setChord(String chordName); // A#m7
		void setRoot(int rootNote); // 36
		void setType(String chordType); // m7
		Array<Note> getNotes();
		Array<int> getMidiNoteNumbers(); // [48, 52, 55]
		Array<String> getPitchClassWithOctaveNotes(); // [A3, C4, E4]
		Array<String> getPitchClassNotes(); // [A, C, E]
		Array<int> getIntegerPitchClassNotes(); // [0, 3, 5, 7]
		Array<String> getIntervals(); // [P1, m3, P5]
	private:
		MidiUtils midiUtils;
		ChordNameToMidiNotes chordNameToMidiNotes;
		MidiNotesToChordName midiNotesToChordName;
		int root;
		String type;
		int octave;
		//ChordVoicing voicing;
	};
}

#endif  // CHORD_H_INCLUDED
