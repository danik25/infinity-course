import java.util.HashMap;

public class cracking_the_coding_interview {

    public static void main(final String[] args) {
        // System.out.println(Strings.URLify(" my name is dani "));

        // linked list
        LinkedList list = new LinkedList();
        list.insert(1);
        list.insert(2);
        list.insert(3);

        // System.out.println(list.isPalindorm());
        System.out.println(list.sumList());
    }
}

class LinkedList {
    Node head = null;
    Node last = null;
    int size = 0;

    void insert(int data) {
        ++size;
        if (head == null) {
            head = new Node(data);
            last = head;
        } else {
            Node newNode = new Node(data);
            last.next = newNode;
            last = newNode;
        }
    }

    int sumList() {
        int answer = 0;
        int mult = 1;
        Node node = head;
        while (node != null) {
            answer = answer + node.data * mult;
            mult *= 10;
            node = node.next;
        }

        return answer;
    }

    LinkedList reverse() {
        LinkedList list = copy();
        Node current = list.head;
        Node next = current;
        Node prev = null;

        while (next != null) {
            current = next;
            next = current.next;
            current.next = prev;
            prev = current;

        }
        list.head = current;

        return list;
    }

    boolean isPalindorm() {
        LinkedList rev = reverse();
        Node first = head;
        Node second = rev.head;

        while (first != null) {
            if (first.data != second.data) {
                return false;
            }
            first = first.next;
            second = second.next;
        }

        return true;

    }

    LinkedList copy() {
        LinkedList newList = new LinkedList();
        Node node = head;
        while (node != null) {
            newList.insert(node.data);
            node = node.next;
        }

        return newList;
    }

    void printList() {
        Node node = head;
        while (node != null) {
            System.out.println(node.data);
            node = node.next;
        }
    }

    private class Node {
        int data;
        Node next = null;

        Node(int data) {
            this.data = data;
        }
    }
}

class Strings {
    static String URLify(String str) {
        char[] oldArr = str.toCharArray();
        int spaceCount = 0;
        for (char c : oldArr) {
            if (c == ' ') {
                ++spaceCount;
            }
        }

        char[] newArr = new char[str.length() + spaceCount * 2];

        for (int i = newArr.length - 1, j = oldArr.length - 1; i >= 0;) {
            if (oldArr[j] == ' ') {
                newArr[i] = '0';
                newArr[i - 1] = '2';
                newArr[i - 2] = '%';

                i -= 3;
                --j;
            } else {
                newArr[i] = oldArr[j];
                --i;
                --j;
            }
        }
        return new String(newArr);
    }

}