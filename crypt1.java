/*
ID: wentcui1
LANG: JAVA
TASK: crypt1
*/
import java.io.*;
import java.util.*;

class crypt1 {
	public static boolean validate(int num, boolean []map) {
		while(num > 0) {
			int last = num % 10;
			if (!map[last])
				return false;
			num /= 10;
		}
		return true;
	}
	public static void main (String [] args) throws IOException {
		// Use BufferedReader rather than RandomAccessFile; it's much faster
		BufferedReader f = new BufferedReader(new FileReader("crypt1.in"));
		// input file name goes above
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("crypt1.out")));
		// Use StringTokenizer vs. readLine/split -- lots faster
		StringTokenizer st = new StringTokenizer(f.readLine());
		// Get line, break into tokens
		boolean[] map = new boolean[10];
		int n = Integer.parseInt(st.nextToken());    // first integer
		int count = 0;
		st = new StringTokenizer(f.readLine());

		for(int i = 0; i < n; i++) {
			int ni = Integer.parseInt(st.nextToken());
			if (!map[ni]) {
				map[ni] = true;
			}
		}

		for(int i = 100; i <= 999; i++) {
			if (!validate(i, map)) continue;
			for(int j = 10; j <= 99; j++) {
				if (!validate(j, map)) continue;
				int r = i * j;
				if (r >= 10000) continue;
				if (i * (j % 10) >= 1000 || !validate(i * (j % 10), map)) continue;
				if (i * (j / 10) >= 1000 || !validate(i * (j / 10), map)) continue;
				if (validate(r, map)) {
					count++;
				}
			}
		}
		out.println(count);
		out.close();
		System.exit(0);
	}
}
