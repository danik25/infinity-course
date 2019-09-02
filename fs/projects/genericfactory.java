package il.co.ilrd.genericfactory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;;

public class genericfactory <T, K, A> {
	private Map<K, Function<A, ? extends T>> newMap= new HashMap<>();

	public void add (K key, Function<A, ? extends T> a)
	{
		;
	}
	public T create(K key, A arguments)
	{
		return null;
	}
}




