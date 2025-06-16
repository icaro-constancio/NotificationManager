#include <iostream>        
#include <cstdlib> 
#include <curl/curl.h> 

using namespace std;

bool NotifyDiscord(const string& message) {
    const char* webhook = getenv("DISCORD_WEBHOOK");
    if (!webhook) {
        cerr << "Webhook link not found\n";
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) return false;

    string discordMessage = "{\"content\": \"" + message + "\"}";
    struct curl_slist* headers = curl_slist_append(nullptr, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, webhook);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, discordMessage.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(curl);
    bool success = (result == CURLE_OK);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return success;
}

bool NotifyEmail() {
    const char* userEmail = getenv("USER_EMAIL"); 
    const char* userPassword = getenv("USER_PASSWORD");
    const char* recipientEmail = getenv("RECIPIENT_EMAIL");

    if (!userEmail || !userPassword || !recipientEmail) {
        cerr << "Environment variables not found\n";
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) return false;

    // Basic configurations
    curl_easy_setopt(curl, CURLOPT_USERNAME, userEmail);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, userPassword);
    curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");

    // Define sender and recipient
    string sender = "<" + string(userEmail) + ">";
    string recipient = "<" + string(recipientEmail) + ">";
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, sender.c_str());
    struct curl_slist* recipientsList = curl_slist_append(nullptr, recipient.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipientsList);

    // Create the email body
    string body = "testing.";
    string subject = "Subject: Test Email";
    struct curl_slist* headers = curl_slist_append(nullptr, subject.c_str());

    curl_mime* mime = curl_mime_init(curl);
    curl_mimepart* part = curl_mime_addpart(mime);
    curl_mime_data(part, body.c_str(), CURL_ZERO_TERMINATED);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode result = curl_easy_perform(curl);
    bool success = (result == CURLE_OK);

    // Free memory
    curl_slist_free_all(recipientsList);
    curl_slist_free_all(headers);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    return success;
}

int main() {
    char option;
    cout << "Key d - Notify Discord\n";
    cout << "Key e - Notify Email\n";
    cout << "Key 0 - Exit\n";

    do {
        cout << "\nPress a key: ";
        cin >> option;

        switch (tolower(option)) {
            case 'd':
                if (NotifyDiscord("Test"))
                    cout << "Notification sent\n";
                else
                    cout << "Notification not sent\n";
                break;

            case 'e':
                if (NotifyEmail())
                    cout << "Email sent\n";
                else
                    cout << "Email not sent\n";
                break;

            case '0':
                cout << "Terminated\n";
                break;

            default:
                cout << "Invalid option, please choose another one\n";
        }

    } while(option != '0');

    return 0;
}
