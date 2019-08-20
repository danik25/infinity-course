package il.co.ilrd.JarDynamicLoader;

import java.util.List;

public class JarDynamicLoaderTest {
	public static void main(String[] args) 
	{
		JarDynamicLoader loader = new JarDynamicLoader("/home/student/git/fs/projects/src/il/co/ilrd/JarPackage/myJar.jar", "jarInterface");
		List<Class<?>> ans = loader.load();
		
		for(Class<?> c : ans)
		{
			System.out.println(c.getName());
		}
		
		
	}
}
