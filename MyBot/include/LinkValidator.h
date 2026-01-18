#pragma once
#include <string>

class LinkValidator {
public:
	static bool isValidMediaLink(const std::string& url);
	static bool isInstagram(const std::string& url);
	static bool isFacebook(const std::string& url);
	static bool isTiktok(const std::string& url);
};