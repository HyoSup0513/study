/**
 * PCshop
 */
public abstract class PCshop {
    public PC orderPC(String name) {
        PC pc;

        pc = assemblePC(name);

        pc.assemble();
        pc.packing();

        return pc;
    }

    abstract PC assemblePC(String name);

}