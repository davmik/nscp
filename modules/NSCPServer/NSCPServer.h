/**************************************************************************
*   Copyright (C) 2004-2007 by Michael Medin <michael@medin.name>         *
*                                                                         *
*   This code is part of NSClient++ - http://trac.nakednuns.org/nscp      *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include <socket_helpers.hpp>
#include <nscp/server/server.hpp>

NSC_WRAPPERS_MAIN();

class NSCPListener : public nscapi::impl::simple_plugin {
private:
	typedef enum {
		inject, script, script_dir,
	} command_type;
	struct command_data {
		command_data() : type(inject) {}
		command_data(command_type type_, std::wstring arguments_) : type(type_), arguments(arguments_) {}
		command_type type;
		std::wstring arguments;
	};

	nscp::server::server::connection_info info_;

public:
	NSCPListener();
	virtual ~NSCPListener();
	// Module calls
	bool loadModule();
	bool loadModuleEx(std::wstring alias, NSCAPI::moduleLoadMode mode);
	bool unloadModule();


	std::wstring getModuleName() {
#ifdef USE_SSL
		return _T("NSCP server");
#else
		return _T("NSCP server (no SSL)");
#endif
	}
	nscapi::plugin_wrapper::module_version getModuleVersion() {
		nscapi::plugin_wrapper::module_version version = {0, 0, 1 };
		return version;
	}
	std::wstring getModuleDescription() {
		return _T("A simple server that listens for incoming NSCP connection and handles them.");
	}

	bool hasCommandHandler();
	bool hasMessageHandler();
	NSCAPI::nagiosReturn handleCommand(const strEx::blindstr command, const unsigned int argLen, wchar_t **char_args, std::wstring &message, std::wstring &perf);
	std::wstring getConfigurationMeta();
	boost::shared_ptr<nscp::server::server> server_;
};

