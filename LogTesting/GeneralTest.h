#if defined(TEST_METHOD_NAME) && defined(LOG_CONCURRENCY_LEVEL)
TEST(GeneralTest, TEST_METHOD_NAME) {
    constexpr int NUM_OF_MSG = 1000;
    const char *msg1 = "it is a test";
    const char *msg2 = "and is going to success";
    std::string runCmd("python TestOutput.py ");
    {
        XmlLogger xml;
        xml.load("Log.config");
        Logger log(xml, 0, LOG_CONCURRENCY_LEVEL);
        runCmd.append("Sys.log ");
        runCmd.append(std::to_string(NUM_OF_MSG));
        runCmd.append(" ");
        runCmd.append(std::to_string(getPid()));
        runCmd.append(" ");
        runCmd.append(std::to_string(getTid()));
        runCmd.append(" ");
        runCmd.append(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        runCmd.append(" RollingFileAppender ");
        runCmd.append("info \"");
        runCmd.append(msg1);
        runCmd.append("\" fatal \"");
        runCmd.append(msg2);
        runCmd.append("\" debug \"");
        runCmd.append(msg1);
        runCmd.append("\" info \"");
        runCmd.append(msg2);
        runCmd.append("\"");
        for (size_t i = 0; i < NUM_OF_MSG / 4; i++) {
            log.info(msg1);
            log.log(6, msg2);
            log.debug(msg1);
            log.log("info", msg2);
        }
    }
    std::string output;
    int ret = exec(runCmd.c_str(), output);
    ASSERT_EQ(0, ret) << output;
}
#endif