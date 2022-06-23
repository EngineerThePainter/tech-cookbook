package danpe.reactor;

import org.reactivestreams.Subscription;
import reactor.core.publisher.BaseSubscriber;
import reactor.core.publisher.Flux;

import java.util.concurrent.atomic.AtomicLong;

public class ReactorMain {

    public static void main(String[] args) {
        System.out.println("Hello Reactor");

        message("Subscribe with lambda");
        Flux<Integer> ints = Flux.range(1, 3);
        ints.subscribe(i -> System.out.println(i));

        message("Subscribe with exception");
        Flux<Integer> intsWithException = Flux.range(1, 5)
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
        Flux<Integer> intsWithDone = Flux.range(1, 4);
        intsWithDone.subscribe(
            integer -> System.out.println(integer),
            throwable -> {
                throw new RuntimeException(throwable.getMessage());
            },
            () -> System.out.println("It is done"));

        message("Subscribe with request");
        Flux<Integer> intsWithRequest = Flux.range(1, 4);
        intsWithRequest.subscribe(
            i -> System.out.println(i),
            error -> System.out.println("Error " + error),
            () -> System.out.println("Done"),
            subscription -> subscription.request(10)
        );

        message("Sample Subscriber");
        SampleSubscriber<Integer> sampleSubscriber = new SampleSubscriber<>();
        Flux<Integer> intsSampleSubscriber = Flux.range(1, 4);
        intsSampleSubscriber.subscribe(sampleSubscriber);

        message("Cancel after first request");
        Flux.range(1, 10)
            .doOnRequest(l -> System.out.println("Request of: " + l))
            .subscribe(new BaseSubscriber<Integer>() {
                @Override
                protected void hookOnSubscribe(Subscription subscription) {
                    request(1);
                }

                @Override
                protected void hookOnNext(Integer value) {
                    System.out.println("Cancel after having a request of: " + value);
                    cancel();
                }
            });

        message("State-based generate");
        Flux<String> stateGenerate = Flux.generate(
            () -> 0,
            (state, sink) -> {
                sink.next("3 x " + state + " = " + 3 * state);
                if (state == 10) {
                    sink.complete();
                }
                return ++state;
            }
        );
        stateGenerate.subscribe(s -> System.out.println(s));

        message("Mutable state generate");
        Flux<String> mutableGenerate = Flux.generate(
            AtomicLong::new,
            (state, sink) -> {
                long i = state.getAndIncrement();
                sink.next("3 x " + i + " = " + 3 * i);
                if (i == 10) {
                    sink.complete();
                }
                return state;
            }
        );
        mutableGenerate.subscribe(s -> System.out.println(s));

        message("Flux::generate with consumer");
        Flux<String> consumerGenerate = Flux.generate(
            AtomicLong::new,
            (state, sink) -> {
                long i = state.getAndIncrement();
                sink.next("3 x " + i + " = " + 3 * i);
                if (i == 10) {
                    sink.complete();
                }
                return state;
            },
            atomicLong -> System.out.println("State: " + atomicLong)
        );
        consumerGenerate.subscribe(s -> System.out.println(s));
    }

    static void message(String m) {
        System.out.println("***** " + m);
    }
}
