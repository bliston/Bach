/*
  ==============================================================================

    ChordNameToMidiNotes.cpp
    Created: 7 Apr 2017 5:49:51pm
    Author:  blist

  ==============================================================================
*/
#include "ChordNameToMidiNotes.h"

struct Bach::ChordRootAndType
{
	int root;
	String type;
};

Bach::ChordNameToMidiNotes::ChordNameToMidiNotes()
{
	resetState();
}

void Bach::ChordNameToMidiNotes::resetState()
{
	//c
	parsing = "quality";
	additionals.clear();
	name.clear();
	chordLength = 2;
	notes = { "P1", "M3", "P5", "m7", "M9", "P11", "M13" };
	explicitMajor = false;
}

void Bach::ChordNameToMidiNotes::setChord(String name)
{
	Array<String> intervals = midiUtils.chordSymbolToIntervalArray(name);
	for (int i = 0, len = intervals.size(); i < len; i++) {
		notes.set(i + 1, intervals[i]);
	}

	chordLength = intervals.size();
}

Array<String> Bach::ChordNameToMidiNotes::split(::std::string s, ::std::regex regexDelimiter)
{
	Array<String> outArray;
	::std::vector<::std::string> out;

	::std::regex re = regexDelimiter;
	::std::string word;

	auto i = s.begin();
	while (i != s.end()) {
		::std::match_results<::std::string::iterator> m;
		if (regex_match(i, s.end(), m, re)) {
			out.push_back(word);
			word.clear();
			out.push_back(::std::string(m[1].first, m[1].second));
			i += out.back().size();
		}
		else {
			word += *i++;
		}
	}
	if (!word.empty()) {
		out.push_back(word);
	}
	for (auto& a : out)
	{
		outArray.add(a);
	}
	return outArray;
}

