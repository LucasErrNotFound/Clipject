#include "include/Config.h"
#include "include/BotCommands.h"
#include <dpp/dpp.h>

int main() {
	dpp::cluster bot(BotConfig::BOT_TOKEN);
	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "inject") {
			BotCommands::handleInjectCommand(event, bot);
		}
	});

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			BotCommands::registerCommands(bot);
		}
	});

	bot.start(dpp::st_wait);
	return 0;
}