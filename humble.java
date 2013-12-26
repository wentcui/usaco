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
		HashMap<Long, Boolean> existed = new HashMap<Long, Boolean>();
		long cur;
		int k = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		int[] set = new int[k];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < k; i++) {
			set[i] = Integer.parseInt(st.nextToken());
			existed.put((long)set[i], true);
		}
		existed.put((long)1, true);

		for(cur = 2; n > 0; cur++) {
			for(int j = 0; j < k; j++) {	
				if (cur >= set[j] && (cur % set[j] == 0) && existed.containsKey(cur / set[j])) {
					existed.put(cur, true);
					n--;
					break;
				}
			}
		}
		fout.println(cur - 1);
		fout.close();
		System.exit(0);
	}
}
