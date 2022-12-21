package wvd.springboot.sleuth;

import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Slf4j
public class SleuthController {

    @Autowired
    private SleuthService sleuthService;

    @RequestMapping("/")
    public String home() {
        log.info("Handling home");
        return "Hello World";
    }

    @RequestMapping("/same-span")
    public String helloSleuthSameSpan() throws InterruptedException {
        log.info("Same span");
        sleuthService.doSomeWorkSameSpan();
        return "success";
    }
}
