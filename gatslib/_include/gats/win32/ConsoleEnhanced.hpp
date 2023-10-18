#pragma once
/*	gats/win32/ConsoleApp/ConsoleEnhanced.hpp

	ConsoleEnhanced class declaration.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.08.29
	C++ 17 version
	Added to gats::win32 namespace

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


#include <gats/win32/ConsoleApp/ConsoleCore.hpp>
#include <string>
#include <vector>



namespace gats::win32 {

	class ConsoleEnhanced {
		// non-copyable
		ConsoleEnhanced(ConsoleEnhanced const&) = delete;
		ConsoleEnhanced(ConsoleEnhanced&&) = delete;
		ConsoleEnhanced& operator = (ConsoleEnhanced const&) = delete;
		ConsoleEnhanced& operator = (ConsoleEnhanced&&) = delete;

	public: // TYPES
		using string_type = std::wstring;

		class State {
			friend class ConsoleEnhanced;
			string_type						consoleTitle_;
			CONSOLE_SCREEN_BUFFER_INFOEX	screenBufferInfoEx_;
			std::vector<CHAR_INFO>			screenBuffer_;
			CONSOLE_CURSOR_INFO				cursorInfo_;
			UINT							wOutputCodePageID_;
			UINT							wInputCodePageID_;
		};

	public:
		// Constructors
		ConsoleEnhanced() = default;

		// State Management
		State GetState() const;
		ConsoleEnhanced& SetState(State const& _state);

		// Window/Buffer operations
		ConsoleEnhanced& Clear();
		ConsoleEnhanced& Clear(Attribute attr);
		ConsoleEnhanced& SetSize(std::uint16_t width, std::uint16_t height);

		// ConsoleCore operations
		template <typename STRING_REF> inline ConsoleEnhanced& SetTitle(STRING_REF const& _title) { ConsoleCore::SetTitle(_title); return *this; }
		template <typename STRING_PTR> inline ConsoleEnhanced& SetTitle(STRING_PTR const * _szConsoleTitle) { ConsoleCore::SetTitle(_szConsoleTitle); return *this; }
	};
} // End-of-namespace gats::win32
