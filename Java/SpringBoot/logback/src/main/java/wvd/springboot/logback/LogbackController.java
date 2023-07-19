package wvd.springboot.logback;

import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import wvd.springboot.logback.helper.LoggingHelper;

@RestController
@Slf4j
public class LogbackController {

    @GetMapping("/logback")
    public String logback() {
        new LoggingHelper().helpMethod();
        log.debug("Debug from controller");
        log.info("Info from controller");
        log.warn("Warn from controller");
        return "success";
    }
}
