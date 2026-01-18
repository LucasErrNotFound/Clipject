#pragma once
#include <string>

class ClipDownloader {
public:
	static bool downloadFile(const std::string& url, const std::string& filepath);
	static std::string getAbsolutePath(const std::string& filepath);
	static size_t WriteDataCallback(void* ptr, size_t size, size_t nmemb, FILE* stream);
};