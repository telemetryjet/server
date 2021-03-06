#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <ctime>
#include <iostream>
#include <chrono>
#include <locale>

/*
 * Gets a timestamp as milliseconds since epoch.
 */
inline uint64_t getCurrentMillis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}

inline std::string getTimestamp() {
    std::time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer, sizeof(buffer), "%m/%d/%y %H:%M:%S", timeinfo);
    std::string str(buffer);
    return str;
}

inline std::pair<std::string, std::string> getAwsTimestamps() {
    std::time_t rawtime;
    struct tm* timeinfo;
    char buffer1[80];
    char buffer2[80];

    std::time(&rawtime);
    timeinfo = std::gmtime(&rawtime);

    std::strftime(buffer1, sizeof(buffer1), "%Y%m%dT%H%M%SZ", timeinfo);
    std::strftime(buffer2, sizeof(buffer2), "%Y%m%d", timeinfo);
    std::string str1(buffer1);
    std::string str2(buffer2);
    return std::make_pair(str1, str2);
}


#endif