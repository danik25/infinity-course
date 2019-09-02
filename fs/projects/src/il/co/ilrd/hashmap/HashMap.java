package il.co.ilrd.hashmap;

import java.util.AbstractSet;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import il.co.ilrd.pair.*;
import java.util.ArrayList;
import java.util.LinkedList;

public class HashMap <K, V> implements Map<K, V>
{
	private int capacity;
	private int size;
	private int version;
	List<List<Entry<K,V>>> table;

	public HashMap()
	{
		this(16);
	}
	
	public HashMap(int capacity)
	{
		this.capacity = capacity;
		table = new ArrayList<List<Entry<K,V>>>(capacity);
		
		for(int i = 0; i < capacity; ++i)
		{
			table.add(new LinkedList<Map.Entry<K,V>>());
		}
	}	
	
	private class EntrySet extends AbstractSet<Entry<K, V>>
	{
		@Override
		public Iterator<Entry<K, V>> iterator()
		{
			return new EntrySetIterator(version);
		}

		@Override
		public int size()
		{
			return size;
		}
		
		private class EntrySetIterator implements Iterator<Entry<K, V>>
		{
			private int innerIterVersion;
			int listIndex;
			private Iterator <Entry<K, V>>currentIter;
			
			EntrySetIterator(int iterVersion)
			{
				innerIterVersion = iterVersion;
				currentIter = findFirstPair();
			}
			
		    /*~~~~~~~~~~~~assistance function~~~~~~~~~~~~*/
			private Iterator<Entry<K, V>> findFirstPair()
			{	
				while(listIndex < capacity && table.get(listIndex).size() == 0)
				{
					++listIndex;
				}
				
				if(listIndex == capacity)
				{
					return null;
				}
				
				return table.get(listIndex).iterator();
			}
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			
			@Override
			public boolean hasNext()
			{	
				if(currentIter != null)
				{
					if(currentIter.hasNext())
					{
						return true;
					}
					
					++listIndex;
					return(findFirstPair() != null);
				}
				
				return false;
			}
			
			@Override
			public Entry<K, V> next()
			{
				Entry<K, V> current = currentIter.next();
				if(innerIterVersion != version)
	            {
	            	throw new ConcurrentModificationException();
	            }

				if(currentIter != null && !currentIter.hasNext())
				{
					++listIndex;
					currentIter = findFirstPair();
				}
				
				return current;
			}
		}
	}
	
	
	private class KeySet extends AbstractSet<K>
	{
		@Override
		public Iterator<K> iterator()
		{
			return new keyIterator();
		}

		@Override
		public int size() {
			return size;
		}
		
		private class keyIterator implements Iterator<K>
		{
			EntrySet entryIter = new EntrySet();
			private Iterator <Entry<K, V>>currentIter = entryIter.iterator();
			
			@Override
			public boolean hasNext() {
				return currentIter.hasNext();
			}

			@Override
			public K next() {
				return currentIter.next().getKey();
			}
		}
	}
	
	
	private class ValueSet extends AbstractSet<V>
	{		
		@Override
		public Iterator<V> iterator() {
			return new ValueSetIterator();
		}

		@Override
		public int size() {
			return size;
		}
		
		private class ValueSetIterator implements Iterator<V>
		{
			EntrySet entryIter = new EntrySet();
			private Iterator <Entry<K, V>>currentIter = entryIter.iterator();
			
			@Override
			public boolean hasNext() {
				return currentIter.hasNext();
			}

			@Override
			public V next() {
				return currentIter.next().getValue();
			}
		}
	}
	
	
	@Override
	public void clear() {
        for(int i = 0; i < capacity; ++i) 
        { 
        	table.get(i).clear();
        }
        ++version;
        size = 0;
	}

	@Override
	public boolean containsKey(Object key) {
		int index = key.hashCode() % capacity;
		
		for(Entry<K,V> a : table.get(index))
		{
			if(a.getKey().equals(key))
			{
				return true; 
			}
		}
		return false;
	}

	@Override
	public boolean containsValue(Object value) {

		for(int i = 0; i < capacity; ++i)
		{
			for(Entry<K,V> a : table.get(i))
			{
				if(a.getValue().equals(value))
				{
					return true;
				}
			}
		}
		
		return false;
	}

	@Override
	public V get(Object key) {
		for(Map.Entry<K,V> entry : entrySet())
		{
			if(entry.getKey().equals(key))
			{
				return entry.getValue();
			}
		}

		return null;
	}

	@Override
	public boolean isEmpty() {
		return 0 == size;
	}

	@Override
	public V put(K key, V value) {
		int index = key.hashCode() % capacity;
		V ans = null;
		if(containsKey(key))
		{
			ans = get(key);
			remove(key);
		}
		table.get(index).add(Pair.of(key, value));
		++size;
		++version;
		
		return ans;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		for(Map.Entry<? extends K, ? extends V> entry: m.entrySet())
		{
			put(entry.getKey(), entry.getValue());
		}
	}

	@Override
	public V remove(Object key) {
		int index = key.hashCode() % capacity;
		V ans = null;
		
		for(Entry<K,V> a : table.get(index))
		{
			if(key.equals(a.getKey()))
			{
				table.get(index).remove(a);
				ans = a.getValue();
				--size;
				++version;
			}
		}
		
		return ans;
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public Collection<V> values() {
		return new ValueSet();
	}	
	
	@Override
	public Set<Entry<K, V>> entrySet() {
		return new EntrySet();
	}
	
	@Override
	public Set<K> keySet() {
		return new KeySet();
	}
}
