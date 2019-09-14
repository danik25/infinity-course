import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;

public class ex1 {
    public static void main(String[] args){
        MyCallable task = new MyCallable("dani");

        ExecutorService executorService = Executors.newFixedThreadPool(4);
        Future<String> result = executorService.submit(task);

        try {
            System.out.println(result.get());
        } catch (InterruptedException | ExecutionException e) {
            System.out.println("Error occured while executing the submitted task");
            e.printStackTrace();
        }

        executorService.shutdown();
    }
}

class MyCallable implements Callable<String> {
    private String firstName;
    MyCallable(String name)
    {
        this.firstName = name;
    }
    @Override
    public String call() throws Exception {
        return ("hello " + firstName + "!");
    }
}