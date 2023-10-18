#pragma once
/*	gats/win32/XError.hpp

	Error system declarations.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.08.25
	C++ 17 version.
	removed min/max macros

Version 2019.01.19
	Production version.

Version 2015.01.01
	Alpha release.

=============================================================

Copyright 2015-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/


#define NOMINMAX
#include <windows.h>
#include <string>


namespace gats::win32 {

	std::wstring ErrorDescription(DWORD dwMessageID);

	/* Console error exception class. */
	class XError {
	public:
		using id_type = DWORD;
		using file_type = char const *;
		using line_type = unsigned;
		using string_type = std::wstring;
	private:
		id_type code_;
		line_type line_;
		file_type file_;
	public:
		XError(int line, file_type file);
		auto code() const -> id_type { return code_; }
		auto line() const -> line_type { return line_; }
		auto file() const -> file_type { return file_; }
		auto text() const -> string_type { return ErrorDescription(code_); }

		string_type message() const;
	};

} // End-of-namespace gats::win32




/* Console error exception throw helper macro. */
#define THROW_IF_WIN32_ERROR(res)	if(!res) throw gats::win32::XError(__LINE__,__FILE__)
#define THROW_WIN32_ERROR()			throw gats::win32::XError(__LINE__,__FILE__)
