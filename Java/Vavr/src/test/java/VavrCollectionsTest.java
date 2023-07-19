import org.junit.Test;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;

public class VavrCollectionsTest {

    @Test(expected = UnsupportedOperationException.class)
    public void whenImmutableCollectionThrows_thenCorrect() {
        List<String> wordList = Arrays.asList("abra-cadabra");
        List<String> list = Collections.unmodifiableList(wordList);
        list.add("boom");
    }

    @Test
    public void whenCreatesVavrList_thenCorrect() {
        io.vavr.collection.List<Integer> intList = io.vavr.collection.List.of(1,2,3);

        assertThat(intList.length()).isEqualTo(3);
        assertThat(intList.get(0)).isEqualTo(new Integer(1));
        assertThat(intList.get(1)).isEqualTo(new Integer(2));
        assertThat(intList.get(2)).isEqualTo(new Integer(3));
    }

    @Test
    public void whenSumVavrList_thenCorrect() {
        int sum = io.vavr.collection.List.of(1,2,3).sum().intValue();

        assertThat(sum).isEqualTo(6);
    }
}
