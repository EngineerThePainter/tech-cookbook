package wvd.springboot.sleuth;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.sleuth.Tracer;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan("org.springframework.cloud.sleuth.Tracer")
public class SleuthApplication {
	@Autowired
	private Tracer tracer;
	public static void main(String[] args) {
		SpringApplication.run(SleuthApplication.class, args);
	}

}
