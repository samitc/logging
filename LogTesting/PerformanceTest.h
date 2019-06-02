#if defined(TEST_LOAD_METHOD_NAME) && defined(TEST_DELAY_METHOD_NAME) && defined(LOG_CONCURRENCY_LEVEL) && defined(LOAD_THRESHOLD) && defined(DELAY_THRESHOLD)
using ChronoClock=std::chrono::high_resolution_clock;
TEST(PerformanceTest, TEST_LOAD_METHOD_NAME) {
    XmlLogger xml;
    xml.load("Log.config");
    constexpr int PERFORMANCE_TEST_NUM_OF_MSG = 40000;
    const char* msg1 = "it is a test";
    const char* msg2 = "and is going to success";
    auto start = ChronoClock::now();
    {
        Logger log(xml, 0, LOG_CONCURRENCY_LEVEL);
        for (size_t i = 0; i < PERFORMANCE_TEST_NUM_OF_MSG / 4; i++)
        {
            log.info(msg1);
            log.log(6, msg2);
            log.debug(msg1);
            log.log("info", msg2);
        }
    }
    auto end = ChronoClock::now();
    constexpr double msgPerMilisec = LOAD_THRESHOLD;
    double diff = std::chrono::duration<double, std::milli>(end - start).count();
    std::string error;
    error.append("Log load test.\ntook: ");
    error.append(std::to_string(diff));
    error.append(" milisecond to complete.\nthe freq was: ");
    error.append(std::to_string(PERFORMANCE_TEST_NUM_OF_MSG / diff));
    std::cout << error.c_str() << std::endl;
    ASSERT_TRUE((double)PERFORMANCE_TEST_NUM_OF_MSG / diff > msgPerMilisec);
}
TEST(PerformanceTest, TEST_DELAY_METHOD_NAME) {
    XmlLogger xml;
    xml.load("Log.config");
    Logger log(xml, 0, LOG_CONCURRENCY_LEVEL);
    constexpr int PERFORMANCE_TEST_NUM_OF_MSG = 40000;
    const char* msg1 = "it is a test";
    const char* msg2 = "and is going to success";
    auto sum = ChronoClock::duration::zero();
    for (size_t i = 0; i < PERFORMANCE_TEST_NUM_OF_MSG / 4; i++) {
        auto a = ChronoClock::now();
        log.info(msg1);
        auto b = ChronoClock::now();
        sum += b - a;
        a = ChronoClock::now();
        log.log(6, msg2);
        b = ChronoClock::now();
        sum += b - a;
        a = ChronoClock::now();
        log.debug(msg1);
        b = ChronoClock::now();
        sum += b - a;
        a = ChronoClock::now();
        log.log("info", msg2);
        b = ChronoClock::now();
        sum += b - a;
    }
    constexpr double delayInMili = DELAY_THRESHOLD;
    std::string error;
    error.append("Log delay test.\nthe delay is: ");
    error.append(std::to_string(std::chrono::duration<double, std::milli>(sum).count() / PERFORMANCE_TEST_NUM_OF_MSG));
    std::cout << error.c_str() << std::endl;
    ASSERT_TRUE((std::chrono::duration<double, std::milli>(sum).count() / PERFORMANCE_TEST_NUM_OF_MSG) < delayInMili);
}
TEST(PerformanceTest, TEST_WRITE_DELAY_METHOD_NAME) {
    char indexBuf[21];
    XmlLogger xml;
    xml.load("Log.config");
    NetworkWriterMock* writer = new NetworkWriterMock("127.0.0.1", 44555, Protocol::UDP);
    constexpr int PERFORMANCE_TEST_NUM_OF_MSG = 40000;
    std::atomic<bool> isDone(false);
    std::mutex m;
    std::condition_variable cv;
    ChronoClock::time_point startTimes[PERFORMANCE_TEST_NUM_OF_MSG];
    ChronoClock::time_point endTimes[PERFORMANCE_TEST_NUM_OF_MSG];
    writer->setCallbackBeforeWrite([&isDone, &cv, &endTimes, PERFORMANCE_TEST_NUM_OF_MSG](const char* text) {
        auto endTime = ChronoClock::now();
        int writeNum = atoi(findMessage(text));
        endTimes[writeNum] = endTime;
        if (writeNum == PERFORMANCE_TEST_NUM_OF_MSG - 1)
        {
            isDone = true;
            cv.notify_one();
        }
    });
    LoggerData loggerData(&xml, 0);
    StreamParam sp;
    sp.streamType = StreamType::NONE;
    sp.customWriter = writer;
    loggerData.setStreamParam(sp);
    {
        Logger log(loggerData, 0, LOG_CONCURRENCY_LEVEL);
        for (size_t i = 0; i < PERFORMANCE_TEST_NUM_OF_MSG / 4; i++)
        {
            startTimes[i * 4 + 0] = ChronoClock::now();
            log.info(itoa(i * 4 + 0, indexBuf, 10));
            startTimes[i * 4 + 1] = ChronoClock::now();
            log.log(6, itoa(i * 4 + 1, indexBuf, 10));
            startTimes[i * 4 + 2] = ChronoClock::now();
            log.debug(itoa(i * 4 + 2, indexBuf, 10));
            startTimes[i * 4 + 3] = ChronoClock::now();
            log.log("info", itoa(i * 4 + 3, indexBuf, 10));
        }
    }
    if (!isDone)
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [&isDone, PERFORMANCE_TEST_NUM_OF_MSG]() {
            return isDone.load();
        });
    }
    auto sum = ChronoClock::duration::zero();
    for (size_t i = 0; i < PERFORMANCE_TEST_NUM_OF_MSG; i++)
    {
        sum += endTimes[i] - startTimes[i];
    }
    constexpr double delayInMili = WRITE_DELAY_THRESHOLD;
    std::string error;
    error.append("Log delay test.\nthe delay is: ");
    error.append(std::to_string(std::chrono::duration<double, std::milli>(sum).count() / PERFORMANCE_TEST_NUM_OF_MSG));
    std::cout << error.c_str() << std::endl;
    ASSERT_TRUE((std::chrono::duration<double, std::milli>(sum).count() / PERFORMANCE_TEST_NUM_OF_MSG) < delayInMili);
}
#endif