import io.vavr.collection.BitSet;
import io.vavr.collection.HashSet;
import io.vavr.collection.SortedSet;
import io.vavr.collection.TreeSet;
import org.junit.Test;

import java.util.Comparator;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.in;

public class VavrSetTest {

    @Test
    public void vavrHashSet() {
        HashSet<Integer> set0 = HashSet.rangeClosed(1,5);
        HashSet<Integer> set1 = HashSet.rangeClosed(3, 6);

        assertThat(set0.union(set1)).isEqualTo(HashSet.rangeClosed(1,6));
        assertThat(set0.diff(set1)).isEqualTo(HashSet.rangeClosed(1,2));
        assertThat(set0.intersect(set1)).isEqualTo(HashSet.rangeClosed(3, 5));
    }

    @Test
    public void vavrTreeSet() {
        SortedSet<String> set = TreeSet.of("Red", "Green", "Blue");
        assertThat(set.head()).isEqualTo("Blue");

        SortedSet<Integer> intSet = TreeSet.of(1,2,3);
        assertThat(intSet.average().get().intValue()).isEqualTo(2);

        SortedSet<String> reversedSet = TreeSet.of(Comparator.reverseOrder(), "Green", "Blue", "Red");
        assertThat(reversedSet.head()).isEqualTo("Red");

        String str = reversedSet.mkString(" and ");
        assertThat(str).isEqualTo("Red and Green and Blue");
    }

    @Test
    public void vavrBitSet() {
        BitSet<Integer> bitSet = BitSet.of(1,2,3,4,5,6,7,8);
        BitSet<Integer> bitSet2 = bitSet.takeUntil(integer -> integer > 3);
        assertThat(bitSet2.size()).isEqualTo(3);
    }
}
