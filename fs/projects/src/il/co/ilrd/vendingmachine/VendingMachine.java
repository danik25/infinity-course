package il.co.ilrd.vendingmachine;

import java.util.*;
import java.util.Timer; 
import java.util.TimerTask; 

public class VendingMachine {
	
	Timer timer = null; 
	
    TimerTask task;
    long timestamp = System.currentTimeMillis();
    
    private float money = 0;
    private StateVM state = StateVM.NOT_READY;
    private List <Product> productList;
    private Display display;

    VendingMachine(Display display, List <Product> productList) { 
    	this.display = display;
    	this.productList = productList;
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
    	if(null == timer)
    	{
    		timer = new Timer();
    		task = new TimeOutTask();
    		timer.schedule(task, 0, 1000);
    	}
    	this.state.start(this);
    }
    public void end() {
    	if(null != timer)
    	{
    		timer.cancel();
    		timer = null;
    	}
    	this.state.end(this);
    }
    
    public VendingMachine getVm()
    {
    	return(this);
    }
    
    class TimeOutTask extends TimerTask {
		@Override
		public void run() {
			state.timeOut(getVm());
		}
    }

    /*******************************************************/
    
    private enum StateVM {
    	/*~~~~~~~~~~~~~~~~~~~~~~NOT_READY~~~~~~~~~~~~~~~~~~~~~~*/
    	
        NOT_READY
        {
            @Override
            void abort(VendingMachine vmObject) {/*do nothing*/}
            
            @Override
            void start(VendingMachine vmObject) {  
            	updateState(vmObject, IDLE);
            }
            @Override
            void insertMoney(VendingMachine vmObject, float amount)
            {
            	vmObject.display.PrintToDisplay("cant insert money, turn on the machine");
            }
            
            @Override
            void end(VendingMachine vmObject) {
            	vmObject.display.PrintToDisplay("already off");
            }
        },
        /*~~~~~~~~~~~~~~~~~~~~~~IDLE~~~~~~~~~~~~~~~~~~~~~~*/
        IDLE
        {
            @Override
            void abort(VendingMachine vmObject) {/*do nothing*/}
        }, 
        /*~~~~~~~~~~~~~~~~~~~~~~COLLECTING_MONEY~~~~~~~~~~~~~~~~~~~~~~*/
        COLLECTING_MONEY
        {        	
            @Override
            void abort(VendingMachine vmObject) {
            	returnMoney(vmObject);
            	updateState(vmObject, IDLE);
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
            	updateState(vmObject, IDLE);
            }
            
            @Override
            void timeOut(VendingMachine vmObject)
            {
            	long tmpTimestamp = System.currentTimeMillis();
            	long threshold = 15; 
            	
            	if(((tmpTimestamp - vmObject.timestamp) / 1000) > threshold)
            	{
            		vmObject.display.PrintToDisplay("TIME OUT");
            		returnMoney(vmObject);
            		updateState(vmObject, IDLE);
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
        	updateState(vmObject, COLLECTING_MONEY);
        	vmObject.money += amount;
        }
        void timeOut(VendingMachine vmObject) {/*do nothing*/}
        
        void start(VendingMachine vmObject) {
        	//default
        	vmObject.display.PrintToDisplay("already on");
        }
        void end(VendingMachine vmObject) {
        	//default
        	returnMoney(vmObject);
        	updateState(vmObject, NOT_READY);
        	
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
        
        void updateState(VendingMachine vmObject, StateVM state)
        {
        	vmObject.state = state;
        	vmObject.timestamp = System.currentTimeMillis();
        }
        /*------------------------------------------------------------*/
    }
}

