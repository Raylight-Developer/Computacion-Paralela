#pragma once

#include "Include.hpp"

#include "Lace.hpp"

// FWD DECL OTHER

// FWD DECL THIS

// DECL
struct Session {
	static Session& getInstance();

	void flushLog();

	Session();
	~Session() = default;

	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;

	Lace log = Lace();
};

#undef LOG
#undef FILE

#define ENDL << Lace_NL()

#define ANSI_RESET  << "\033[0m"

#define ANSI_BLACK  << "\033[90m"
#define ANSI_R      << "\033[91m"
#define ANSI_G      << "\033[92m"
#define ANSI_YELLOW << "\033[93m"
#define ANSI_B      << "\033[94m"
#define ANSI_PURPLE << "\033[95m"
#define ANSI_CYAN   << "\033[96m"
#define ANSI_WHITE  << "\033[97m"

#define NL  << Lace_NL()
#define SP  << Lace_S()
#define TAB << Lace_TAB()
#define PTR << "* "

#define LOG Session::getInstance().log
#define FLUSH Session::getInstance().flushLog()
#define COUT_S Lace lace; lace <<
#define COUT_E ; cout << lace.str()