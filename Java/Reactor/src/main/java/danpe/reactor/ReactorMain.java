package danpe.reactor;

import reactor.core.publisher.Flux;

public class ReactorMain {
    public static void main(String[] args) {
        System.out.println("Hello Reactor");

        message("Subscribe with lambda");
        Flux<Integer> ints = Flux.range(1,3);
        ints.subscribe(i -> System.out.println(i));

        message("Subscribe with exception");
        Flux<Integer> intsWithException = Flux.range(1,5)
            .map(integer -> {
                if (integer >= 5) {
                    throw new RuntimeException("Error: Integer greater or equal 5");
                }
                return integer;
            });
        intsWithException.subscribe(
            integer -> System.out.println(integer),
            throwable -> System.out.println(throwable.getMessage()));

        message("Subscribe with done");
        Flux<Integer> intsWithDone = Flux.range(1,4);
        intsWithDone.subscribe(
            integer -> System.out.println(integer),
            throwable -> {throw new RuntimeException(throwable.getMessage());},
            () -> System.out.println("It is done"));

        message("Subscribe with request");
        Flux<Integer> intsWithRequest = Flux.range(1,4);
        intsWithRequest.subscribe(
          i-> System.out.println(i),
          error -> System.out.println("Error " + error),
          () -> System.out.println("Done"),
          subscription -> subscription.request(10)
        );

        message("Sample Subscriber");
        SampleSubscriber<Integer> sampleSubscriber = new SampleSubscriber<>();
        Flux<Integer> intsSampleSubscriber = Flux.range(1,4);
        intsSampleSubscriber.subscribe(sampleSubscriber);
    }

    static void message(String m) {
        System.out.println(m);
    }
}
