package il.co.ilrd.genericfactory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;;

class Factory <T, K, A> {
	Map<K, Function<A, ? extends T>> newMap= new HashMap<>();

	void add (K key, Function<A, ? extends T> a)
	{
		;
	}
	T create(K key, A arguments)
	{
		return null;
	}
}




