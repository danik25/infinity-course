package il.co.ilrd.logmonitorNetworking;
import java.io.Serializable;

public interface CRUDNetworking <T extends Serializable , K extends Serializable> extends AutoCloseable {
	public K create(T item); 
	public T read(K key);
	public void update (K key, T item); 
	public void delete (K key);
}

