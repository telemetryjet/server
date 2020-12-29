#ifndef TELEMETRYJETCLI_MQTT_CLIENT_H
#define TELEMETRYJETCLI_MQTT_CLIENT_H

#include "core/data_source.h"
#include <mqtt_client_cpp.hpp>

/**
 * "host"
 * "port"
 * "transport": "tcp", "websocket"
 * "tls":
 *  - "caCertFile"
 *  - "certFile"
 *  - "privateKeyFile"
 */
class MqttClientDataSource: public DataSource {
private:
    std::string host;
    uint64_t port = 1883;
    std::string transport = "tcp";
    bool tlsEnabled = false;
    std::string caCertFile;
    std::unique_ptr<boost::asio::io_context> ioContext;
    std::unique_ptr<MQTT_NS::sync_client> client;
public:
    explicit MqttClientDataSource(const json &definition);
    void open() override;
    void close() override;
    void update() override;
};

#endif