import io.vavr.Function2;
import org.junit.Test;

import java.util.function.BiFunction;
import java.util.function.Function;

import static org.assertj.core.api.Assertions.assertThat;

public class VavrFunctionalInterfacesTest {

    @Test
    public void givenJava8Function_whenWorks_thenCorrect() {
        Function<Integer, Integer> square = (num) -> num*num;
        int result = square.apply(2);
        assertThat(result).isEqualTo(4);
    }

    @Test
    public void givenJava8BiFunction_whenWorks_thenCorrect() {
        BiFunction<Integer, Integer, Integer> sum = (num1, num2) -> num1 + num2;
        int result = sum.apply(5, 7);

        assertThat(result).isEqualTo(12);
    }

    @Test
    public void givenVavrBiFunction_whenWorks_thenCorrect() {
        Function2<Integer, Integer, Integer> sum = (num1, num2) -> num1+num2;
        int result = sum.apply(5, 7);

        assertThat(result).isEqualTo(12);
    }

    public int sum(int a, int b) {
        return a + b;
    }

    @Test
    public void givenVavrBiFunction_wjenWorks_thenCorrect2() {
        Function2<Integer, Integer, Integer> sum = Function2.of(this::sum);
        int summed = sum.apply(5, 6);

        assertThat(summed).isEqualTo(11);
    }
}
