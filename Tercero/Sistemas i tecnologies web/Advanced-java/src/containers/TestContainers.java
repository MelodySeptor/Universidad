package containers;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;

/**
 * Class to test containers.
 *
 */
public class TestContainers {

	/**
	 * Constructor.
	 */
	public TestContainers(){
		
	}
	
	/**
	 * Print all fruits on the list.
	 * @param list
	 */
	public static void printFruitsList(List<? extends Fruit> list){
		for (Fruit f : list){
			System.out.println(f.toString());
		}
	}
	
	/**
	 * Print all fruits of the list.
	 * @param hashMap
	 */
	@SuppressWarnings("unchecked")
	public static void printFruitsMap(HashMap<FruitType, List<? extends Fruit>> hashMap){
		for (Entry<FruitType, List<? extends Fruit>> element : hashMap.entrySet()){
			System.out.println(element.getKey().getName());
			printFruitsList((ArrayList<Fruit>) element.getValue());
		}
	}
	
	/**
	 * Main
	 * @param args
	 */
	public static void main(String [] args){
		TestContainers.printFruitsList(FruitFactory.generateAppleArrayList());
		
		TestContainers.printFruitsMap(FruitFactory.generateFruitsMap());
	}
}
