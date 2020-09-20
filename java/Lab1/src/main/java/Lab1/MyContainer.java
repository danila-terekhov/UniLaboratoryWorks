package Lab1;

public class MyContainer<E> {
	private int size;
	private int total = 0;
	final int step=5;
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
		for (int i = 0; i < total ; i++)
			System.out.print(array[i]);
		System.out.println();
	}
	public E get(int i) {
		@SuppressWarnings("unchecked")
		final E e = (E)array[i];
		return e;
	}
	public void set(int i, E e) {
		if (i < total)
			array[i] = e;
		else
			System.out.println("There is no such element.");
	}
	public void add(E e) {
		array[total++] = e;
		if (total == size) resize();
	}

	public void delete(int i) {
		if (i < total) {
			--total;
			for (; i < total ; i++)
				array[i] = array[i+1];
		}
		else
			System.out.println("Wrong index.");
	}

	private void resize() {
		int newSize = size + step;
		Object[] newArray = new Object[newSize];
		for (int i = 0; i < size; i++)
			newArray[i] = array[i];
		array = newArray;
		size = newSize;
	}

}


