#include <services/ServiceManager.h>
#include <iostream>
#include <utility/timeUtils.h>
#include <fmt/format.h>

/**
 * Main Program Entry Point
 * Starts and runs the server loop.
 */

int exitCode = 0;
bool running = true;

void signalHandler(int signum) {
    running = false;
}

int main() {
    long long startInit = getCurrentMillis();

    std::cout << "  _ _  ______  __     __\n";
    std::cout << "  __  /_  __/ / /__  / /_\n";
    std::cout << "   ___ / /_  / / _ \\/ __/\n";
    std::cout << "  __  / / /_/ /  __/ /_\n";
    std::cout << " _ _ /_/\\____/\\___/\\__/\n";
    std::cout << "TelemetryJet Server v0.1.0\n";
    std::cout << "--------------------------\n";

            signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // Initialize the common services.
    ServiceManager::init();

    long long elapsedInitTime = getCurrentMillis() - startInit;

    ServiceManager::getLogger()->info(fmt::format("Started Telemetry Server in {} ms.",elapsedInitTime));

    // Run the server loop
    while (running) {
    }

    ServiceManager::getLogger()->info("Stopping Telemetry Server...");

    // Shutdown the common services
    ServiceManager::destroy();

    // Exit main program
    std::cout << "Done.\n";
    return exitCode;
}