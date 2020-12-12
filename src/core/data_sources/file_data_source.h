#ifndef TELEMETRYJETCLI_FILE_DATA_SOURCE_H
#define TELEMETRYJETCLI_FILE_DATA_SOURCE_H

#include "core/data_source.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <regex>
#include "utility/timer/simple_timer.h"

class FileDataSource : public DataSource {
protected:
    std::ofstream outputFile;
    std::string filename;
    std::ios::openmode mode;
    std::string modeString;
    bool generateNewFile;
    SimpleTimer* flushTimer;
public:
    FileDataSource(const std::string& id, const std::string& type, const json &options);
    ~FileDataSource() override;
    void open() override;
    void close() override;
    bool isOpen() override;
};

#endif
