
public class enumTest
{
    public static void main(String[] args) 
    {
        EWeekDay day = EWeekDay.MONDAY;
        EWeekDay day2 = EWeekDay.MONDAY;
        System.out.println("int value of monday: " + day.getIntVal());
        System.out.println("enum of '4' int value: " + EWeekDay.fromVal(4));
        System.out.println("the days of the week:");
        EWeekDay.printDayOfTheWeek();
    }
}

enum EWeekDay
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY;
    
    public int getIntVal()
    {
        return(this.ordinal());
        //return(this.intVal);
    }
    public static EWeekDay fromVal(int index)
    {
        return (EWeekDay.values()[index]);
    }

    public static void printDayOfTheWeek()
    {
        for (EWeekDay day : EWeekDay.values()) 
        {
            System.out.println(day);
        }
    }
    
}