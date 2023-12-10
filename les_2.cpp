
#include <iostream>
#include <curl.h>
using namespace std;
// Callback function to handle the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {







    // Initialize cURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error initializing cURL." << std::endl;
        return 1;
    }

    // Set the URL for the GET request
    string url;
    cin>>url;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set up a string to store the response
    std::string response;

    // Set the callback function to receive the response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Disable SSL verification (for testing purposes only)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    // Perform the HTTP GET request
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        // Print the response
        std::cout << "Response:\n" << response << std::endl;
    }

    // Clean up
    curl_easy_cleanup(curl);

    return 0;
}
