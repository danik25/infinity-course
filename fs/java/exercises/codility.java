import java.util.*;

public class codility {
    public static void main(String[] args) {
        // Solution sol = new Solution();
        // System.out.println(sol.solution(0));
        // Bursa b = new Bursa();

        // System.out.println(b.solution(new int[]{60, 50, 79, 55, 80}));
        // System.out.println(b.solution(new int[]{27, 38, 25, 70, 90, 15}));
        Fish fish = new Fish();
        System.out.println(
                fish.solution(new int[] { 4, 3, 2, 1, 5 }, new int[] { 0, 1, 0, 0, 0 }) == 2 ? "correct!" : "wrong!");
        System.out.println(
                fish.solution(new int[] { 2, 1, 3, 5, 4 }, new int[] { 0, 0, 1, 1, 0 }) == 4 ? "correct!" : "wrong!");
        System.out
                .println(fish.solution(new int[] { 2, 1, 3, 1, 4, 6 }, new int[] { 1, 0, 1, 1, 0, 1 }) == 2 ? "correct!"
                        : "wrong!");
        System.out
                .println(fish.solution(new int[] { 2, 3, 1, 2, 4, 1 }, new int[] { 1, 1, 0, 0, 1, 0 }) == 3 ? "correct!"
                        : "wrong!");
    }
}

class Fish {
    public int solution(int[] A, int[] B) {
        Stack<Integer> fishStackA = new Stack<>();
        Stack<Integer> fishStackB = new Stack<>();
        fishStackA.push(A[0]);
        fishStackB.push(B[0]);

        for (int i = 1; i < A.length; ++i) {
            while (fishStackB.size() > 0 && fishStackA.peek() < A[i] && fishStackB.peek() > B[i]) {
                fishStackA.pop();
                fishStackB.pop();
            }

            if (fishStackB.size() == 0 || fishStackB.peek() <= B[i]) {
                fishStackA.push(A[i]);
                fishStackB.push(B[i]);
            }
        }

        return fishStackA.size();
    }
}

class Bursa {
    public int solution(int[] A) {
        // write your code in Java SE 8
        int max = 0;
        int i = 1;
        int start = 0;

        while (i < A.length) {
            if (A[i] - A[start] > max) {
                max = A[i] - A[start];
            }
            if (A[i] - A[start] < 0) {
                start = i;
            }
            ++i;

        }
        return max;
    }
}

class Solution2 {
    public int solution(String S) {
        // write your code in Java SE 8
        String[] splited = S.split(" ");
        int max = -1;
        for (String s : splited) {
            if (isCorrect(s)) {
                if (s.length() > max) {
                    max = s.length();
                }
            }
        }
        return max;
    }

    boolean isCorrect(String word) {
        int numOfLetters = 0;
        int numofDigits = 0;

        for (char c : word.toCharArray()) {
            if (Character.isLetter(c)) {
                ++numOfLetters;
            } else if (Character.isDigit(c)) {
                ++numofDigits;
            }

            else {
                return false;
            }
        }
        if (numOfLetters % 2 == 0 && numofDigits % 2 != 0) {
            return true;
        }
        return false;
    }
}

class Solution {
    public int solution(int N) {
        int max = 0;
        int count = 0;
        arr(N);
        while (N > 0) {
            if ((N & 1) > 0) {
                while ((N > 0) && (N & 1) > 0) {
                    N >>= 1;
                }
                while (N > 0 && (N & 1) == 0) {
                    N >>= 1;
                    ++count;

                    if ((N & 1) == 1) {
                        break;
                    }
                }
                if (N != 0) {
                    if (count > max) {
                        max = count;
                    }
                    count = 0;
                }
            } else {
                N >>= 1;
            }
        }

        return max;
    }

    public void arr(int N) {
        int size = 8;
        int[] arr = new int[size];
        Arrays.fill(arr, 0);
        int i = size - 1;
        while (N > 0) {
            arr[i] = N & 1;
            --i;
            N >>= 1;
        }
        printArr(arr);
    }

    void printArr(int[] arr) {
        for (int i = 0; i < arr.length; ++i) {
            System.out.print(arr[i] + " ");
        }
        System.out.println("");
    }

    int seekLargest(int[] arr) {
        int max = 0;
        int count = 0;
        int i = 1;
        while (i < arr.length) {
            while (arr[i] != 1) {
                ++i;
            }
            while (i < arr.length && arr[i] != 0) {
                ++i;
            }
            while (i < arr.length && arr[i] == 0) {
                ++count;
                ++i;
            }
            if (i == arr.length) {
                System.out.println(count);
                if (arr[i - 1] == 1) {
                    if (count > max) {
                        max = count;
                    }
                    count = 0;
                }
            } else if (arr[i] == 1) {
                System.out.println(count);
                if (count > max) {
                    max = count;
                }
                count = 0;
            }

        }
        return max;
    }
}

class Socks {
    public int solution(int K, int[] C, int[] D) {
        int[] clean = new int[50];
        int[] dirty = new int[50];
        int count = 0;

        for (int i = 0; i < C.length; ++i) {
            ++clean[C[i]];
            if (clean[C[i]] % 2 == 0) {
                ++count;
            }
        }

        for (int i = 0; i < D.length; ++i) {
            if (K == 0) {
                break;
            }
            ++dirty[D[i]];
            if (clean[D[i]] % 2 != 0) {
                --K;
                --dirty[D[i]];
                ++count;
            }
        }
        int i = 0;
        while (K > 1 && i < D.length) {
            if (dirty[D[i]] > 1) {
                ++count;
                dirty[D[i]] -= 2;
                K -= 2;
            }
            ++i;
        }

        return count;
    }
}