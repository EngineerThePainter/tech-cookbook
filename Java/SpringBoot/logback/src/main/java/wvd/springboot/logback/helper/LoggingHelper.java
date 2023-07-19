package wvd.springboot.logback.helper;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class LoggingHelper {
    public void helpMethod() {
        log.debug("This is debug");
        log.info("This is info");
        log.warn("This is warn");
        log.error("This is error");
    }
}
