#include <../include/ClipDownloader.h>
#include <curl/curl.h>
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <limits.h>
	#include <stdlib.h>
#endif

size_t ClipDownloader::WriteDataCallback(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	return fwrite(ptr, size, nmemb, stream);
}

bool ClipDownloader::downloadFile(const std::string& url, const std::string& filepath) {
	CURL* curl = curl_easy_init();
	if (!curl) return false;

	FILE* fp = nullptr;
#ifdef _WIN32
	errno_t err = fopen_s(&fp, filepath.c_str(), "wb");
	if (err != 0 || !fp) {
#else
	fp = fopen(filepath.c_str(), "wb");
	if (!fp) {
#endif
		curl_easy_cleanup(curl);
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	CURLcode res = curl_easy_perform(curl);

	fclose(fp);
	curl_easy_cleanup(curl);

	if (res == CURLE_OK) {
		std::string absPath = getAbsolutePath(filepath);
		std::cout << "✅ Downloaded to: " << absPath << std::endl;
	}

	return (res == CURLE_OK);
}

std::string ClipDownloader::getAbsolutePath(const std::string & filepath) {
#ifdef _WIN32
	char absolutePath[MAX_PATH];
	if (_fullpath(absolutePath, filepath.c_str(), MAX_PATH) != nullptr) {
		return std::string(absolutePath);
	}
#else
	char absolutePath[PATH_MAX];
	if (realpath(filepath.c_str(), absolutePath) != nullptr) {
		return std::string(absolutePath);
	}
#endif
	return filepath + " (relative path)";
}