#ifndef TELEMETRYSERVER_CONSTANTS_H
#define TELEMETRYSERVER_CONSTANTS_H

#define TELEMETRYJET_VERSION "0.1.0"

// streaming server
#define INCOMING_MESSAGE_TYPE_KEY "message_type"
#define INCOMING_MESSAGE_BODY_KEY "body"

#define OUTGOING_MESSAGE_TYPE_KEY "message_type"
#define OUTGOING_MESSAGE_BODY_KEY "body"

// rest api server
#define LIMIT_QUERY_PARAM "limit"
#define BEFORE_ID_QUERY_PARAM "before_id"
#define BEFORE_QUERY_PARAM "before"
#define AFTER_QUERY_PARAM "after"
#define KEY_QUERY_PARAM "key"

// log levels
#define LOG_LEVEL_HEADER "header"
#define LOG_LEVEL_DEBUG "debug"
#define LOG_LEVEL_INFO "info"
#define LOG_LEVEL_WARNING "warning"
#define LOG_LEVEL_ERROR "error"
#define LOG_LEVEL_ALERT "alert"
#define LOG_LEVEL_NONE "none"

#endif
