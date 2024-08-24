#pragma once

#include "Include.hpp"

// FWD DECL OTHER

// FWD DECL THIS
struct Lace;
struct Bin_Lace;

// DECL
struct Lace_S { //------------Add Space(s) to Lace------------
	uint16 count;
	Lace_S(const uint16& count = 1) : count(count) {};
};

struct Lace_NL { //------------Add New Line(s) and/or Global Tab To Lace------------
	uint16 count;
	bool use_global_tabs;
	Lace_NL(const uint16& count = 1, const bool& use_global_tabs = true) : count(count), use_global_tabs(use_global_tabs) {}
};

struct Lace_TAB { //------------Add Tab(s) to Lace------------
	uint16 count;
	Lace_TAB(const uint16& count = 1) : count(count) {}
};

struct Lace_CHR { //------------Add Char(s) to Lace------------
	uint16 count;
	Lace_CHR(const uint16& count = 1) : count(count) {}
};

struct Lace_DEL { //------------Remove first Char(s) from Lace------------
	uint16 count;
	Lace_DEL(const uint16& count = 1) : count(count) {}
};

struct Lace_POP { //------------Remove last Char(s) from Lace------------
	uint16 count;
	Lace_POP(const uint16& count = 1) : count(count) {}
};

struct Lace { //------------Utility for string manipulation------------
	stringstream data;
	uint16 current_tab; // Global Tabbing to be transferred through new lines
	const string character;

	Lace();
	Lace(const string& character);

	Lace& operator<< (const Lace& value);
	Lace& operator>> (const Lace& value);

	Lace& operator+= (const uint16& value);
	Lace& operator-= (const uint16& value);
	Lace& operator++ (int);
	Lace& operator-- (int);

	Lace& operator<<(const Lace_S& val);
	Lace& operator<<(const Lace_NL& val);
	Lace& operator<<(const Lace_TAB& val);
	Lace& operator<<(const Lace_CHR& val);
	Lace& operator<<(const Lace_DEL& val);
	Lace& operator<<(const Lace_POP& val);

	Lace& clear();
	string str() const;

	// Feed directly

#if defined(COMPILE_EDITOR) || defined(COMPILE_GUI_SCRIPTING)
	Lace& operator<< (const QPointF& value);
	Lace& operator<< (const QString& value);
#endif

	Lace& operator<< (const bool& value);
	Lace& operator<< (const char* value);
	Lace& operator<< (const string& value);
	Lace& operator<< (const stringstream& value);

	Lace& operator<< (const int8& value);
	Lace& operator<< (const int16& value);
	Lace& operator<< (const int32& value);
	Lace& operator<< (const int64& value);
	Lace& operator<< (const uint8& value);
	Lace& operator<< (const uint16& value);
	Lace& operator<< (const uint32& value);
	Lace& operator<< (const uint64& value);
	Lace& operator<< (const ivec2& value);
	Lace& operator<< (const ivec3& value);
	Lace& operator<< (const ivec4& value);
	Lace& operator<< (const uvec2& value);
	Lace& operator<< (const uvec3& value);
	Lace& operator<< (const uvec4& value);

	Lace& operator<< (const vec1& value);
	Lace& operator<< (const vec2& value);
	Lace& operator<< (const vec3& value);
	Lace& operator<< (const vec4& value);
	Lace& operator<< (const quat& value);
	Lace& operator<< (const mat2& value);
	Lace& operator<< (const mat3& value);
	Lace& operator<< (const mat4& value);

	Lace& operator<< (const dvec1& value);
	Lace& operator<< (const dvec2& value);
	Lace& operator<< (const dvec3& value);
	Lace& operator<< (const dvec4& value);
	Lace& operator<< (const dquat& value);
	Lace& operator<< (const dmat2& value);
	Lace& operator<< (const dmat3& value);
	Lace& operator<< (const dmat4& value);

	// Feed Single Units With Space Before
	Lace& operator>> (const bool& value);
	Lace& operator>> (const char* value);
	Lace& operator>> (const float& value);
	Lace& operator>> (const double& value);
	Lace& operator>> (const int8& value);
	Lace& operator>> (const int16& value);
	Lace& operator>> (const int32& value);
	Lace& operator>> (const int64& value);
	Lace& operator>> (const uint8& value);
	Lace& operator>> (const uint16& value);
	Lace& operator>> (const uint32& value);
	Lace& operator>> (const uint64& value);

	// Vectors
	Lace& operator<< (const vector<string>& value);
};

string d_to_str(const dvec1& value);
string f_to_str(const vec1& value);

template<typename T>
T f_readBinary(const vector<Byte>& data, const uint64& start) {
	T value;
	std::memcpy(&value, data.data() + start, sizeof(T));
	return value;
};

template<typename T>
T f_readBinary(const vector<Byte>& data, const uint64& start, const uint64& size) {
	T value;
	std::memcpy(&value, data.data() + start, size);
	return value;
}

template<>
string f_readBinary<string>(const vector<Byte>& data, const uint64& start, const uint64& size);

template<typename T>
vector<Byte> f_toBinary(const T& value) {
	vector<Byte> data;
	const uint64 size = sizeof(T); // - 1 Careful: removing null terminator
	const Byte* byte_data = reinterpret_cast<const Byte*>(&value);

	data.reserve(size);
	data.insert(data.end(), byte_data, byte_data + size);
	return data;
};

template<>
vector<Byte> f_toBinary<string>(const string& value);

struct Bin_Lace { //------------Utility for binary manipulation------------
	vector<Byte> data;
	Bin_Lace();

	Bin_Lace& operator<< (const Bin_Lace& value);

	template <typename T>
	Bin_Lace& operator<< (const T& value) {
		vector<Byte> bytes = f_toBinary(value);
		const uint64 size = bytes.size();

		data.reserve(data.size() + size);
		data.insert(data.end(), bytes.begin(), bytes.end());
		return *this;
	};
};