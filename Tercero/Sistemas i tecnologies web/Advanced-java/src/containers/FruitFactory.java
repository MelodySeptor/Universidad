package containers;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class FruitFactory {

	/**
	 * Constructor.
	 */
	public FruitFactory(){
		
	}
	
	/**
	 * Generate array list for apple.
	 * @return List<Apple>
	 */
	public static List<Apple> generateAppleArrayList(){
		List<Apple> list = new ArrayList<>();
		list.add(new Apple());
		list.add(new Apple());
		list.add(new Apple());
		return list;
	}
	
	/**
	 * Generate array list for orange.
	 * @return List<orange>
	 */
	public static List<Orange> generateOrangeArrayList(){
		List<Orange> list = new ArrayList<>();
		list.add(new Orange());
		list.add(new Orange());
		list.add(new Orange());
		return list;
	}
	
	/**
	 * Generate a HashMap of fruits.
	 * @return
	 */
	public static HashMap<FruitType,List<? extends Fruit >> generateFruitsMap(){
		HashMap<FruitType,List<? extends Fruit >> map = new HashMap<FruitType, List<? extends Fruit>>();
		map.put(FruitType.APPLE, generateAppleArrayList());
		map.put(FruitType.ORANGE, generateOrangeArrayList());
		return map;
		
	}
}
