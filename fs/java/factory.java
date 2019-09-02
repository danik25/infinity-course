

interface AbstractFactory <T>
{
    T get(String type);
}

public class FoodFactory implements AbstractFactory<Food> {
 
    @Override
    public Food get(String FoodName) 
    {
        if ("Candy".equals(FoodName)) {
            return new Candy();
        } 
        if ("Burger".equals(FoodName)) {
            return new Burger();
        }
 
        return null;
    }
}

public class FactoryProvider {
    public static AbstractFactory getFactory(String choice){
         
        if("Food".equals(choice)){
            return new FoodFactory();
        }

        return null;
    }
}