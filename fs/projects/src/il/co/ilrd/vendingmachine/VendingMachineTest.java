package il.co.ilrd.vendingmachine;

import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

public class VendingMachineTest {
	public static void main(String[] args) {
		VMPrint obj = new VMPrint();
		List<Product> productList = CreateList.ListCreation();
		
		VendingMachine machine = new VendingMachine( obj, productList);
		
		System.out.println("vending machine:");
		for(Product prod : productList)
		{
			System.out.println(prod.getProductName() + ": " + prod.getProductPrice());
		}
		
		System.out.println("choos one:\nstart\n"
				+ "abort\n"
				+ "end\n"
				+ "choose product - type product name\n"
				+ "insert money - type a number");
		
		System.out.println("\nstarting the test:\n");
		
		boolean flag = true;
		float amount = 0;
		String prodName;
		Scanner scanner = new Scanner(System.in);
		
		while(flag == true)
		{
			
			//scanner = new Scanner(System.in);
			
			if(scanner.hasNextFloat())
			{
				System.out.println("money");
				amount = scanner.nextFloat();
				machine.insertMoney(amount);
			}
			else if(scanner.hasNextLine())
			{
				prodName = scanner.nextLine();
				switch(prodName)
				{
					case "start":
					{
						machine.start();
						break;
					}
					case "end":
					{
						machine.end();
						break;
					}	
					case "abort":
					{
						machine.abort();
						break;
					}
					default:
					{
						machine.chooseProduct(prodName);
						break;
					}	
				}
			}
		}

		/*for(int i = 0; i < 5; ++i)
		{
			Scanner scanner = new Scanner(System.in);
			if(scanner.hasNextFloat())
			{
				amount = scanner.nextFloat();
				machine.insertMoney(amount);
			}
			else if(scanner.hasNextLine())
			{
				prodName = scanner.nextLine();
				machine.chooseProduct(prodName);
			}		
			
		}*/

        
	}

}

class CreateList
{
	static List<Product> ListCreation()
	{
		Product p1 = new Product("Coca Cola", 4);
		Product p2 = new Product("Bamba", 3);
		Product p3 = new Product("Kinder Bueno", 5);
		Product p4 = new Product("Yogurt", 4);
		
		List<Product> productList = new ArrayList<Product> ();   
		productList.add(p1); 
		productList.add(p2); 
		productList.add(p3); 
		productList.add(p4);
		
		return(productList);
	}
}

class VMPrint implements Display
{
	@Override
	public void PrintToDisplay(String str)
	{
		System.out.println(str);
	}
}
