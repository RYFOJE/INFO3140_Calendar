#pragma once
/*	gats/win32/ConsoleApp/ConsoleCore.hpp

	ConsoleCore and Attribute class declarations.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.08.24
	C++ 17 Version
	Moved to namespace gats::win32

Version 2015.03.20
	Alpha release.

==============================================================================
Copyright 2015-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/

#include <gats/win32/XError.hpp>
#include <cassert>
#include <ostream>
#include <string>
#include <vector>


namespace gats::win32 {

#pragma region Attribute Class
struct Attribute {
	WORD mask_;
	constexpr Attribute(WORD attr) :mask_(attr) {}
};
inline constexpr Attribute operator + (const Attribute lhs, const Attribute rhs) { return lhs.mask_ | rhs.mask_; }

constexpr Attribute black = 0;
constexpr Attribute blue = 1;
constexpr Attribute green = 2;
constexpr Attribute red = 4;
constexpr Attribute cyan = blue + green;
constexpr Attribute magenta = blue + red;
constexpr Attribute yellow = green + red;
constexpr Attribute white = blue + green + red;
inline constexpr Attribute background(Attribute const& color) { return color.mask_ << 4; }
inline constexpr Attribute bright(Attribute const& color) { return color.mask_ | 8; }
#pragma endregion



#pragma region ConsoleCore
/*!	Facade for the Windows Console API.
*/
class ConsoleCore {
	static HANDLE hInput() { return GetStdHandle(STD_INPUT_HANDLE); }
	static HANDLE hOutput() { return GetStdHandle(STD_OUTPUT_HANDLE); }
	static HANDLE hError() { return GetStdHandle(STD_ERROR_HANDLE); }

public:

	// Code Page Operations
	static std::uint32_t GetInputCodePage();
	static std::uint32_t GetOutputCodePage();
	static void SetInputCodePage(std::uint32_t wCodePageID);
	static void SetOutputCodePage(std::uint32_t wCodePageID);


	// Control Handlers
	static void SetCtrlHandler(PHANDLER_ROUTINE pHandler, bool add);


	// Cursor operations
	static void GetCursorInfo(CONSOLE_CURSOR_INFO& consoleCursorInfo);
	static void SetCursorInfo(CONSOLE_CURSOR_INFO const& consoleCursorInfo);
	static COORD GetCursorPosition();
	static void SetCursorPosition(COORD dwCursorPosition);


	// Input operations
	static std::uint32_t ReadInput(std::vector<INPUT_RECORD>& events);


	// Mode operations
	static std::uint32_t GetMode();
	static void SetMode(std::uint32_t mode);


	// Output operations
	static std::uint32_t FillOutputAttribute(std::uint16_t attribute, std::uint32_t nLength, COORD dwWriteCoord);
	static std::uint32_t FillOutputCharacter(wchar_t cCharacter, std::uint32_t nLength, COORD dwWriteCoord);
	static void ReadOutput(std::vector<CHAR_INFO>& buffer, COORD bufferSize, COORD pos, SMALL_RECT& readRegion);
	static void WriteOutput(std::vector<CHAR_INFO> const& buffer, COORD bufferSize, COORD pos, SMALL_RECT& writeRegion);


	// Title operations
	static std::wstring GetTitle();
	static void GetTitle(std::string& _consoleTitle);
	static void GetTitle(std::wstring& _consoleTitle);
	static void SetTitle(char const * _szConsoleTitle);
	static void SetTitle(wchar_t const* _szConsoleTitle);
	static void SetTitle(std::string const & _consoleTitle);
	static void SetTitle(std::wstring const & _consoleTitle);

	// Window/Buffer operations
	static CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo();
	static CONSOLE_SCREEN_BUFFER_INFOEX GetScreenBufferInfoEx();
	static void GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO& _consoleScreenBufferInfo);
	static void GetScreenBufferInfoEx(CONSOLE_SCREEN_BUFFER_INFOEX& _consoleScreenBufferInfoEx);
	static Attribute GetTextAttribute();
	static void GetTextAttribute(Attribute& attribute);
	static void SetScreenBufferInfoEx(CONSOLE_SCREEN_BUFFER_INFOEX& _consoleScreenBufferInfoEx);
	static void SetScreenBufferSize(COORD size);
	static void SetTextAttribute(Attribute attribute);
	static void SetWindowInfo(BOOL _bAbsolute, SMALL_RECT const& _consoleWindow);
};
#pragma endregion


#pragma region ScopedAttributeState class
class ScopedAttributeState {
	Attribute attribute_m;
public:
	ScopedAttributeState();
	~ScopedAttributeState();
};
#pragma endregion


} // end-of-namespace gats::win32


// Attribute ostream operator
template <typename CHAR_T>
inline std::basic_ostream<CHAR_T>& operator << (std::basic_ostream<CHAR_T>& os, const gats::win32::Attribute& attribute) {
	gats::win32::ConsoleCore::SetTextAttribute(attribute);
	return os;
}
