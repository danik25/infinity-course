

interface jarInterface
{
	void printMethod();
}

public class jarClasses{
	public static void main(String[] args) {}
}

class jarImplement implements jarInterface{
	@Override
	public void printMethod()
	{
		System.out.println("jar");
	}
}
