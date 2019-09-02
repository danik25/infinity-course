package il.co.ilrd.genericfactory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class Factory <T, K, A> {
	private Map<K, Function<A, ? extends T>> mapCreators = new HashMap<>();

	public void add (K key, Function<A, ? extends T> a)
	{
		mapCreators.put(key, a);
	}
	public T create(K key, A arguments)
	{
		return mapCreators.get(key).apply(arguments);
	}
}




