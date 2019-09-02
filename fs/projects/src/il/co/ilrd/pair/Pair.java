package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;


public class Pair <K, V> implements Map.Entry<K, V>{

	private K key;
	private V value;
		
	private Pair(K key, V value){
		this.key = key;
		this.value = value;
	}
	
	public static <K, V> Pair<K, V> of(K key, V value){
		return new Pair<K, V>(key, value);
	}
	
	public static <K, V> Pair<V, K> swap(Pair<K, V> pair){
		return new Pair<V, K>(pair.value, pair.key);
	}
	
	public static <T extends Comparable <T>> Pair<T, T> minMax(T[] elements){
		
		class compareClass implements Comparator<T> 
		{ 
			@Override
			public int compare(T a, T b) 
		    { 
		        return a.compareTo(b); 
		    } 
		}
		return minMax(elements, new compareClass());
	}
	
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/	
	
	
	private static <T> Pair<T, T> comparePair(T left, T right, Comparator <T> c)
	{
		if(c.compare(left, right) > 0)
		{
			return new Pair<T,T>(right, left);
		}
		return new Pair<T,T>(left, right);
	}
	
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/		
	
	public static <T> Pair<T, T> minMax(T[] elements, Comparator <T> c){
		T min = elements[0];
		T max = elements[0];
		int i = 0;
		List<Pair<T,T>> pairs = new ArrayList<Pair<T,T>>();
		
		
		for(; i < elements.length - 2; i += 2)
		{
			pairs.add(comparePair(elements[i], elements[i + 1], c));
		}
		
		if(elements.length % 2 != 0)
		{
			pairs.add(comparePair(elements[i], elements[i], c));
		}
		
		else
		{
			pairs.add(comparePair(elements[i], elements[i + 1], c));
		}
		
		for(Pair<T,T> p : pairs)
		{
			if(c.compare(p.key, min) < 0)
			{
				min = p.key;
			}
			if(c.compare(p.value, max) > 0)
			{
				max = p.value;
			}
		}
		
		return new Pair<T,T>(min, max);
	}
	
	@Override
	public K getKey() {

		return key;
	}
	
	public K setKey(K newKey){
		K tmpkey = newKey;
		key = tmpkey;
		return tmpkey;
	}

	@Override
	public V getValue() {
		return value;
	}
	
	@Override
	public V setValue(V newValue) {
		V tmpVal = value;
		value = newValue;
		return tmpVal;
	}

	@Override
	public String toString() {
		return ("key: " + key + ", value: " + value) ;
	}

	@Override
	public int hashCode() {
		int result = 17;
        result = 31 * result + key.hashCode();
        result = 31 * result + value.hashCode();
        return result;
	}
	
	@Override
	@SuppressWarnings("unchecked")
	public boolean equals(Object obj) {
		if(this == obj)
		{
			return true;
		}
		if (obj instanceof Pair)
		{
			return (key == ((Pair<K,V>)obj).key && value == ((Pair<K,V>)obj).value);
		}
		return false;
	}
}

