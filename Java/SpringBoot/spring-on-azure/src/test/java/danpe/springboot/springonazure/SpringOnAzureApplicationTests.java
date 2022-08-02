package danpe.springboot.springonazure;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.context.SpringBootTest.WebEnvironment;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.web.reactive.server.WebTestClient;

import static org.assertj.core.api.Assertions.assertThat;

@ExtendWith(SpringExtension.class)
@SpringBootTest(webEnvironment = WebEnvironment.RANDOM_PORT)
class SpringOnAzureApplicationTests {

	@Autowired
	private WebTestClient webTestClient;

	@Test
	void helloWithoutSpecifiedParamShouldPassDefaultValue() {
		webTestClient
			.get()
			.uri("/hello")
			.accept(MediaType.APPLICATION_JSON)
			.exchange()
			.expectStatus()
			.isOk()
			.expectBody(Greeting.class)
			.value(greeting -> {
				assertThat(greeting.getMessage()).isEqualTo("Hello!");
			});
	}

	@Test
	void helloWithParamShouldPassThatParamInMessage() {
		webTestClient
			.get()
			.uri("/hello?name=Dan")
			.accept(MediaType.APPLICATION_JSON)
			.exchange()
			.expectStatus()
			.isOk()
			.expectBody(Greeting.class)
			.value(greeting -> {
				assertThat(greeting.getMessage()).isEqualTo("Hello Dan!");
			});
	}

	@Test
	void helloWithEmptyParamShouldPassDefaultMessage() {
		webTestClient
			.get()
			.uri("/hello?name=")
			.accept(MediaType.APPLICATION_JSON)
			.exchange()
			.expectStatus()
			.isOk()
			.expectBody(Greeting.class)
			.value(greeting -> {
				assertThat(greeting.getMessage()).isEqualTo("Hello!");
			});
	}

	@Test
	void helloWithBlankParamShouldPassDefaultMessage() {
		webTestClient
			.get()
			.uri("/hello?name= ")
			.accept(MediaType.APPLICATION_JSON)
			.exchange()
			.expectStatus()
			.isOk()
			.expectBody(Greeting.class)
			.value(greeting -> {
				assertThat(greeting.getMessage()).isEqualTo("Hello!");
			});
	}

}
