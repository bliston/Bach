/*
  ==============================================================================

    Chord.cpp
    Created: 3 Jun 2017 4:15:43pm
    Author:  blist

  ==============================================================================
*/

#include "Chord.h"
Bach::Chord::Chord() // C
{
	octave = 5;
	setChord("C");
}
Bach::Chord::Chord(String chordName) // A#m7
{
	octave = 5;
	setChord(chordName);
}

void Bach::Chord::setChord(String chordName) // A#m7/B
{
	root = chordNameToMidiNotes.getChordRoot(chordName);
	type = chordNameToMidiNotes.getChordType(chordName);
	bass = chordNameToMidiNotes.getChordBass(chordName);
}

void Bach::Chord::setRoot(String rootNote) // A#
{
	bass = rootNote;
}

void Bach::Chord::setType(String chordType) // m7
{
	type = chordType;
}

void Bach::Chord::setBass(String bassNote) // B
{
	bass = bassNote;
}

Array<Bach::Note> Bach::Chord::getNotes()
{
	Array<Note> notes;
	return notes;
}

Array<int> Bach::Chord::getMidiNoteNumbers() // [48, 52, 55]
{
	Array<int> notes = chordNameToMidiNotes.get(root, type, bass, octave);
	return notes;
}

Array<String> Bach::Chord::getPitchClassWithOctaveNotes() // [A3, C4, E4]
{
	return {};
}

Array<String> Bach::Chord::getPitchClassNotes() // [A, C, E]
{
	return {"A"};
}

Array<int> Bach::Chord::getIntegerPitchClassNotes() // [0, 3, 5, 7]
{
	return {0};
}

Array<String> Bach::Chord::getIntervals() // [P1, m3, P5]
{
	return {"P1"};
}