
package il.co.ilrd.vendingmachine;

public class Product {
    private String productName;
    private float productPrice;
    
    Product(String productName, float productPrice) {
    	this.productName = productName;
    	this.productPrice = productPrice;
    }

    public String getProductName() {
        return productName;
    }

    public float getProductPrice() {
        return productPrice;
    }    
}