Array<String> Bach::ChordNameToMidiNotes::readChord(String symbol)
{
	resetState();
	// Remove whitespace, commas and parentheses
	symbol = symbol.removeCharacters(" [(,)]");
	//string regexString = ".";
	//regex regexDelimiter(regexString, std::regex_constants::icase);
	//Array<String> charArr = split(symbol.toStdString(), regexDelimiter);
	for (int i = 0, len = symbol.length(); i < len; i++) {
		char ch = symbol.toStdString().at(i);
		::std::string str(1, ch);
		c = str;
		if (parsing == "quality") {
			String sub3 = (i + 2) < len ? String(symbol.toStdString().substr(i, 3)).toLowerCase() : "invalid";
			String sub2 = (i + 1) < len ? String(symbol.toStdString().substr(i, 2)).toLowerCase() : "invalid";
			if (midiUtils.isValidBasicChordSymbol(sub3))
				name = sub3;
			else if (midiUtils.isValidBasicChordSymbol(sub2))
				name = sub2;
			else if (midiUtils.isValidBasicChordSymbol(c))
				name = c;
			else
				name = "";

			if (name.isNotEmpty())
				setChord(name);

			if (name == "M" || name == "ma" || name == "maj")
				explicitMajor = true;


			i += name.length() - 1;
			parsing = "extension";
		} else if (parsing == "extension") {
      c = (c == "1" && symbol[i + 1]) ? String(symbol.toStdString().substr(i, 2)).getIntValue() : (int)c;

      if (c && (int)c != 6) {
        chordLength = ((double)c - 1) / 2;

        //if (chordLength != Math.round(chordLength)) {
          //throw ParseError({
          //  title: 'Invalid interval extension',
          //  token: c,
          //  index: i
          //});
        //}

        if (name == "o" || name == "dim")
          notes.set(3, "d7");
        else if (explicitMajor)
			notes.set(3, "M7");

        i += (int)c >= 10 ? 1 : 0;
      } else if ((int)c == 6) {
		  notes.set(3, "M6");
        chordLength = jmax(3, (int)chordLength);
      } else
        i -= 1;

      parsing = "alterations";
    }
		else if (parsing == "alterations") {
			::std::string symbolToSplit = symbol.toStdString().substr(i);
			::std::string regexString = "\(#|b|add|maj|sus|M).*";
			::std::regex regexDelimiter(regexString, ::std::regex_constants::icase);
			Array<String> alterations = split(symbolToSplit, regexDelimiter);
			int next;
			bool flat = false;
			bool sharp = false;

			//if (alterations.length() == = 1) {
			//	throw ParseError({
			//	title: 'Invalid alteration',
			//		   token : symbol.substr(i),
			//				   index : i
			//	});
			//}
			//else if (alterations[0].length() != = 0) {
			//	throw ParseError({
			//	title: 'Invalid token',
			//		   token : alterations[0],
			//				   index : i
			//	});
			//}

			bool ignore = false;
			int alterationStringIndex = 0;
			int altIndex = 0;
			Array<String> arr = alterations;
			for (auto alt : arr)
			{
				alterationStringIndex += alt.length();
				if (ignore || !alt.length()) {
					// return ignore == false;
					altIndex++;
					ignore = false;
					continue;
				}

				int next = arr[altIndex + 1].getIntValue();
				String lower = alt.toLowerCase();
				if (alt == "M" || lower == "maj") {
					if (next == 7)
						ignore = true;

					chordLength = jmax(3, (int)chordLength);
					notes.set(3, "M7");
				}
				else if (lower == "sus") {
					String type = "P4";
					if (next == 2 || next == 4) {
						ignore = true;

						if (next == 2)
							type = "M2";
					}

					notes.set(1, type); // Replace third with M2 or P4
				}
				else if (lower == "add") {
					if (next == 9)
						additionals.add("M9");
					else if (next == 11)
						additionals.add("P11");
					else if (next == 13)
						additionals.add("M13");
					else {
						//throw ParseError({
						//title: 'Invalid token',
						//	   token : next,
						//			   index : i + alterationStringIndex
						//});
					}

					ignore = true;
				}
				else if (lower == "b") {
					flat = true;
				}
				else if (lower == "#") {
					sharp = true;
				}
				else {
					int token = alt.getIntValue();
					String quality;
					int intPos;
					if (token || String(token).length() != alt.length()) {
						/*throw ParseError({
						title: 'Invalid token',
							   token : alt,
									   index : i + alterationStringIndex - alt.length()
						});*/
					}

					if (token > 13) {
						/*throw ParseError({
						title: 'Cannot alterate intervals bigger than 13',
							   token : alt,
									   index : i + alterationStringIndex - alt.length()
						});*/
					}

					if (token == 6) {
						if (sharp)
							notes.set(3, "A6");
						else if (flat)
							notes.set(3, "m6");
						else
							notes.set(3, "M6");

						chordLength = jmax(3, (int)chordLength);
						//return{ "" };
						altIndex++;
						continue;
					}

					// Calculate the position in the 'note' array
					intPos = (token - 1) / 2;
					if ((int)chordLength < intPos)
						chordLength = intPos;

					//if (token < 5 || token == 7 || intPos != Math.round(intPos)) {
					//	throw ParseError({
					//	title: 'Invalid alteration',
					//		   token : token,
					//				   index : i + alterationStringIndex - alt.length()
					//	});
					//}

					quality = String::charToString(notes[intPos][0]);

					// Alterate the quality of the interval according the accidentals
					if (sharp) {
						if (quality == "d")
							quality = "m";
						else if (quality == "m")
							quality = "M";
						else if (quality == "M" || quality == "P")
							quality = "A";
					}
					else if (flat) {
						if (quality == "A")
							quality = "M";
						else if (quality == "M")
							quality = "m";
						else if (quality == "m" || quality == "P")
							quality = "d";
					}

					sharp = flat = false;
					notes.set(intPos, quality + String(token));
				}
				altIndex++;
			}//end of range loop
			parsing = "ended";
		}
		else if (parsing == "ended") {
			break;
		}
	}
	notes.removeRange((int)chordLength + 1, notes.size());
	notes.addArray(additionals);
	return notes;
}

Bach::ChordRootAndType Bach::ChordNameToMidiNotes::getChordRootAndType(String chordName, int octave)
{
	String rootNote = chordName.substring(0, 2);
	int rootMidiNoteNumber = midiUtils.pitchClassAndOctaveToMidiNumber(rootNote, octave);
	String type = chordName.substring(2);
	if (!midiUtils.isPitchClass(rootNote))
	{
		rootNote = chordName.substring(0, 1);
		rootMidiNoteNumber = midiUtils.pitchClassAndOctaveToMidiNumber(rootNote, octave);
		type = chordName.substring(1);
		if (!midiUtils.isPitchClass(rootNote))
		{
			return {-1, "INVALID"};
		}
	}
	return {rootMidiNoteNumber, type};
}

int Bach::ChordNameToMidiNotes::getChordRoot(String chordName, int octave)
{
	return getChordRootAndType(chordName, octave).root;
}

String Bach::ChordNameToMidiNotes::getChordType(String chordName, int octave)
{
	return getChordRootAndType(chordName, octave).type;
}

Array<int> Bach::ChordNameToMidiNotes::get(int chordRoot, String chordType)
{
	Array<int> midChord;
	Array<String> intervalArray = readChord(chordType);
	for (auto i : intervalArray)
	{
		jassert(midiUtils.isValidInterval(i));
		midChord.add(midiUtils.intervalToMidiNoteValue(i) + chordRoot);
	}
	return midChord;
}