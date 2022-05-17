package danpe.records;

// Based on https://www.geeksforgeeks.org/what-are-java-records-and-how-to-use-them-alongside-constructors-and-methods/
public class Main {

    public static void main(String[] args) {
	    Employee employee = new Employee(11111, "Normal", "Employee");
        System.out.println(employee);
        employee.setId(33333);
        System.out.println(employee);
        RecordEmployee recordEmployee = new RecordEmployee(22222, "Record", "Employee");
        //Record employee has getter fields in a convention that I saw in C++
        System.out.println("Record employee id: " + recordEmployee.id());
        System.out.println(recordEmployee);
    }
}
