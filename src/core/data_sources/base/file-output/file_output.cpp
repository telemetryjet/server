        throw std::runtime_error(fmt::format("[{}] data source type '{}' requires an options object", id, type));
        throw std::runtime_error(fmt::format("[{}] data source type '{}' requires option 'filename' of type String", id, type));
        throw std::runtime_error(fmt::format("[{}] data source type '{}' requires option 'mode' of type String", id, type));
        throw std::runtime_error(fmt::format("[{}] data source type '{}' has invalid value for 'mode': {}", id, type, modeString));
    assertDependency("file", filename, fmt::format("[{}] Multiple data sources cannot share the same input/output filename: {}", id, filename));
        SM::getLogger()->error(fmt::format("[{}] Failed to open file {}", id, pathObj.filename().string()));
        throw std::runtime_error(fmt::format("[{}] Failed to open file {}", id, pathObj.filename().string()));
        SM::getLogger()->info(fmt::format("[{}] Opened file {}", id, pathObj.filename().string()));