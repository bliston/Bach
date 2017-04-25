/*
  ==============================================================================

    ChordReader.cpp
    Created: 7 Apr 2017 5:49:51pm
    Author:  blist

  ==============================================================================
*/
#include "ChordReader.h"
Bach::ChordReader::ChordReader()
{
	resetState();
}

void Bach::ChordReader::resetState()
{
	INTERVALS.clear();
	INTERVALS.set("P1", 0); INTERVALS.set("d2", 0);
	INTERVALS.set("m2", 1); INTERVALS.set("A1", 1);
	INTERVALS.set("M2", 2); INTERVALS.set("d3", 2);
	INTERVALS.set("m3", 3); INTERVALS.set("A2", 3);
	INTERVALS.set("M3", 4); INTERVALS.set("d4", 4);
	INTERVALS.set("P4", 5); INTERVALS.set("A3", 5);
	INTERVALS.set("d5", 6); INTERVALS.set("A4", 6);
	INTERVALS.set("P5", 7); INTERVALS.set("d6", 7);
	INTERVALS.set("m6", 8); INTERVALS.set("A5", 8);
	INTERVALS.set("M6", 9); INTERVALS.set("d7", 8);
	INTERVALS.set("m7", 10); INTERVALS.set("A6", 10);
	INTERVALS.set("M7", 11); INTERVALS.set("d8", 11);
	INTERVALS.set("P8", 12); INTERVALS.set("A7", 12); INTERVALS.set("d9", 12);
	INTERVALS.set("m9", 13); INTERVALS.set("A8", 13);
	INTERVALS.set("M9", 14); INTERVALS.set("d10", 14);
	INTERVALS.set("m10", 15); INTERVALS.set("A9", 15);
	INTERVALS.set("M10", 16); INTERVALS.set("d11", 16);
	INTERVALS.set("P11", 17); INTERVALS.set("A10", 17);
	INTERVALS.set("d12", 18); INTERVALS.set("A11", 18);
	INTERVALS.set("P12", 19); INTERVALS.set("d13", 19);
	INTERVALS.set("m13", 20); INTERVALS.set("A12", 20);
	INTERVALS.set("M13", 21); INTERVALS.set("d14", 21);
	INTERVALS.set("m14", 22); INTERVALS.set("A13", 22);
	INTERVALS.set("M14", 23); INTERVALS.set("d15", 23);
	INTERVALS.set("P15", 24); INTERVALS.set("A14", 24);
	INTERVALS.set("A15", 25);
	SYMBOLS.clear();
	SYMBOLS.set("m", { "m3", "P5" });
	SYMBOLS.set("mi", { "m3", "P5" });
	SYMBOLS.set("min", { "m3", "P5" });
	SYMBOLS.set("-", { "m3", "P5" });

	SYMBOLS.set("M", { "M3", "P5" });
	SYMBOLS.set("ma", { "M3", "P5" });
	SYMBOLS.set("", { "M3", "P5" });

	SYMBOLS.set("+", { "M3", "A5" });
	SYMBOLS.set("aug", { "M3", "A5" });

	SYMBOLS.set("dim", { "m3", "d5" });
	SYMBOLS.set("o", { "m3", "d5" });

	SYMBOLS.set("maj", { "M3", "P5", "M7" });
	SYMBOLS.set("dom", { "M3", "P5", "m7" });
	//SYMBOLS.set("ø",{ "m3", "d5", "m7" });

	SYMBOLS.set("5", { "P5" });

	SYMBOLS.set("6/9", { "M3", "P5", "M6", "M9" });
	//c
	parsing = "quality";
	additionals.clear();
	name.clear();
	chordLength = 2;
	notes = { "P1", "M3", "P5", "m7", "M9", "P11", "M13" };
	explicitMajor = false;
}

void Bach::ChordReader::setChord(String name)
{
	Array<String> intervals = SYMBOLS[name];
	for (int i = 0, len = intervals.size(); i < len; i++) {
		notes.set(i + 1, intervals[i]);
	}

	chordLength = intervals.size();
}

Array<String> Bach::ChordReader::split(::std::string s, ::std::regex regexDelimiter)
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

Array<String> Bach::ChordReader::readChord(String symbol)
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
			if (SYMBOLS.contains(sub3))
				name = sub3;
			else if (SYMBOLS.contains(sub2))
				name = sub2;
			else if (SYMBOLS.contains(c))
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

Array<int> Bach::ChordReader::midiChord(String symbol, int rootMIDI)
{
	Array<int> midChord;
	Array<String> intervalChord = readChord(symbol);
	for (auto i : intervalChord)
	{
		jassert(INTERVALS.contains(i));
		midChord.add(INTERVALS[i] + rootMIDI);
	}
	return midChord;
}