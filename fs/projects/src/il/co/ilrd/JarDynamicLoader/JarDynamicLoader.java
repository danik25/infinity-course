package il.co.ilrd.JarDynamicLoader;

import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry; // ZipInputStream
import java.util.ArrayList; // list
import java.util.List;
import java.io.FileInputStream;  //FileInputStream


public class JarDynamicLoader 
{
	private String path;
	private String interfaceName; 
	
	public JarDynamicLoader(String path, String interfaceName) 
	{
		this.path = path;
		this.interfaceName = interfaceName;
	}
	
	public List<Class<?>> load()
	{
		List<Class<?>> classNames = new ArrayList<Class<?>>();
		String namePart;
		
		try {
        ZipInputStream zip = new ZipInputStream(new FileInputStream(this.path));
        ZipEntry ze;

        while ((ze = zip.getNextEntry()) != null) 
        {
        		String fullName = ze.getName();
        		
        		if(fullName.contains(".class"))
        		{       			

        			namePart = fullName.replaceAll("/", ".").replaceAll(".class","");
 
                    try {
                    
                    Class<?> cls = Class.forName(namePart);
                    
                    Class<?>[] interfaces = cls.getInterfaces();
                    
                    for(Class<?> c : interfaces)
                    {
                    	if(c.getName().endsWith(this.interfaceName))
                        {
                        	classNames.add(cls);
                        }
                    }
                    
                    
                    }catch(ClassNotFoundException ex) {
                        System.out.println(ex.toString());
                    }
        		}        
        }
        zip.close();
		}catch(Exception e) {}
        
        return classNames;
	}	
}
