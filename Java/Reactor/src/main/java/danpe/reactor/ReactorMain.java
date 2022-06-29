package danpe.reactor;

import org.reactivestreams.Subscription;
import reactor.core.publisher.BaseSubscriber;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;
import reactor.core.scheduler.Scheduler;
import reactor.core.scheduler.Schedulers;

import java.util.concurrent.atomic.AtomicLong;

public class ReactorMain {

    public static void main(String[] args) throws InterruptedException {
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

        message("Flux::create");
        EventObserver fluxCreateObserver = new EventObserver();
        Flux<String> bridge = Flux.create(
          stringFluxSink -> {
              fluxCreateObserver.register(new EventListener<String>() {
                  @Override
                  public void onNewData(String data) {
                      System.out.println("OnNewData: " + data);
                      stringFluxSink.next(data);
                  }

                  @Override
                  public void onDone() {
                      System.out.println("OnDone");
                      stringFluxSink.complete();
                  }
              });
          }
        );
        bridge.subscribe();
        fluxCreateObserver.addData("Data");
        fluxCreateObserver.addData("is");
        fluxCreateObserver.addData("fun");
        fluxCreateObserver.done();


        message("Flux::Push");
        EventObserver fluxPushObserver = new EventObserver();
        Flux<String> pushBridge = Flux.create(
            stringFluxSink -> {
                fluxPushObserver.register(new EventListener<String>() {
                    @Override
                    public void onNewData(String data) {
                        System.out.println("OnNewData: " + data);
                        stringFluxSink.next(data);
                    }

                    @Override
                    public void onDone() {
                        System.out.println("OnDone");
                        stringFluxSink.complete();
                    }
                });
            }
        );
        pushBridge.subscribe();
        fluxPushObserver.addData("Data");
        fluxPushObserver.addData("is");
        fluxPushObserver.addData("fun");
        fluxPushObserver.done();

        message("Mono on separate thread");
        final Mono<String> threadMono = Mono.just("Hello");
        Thread t = new Thread(() -> threadMono
            .map(s -> s + " thread: ")
            .subscribe(s -> System.out.println(s + Thread.currentThread().getName()))
        );
        t.start();
        t.join();

        message("FLux::publishOn");
        Scheduler publishOnScheduler = Schedulers.newParallel("publish-parallel-scheduler", 4);
        final Flux<String> publishOnFlux = Flux
            .range(1, 2)
            .map(integer -> 10+integer)
            .publishOn(publishOnScheduler)
            .map(integer -> "value " + integer);
        Thread publishOnThread = new Thread(() -> publishOnFlux.subscribe(System.out::println,
            throwable -> System.out.println("Error"),
            () -> publishOnScheduler.dispose()));
        publishOnThread.start();
        publishOnThread.join();
    }

    static void message(String m) {
        System.out.println("***** " + m);
    }
}
