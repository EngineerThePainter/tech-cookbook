package wvd.springboot.sleuth;

import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.concurrent.Executor;

@RestController
@Slf4j
public class SleuthController {

    private final SleuthService sleuthService;
    private final Executor executor;

    @Autowired
    public SleuthController(SleuthService sleuthService, Executor executor) {
        this.sleuthService = sleuthService;
        this.executor = executor;
    }

    @RequestMapping("/")
    public String home() {
        log.info("Handling home");
        return "Hello World";
    }

    @SneakyThrows
    @RequestMapping("/same-span")
    public String helloSleuthSameSpan() {
        log.info("Same span");
        sleuthService.doSomeWorkSameSpan();
        return "success";
    }

    @SneakyThrows
    @RequestMapping("/new-span")
    public String helloSleuthNewSpan() {
        log.info("New span");
        sleuthService.doSomeWorkNewSpan();
        return "success";
    }

    @RequestMapping("/new-thread")
    public String helloSleuthNewThread() {
        log.info("New thread");
        Runnable runnable = () -> {
            try {
                Thread.sleep(1000L);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            log.info("I'm inside the new thread - with a new span");
        };
        executor.execute(runnable);
        log.info("Done with the original span again");
        return "success";
    }

    @GetMapping("/async")
    public String helloSleuthAsync() throws InterruptedException {
        log.info("Before async method call");
        sleuthService.asyncMethod();
        log.info("After async method call");
        return "success";
    }
}
