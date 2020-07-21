public class Client {
    public static void main(String[] args) {
        Student s1 = new Student.StudentBuilder(888801234, "John").major("Computer Science").age(22)
                .email("john1234@gmail.com").build();
        System.out.println(s1);
    }
}