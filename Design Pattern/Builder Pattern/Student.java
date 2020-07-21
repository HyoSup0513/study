public class Student {
    private long id;
    private String name;
    private String major;
    private int age;
    private String email;

    public Student() {
    }

    @Override
    public String toString() {
        return "Student [id]: " + id + " [name]: " + name + " [major]: " + major + " [age]: " + age + " [address]: "
                + email;
    }

    public static class StudentBuilder {
        // Essential parameter
        private final long id;
        private final String name;
        // Selective parameter
        private String major = "";
        private int age = 0;
        private String email = "";

        public StudentBuilder(long id, String name) {
            this.id = id;
            this.name = name;
        }

        public StudentBuilder major(String major) {
            this.major = major;
            return this;
        }

        public StudentBuilder age(int age) {
            this.age = age;
            return this;
        }

        public StudentBuilder email(String email) {
            this.email = email;
            return this;
        }

        public Student build() {
            return new Student(this);
        }
    }

    private Student(StudentBuilder builder) {
        this.id = builder.id;
        this.name = builder.name;
        this.major = builder.major;
        this.age = builder.age;
        this.email = builder.email;
    }
}