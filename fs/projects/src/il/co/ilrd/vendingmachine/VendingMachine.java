package il.co.ilrd.vendingmachine;

import java.util.*;
import java.util.Timer; 
import java.util.TimerTask; 

public class VendingMachine {
	
	Timer timer; 
    TimerTask task = new TimeOutTask();
    
    private float money;
    private StateVM state;
    private List <Product> productList;
    private Display display;

    VendingMachine(Display display, List <Product> productList) {
    	this.display = display;
    	this.productList = productList;
    	this.money = 0;
    	this.state = StateVM.NOT_READY;
    }

    public void insertMoney(float amount) {
    	this.state.insertMoney(this, amount);
    }
    public void chooseProduct(String productName) {
    	this.state.chooseProduct(this, productName);
    }
    public void abort() {
    	this.state.abort(this);
    }
    public void start() {
    	this.state.start(this);
    }
    public void end() {
    	this.state.end(this);
    }
    
    private VendingMachine getVM()
    {
    	return(this);
    }
    
    class TimeOutTask extends TimerTask {
		@Override
		public void run() {
			state.timeOut(getVM());
		}
    }

    /*******************************************************/
    
    private enum StateVM {
    	/*~~~~~~~~~~~~~~~~~~~~~~NOT_READY~~~~~~~~~~~~~~~~~~~~~~*/
        NOT_READY
        {
            @Override
            void abort(VendingMachine vmObject) {
            	;
            }
            @Override
            void start(VendingMachine vmObject) {
            	vmObject.timer = new Timer();
            	vmObject.timer.schedule(vmObject.task, 0, 1000);
            	
            	vmObject.state = IDLE;
            }
        },
        /*~~~~~~~~~~~~~~~~~~~~~~IDLE~~~~~~~~~~~~~~~~~~~~~~*/
        IDLE
        {
            @Override
            void abort(VendingMachine vmObject) {
            	;
            }
            
            @Override
            void end(VendingMachine vmObject) {
            	vmObject.state = NOT_READY;
            	vmObject.timer.cancel();
            	vmObject.timer.purge();
            }
            
            @Override
            void insertMoney(VendingMachine vmObject, float amount) {
            	vmObject.state = COLLECTING_MONEY;
            	vmObject.state.insertMoney(vmObject, amount);
            	
            }
        }, 
        /*~~~~~~~~~~~~~~~~~~~~~~COLLECTING_MONEY~~~~~~~~~~~~~~~~~~~~~~*/
        COLLECTING_MONEY
        {
        	long timestamp = System.currentTimeMillis();
        	
            @Override
            void abort(VendingMachine vmObject) {
            	returnMoney(vmObject);
            	vmObject.state = IDLE;
            }
            
            @Override
            void end(VendingMachine vmObject) {
            	returnMoney(vmObject);
            	vmObject.state = NOT_READY;
            	vmObject.timer.cancel();
            	vmObject.timer.purge();
            }
            
            @Override
            void insertMoney(VendingMachine vmObject, float amount)
            {
            	//System.out.println("inserted");
            	timestamp = System.currentTimeMillis();
            	vmObject.money += amount;
            }
            
            @Override
            void chooseProduct(VendingMachine vmObject, String productName)
            {
            	Product tmpProd = findProdByName(productName, vmObject);
            	//checking whether the product inserted exists
            	if (null != tmpProd)
            	{
            		//checking whether enough money was inserted
            		if(tmpProd.getProductPrice() <= vmObject.money)
            		{
            			vmObject.display.PrintToDisplay("'"+ productName + "' chosen successfully");
            			vmObject.money -= tmpProd.getProductPrice();
            		}
            		else
            		{
            			vmObject.display.PrintToDisplay("not enogh money");
            		}
            	}
            	else
            	{
            		vmObject.display.PrintToDisplay("no such product");
            	}
            	returnMoney(vmObject);
            	vmObject.state = IDLE;
            }
            
            @Override
            void timeOut(VendingMachine vmObject)
            {
            	long tmpTimestamp = System.currentTimeMillis();
            	
            	if(((tmpTimestamp - timestamp) / 1000) > 15)
            	{
            		System.out.println(tmpTimestamp + "\n" + timestamp);
            		vmObject.display.PrintToDisplay("TIME OUT");
            		returnMoney(vmObject);
            		vmObject.state = IDLE;
            	}
            }
        };
    	
        /*------------------------------------------------------------*/
        abstract void abort(VendingMachine vmObject);
        void chooseProduct(VendingMachine vmObject, String productName) {
        	//default
        	vmObject.display.PrintToDisplay("cant choose product in this state");
        }
        void insertMoney(VendingMachine vmObject, float amount) {
        	//default
        	vmObject.display.PrintToDisplay("cant insert money in this state");
        }
        void timeOut(VendingMachine vmObject) {
        	;
        }
        
        void start(VendingMachine vmObject) {
        	//default
        	vmObject.display.PrintToDisplay("already on");
        }
        void end(VendingMachine vmObject) {
        	//default
        	vmObject.display.PrintToDisplay("already off");
        }
        
        /*----------------------------------------------------*/
       	/*				  assistance functions				  */
        /*----------------------------------------------------*/
        void returnMoney(VendingMachine vmObject)
        {
        	vmObject.display.PrintToDisplay(vmObject.money + " returned");
        	vmObject.money = 0;
        }
        
        Product findProdByName(String name, VendingMachine vmObject) {
            for(Product prodObj : vmObject.productList) {
                if(prodObj.getProductName().equals(name)) {
                    return prodObj;
                }
            }
            return null;
        }
        /*------------------------------------------------------------*/
    }
}

