package il.co.ilrd.genericfactory;

 public interface genericfactory <T>
{
    T create(String type);
}

class FoodFactory implements genericfactory<Food> {
 
    @Override
    public Food create(String FoodName) 
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

class Food{
	;
}
class Candy extends Food{
	;
}
class Burger extends Food{
	;
}

class FactoryProvider {
    public static genericfactory<?> getFactory(String choice){
         
        if("Food".equals(choice)){
            return new FoodFactory();
        }

        return null;
    }
}