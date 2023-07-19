import io.vavr.control.Option;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VavrOptionTest {

    @Test
    public void givenValue_whenNullCheckNeeded_thenCorrect() {
        Object possibleNullObj = null;
        if (possibleNullObj == null) {
            possibleNullObj = "someDefaultValue";
        }
        assertThat(possibleNullObj).isNotNull();
    }

    @Test
    public void givenValue_whenCreatesOption_thenCorrect() {
        Option<Object> noneOption = Option.of(null);
        Option<Object> someOption = Option.of("val");

        assertThat(noneOption.toString()).isEqualTo("None");
        assertThat(someOption.toString()).isEqualTo("Some(val)");
    }

    @Test
    public void givenNull_thenCreatesOption_thenCorrect() {
        String name = null;
        Option<String> nameOption = Option.of(name);
        assertThat(nameOption.getOrElse("testValue")).isEqualTo("testValue");
    }

    @Test
    public void givenNotNull_whenCreatesOption_thenCorrect() {
        String name = "testName";
        Option<String> nameOption = Option.of(name);

        assertThat(nameOption.getOrElse("notTestName")).isEqualTo("testName");
    }
}
