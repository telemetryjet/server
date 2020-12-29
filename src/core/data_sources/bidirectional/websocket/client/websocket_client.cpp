#include "websocket_client.h"

WebsocketClientDataSource::WebsocketClientDataSource(const json& definition)
    : DataSource(definition)
    , path(getServerPath())
    , client(path) {
}

void WebsocketClientDataSource::open() {
    client.on_open = [this](const std::shared_ptr<WsClient::Connection>& connection) {
        wsConnection = connection;
        SM::getLogger()->info(
            fmt::format("Opened websocket client connection to server at {}.", path));
    };

    client.on_close = [this](const std::shared_ptr<WsClient::Connection>& connection,
                             int status,
                             const std::string& reason) {
        wsConnection.reset();
        SM::getLogger()->info(
            fmt::format("Closed websocket client connection to server at {} with status code {}.",
                        path,
                        status));
    };

    client.on_error = [this](const std::shared_ptr<WsClient::Connection>& connection,
                             const SimpleWeb::error_code& ec) {
        SM::getLogger()->error(
            fmt::format("Error in websocket client connection to server at {}. {}",
                        path,
                        ec.message()));
    };

    client.on_message = [this](const std::shared_ptr<WsClient::Connection>& connection,
                               const std::shared_ptr<WsClient::InMessage>& message) {
        auto jsonObj = json::parse(message->string());
        if (!jsonObj.contains("key") || !jsonObj.contains("timestamp") || !jsonObj.contains("value")
            || !jsonObj.contains("type")) {
            throw std::runtime_error(
                fmt::format("Unable to parse message from websocket server: {}",
                            message->string()));
        }
        write(createDataPointFromString(jsonObj["key"], jsonObj["timestamp"], jsonObj["value"]));
    };

    client.start();
    DataSource::open();
}

void WebsocketClientDataSource::close() {
    wsConnection->send_close(1000);
    DataSource::close();
}

void WebsocketClientDataSource::update() {
    // send incoming data points to ws server
    if (!in.empty()) {
        for (auto& dp : in) {
            wsConnection->send(dp->toJson());
        }

        // TODO: write to sql cache when ws server is offline
    }
}

std::string WebsocketClientDataSource::getServerPath() {
    if (!options.contains("server_port_path")) {
        throw std::runtime_error("Websocket client data source requires server_port_path option.");
    }

    return options["server_port_path"];
}