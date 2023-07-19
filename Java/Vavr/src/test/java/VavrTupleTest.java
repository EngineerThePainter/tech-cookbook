import io.vavr.Tuple;
import io.vavr.Tuple2;
import io.vavr.Tuple3;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VavrTupleTest {

    @Test
    public void thenCreatesTuple_thenCorrect1() {
        Tuple2<String, Integer> java8 = Tuple.of("Java", 8);
        String element = java8._1;
        int element2 = java8._2;
        assertThat(element).isEqualTo("Java");
        assertThat(element2).isEqualTo(8);
    }

    @Test
    public void thenCreatesTuple_thenCorrect2() {
        Tuple3<String, Integer, Double> java8 = Tuple.of("Java", 8, 1.8);
        String element1 = java8._1;
        int element2 = java8._2;
        double element3 = java8._3;

        assertThat(element1).isEqualTo("Java");
        assertThat(element2).isEqualTo(8);
        assertThat(element3).isEqualTo(1.8);
    }
}
