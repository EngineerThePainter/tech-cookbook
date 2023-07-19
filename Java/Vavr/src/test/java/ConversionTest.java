import io.vavr.collection.HashSet;
import io.vavr.collection.List;
import io.vavr.collection.Set;
import org.junit.Test;

import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import static org.assertj.core.api.Assertions.assertThat;

public class ConversionTest {

    @Test
    public void javaToVavr() {
        java.util.List<Integer> javaList = Arrays.asList(1,2,3,4);
        List<Integer> vavrList = List.ofAll(javaList);
        Stream<Integer> javaStream = javaList.stream();
        Set<Integer> vavrSet = HashSet.ofAll(javaStream);

        List<Integer> vavrList2 = IntStream.range(1, 10)
                .boxed()
                .filter(integer -> integer%2 == 0)
                .collect(List.collector());
        assertThat(vavrList2.size()).isEqualTo(4);
        assertThat(vavrList2.head()).isEqualTo(2);
    }

    @Test
    public void vavrToJava() {
        Integer[] array = List.of(1,2,3)
                .toJavaArray(Integer[]::new);

        java.util.Set<Integer> javaSet = List.of(1,2,3)
                .collect(Collectors.toSet());

        assertThat(javaSet.size()).isEqualTo(3);
        assertThat(javaSet.toArray()[0]).isEqualTo(1);

    }
}
