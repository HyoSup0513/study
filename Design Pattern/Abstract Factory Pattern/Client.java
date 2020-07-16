public class Client {
    public static void main(String[] args) {

        KeyboardStore keyboardOrder01 = new KeyboardStore();

        VendorID vendorID;
        vendorID = VendorID.CHERRY;
        keyboardOrder01.orderKeyboards(vendorID);

        System.out.println();
        vendorID = VendorID.GATERON;
        keyboardOrder01.orderKeyboards(vendorID);
    }
}