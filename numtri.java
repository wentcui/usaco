/*
ID: wentcui1
LANG: JAVA
TASK: numtri
 */
import java.io.*;
import java.util.*;

class numtri {
	public static void main (String [] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("numtri.in"));
    	PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("numtri.out")));

		StringTokenizer st = new StringTokenizer(f.readLine());
		int[] pre = new int[1];
		int[] cur = new int[1];
		int pos = 0;
		int n = Integer.parseInt(st.nextToken());
		while(n > 0) {
			st = new StringTokenizer(f.readLine());
			for(int i = 0; i <= pos; i++) {
				if (i == 0)
					cur[i] = pre[i] + Integer.parseInt(st.nextToken());
				else if (i == pos)
					cur[i] = pre[i - 1] + Integer.parseInt(st.nextToken());
				else {
					cur[i] = Math.max(pre[i - 1], pre[i]) + Integer.parseInt(st.nextToken());
				}
			}
			pre = cur;
			pos++;
			cur = new int[pos + 1];
			n--;
		}
		int max = 0;
		for(int i = 0; i < pre.length; i++) {
			if (pre[i] > max)
				max = pre[i];
		}
		out.println(max);
		out.close();
		System.exit(0);
	}
}
