

public static void main(String[] args) {
    
}

class findPassword {
    static boolean isLegitPassword(String pass)
    {
        int capitalCount = 0;
        String maxS;

        for(int i = 0; i < pass.length(); ++i)
        {
            String tmp;
            int j = i;
            while(j < pass.length())
            {
                if(!legitChar(pass.charAt(j)))
                {
                    break;
                }
                if(Character.isUpperCase(pass.charAt(j)))
                {
                    ++capitalCount;
                }
            }
        }
        return false;
    }

    static boolean legitChar(char c)
    {
        return Character.isLetter(c);
    }
}