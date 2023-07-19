package wvd.springboot.sleuth;

import brave.Span;
import brave.Tracer;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class SleuthService {

    @Autowired
    private Tracer tracer;

    public void doSomeWorkSameSpan() throws InterruptedException {
        log.info("In a new span doing cool stuff...");
        Thread.sleep(1000L);
    }

    public void doSomeWorkNewSpan() throws InterruptedException {
        log.info("I'm in the original span");

        Span newSpan = tracer.nextSpan().name("newSpan").start();
        try (Tracer.SpanInScope ws = tracer.withSpanInScope(newSpan.start())) {
            Thread.sleep(1000L);
            log.info("In a new span doing cool stuff...");
        } finally {
            newSpan.finish();
        }

        log.info("I'm in the original span");
    }

    @Async
    public void asyncMethod() throws InterruptedException {
        log.info("Start async method");
        Thread.sleep(1000L);
        log.info("End async method");
    }
}
