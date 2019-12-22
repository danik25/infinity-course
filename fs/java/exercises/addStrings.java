import javax.lang.model.util.ElementScanner6;

public class addStrings {
    public static void main(String[] args) {
        resolve r = new resolve();
        r.create();
    }
}

class resolve {
    void create() {
        String f = "200";
        String s = "19";

        System.out.println(sAdd(f, s));
    }

    String sAdd(String first, String second) {
        int leftOver = 0;
        int firstLen = first.length();
        int secLen = second.length();
        int num = 0;

        int len = firstLen > secLen ? firstLen : secLen;
        char[] str = new char[len + 1];
        while (len >= 0) {
            int firstNum = firstLen > 0 ? Character.getNumericValue(first.charAt(firstLen - 1)) : 0;
            int secNum = secLen > 0 ? Character.getNumericValue(second.charAt(secLen - 1)) : 0;

            num = firstNum + secNum + leftOver;

            if (num > 9) {
                num %= 10;
                leftOver = 1;
            } else {
                leftOver = 0;
            }
            str[len] = (char) (num + '0');
            --len;
            --firstLen;
            --secLen;
        }

        if (str[0] == (char) (num + '0')) {
            return new String(permute(str));
        }
        return new String(str);
    }

    char[] permute(char[] str) {
        char[] newChar = new char[str.length - 1];
        for (int i = 1; i < str.length; ++i) {
            newChar[i - 1] = str[i];
        }

        return newChar;
    }
}
