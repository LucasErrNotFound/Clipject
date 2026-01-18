#include <../include/LinkValidator.h>
#include <regex>
#include <vector>

bool LinkValidator::isValidMediaLink(const std::string& url) {
	return isInstagram(url) || isTiktok(url) || isFacebook(url);
}

bool LinkValidator::isFacebook(const std::string& url) {
	std::regex pattern(R"(^(https?://)?(www\.)?(facebook\.com|fb\.watch)/(watch/\?v=|reel/|share/r/|[\w.-]+/videos/)[\w-]+)");
	return std::regex_search(url, pattern);
}

bool LinkValidator::isInstagram(const std::string& url) {
	std::regex pattern(R"(^(https?://)?(www\.)?instagram\.com/(p|reel|tv)/[\w-]+)");
	return std::regex_search(url, pattern);
}

bool LinkValidator::isTiktok(const std::string& url) {
	std::regex pattern(R"(^(https?://)?(www\.)?(tiktok\.com/@[\w.-]+/video/\d+|vm\.tiktok\.com/[\w-]+|vt\.tiktok\.com/[\w-]+))");
	return std::regex_search(url, pattern);
}
