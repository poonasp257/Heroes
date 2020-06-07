#include "stdafx.h"

HttpRequest::HttpRequest() 
    : curlContext(curl_easy_init()) {
    httpHeaderList = curl_slist_append(httpHeaderList, "Content-Type: application/json");
    curl_easy_setopt(curlContext, CURLOPT_HTTPHEADER, httpHeaderList);
    curl_easy_setopt(curlContext, CURLOPT_NOSIGNAL, 1L);
}

HttpRequest::~HttpRequest() {
	if (curlContext) curl_easy_cleanup(curlContext);

    curl_slist_free_all(httpHeaderList);
}

size_t HttpRequest::writeCallback(void* ptr, size_t size, size_t count, void* buffer) {
    auto newBuffer = reinterpret_cast<std::string*>(buffer);
    auto receiveBuffer = reinterpret_cast<char*>(ptr);
    newBuffer->append(receiveBuffer, 0, size * count);
    return size * count;
}

size_t HttpRequest::readCallback(void* ptr, size_t size, size_t count, void* buffer) {
    // Implement...
    return 0;
}

bool HttpRequest::Get(const std::string& url, HttpForm form, std::string& buffer) {
    if (curlContext == nullptr) throw std::runtime_error("CurlContext doesn't exist");

    curl_easy_setopt(curlContext, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlContext, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curlContext, CURLOPT_WRITEFUNCTION, &HttpRequest::writeCallback);
    curl_easy_setopt(curlContext, CURLOPT_WRITEDATA, (void*)&buffer);

    CURLcode result = curl_easy_perform(curlContext);
    if (result != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        return false;
    }

    return true;
}

bool HttpRequest::Post(const std::string& url, HttpForm form, HttpCallback callBack) {
    if (curlContext == nullptr) throw std::runtime_error("CurlContext doesn't exist");

    std::string jsonData = form.getJsonData();
    curl_easy_setopt(curlContext, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlContext, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curlContext, CURLOPT_POSTFIELDS, jsonData.c_str());

    std::string buffer;
    curl_easy_setopt(curlContext, CURLOPT_WRITEFUNCTION, &HttpRequest::writeCallback);
    curl_easy_setopt(curlContext, CURLOPT_WRITEDATA, (void*)&buffer);

    CURLcode result = curl_easy_perform(curlContext);
    if (result != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        return false;
    }

    if(callBack) callBack(buffer);

    return true;
}