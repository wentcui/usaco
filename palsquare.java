/*
ID: wentcui1
LANG: JAVA
TASK: palsquare
*/
import java.io.*;
import java.util.*;

class palsquare {
	public static boolean isPalindrome(int x, int f) {
		// Start typing your Java solution below
		// DO NOT write main() function
		int factor_h = 1, factor_t = f, f2 = f * f;

		while(x / factor_h >= f) {
			factor_h *= f;
		}

		while (x > 0) {
			int h = x / factor_h;
			int t = x % factor_t;

			if (t != h)
				return false;

			x %= factor_h;
			x /= factor_t;

			factor_h /= f2;
		}
		return true;
	}

	public static void main (String [] args) throws IOException {
		// Use BufferedReader rather than RandomAccessFile; it's much faster
		BufferedReader f = new BufferedReader(new FileReader("palsquare.in"));
		// input file name goes above
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("palsquare.out")));
		// Use StringTokenizer vs. readLine/split -- lots faster
		StringTokenizer st = new StringTokenizer(f.readLine());
		// Get line, break into tokens
		int base = Integer.parseInt(st.nextToken());    // first integer
		for(int i = 1; i <= 300; i++) {
			if (isPalindrome(i * i, base)) {
				out.println(Integer.toString(i, base).toUpperCase() + " " + Integer.toString(i * i, base).toUpperCase());
			}
		}

		out.close();                                  // close the output file
		System.exit(0);                               // don't omit this!
	}
}
