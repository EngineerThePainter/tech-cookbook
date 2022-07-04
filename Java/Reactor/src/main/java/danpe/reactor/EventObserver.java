package danpe.reactor;

import java.util.ArrayList;
import java.util.List;

public class EventObserver {
    private List<EventListener<String>> listeners;

    public EventObserver() {
        listeners = new ArrayList<>();
    }

    public void register(EventListener<String> listener) {
        listeners.add(listener);
    }

    public void addData(String data) {
        System.out.println("Data Added");
        listeners.forEach(listener -> listener.onNewData(data));
    }

    public void done() {
        listeners.forEach(listener -> listener.onDone());
    }
}
