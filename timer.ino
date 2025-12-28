// Include time Library
#include <time.h>

// Timezone Settings
// Central European Time (Berlin) with automatic Daylight Savings
const char* TZ_INFO = "CET-1CEST,M3.5.0,M10.5.0/3";

// Initialize NTP time and timezone
void timerInit() {
    // Configure NTP
    // Offsets are 0 because TZ_INFO handles daylight savings
    configTime(0, 0, "pool.ntp.org");

    // Set timezone environment
    setenv("TZ", TZ_INFO, 1);
    tzset();
}

// Check if the current local time matches a target
// targetH = target hour, targetM = target minute, targetS = target second
// Returns true only if the target time matches and it hasn't been triggered yet
bool isTime(int targetH, int targetM, int targetS) {
    struct tm timeinfo;

    // Get current local time
    if (!getLocalTime(&timeinfo)) return false;

    bool match = (timeinfo.tm_hour == targetH &&
                  timeinfo.tm_min  == targetM &&
                  timeinfo.tm_sec  == targetS);

    // Prevent multiple triggers in the same second
    if (match) {
        return true;
    }

    return false;
}

String getTimeString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return "00:00";

    char buffer[6];
    sprintf(buffer, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
    return String(buffer);
}