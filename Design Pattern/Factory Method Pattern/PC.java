public abstract class PC {
    String productName;
    String cpu;
    String gpu;
    String ram;
    String storage;

    void assemble() {

        System.out.println("Now, assembling your PC.");
    }

    void packing() {

        System.out.println("Now, packing your PC for delivery.");
    }

    public String[] getInfo() {
        String[] productInfo = { productName, cpu, gpu, ram, storage };

        return productInfo;
    }
}