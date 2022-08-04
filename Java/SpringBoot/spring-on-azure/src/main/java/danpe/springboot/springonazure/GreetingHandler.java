package danpe.springboot.springonazure;

import org.springframework.http.MediaType;
import org.springframework.stereotype.Component;
import org.springframework.web.reactive.function.BodyInserters;
import org.springframework.web.reactive.function.server.ServerRequest;
import org.springframework.web.reactive.function.server.ServerResponse;
import reactor.core.publisher.Mono;

import java.util.Optional;

@Component
public class GreetingHandler {

    public Mono<ServerResponse> hello(ServerRequest request) {
        String greetingMessage = "Hello!";
        Optional<String> nameParam = request.queryParam("name");
        if (nameParam.isPresent() && !nameParam.get().isEmpty() && !nameParam.get().isBlank()) {
            greetingMessage = "Hello " + nameParam.get() + "!";
        }

        return ServerResponse
            .ok()
            .contentType(MediaType.APPLICATION_JSON)
            .body(BodyInserters.fromValue(new Greeting(greetingMessage)));
    }

}
