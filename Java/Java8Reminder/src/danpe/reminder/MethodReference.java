package danpe.reminder;

@FunctionalInterface
interface Sayable {
    public void say();
}

public class MethodReference {

    @FunctionalInterface
    interface Messengable {
        Message getMessage(String str);
    }

    private class Message {
        Message(String str) {
            System.out.println(str);
        }
    }

    private class InstanceSaying {
        public void sayingSomething() {
            System.out.println("Instance is saying something");
        }
    }

    public static void imSaying() {
        System.out.println("I'm saying something");
    }

    public void demoMethodReference () {
        System.out.println("**********METHOD REFERENCE**********");
        Sayable sayable = MethodReference::imSaying;
        sayable.say();

        InstanceSaying instanceSaying = new InstanceSaying();
        Sayable instanceSayable = instanceSaying::sayingSomething;
        instanceSayable.say();

        Messengable message = Message::new;
        message.getMessage("Hello from constructor in reference method");
        System.out.println("********************");
    }
}
