#include "Ops.hpp"

#include "Lace.hpp"

Tokens f_split(const string& input) {
	Tokens result;
	istringstream iss(input);
	string token;
	while (iss >> token) {
		result.push_back(token);
	}
	return result;
}

Tokens f_split(const string& input, const string& delimiter) {
	Tokens result;
	uint64 start = 0;
	uint64 end = input.find(delimiter);

	while (end != string::npos) {
		result.push_back(input.substr(start, end - start));
		start = end + delimiter.length();
		end = input.find(delimiter, start);
	}

	result.push_back(input.substr(start));
	return result;
}

Tokens f_closingPair(const Token_Array& tokens, const string& open, const string& close) {
	uint openCount = 0;
	bool collecting = false;
	Tokens result;

	for (const auto& tokenList : tokens) {
		Tokens line;
		for (const auto& token : tokenList) {
			if (token == open) {
				openCount++;
				if (openCount == 1) {
					collecting = true;
				}
			} 
			else if (token == close) {
				openCount--;
				if (openCount == 0) {
					collecting = false;
					return result;
				}
			}
			else if (collecting) {
				line.push_back(token);
			}
		}
		result.push_back(f_join(line));
	}
	return {};
}

string f_closingPair(const Tokens& lines, const string& open, const string& close) {
	uint openCount = 0;
	bool collecting = false;
	vector<string> result;

	for (const string& line : lines) {
		if (f_contains(line, open)) {
			openCount++;
			if (openCount == 1) {
				collecting = true;
			}
		} 
		else if (f_contains(line, close)) {
			openCount--;
			if (openCount == 0) {
				collecting = false;
				return f_join(result, "\n");
			}
		}
		else if (collecting) {
			result.push_back(line);
		}
	}
	return f_join(result, "\n");
}

string f_join(const Tokens& tokens, const string& join, const uint64& start, const uint64& end) {
	return accumulate(
		tokens.begin() + start, tokens.end() - end, string(),
		[join](const string& accumulator, const string& current) {
			return accumulator.empty() ? current : accumulator + join + current;
		}
	);
}

string f_join(const Tokens& tokens, const uint64& start, const uint64& end) {
	return accumulate(
		tokens.begin() + start, tokens.end() - end, string(),
		[](const string& accumulator, const string& current) {
			return accumulator.empty() ? current : accumulator + " " + current;
		}
	);
}

string f_addLinesToLine(const string& value, const string& character) {
	istringstream stream(value);
	ostringstream result;
	string line;

	while (getline(stream, line)) {
		result << character << line << "\n";
	}

	return result.str();
}

string f_remove(const string& input, const string& remove) {
	string copy = input;
	size_t pos = copy.find(remove);
	while (pos != string::npos) {
		copy.erase(pos, remove.length());
		pos = copy.find(remove);
	}
	return copy;
}

bool f_contains(const string& input, const std::string& substring) {
	return input.find(substring) != string::npos;
}

string f_replace(const string& input, const string& old_str, const string& new_str) {
	string copy = input;
	size_t pos = 0;
	while ((pos = copy.find(old_str, pos)) != string::npos) {
		copy.replace(pos, old_str.length(), new_str);
		pos += new_str.length();
	}
	return copy;
}

string f_strip(const string& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");
	if (first == string::npos)
		return "";
	return str.substr(first, last - first + 1);
}

string loadFromFile(const string& file_path) {
	ifstream in(file_path, ios::binary);
	if (in) {
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw runtime_error(to_string(errno));
}

void writeToFile(const string& filename, const string& content) {
	ofstream file(filename, ios::binary);

	if (!file.is_open()) {
		throw runtime_error("Unable to open file");
	}

	for (char c : content) {
		if (c == '\r') {
			continue;
		}
		else if (c == '\n') {
			file.put('\n');
		}
		else {
			file.put(c);
		}
	}
	file.close();
}

string processSubShader(const string& file_path) {
	ifstream in(file_path, ios::binary);
	if (in) {
		Lace output;
		string line;

		while (getline(in, line)) {
			if (!line.empty()) {
				size_t includePos = line.find("#include");
				size_t versionPos = line.find("#version");
				size_t extensionPos = line.find("#extension");
				if (includePos == string::npos && versionPos == string::npos && extensionPos == string::npos) {
					line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
					output << line << Lace_NL();
				}
			}
		}
		return output.str();
	}
	throw runtime_error(to_string(errno));
}

string preprocessShader(const string& file_path) {
	ifstream in(file_path, ios::binary);
	if (in) {
		Lace output;
		string line;

		while (getline(in, line)) {
			if (!line.empty()) {
				size_t includePos = line.find("#include");
				if (includePos != string::npos) {
					size_t quotePos = line.find("\"", includePos);
					if (quotePos != string::npos) {
						size_t endQuotePos = line.find("\"", quotePos + 1);
						if (endQuotePos != string::npos) {
							string includeFilename = line.substr(quotePos + 1, endQuotePos - quotePos - 1);
							output << processSubShader("./Resources/Shaders/" + includeFilename);
							continue;
						}
					}
				}
				line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
				output << line << Lace_NL();
			}
		}
		return output.str().substr(0, output.str().size() - 1);
	}
	throw runtime_error(to_string(errno));
}