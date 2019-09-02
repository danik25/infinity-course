
package il.co.ilrd.hashmap;

import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import il.co.ilrd.pair.Pair;

public class HashMap <K, V>  implements Map<K, V>
{
	private int capacity = 0;
	private int size = 0;
	private int version = 0;
	private List<List<Entry<K,V>>> table;
	
	//*************************** Constructors ***************************//
	public HashMap(){
		this(16);
	}
	
	public HashMap(int capacity)
	{
		this.capacity = capacity; 	
		table = new ArrayList<>(capacity);
		for (int i = 0; i < capacity; ++i) {
			table.add(new LinkedList<Entry<K,V>>());
		}	
	}

	//*************************** public methods ***************************//

	@Override
	public boolean containsKey(Object key) {	
		for (Entry<K,V> localEntry: table.get(getIndex(key))) {
			if (key.equals(localEntry.getKey())) {
				return true; 
			}
		}
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		
		for(Object obj: values()) 
			if (obj.equals(value))
				return true;
				
		return false;
	}

	
	//*************************** Size/ Is Empty ***************************//
	@Override
	public boolean isEmpty() {
		return (size == 0);
	}
	
	@Override
	public int size() {
		return size;
	}
	//*************************** Get/ Put/ Put all ***************************//
	@Override
	public V get(Object key) {
		
		for (Map.Entry<K,V> element : entrySet()) {
			if (key.equals(element.getKey())){
				return element.getValue(); 
			}
		}
		return null; 
	}
	
	@Override
	public V put(K key, V value) {
		int index = getIndex(key);
		V oldValue = null;
		
		for (Entry<K,V> localEntry: table.get(index)) {
			if (key.equals(localEntry.getKey())) {
				oldValue = localEntry.getValue();
				localEntry.setValue(value);
				++version; 
				return oldValue; 
			}
		}
		
		table.get(index).add(Pair.of(key, value));
		++size; 
		++version;
		
		return oldValue; 
	}
				
	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		for (Map.Entry<? extends K, ? extends V> element : m.entrySet()) {
			put(element.getKey(),element.getValue());
		}	
	}
	
	//*************************** Remove, Clear  ******************************//
	@Override
	public V remove(Object key) {
		int index = getIndex(key);
		V value = null;
		
		for (Entry<K,V> localEntry: table.get(index)) {
			if (key.equals(localEntry.getKey())) {
				table.get(index).remove(localEntry);
				--size;
				++version;
			}
		}
		
		return value;
	}

	@Override
	public void clear() {
		for (List<Entry<K,V>> bucket: table) {
			bucket.clear();
		}	
		
		size = 0; 
		++version;
	}
	//************************ Private functions ******************************//
	private int getIndex(Object key){
		return key.hashCode() % capacity;
	}
	
	/*
	 * private HashMap.Entry<K,V> containedEntry(K key, int index) { for (Entry<K,V>
	 * localEntry: table.get(index)) { if (localEntry.getKey() == key) { return
	 * localEntry; } } return null; }
	 */
	//*************************************************************************//
	@Override
	public Collection<V> values() {
		return (new ValueSet());
	}	
	
	@Override
	public Set<Entry<K, V>> entrySet() {
		return (new EntrySet());
	}
	
	@Override
	public Set<K> keySet() {
		return (new KeySet());
	}
	//********************** EntrySet, KeySet, ValueSet ***********************************//
	private class EntrySet extends AbstractSet<Entry<K, V>>
	{		
		@Override
		public Iterator<Entry<K, V>> iterator(){	
			return (new EntrySetIterator(version));
		}

		@Override
		public int size(){
			return size;
		}
		
		private class EntrySetIterator implements Iterator<Entry<K, V>>
		{
			private int iterVersion; 
			private Iterator<List<Entry<K, V>>> currentBucketIter; 
			private Iterator<Entry<K, V>> currentEntryIter;
			
			EntrySetIterator(int iterVersion){
				this.iterVersion = iterVersion;
				currentBucketIter = table.iterator();	
				currentEntryIter = table.get(0).iterator();
					
			}
			
			@Override
			public boolean hasNext(){			
				
				if (iterVersion != version) {
					throw new ConcurrentModificationException();
				}
				
				if (currentEntryIter.hasNext()) {
					return true;
				}
				
				while (currentBucketIter.hasNext()){
					currentEntryIter = currentBucketIter.next().iterator();
					if (currentEntryIter.hasNext())
						return true; 
				}
				
				return false; 				
			}
			
			@Override
			public Entry<K, V> next(){	
			
				if (iterVersion != version){
					throw new ConcurrentModificationException();
				}
				
				return currentEntryIter.next();
			}
		}
	}
	
	
	private class KeySet extends AbstractSet<K>
	{	
		
		@Override
		public Iterator<K> iterator(){
			return (new KeyIterator());
		}

		@Override
		public int size(){
			return size;
		}
		
		private class KeyIterator implements Iterator<K>
		{
			private Iterator<Entry<K, V>> entryIterator; 
			private KeyIterator() {
				entryIterator = new EntrySet().iterator();
			}
			@Override
			public boolean hasNext() {
				return entryIterator.hasNext();
			}

			@Override
			public K next() {
				return entryIterator.next().getKey();
			}
		}
	}
	
	
	private class ValueSet extends AbstractSet<V>
	{
		@Override
		public Iterator<V> iterator() {
			return (new ValueSetIterator());
		}

		@Override
		public int size() {
			return size;
		}
		
		private class ValueSetIterator implements Iterator<V>
		{
			private Iterator<Entry<K, V>> entryIterator; 
			
			private ValueSetIterator() {
				entryIterator = new EntrySet().iterator();
			}
			@Override
			public boolean hasNext() {
				return entryIterator.hasNext();
			}

			@Override
			public V next() {
				return entryIterator.next().getValue();
			}
		}
	}
	
}
