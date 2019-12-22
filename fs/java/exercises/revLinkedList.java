public class revLinkedList {
    public static void main(String[] args) {
        LinkedList myList = new LinkedList();
        myList.insert(1);

        myList.insert(2);
        /*
         * myList.insert(3); myList.insert(4);
         */

        myList.printList();
        System.out.println("\nreversed\n");
        myList.rev();
        myList.printList();
    }
}

class LinkedList {
    Node head;
    Node tail;

    LinkedList() {
        ;
    }

    void insert(int data) {
        if (head == null) {
            head = new Node(data);
            tail = head;
        } else {
            Node newNode = new Node(data);
            tail.next = newNode;
            tail = newNode;
        }
    }

    void printList() {
        Node node = head;
        while (node != null) {
            System.out.println(node.data);
            node = node.next;
        }
    }

    void rev() {
        recRev(head);
    }

    Node recRev(Node node) {
        if (node.next == null) {
            return node;
        }

        head = recRev(node.next);
        node.next.next = node;
        node.next = null;

        return head;
    }

    private class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }

        Node(int data, Node next) {
            this.data = data;
            this.next = next;
        }
    }
}