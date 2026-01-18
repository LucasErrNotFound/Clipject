#include <../include/Cobalt.h>
#include <../include/Config.h>
#include <curl/curl.h>
#include <json/json.h>
#include <sstream>
#include <iostream>

size_t Cobalt::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
	userp->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::pair<bool, std::string> Cobalt::downloadMedia(const std::string& url) {
	CURL* curl = curl_easy_init();
	if (!curl) return { false, "CURL initialization failed" };

	std::string response;
	struct curl_slist* headers = nullptr;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");

	Json::Value requestJson;
	requestJson["url"] = url;
	requestJson["videoQuality"] = "720";
	requestJson["audioFormat"] = "mp3";
	requestJson["filenameStyle"] = "classic";

	Json::StreamWriterBuilder writer;
	std::string requestBody = Json::writeString(writer, requestJson);

	curl_easy_setopt(curl, CURLOPT_URL, BotConfig::COBALT_API.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

	CURLcode res = curl_easy_perform(curl);
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	if (res != CURLE_OK) {
		return { false, "Network error: " + std::string(curl_easy_strerror(res)) };
	}

	std::cout << "API Response: " << response << std::endl;

	Json::CharReaderBuilder reader;
	Json::Value jsonData;
	std::string errs;
	std::istringstream s(response);

	if (!Json::parseFromStream(reader, s, &jsonData, &errs)) {
		return { false, "Failed to parse API response: " + errs };
	}

	if (jsonData.isMember("status") && jsonData["status"].asString() == "error") {
		std::string errorText = jsonData.isMember("error") ?
			jsonData["error"]["code"].asString() : "Unknown error";
		return { false, errorText };
	}

	std::string downloadUrl;
	if (jsonData.isMember("url")) {
		downloadUrl = jsonData["url"].asString();
	}

	if (downloadUrl.empty()) {
		return { false, "No download URL received from API" };
	}

	return { true, downloadUrl };
}
