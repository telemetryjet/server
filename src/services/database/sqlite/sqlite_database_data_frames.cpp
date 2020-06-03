#include "sqlite_database.h"
#include <fmt/format.h>

std::vector<record_data_frame_t> SqliteDatabase::getAllDataFrames(int system_id) {
    const std::lock_guard<std::mutex> lock(databaseMutex);  // Acquire database lock for this scope

    std::vector<record_data_frame_t> dataFrames;
    try {
        SQLite::Statement query(*db,
                                fmt::format("select * from data_frames where system_id={}",
                                            system_id));
        while (query.executeStep()) {
            dataFrames.push_back(
                {query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3)});
        }
    } catch (std::exception& e) {
        throwError(fmt::format("Error in getDataFrames: {}", e.what()));
    }
    return dataFrames;
}

std::vector<record_data_frame_t>
SqliteDatabase::getDataFrames(int system_id, long long before, long long after) {
    const std::lock_guard<std::mutex> lock(databaseMutex);  // Acquire database lock for this scope

    std::vector<record_data_frame_t> dataFrames;
    try {
        std::string whereConditions = fmt::format("system_id={}", system_id);
        if (before != -1) {
            whereConditions += fmt::format(" and timestamp < {}", before);
        }
        if (after != -1) {
            whereConditions += fmt::format(" and timestamp > {}", after);
        }
        SQLite::Statement query(*db,
                                fmt::format("select * from data_frames where {}", whereConditions));
        while (query.executeStep()) {
            dataFrames.push_back(
                {query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3)});
        }
    } catch (std::exception& e) {
        throwError(fmt::format("Error in getDataFrames: {}", e.what()));
    }
    return dataFrames;
}

record_data_frame_t SqliteDatabase::getDataFrame(int id) {
    const std::lock_guard<std::mutex> lock(databaseMutex);  // Acquire database lock for this scope

    SQLite::Statement query(*db, "select * from data_frames where id=?");
    query.bind(1, id);
    query.executeStep();
    if (query.hasRow()) {
        return {query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3)};
    } else {
        throwError(fmt::format("Error in getDataFrames: Data Frame with id = {} not found.", id));
    }
}

record_data_frame_t SqliteDatabase::createDataFrame(record_data_frame_t dataFrame) {
    const std::lock_guard<std::mutex> lock(databaseMutex);  // Acquire database lock for this scope

    try {
        SQLite::Statement insertStatement(*db, "insert into data_frames values (null,?,?,?)");
        insertStatement.bind(1, dataFrame.system_id);
        insertStatement.bind(2, dataFrame.timestamp);
        insertStatement.bind(3, dataFrame.data);
        insertStatement.exec();
        dataFrame.id = db->getLastInsertRowid();
        return dataFrame;
    } catch (std::exception& e) {
        throwError(fmt::format("Error in createDataFrame: {}", e.what()));
    }
}

void SqliteDatabase::updateDataFrame(record_data_frame_t dataFrame) {
    const std::lock_guard<std::mutex> lock(databaseMutex);  // Acquire database lock for this scope

    try {
        SQLite::Statement
            updateStatement(*db,
                            "update data_frames set system_id=?, timestamp=?, data=? where id=?");
        updateStatement.bind(1, dataFrame.system_id);
        updateStatement.bind(2, dataFrame.timestamp);
        updateStatement.bind(3, dataFrame.data);
        updateStatement.bind(4, dataFrame.id);
        updateStatement.exec();
    } catch (std::exception& e) {
        throwError(fmt::format("Error in updateDataFrame: {}", e.what()));
    }
}

void SqliteDatabase::deleteAllDataFramesForCurrentSystem() {
    deleteBySystemId("data_frames", record_system_t::getActiveSystem().id);
}