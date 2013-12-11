/*
ID: wentcui1
LANG: JAVA
TASK: preface
 */
import java.io.*;
import java.util.*;

class preface{
    public static void main (String [] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("preface.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("preface.out")));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        int n = Integer.parseInt(st.nextToken());
        char[] singleRomanMap = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        String[] roman = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M", "OUT"};
        int[] integer = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000, 4000};
        int[] map = new int[256]; 
        int[][] ret = new int[n + 1][8];
        map['I'] = 1;
        map['V'] = 2;
        map['X'] = 3;
        map['L'] = 4;
        map['C'] = 5;
        map['D'] = 6;
        map['M'] = 7;

        int lastindex = 0;
        for(int v = 1; v <= n; v++) {
            int left = v - integer[lastindex];
            String r = null;
            if (left == 0) {
                r = roman[lastindex];
                lastindex++;
            } else {
                r = roman[lastindex - 1];
                int sub = v - integer[lastindex - 1];
                for(int i = 0; i < 8; i++) {
                    ret[v][i] += ret[sub][i];
                }
            }
            for(int i = 0; i < r.length(); i++) {
                ret[v][map[r.charAt(i)]]++;
            }
        }

        for(int j = 1; j < 8; j++) {
            int v = 0;
            for(int i = 1; i <= n; i++) {
                v += ret[i][j];
            }
            if (v > 0)
                fout.println(singleRomanMap[j - 1] + " " + v);
        }
        fout.close();
        System.exit(0);
    }
}
