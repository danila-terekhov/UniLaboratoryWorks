package Lab1;

public class MyContainer<E> {
	private int size;
	private int total = -1;
	final int step = 5;
	private Object[] array;

	public MyContainer(int size) {
		this.size = size;
		array = new Object[size];
	}

	public void show() {
		if (total == 0) {
			System.out.println("Container is empty!");
			return;
		}
		for (int i = 0; i <= total ; i++)
			System.out.printf("%d%s",array[i], i<total?",":".");
		System.out.println();
	}
	public E get(int i) {
		if (i > total) {
			System.out.println("There is no such element");
			return null;
		}
		@SuppressWarnings("unchecked")
		final E e = (E)array[i];
		return e;
	}
	public E getFirst() {
		@SuppressWarnings("unchecked")
		final E e = (E)array[0];
		return e;
	}
	public E getLast() {
		@SuppressWarnings("unchecked")
		final E e = (E)array[total];
		return e;
	}
	public void set(int i, E e) {
		if (i < total)
			array[i] = e;
		else
			System.out.println("There is no such element.");
	}
	public int getTotal() {
		return total+1;
	}
	public int getSize(){
		return size;
	}
	public void setSize(int size){
		resize(size);
	}

	public void add(E e) {
		if (total+1 == size) resize(size + step);
		array[++total] = e;
	}

	public void delete(int i) {
		if (i <= total) {
			--total;
			for (; i < total ; i++)
				array[i] = array[i+1];
		}
		else
			System.out.println("Wrong index.");
	}

	private void resize(int newSize) {
		int length;
		if (newSize < size) { // cut a part of array
			length = newSize;
			total = newSize-1;
		} else {
			length = size;
		}
		Object[] newArray = new Object[newSize];
		System.arraycopy(array, 0, newArray, 0, length);
		//for (int i = 0; i < length; i++)
			//newArray[i] = array[i];
		array = newArray;
		size = newSize;
	}
}
