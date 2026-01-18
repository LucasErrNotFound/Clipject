#pragma once
#include <dpp/dpp.h>

class BotCommands {
public:
	static void handleInjectCommand(const dpp::slashcommand_t& event, dpp::cluster& bot);
	static void registerCommands(dpp::cluster& bot);
};