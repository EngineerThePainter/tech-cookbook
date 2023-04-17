import io.vavr.collection.Iterator;
import io.vavr.collection.List;
import io.vavr.collection.Map;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VavrSeqTest {

    @Test
    public void vavrList() {
        List<String> list = List.of("Java", "C++", "Lua", "Python");
        List list1 = list.drop(2);
        assertThat(list1.contains("Java") || list1.contains("C++")).isFalse();

        List list2 = list.dropRight(2);
        assertThat(list2.contains("Lua") || list2.contains("Python")).isFalse();

        List list3 = list.dropUntil(s -> s.contains("Lua"));
        assertThat(list3.length()).isEqualTo(2);

        List list4 = list.dropWhile(s -> s.length() > 0);
        assertThat(list4.isEmpty()).isTrue();

        List list5 = list.take(1);
        assertThat(list5.single()).isEqualTo("Java");

        List list6 = list.takeRight(1);
        assertThat(list6.single()).isEqualTo("Python");

        List list7 = list.takeUntil(s -> s.length() > 4);
        assertThat(list7.size()).isEqualTo(3);

        List list8 = list.distinctBy((s1, s2) -> s1.length() == s2.length() ? 0 : 1);
        assertThat(list8.size()).isEqualTo(3);

        String words = List.of("Boys", "Girls")
                .intersperse("and")
                .reduce((s1,s2)->s1.concat(" " + s2))
                .trim();
        assertThat(words).isEqualTo("Boys and Girls");

        Iterator<List<String>> iterator = list.grouped(2);
        assertThat(iterator.head().size()).isEqualTo(2);

        Map<Boolean, List<String>> map = list.groupBy(e->e.startsWith("J"));
        assertThat(map.size()).isEqualTo(2);
        assertThat(map.get(false).get().size()).isEqualTo(3);
        assertThat(map.get(true).get().size()).isEqualTo(1);
    }
}
