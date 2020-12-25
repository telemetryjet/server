FileOutputDataSource::FileOutputDataSource(const json &definition): DataSource(definition) {
    state = ACTIVE_OUTPUT_ONLY;
    if (outputFile.is_open()){
        outputFile.close();
    flushTimer.reset();
    DataSource::close();
}