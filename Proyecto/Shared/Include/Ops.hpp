#pragma once

#include "Include.hpp"

// string
Tokens f_split(const string& input);
Tokens f_split(const string& input, const string& delimiter);
Tokens f_closingPair(const Token_Array& tokens, const string& open = "┌", const string& close = "└");
string f_closingPair(const Tokens& lines, const string& open = "┌", const string& close = "└");
string f_join(const Tokens& tokens, const string& join, const uint64& start = 0, const uint64& end = 0);
string f_join(const Tokens& tokens, const uint64& start = 0, const uint64& end = 0);
string f_addLinesToLine(const string& value, const string& character);

string f_remove(const string& input, const string& remove);
string f_replace(const string& input, const string& old_str, const string& new_str);
string f_strip(const string& str);
bool   f_contains(const string& input, const string& substring);

// I/O
string loadFromFile(const string& file_path);
void writeToFile(const string& filename, const string& content);


// Opengl
string processSubShader(const string& file_path);
string preprocessShader(const string& file_path);

// Templates
template<typename T>
struct Observable_Ptr {
	T* uptr;
	map<void*, function<void()>> callbacks;

	Observable_Ptr() : uptr(nullptr) {}
	Observable_Ptr(T* pointer) : uptr(pointer) {}

	void set(T* pointer) {
		uptr = pointer;
		for (const auto& [key, func] : callbacks)
			func();
	}

	void addCallback(void* key, function<void()> func) {
		callbacks[key] = move(func);
	}

	void clearCallbacks() {
		callbacks.clear();
	}
};

template <typename K, typename V>
struct BiMap {
	map<K, V> key_to_val;
	map<V, K> val_to_key;

	void insert(const K& key, const V& val) {
		if (key_to_val.find(key) != key_to_val.end() || val_to_key.find(val) != val_to_key.end()) {
			throw std::runtime_error("Key or value already exists");
		}
		key_to_val[key] = val;
		val_to_key[val] = key;
	}

	void removeKey(const K& key) {
		auto it = key_to_val.find(key);
		if (it == key_to_val.end()) {
			throw std::runtime_error("Key not found");
		}
		V value = it->second;
		key_to_val.erase(it);
		val_to_key.erase(value);
	}

	void removeVal(const V& val) {
		auto it = val_to_key.find(val);
		if (it == val_to_key.end()) {
			throw std::runtime_error("Value not found");
		}
		K key = it->second;
		val_to_key.erase(it);
		key_to_val.erase(key);
	}

	V getVal(const K& key) const {
		auto it = key_to_val.find(key);
		if (it != key_to_val.end()) {
			return it->second;
		}
		throw std::runtime_error("Key not found");
	}

	K getKey(const V& value) const {
		auto it = val_to_key.find(value);
		if (it != val_to_key.end()) {
			return it->second;
		}
		throw std::runtime_error("Value not found");
	}

	void clear() {
		key_to_val.clear();
		val_to_key.clear();
	}

	uint64 size() const {
		return key_to_val.size();
	}
};

template<typename T>
uint e_to_u(const T& enumerator) {
	return static_cast<uint>(enumerator);
};

template<typename T>
T ptr(const uint64& hash) {
	return reinterpret_cast<T>(hash);
}

template <typename T>
uint64 uptr(const T pointer) {
	return reinterpret_cast<uint64>(pointer);
}

template<typename T>
uint len32(const vector<T>& vector) {
	return ul_to_u(vector.size());
};

template<typename T>
void printSize(const string& label, const vector<T>& value) {
	cout << fixed << setprecision(2) << label << " | " << static_cast<double>(sizeof(T) * value.size()) / (1024.0 * 1024.0) << " mb | " << static_cast<double>(sizeof(T) * value.size()) / 1024.0 << " kb | " << sizeof(T) * value.size() << " b" << endl;
};

template<typename T>
T f_roundToNearest(const T& num, const T& factor) {
	return round(num / factor) * factor;
};

