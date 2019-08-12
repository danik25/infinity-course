package il.co.ilrd.Complex;
import java.lang.Math; 
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Complex implements Comparable <Complex> {

    private double real;
    private double imaginary;

    Complex()
    {
    	real = 0;
    	imaginary = 0;
    }
    
    Complex(double real, double imaginary)
    {
    	this.real = real;
    	this.imaginary = imaginary;
    }

    public void setReal(double real)
    {
    	this.real = real;
    }
    
    public void setImaginary(double imaginary)
    {
    	this.imaginary = imaginary;
    }
    
    public void setValue(double real, double imaginary)
    {
    	this.real = real;
    	this.imaginary = imaginary;
    }
    
    public double getReal()
    {
    	return(real);
    }
    
    public double getImaginary()
    {
    	return(imaginary);
    }
    
    public Complex add(Complex toAdd)
    {
    	Complex answer = new Complex(this.real + toAdd.real, this.imaginary + toAdd.imaginary);
    	return(answer);
    }
    
    public Complex subtract(Complex toSubtract)
    {
    	Complex answer = new Complex(this.real - toSubtract.real, this.imaginary - toSubtract.imaginary);
    	return(answer);
    }
    
    public boolean isReal()
    {
    	return(imaginary == 0 && real != 0);
    }
    
    public boolean isImaginary()
    {
    	return(real == 0 && imaginary != 0);
    }
    
    public static Complex stringToComplex(String strToComplex)
    {
    	double real = 0;
    	double imaginary = 0;    	

    	if(!isValid(strToComplex))
    	{
    		return(null);
    	}
    	
    	Pattern findNumber = Pattern.compile("([+-])?\\d+");
        Matcher matchNumber = findNumber.matcher(strToComplex);        
        
        matchNumber.find();
        real = Double.parseDouble(matchNumber.group());
        
        matchNumber.find();
        imaginary = Double.parseDouble(matchNumber.group());
        
    	Complex ans = new Complex(real, imaginary);
    
    	return(ans);	
    }
    
    static private boolean isValid(String strToComplex)
	{
		// checking if it is a legal string
    	Pattern correctness = Pattern.compile("^([+-])?\\d+(\\.\\d+)?(\\s+)?[+-](\\s+)?\\d+(\\.\\d+)?[i]$");
    	Matcher matchCorrectness = correctness .matcher(strToComplex);
    	
    	return(matchCorrectness.matches());
	}
    
    @Override
    public int compareTo(Complex otherComplex)
    {
    	double firstSize = Math.sqrt(Math.pow(real, 2) + Math.pow(imaginary, 2));
    	double secondSize = Math.sqrt(Math.pow(otherComplex.real, 2) + Math.pow(otherComplex.imaginary, 2));
    	
    	return((int)firstSize - (int)secondSize);
    }

    @Override
    public boolean equals(Object toCompare)
    {
    	if (!(toCompare instanceof Complex))
    	{
    		return (false);
    	}
    	
    	Complex tmp = (Complex)toCompare;
    	return(this.getReal() == tmp.getReal() && this.getImaginary() == tmp.getImaginary());
    } 
    
    @Override
    public int hashCode()
    {
    	return((int)(31 * getReal() + 7 * getImaginary() + 5));
    } 
    
    
    @Override
    public String toString()
    {
    	if(getImaginary() < 0)
    	{
    		return(real + " - " + -imaginary + "i");
    	}
    	return(real + " + " + imaginary + "i");
    }
}
