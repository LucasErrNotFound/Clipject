#pragma once
#include <string>
#include <utility>

class Cobalt {
public:
	static std::pair<bool, std::string> downloadMedia(const std::string& url);

private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};