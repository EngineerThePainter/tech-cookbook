package danpe.reminder;

public class Main {

    public static void main(String[] args) {

        StreamApi streamApi = new StreamApi();
        streamApi.demoStreamApi();

        Lambdas lambdas = new Lambdas();
        lambdas.demoLambdas();

        MethodReference methodReference = new MethodReference();
        methodReference.demoMethodReference();
    }
}
