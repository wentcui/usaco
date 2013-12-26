/*
ID: wentcui1
LANG: JAVA
TASK: humble
*/

import java.io.*;
import java.util.*;

class humble {
	public static void main (String [] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("humble.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("humble.out")));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int k = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		int[] set = new int[k + 1];
		int[] rec = new int[k + 1];
		long[] dp = new long[n + 2];
		int cur = 2;
		st = new StringTokenizer(fin.readLine());
		for(int i = 1; i <= k; i++) {
			set[i] = Integer.parseInt(st.nextToken());
			rec[i] = 1;
		}
		dp[0] = (long)1;
		dp[1] = (long)1;
		for(int i = 0; i < n; i++) {
			long minv = Long.MAX_VALUE;
			int minp = 1;
			for(int j = 1; j <= k; j++) {
				long nextv = dp[rec[j]] * set[j];
				if (nextv < minv) {
					minp = j;
					minv = nextv;
				}
			}
			if (minv <= dp[cur - 1]) {
				rec[minp]++;
				i--;
				continue;
			}
			dp[cur++] = minv;
			rec[minp]++;
		}

		fout.println(dp[n + 1]);
		fout.close();
		System.exit(0);
	}
}
