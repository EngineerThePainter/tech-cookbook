package danpe.reminder;

import java.util.*;
import java.util.stream.Collectors;

public class StreamApi {

    public class Product {
        int id;
        String name;
        float price;

        public Product(int id, String name, float price) {
            this.id = id;
            this.name = name;
            this.price = price;
        }

        @Override
        public String toString() {
            return "Product name: " + this.name + ", price: " + this.price;
        }
    }

    private void printCollection(final String message, List<Product> products) {
        System.out.println("*****" + message);
        products.forEach(product -> System.out.println(product.toString()));
        System.out.println("**********");
    }

    public void demoStreamApi() {
        System.out.println("**********STREAM API**********");
        List<Product> productList = new ArrayList<>();
        productList.add(new Product(1, "Tactical Squad", 139f));
        productList.add(new Product(2, "Devastator Squad", 140f));
        productList.add(new Product(3, "Attack Bike", 95.99f));
        productList.add(new Product(4, "Dreadnought", 159.99f));
        productList.add(new Product(5, "Librarian", 85f));

        printCollection("Filter", productList.stream().filter(product -> product.price > 120).collect(Collectors.toList()));
        System.out.println("Number of lesser than 100: " + productList.stream().filter(product -> product.price <= 100f).count());
        System.out.println("Max: " + productList.stream().max((o1, o2) -> o1.price > o2.price ? 1 : -1).get().toString());
        Set<String> names = productList.stream().map(product -> product.name).collect(Collectors.toSet());
        System.out.println(names);
        Map<Integer, String> map = productList.stream().collect(Collectors.toMap(p->p.id, p->p.name));
        System.out.println(map);
        System.out.println("Foreach");
        productList.forEach(product -> {System.out.println(product);});
        System.out.println("********************");
    }
}
