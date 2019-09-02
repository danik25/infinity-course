package il.co.ilrd.hashmap;

import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import il.co.ilrd.pair.*;


public class HashMap<K, V> implements Map<K, V>
{
	private List<List<Entry<K, V>>> table;
	private int tableSize = 0;
	private int mapVersion = 0;
	private int capacity;
	
	public HashMap()
	{
		this(16);
	}
	
	public HashMap(int capacity)
	{
		this.capacity = capacity;
		table = new ArrayList<List<Entry<K, V>>>(capacity);
		
		for (int i = 0; i < capacity; ++i)
		{
			table.add(new LinkedList<Entry<K,V>>());
		}
	}
	
	@Override
	public void clear() 
	{
		for (List<Entry<K, V>> linkedList: table)
		{
			linkedList.clear();
		}
		tableSize = 0;
		++mapVersion;
	}

	@Override
	public boolean containsKey(Object key) 
	{
		Iterator<K> keyItr = keySet().iterator();
	
		while (keyItr.hasNext())
		{
			if (key.equals(keyItr.next()))
			{
				return true;
			}
		}
	
		return false;
	}

	@Override
	public boolean containsValue(Object value)
	{
		Iterator<V> valueItr = values().iterator();

		while (valueItr.hasNext())
		{
			if (value.equals(valueItr.next()))
			{
				return true;
			}
		}

		return false;
	}

	@Override
	public V get(Object key) 
	{
		Iterator<Entry<K, V>> itr = entrySet().iterator();
		Entry<K, V> currentPair = null;
		while (itr.hasNext())
		{
			currentPair = itr.next();
			if (key.equals(currentPair.getKey()))
			{
				return currentPair.getValue();
			}
		}
		return null;
	}

	@Override
	public boolean isEmpty()
	{
		return tableSize == 0;
	}

	@Override
	public V put(K key, V value) 
	{
		++mapVersion;
		
		for (Entry<K, V> currentEntry: this.entrySet())
		{
			if (currentEntry.getKey().equals(key))
			{
				V oldValue = currentEntry.getValue();
				currentEntry.setValue(value);
				return oldValue;
			}
		}
		
		int tableIndex = key.hashCode() % capacity;
		table.get(tableIndex).add(Pair.of(key, value));
		++tableSize;
		return null;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m)
	{
		Iterator<? extends K> itr = m.keySet().iterator();
		while (itr.hasNext())
		{
			K currentKey = itr.next();
			this.put(currentKey, m.get(currentKey));
		}
	}

	@Override
	public V remove(Object key) 
	{
		++mapVersion;
		
		if (!this.containsKey(key))
		{
			return null;
		}
		
		V oldValue = this.get(key);
		
		--tableSize;
		table.get(key.hashCode() % capacity).remove(Pair.of(key, oldValue));
		return oldValue;
	}

	@Override
	public int size() 
	{
		return tableSize;
	}

	@Override
	public Collection<V> values() 
	{
		return new ValueSet();
	}	
	
	@Override
	public Set<Entry<K, V>> entrySet() 
	{
		return new EntrySet();
	}
	
	@Override
	public Set<K> keySet() 
	{
		return new KeySet();
	}
	
	private class EntrySet extends AbstractSet<Entry<K, V>>
	{
		@Override
		public Iterator<Entry<K, V>> iterator() 
		{
			return new EntrySetIterator();
		}

		@Override
		public int size()
		{
			return tableSize;
		}
		
		private class EntrySetIterator implements Iterator<Entry<K, V>>
		{
			Iterator<List<Entry<K, V>>> tableItr;
			Iterator<Entry<K, V>> pairItr;
			int itrVersion;
			
			private EntrySetIterator() 
			{
				itrVersion = mapVersion;
				tableItr = table.iterator();
				pairItr = tableItr.next().iterator();
			}
			
			@Override
			public boolean hasNext() 
			{
				if (pairItr.hasNext())
				{
					return true;
				}
				
				List<Entry<K, V>> currentList = null;
				while(tableItr.hasNext())
				{
					currentList = tableItr.next();
					if (!currentList.isEmpty())
					{
						pairItr = currentList.iterator();
						return true;
					}
				}
			
				return false;
			}

			@Override
			public Entry<K, V> next() 
			{
				if (itrVersion != mapVersion)
				{
					throw new ConcurrentModificationException();
				}
				
				return pairItr.next();
			}
		}
	}
	
	private class KeySet extends AbstractSet<K>
	{		
		@Override
		public Iterator<K> iterator() 
		{
			return new KeySetIterator();
		}

		@Override
		public int size() 
		{
			return tableSize;
		}
		
		private class KeySetIterator implements Iterator<K>
		{
			int keyItrVersion;
			Iterator<Entry<K, V>> entrySetItr;
			
			private KeySetIterator() 
			{
				keyItrVersion = mapVersion;
				entrySetItr = entrySet().iterator();
			}
			
			@Override
			public boolean hasNext()
			{
				return entrySetItr.hasNext();
			}

			@Override
			public K next() 
			{
				if (keyItrVersion != mapVersion)
				{
					throw new ConcurrentModificationException();
				}
				
				Entry<K, V> currentPair = entrySetItr.next();
				if (currentPair != null)
				{
					return currentPair.getKey();
				}
				
				return null;
			}
		}
	}
	
	private class ValueSet extends AbstractSet<V>
	{
		@Override
		public Iterator<V> iterator() 
		{
			return new ValueSetIterator();
		}

		@Override
		public int size() 
		{
			return tableSize;
		}
		
		private class ValueSetIterator implements Iterator<V>
		{
			int valueItrVersion;
			Iterator<Entry<K, V>> entrySetItr;
			
			private ValueSetIterator() 
			{
				valueItrVersion = mapVersion;
				entrySetItr = entrySet().iterator();
			}
			
			@Override
			public boolean hasNext()
			{
				return entrySetItr.hasNext();
			}

			@Override
			public V next() 
			{
				if (valueItrVersion != mapVersion)
				{
					throw new ConcurrentModificationException();
				}
				
				Entry<K, V> currentPair = entrySetItr.next();
				if (currentPair != null)
				{
					return currentPair.getValue();
				}
				
				return null;
			}
		}
	}
}
