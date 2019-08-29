package il.co.ilrd.HashMap;

import java.util.AbstractSet;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import java.util.ArrayList;
import il.co.ilrd.LinkedList.LinkedList;

import il.co.ilrd.Pair.*;

public class HashMap <K, V> implements Map<K, V>
{
	private int capacity = 16;
	private int size;
	private int version;
	List<List<Entry<K,V>>> table;

	public HashMap()
	{
		table = new ArrayList<List<Entry<K,V>>>(capacity);
		setArray();
	}
	
	public HashMap(int capacity)
	{
		this.capacity = capacity;
		table = new ArrayList<List<Entry<K,V>>>(capacity);
		setArray();
	}
	
	private void setArray()
	{
		for(int i = 0; i < capacity; ++i)
		{
			table.add(i ,new java.util.LinkedList<Entry<K,V>>());
		}
	}
	
	private class EntrySet extends AbstractSet<Entry<K, V>>
	{
		@Override
		public Iterator<Entry<K, V>> iterator() {
			return null;
		}

		@Override
		public int size() {
			return 0;
		}
		
		private class EntrySetIterator implements Iterator<Entry<K, V>>
		{

			@Override
			public boolean hasNext() {
				return false;
			}

			@Override
			public Entry<K, V> next() {
				return null;
			}
		}
	}
	
	
	private class KeySet extends AbstractSet<K>
	{
		@Override
		public Iterator<K> iterator() {
			return null;
		}

		@Override
		public int size() {
			return 0;
		}
		
		private class EntrySetIterator implements Iterator<K>
		{

			@Override
			public boolean hasNext() {
				return false;
			}

			@Override
			public K next() {
				return null;
			}
		}
	}
	
	
	private class ValueSet extends AbstractSet<V>
	{
		@Override
		public Iterator<V> iterator() {
			return null;
		}

		@Override
		public int size() {
			return 0;
		}
		
		private class EntrySetIterator implements Iterator<V>
		{

			@Override
			public boolean hasNext() {
				return false;
			}

			@Override
			public V next() {
				return null;
			}
		}
	}
	
	
	@Override
	public void clear() {
	}

	@Override
	public boolean containsKey(Object key) {
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		return false;
	}

	@Override
	public V get(Object key) {
		return null;
	}

	@Override
	public boolean isEmpty() {
		return false;
	}

	@Override
	public V put(K key, V value) {
		int index = key.hashCode() % capacity;
			
		table.get(index).add(Pair.of(key, value));
		++size;
		
		return null;
		
		//TODO: return old value;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		for(Map.Entry<? extends K, ? extends V> a: entrySet())
		{
			put(a.getKey(), a.getValue());
			++size;
		}
	}

	@Override
	public V remove(Object key) {
		int index = key.hashCode() % capacity;
		V ans = null;
		int removeIndex = 0;
		
		for(Entry<K,V> a : table.get(index))
		{
			if(key == a.getKey())
			{
				table.get(index).remove(removeIndex);
				ans = a.getValue();
			}
			++removeIndex;
		}
		
		return ans;
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public Collection<V> values() {
		Collection<V> hashValues = new ArrayList<>();
		for(int i = 0; i < capacity; ++i)
		{
			for(Entry<K,V> a : table.get(i))
			{
				hashValues.add(a.getValue());
			}
		}
		return hashValues;
	}	
	
	@Override
	public Set<Entry<K, V>> entrySet() {
		return null;
	}
	
	@Override
	public Set<K> keySet() {
		return null;
	}
}
