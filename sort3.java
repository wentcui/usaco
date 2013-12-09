/*
ID: wentcui1
LANG: JAVA
TASK: sort3
*/
import java.io.*;
import java.util.*;

public class sort3 {
	public static void swap(int[] A, int a, int b) {
		int temp = A[a];
		A[a] = A[b];
		A[b] = temp;
	}
	public static int sortColors(int[] A) {
		// Start typing your Java solution below
		// DO NOT write main() function
		int head = 0, tail = A.length - 1, cur = 0;
		int ret = 0;
		while(cur <= tail) {
			if (A[cur] == 2)
				cur++;
			else if (A[cur] == 1) {
				if (cur != head)
					ret++;

				A[cur++] = A[head];
				A[head++] = 1;
			} else {
				if (cur != tail)
					ret++;

				A[cur] = A[tail];
				A[tail--] = 3;
			}
		}
		return ret;
	}
	
	public static void main(String[] args) throws IOException {
		HashMap<String, Integer> map = new HashMap<String, Integer>();
		BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sort3.out")));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int[] A = new int[n];
		int[] sortedA = new int[n];
		int ret = 0;
		
		map.put("1*2", 0);
		map.put("1*3", 0);
		map.put("2*1", 0);
		map.put("2*3", 0);
		map.put("3*1", 0);
		map.put("3*2", 0);

		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			A[i] = Integer.parseInt(st.nextToken());
			sortedA[i] = A[i];
		}
		sortColors(sortedA);
		for(int i = 0; i < n; i++) {
			if (sortedA[i] == A[i]) continue;
			String key = "" + A[i] + "*" + sortedA[i];
			String revskey = "" + sortedA[i] + "*" + A[i];
			int v = map.get(key);
			int rv = map.get(revskey);
			if (rv > 0) {
				map.put(revskey, rv - 1);
				ret++;
			} else
				map.put(key, v + 1);
		}
		ret += (map.get("1*2") * 2);
		ret += (map.get("2*1") * 2);
		fout.println(ret);
		fout.close();
		System.exit(0);
	}
}
