import io.vavr.control.Try;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VavrTryTest {

    @Test(expected = ArithmeticException.class)
    public void givenBadCode_thenThrowException_thenCorrect() {
        int i = 1 / 0;
    }

    @Test
    public void givenBadCode_thenTryHandles_thenCorrect() {
        Try<Integer> result = Try.of(() -> 1/0);
        assertThat(result.isFailure()).isTrue();
    }

    @Test
    public void givenBadCode_whenTryHandles_thenCorrect2() {
        Try<Integer> computation = Try.of(() -> 1/0);
        int errorSentinel = computation.getOrElse(-1);
        assertThat(errorSentinel).isEqualTo(-1);
    }

    @Test(expected = ArithmeticException.class)
    public void givenBadCode_whenTryHandles_thenCorrect3() {
        Try<Integer> result = Try.of(() -> 1/0);
        result.getOrElseThrow(throwable -> new ArithmeticException());
    }
}
