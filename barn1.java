/*
ID: wentcui1
LANG: JAVA
TASK: barn1
 */
import java.io.*;
import java.util.*;

class barn1 {
	public static void main (String [] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("barn1.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("barn1.out")));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int M = Integer.parseInt(st.nextToken());
    	int S = Integer.parseInt(st.nextToken());
		int C = Integer.parseInt(st.nextToken());
		int curlen = 0, numb = 0, singlelen = 1;
		int[] arr = new int[C];
		for(int i = 0; i < C; i++) {
			st = new StringTokenizer(fin.readLine());
			arr[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(arr);
		if (M == 1) {
			fout.println(arr[C - 1] - arr[0] + 1);
			fout.close();
			System.exit(0);
		}
		ArrayList<ArrayList<Integer>> os = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < C; i++) {
			ArrayList<Integer> l = new ArrayList<Integer>();
			l.add(arr[i]);
			os.add(l);
			curlen++;
			numb++;
		}

		while(numb > M) {
			int leastlen = Integer.MAX_VALUE;
			for(int i = 0; i < os.size() - 1; i++) {
				ArrayList<Integer> curl = os.get(i);
				ArrayList<Integer> nextl = os.get(i + 1);
				int gap = nextl.get(0) - curl.get(curl.size() - 1);
				if (gap == singlelen) {
					curl.addAll(os.remove(i + 1));
					curlen += (singlelen - 1);
					i--;
					numb--;
					if (numb == M)
						break;
				} else if (gap < leastlen)
					leastlen = gap;
						
			}
			singlelen++;
		}
		fout.println(curlen);
		fout.close();
		System.exit(0);
	}
}
