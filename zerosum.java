/*
ID: wentcui1
LANG: JAVA
TASK: lamps
 */
import java.io.*;
import java.util.*;

class zerosum {
	static ArrayList<String> res = new Arraylist<String>();
	static boolean validate(String str) {
		int posopa = 0, posopr = 0;
		char[] opa = new char[10];
		int[] opr = new int[10];
		int prev = 0;
		for(int i = 0; i < str.length(); i++) {
			char c = str.charAt(i);
			if (c == '+' || c == '-')
				opa[posopa++] = c;
			else if (c == ' ') {
				int j = 
				while() {
				}
			}
		}
	}
	static void strGen(int curindex, int n, String str) {
		if (curindex == n) {
			if (validate(str))
				res.add(str);
			return;
		}

		strGen(curindex + 1, n, new String(str) + '+');
		strGen(curindex + 1, n, new String(str) + '-');
		strGen(curindex + 1, n, new String(str) + ' ');
	}
	public static void main(String[] args) throws IOException {
        BufferedReader f = new BufferedReader(new FileReader("zerosum.in"));
        out = new PrintWriter(new BufferedWriter(new FileWriter("zerosum.out")));
        StringTokenizer st = new StringTokenizer(f.readLine());
		int n = Integer.parseInt(st.nextToken());
	}
}