template<typename T, typename U>
T f_roundToNearest(const T& num, const U& factor) {
	return round(num / factor) * factor;
};

template<typename T>
T f_map(const T& from_min, const T& from_max, const T& to_min, const T& to_max, const T& value) {
	return (to_min + ((to_max - to_min) / (from_max - from_min)) * (value - from_min));
}

template<typename T>
T f_mapClamped(const T& from_min, const T& from_max, const T& to_min, const T& to_max, const T& value) {
	if (value > from_max) return to_max;
	else if (value < from_min) return to_min;
	else return (to_min + ((to_max - to_min) / (from_max - from_min)) * (value - from_min));
}

template<typename T>
T f_lerp(const T& a, const T& b, const dvec1& t) {
	return a + (b - a) * t;
}

template<typename T, typename U>
T f_ramp(const map<U, T>& curve, const U& t) {
	auto lower = curve.lower_bound(t);

	if (lower == curve.begin())
		return lower->second;
	if (lower == curve.end())
		return (--lower)->second;

	const U& key_b = lower->first;
	const T& val_b = lower->second;
	--lower;
	const U& key_a = lower->first;
	const T& val_a = lower->second;

	const dvec1 t_lerp = static_cast<dvec1>(t - key_a) / static_cast<dvec1>(key_b - key_a);

	return f_lerp<T>(val_a, val_b, t_lerp);
}

template<typename K, typename V>
pair<bool, V> f_getMapValue(const map<K, V>& map, const K& key, const V& fail) {
	auto it = map.find(key);
	if (it != map.end()) {
		return make_pair(true, it->second);
	}
	return make_pair(false, fail);
}

template<typename K, typename V>
pair<bool, V> f_getMapValue(const unordered_map<K, V>& map, const K& key, const V& fail) {
	auto it = map.find(key);
	if (it != map.end()) {
		return make_pair(true, it->second);
	}
	return make_pair(false, fail);
}

template<typename K, typename V>
pair<bool, K> f_getMapKey(const map<K, V>& map, const V& value, const K& fail) {
	for (const auto& pair : map) {
		if (pair.second == value) {
			return make_pair(true, pair.first);
		}
	}
	return make_pair(false, fail);
}

template<typename K, typename V>
pair<bool, K> f_getMapKey(const unordered_map<K, V>& map, const V& value, const K& fail) {
	for (const auto& pair : map) {
		if (pair.second == value) {
			return make_pair(true, pair.first);
		}
	}
	return make_pair(false, fail);
}

template<typename T>
bool f_hasVectorItem(const vector<T>& vec, const T& value) {
	auto it = find(vec.begin(), vec.end(), value);
	if (it != vec.end()) {
		return true;
	}
	return false;
}

template<typename T>
pair<bool, uint64> f_getVectorIndex(const vector<T>& vec, const T& value, const uint64& fail = 0U) {
	auto it = find(vec.begin(), vec.end(), value);
	if (it != vec.end()) {
		return make_pair(true, distance(vec.begin(), it));
	}
	return make_pair(false, fail);
}

template<typename K, typename V>
void f_removeMapItem(map<K, V>& map, const V& value) {
	for (auto it = map.begin(); it != map.end(); ) {
		if (it->second == value) {
			it = map.erase(it);
		} else {
			++it;
		}
	}
}

template<typename K, typename V>
void f_removeMapItem(unordered_map<K, V>& map, const V& value) {
	for (auto it = map.begin(); it != map.end(); ) {
		if (it->second == value) {
			it = map.erase(it);
		} else {
			++it;
		}
	}
}

template<typename K, typename V>
void f_removeMapItem(map<K, V>& map, const K& key) {
	map.erase(key);
}

template<typename K, typename V>
void f_removeMapItem(unordered_map<K, V>& map, const K& key) {
	map.erase(key);
}

template<typename T>
void f_removeVectorItem(vector<T>& vec, const T& value) {
	vec.erase(find(vec.begin(), vec.end(), value));
}