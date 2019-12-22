public class TestInt {
    public static void main(String[] args) {
        DerivedInit d = new DerivedInit();
    }
}

class BaseInit {
    private int member1 = 1;
    private int member2 = 2;

    public BaseInit() {
        System.out.println("Base Ctor");
        printFirst();
        printSecond();
    }

    void printFirst() {
        System.out.println(member1);
    }

    void printSecond() {
        System.out.println(member2);
    }
}

class DerivedInit extends BaseInit {
    private int member3 = 3;
    private int member4 = 4;

    public DerivedInit() {
        System.out.println("Derived Ctor");
        printFirst();
        printSecond();
    }

    void printFirst() {
        System.out.println(member3);
    }

    void printSecond() {
        System.out.println(member4);
    }
}