import java.util.Arrays;
import java.util.HashMap;

public class codeWars {
    public static void main(String[] args) {
        // System.out.println(Line.Tickets(new int[] { 25, 25, 50, 50, 100 }));
        // {1,1,1,3,5,9,17,31,57,105}
        /*
         * double[] answer = Xbonacci.tribonacci(new double[] { 1, 1, 1 }, 10); for (int
         * i = 0; i < answer.length; ++i) { System.out.println(answer[i]); }
         */

        System.out.println(Kata.findEvenIndex(new int[] { 1, 100, 50, -51, 1, 1 }));

    }
}

class Vowels {

    static int getCount(String str) {
        int vowelsCount = 0;
        String newString = str.toLowerCase();

        for (char c : newString.toCharArray()) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o') {
                ++vowelsCount;
            }
        }
        return vowelsCount;
    }

}

class Line {
    static String Tickets(int[] peopleInLine) {
        HashMap<Integer, Integer> map = new HashMap<>();
        map.put(25, 0);
        map.put(50, 0);
        map.put(100, 0);

        for (int sum : peopleInLine) {
            System.out.println(sum);
            if (!isEnough(sum, map)) {
                return "NO";
            }
            map.put(sum, map.get(sum) + 1);
        }
        return "YES";
    }

    static boolean isEnough(int num, HashMap<Integer, Integer> map) {
        if (num == 100) {
            if ((map.get(50) >= 1 && map.get(25) >= 1)) {
                map.put(50, map.get(50) - 1);
                map.put(25, map.get(25) - 1);
                return true;
            }
            if (map.get(25) >= 3) {
                map.put(25, map.get(25) - 3);
                return true;
            }
        }
        if (num == 50) {
            if (map.get(25) >= 1) {
                map.put(25, map.get(25) - 1);
                return true;
            }
        }
        if (num == 25) {
            return true;
        }
        return false;
    }
}

class Xbonacci {

    static double[] tribonacci(double[] s, int n) {
        double[] trib = new double[n];
        for (int i = 0; i < s.length; ++i) {
            trib[i] = s[i];
        }
        // hackonacci me
        // fillArrayRec(trib, n - 1);
        fillArrayIter(trib, n - 1);
        return trib;
    }

    static double fillArrayRec(double[] s, int n) {
        if (n <= 2) {
            return s[n];
        }
        double sum = (fillArrayRec(s, n - 1) + fillArrayRec(s, n - 2) + fillArrayRec(s, n - 3));
        s[n] = sum;

        return sum;
    }

    static void fillArrayIter(double[] s, int n) {
        double third = s[0];
        double second = s[1];
        double first = s[2];
        int i = 3;
        while (i <= n) {
            s[i] = first + second + third;
            third = second;
            second = first;
            first = s[i];
            ++i;
        }
    }
}

class Kata {
    public static int findEvenIndex(int[] arr) {
        int sumRight = Arrays.stream(arr).sum();
        int sumLeft = 0;

        for (int i = 0; i < arr.length; ++i) {
            sumRight -= arr[i];
            System.out.println("");
            if (sumLeft == sumRight) {
                return i;
            }
            sumLeft += arr[i];
        }
        return -1;
    }
}

class Kata2 {
    public static boolean solution(String str, String ending) {

      for(int i = ending.length() - 1, j = str.length() - 1; i >= 0; --i, --j)
      {
          if(ending.charAt(i) != str.charAt(j))
          {
              return false;
          }
      }
      return true;
    }
  }

class DuplicateEncoder {
	static String encode(String word){
        char[] newWord = new char[word.length()];
        int[] lut = new int[256];
        word = word.toLowerCase();
        for(char c : word.toCharArray())
        {
            ++lut[c];
        }
        for(int i = 0 ; i < word.length(); ++i)
        {
            newWord[i] = lut[word.charAt(i)] > 1 ? ')' : '(';
        }
    return new String(newWord);
  }
}
