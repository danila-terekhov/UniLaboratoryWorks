### usage:
```
$ java Main.java numberOfOperations # it works w/o precompilation!
```

### N ~= 15000 *результаты зависят от N*

***

**add**  
Add to the end:  `ArrayList.add() > LinkedList.addLast() >>  LinkedList.add()`  
//Что самое странное, на N>100k Ll.addLast() начинает обгонять массив  
Add to the middle: `ArrayList.add(i/2,value) >> LinkedList(i/2,value)`  
Add to the begin: `LinkedList.addFirst > LinkedList.add(0,val) >>>> ArrayList.add(0,val) // в случае Array нужно сдвинуть весь массив`  

***

**remove**  
Remove from the end: `LinkedList.removeLast >> LinkedList.remove(iLast) ~= LinkedList.remove() > ArrayList.remove(iLast)`  
Remove from the middle: `ArrayList.remove(i/2) >> LinkedList.remove(i/2) ` i = N-1 .. 0  
// чем больше i, тем дольше происходит поиск элемента в Linked  
//и тем меньше элементов нужно копировать от конца в Array  
Remove from the begin: `LinkedList.removeFirst > LinkedList.remove(0) > ArrayList.remove(0) ` // в Array опять нужно сдвигать весь массив  

***

**get**  
Очевидно, что для ArrayList время одинаково для любого элемента,  
LinkedList.getFirst() ~= LinkedList.getLast() ~= ArrayList.get() ~= O(n),  
a LinkedList.get(i) самый медленный O(n), т.к. нужно по списку дойти до i-го элемента  


