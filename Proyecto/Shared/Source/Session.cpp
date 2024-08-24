#include "Session.hpp"

Session::Session() {}

Session& Session::getInstance() {
	static Session instance;
	return instance;
}

void Session::flushLog() {
	cout << log.str();
	log.clear();
}