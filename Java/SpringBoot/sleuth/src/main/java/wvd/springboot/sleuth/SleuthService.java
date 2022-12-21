package wvd.springboot.sleuth;

import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class SleuthService {
    @SneakyThrows
    public void doSomeWorkSameSpan() {
        Thread.sleep(1000L);
        log.info("Doing some work");
    }
}
