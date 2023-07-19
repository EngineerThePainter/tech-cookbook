package danpe.reactor;

public interface EventListener<T> {
    public void onNewData(T data);
    public void onDone();
}