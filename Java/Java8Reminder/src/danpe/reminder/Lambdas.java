package danpe.reminder;

public class Lambdas {

    interface Drawable {
        public void draw();
    }

    public void demoLambdas () {
        System.out.println("**********LAMBDAS**********");
        int width = 42;
        Drawable d = () -> {
            System.out.println("With lambda: " + width);
        };
        d.draw();
        System.out.println("********************");
    }
}
