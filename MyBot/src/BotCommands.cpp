#include "../include/BotCommands.h"
#include "../include/Config.h"
#include "../include/LinkValidator.h"
#include "../include/Cobalt.h"
#include "../include/ClipDownloader.h"
#include <ctime>

void BotCommands::handleInjectCommand(const dpp::slashcommand_t& event, dpp::cluster& bot) {
	std::string link = std::get<std::string>(event.get_parameter("link"));
	event.reply(dpp::message("🔍 Validating link...").set_flags(dpp::m_ephemeral));

	// Validate link
	if (!LinkValidator::isValidMediaLink(link)) {
		event.edit_original_response(dpp::message("❌ Invalid link! Supported: Instagram, TikTok, Facebook"));
		return;
	}

	// Update status
	event.edit_original_response(dpp::message("📥 Downloading media from API..."));

	// Get download URL from API
	auto [success, result] = Cobalt::downloadMedia(link);
	if (!success) {
		event.edit_original_response(dpp::message("❌ Error: " + result));
		return;
	}

	// Download file
	std::string filename = BotConfig::DOWNLOAD_DIR + "media_" +
		std::to_string(time(nullptr)) + ".mp4";
	event.edit_original_response(dpp::message("💾 Downloading file..."));

	if (!ClipDownloader::downloadFile(result, filename)) {
		event.edit_original_response(dpp::message("❌ Failed to download the media file"));
		return;
	}

	// Send file to Discord
	event.edit_original_response(dpp::message("📤 Uploading to Discord..."));

	dpp::user author = event.command.get_issuing_user();
	dpp::message msg(event.command.channel_id, author.get_mention() + " has injected a clip!");
	msg.add_file(filename, dpp::utility::read_file(filename));

	bot.message_create(msg, [filename, event](const dpp::confirmation_callback_t& callback) mutable {
		// Clean up file after sending
		if (!BotConfig::KEEP_DOWNLOADED_FILES) {
			std::remove(filename.c_str());
		}

		if (callback.is_error()) {
			event.edit_original_response(dpp::message("❌ Failed to send file to Discord"));
		}
		else {
			event.edit_original_response(dpp::message("✅ Media injected successfully!"));
		}
	});
}

void BotCommands::registerCommands(dpp::cluster& bot) {
	dpp::slashcommand cmd("inject", "Download and inject media from social platforms", bot.me.id);
	cmd.add_option(dpp::command_option(dpp::co_string, "link", "Instagram, TikTok, or Facebook link", true));
	bot.global_command_create(cmd);
}