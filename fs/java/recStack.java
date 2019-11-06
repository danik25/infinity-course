
import java.util.*;
public class recStack
{
    public static void main(String [] args)
    {
        sortedStack newStack = new sortedStack();
        newStack.insert(1);
        newStack.insert(8);
        newStack.insert(3);
        newStack.insert(5);
        newStack.insert(4);

        newStack.print();
    }
}

class sortedStack
{
    Stack stack = new Stack();
    sortedStack()
    {
        ;
    }
    void insert(int data)
    {
        if(!stack.isEmpty() && (int)stack.peek() > data)
        {
            int tmp = (int)stack.pop();
            insert(data);
            stack.push(tmp);
        }
        else
        {
            stack.push(data);
        }
    }

    void print()
    {
        while(!stack.isEmpty())
        {
            System.out.println((int)stack.pop());
        }
    }
}