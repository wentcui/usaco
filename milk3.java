/*
ID: wentcui1
LANG: JAVA
TASK: milk3
 */
import java.io.*;
import java.util.*;

class milk3 {
	static int A, B, C;
	// check whether this is the original status
	public static boolean check(int stat) {
		return (getv(stat, 2) == 0 && getv(stat, 1) == 0);
	}

	// candidate stat?
	public static boolean validate(int stat) {
		return getv(stat, 2) == 0;
	}

	public static int getv(int stat, int pos) {
		int mask = ((1 << 5) - 1) << (pos * 5);
		return (stat & mask) >> (pos * 5);

	}
	public static int transfer(int stat, int v, int from, int to) {
		// op true, +; false -;
		stat -= (v << (from * 5));
		stat += (v << (to * 5));
		return stat;
	}
	public static void main (String [] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("milk3.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk3.out")));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		A = Integer.parseInt(st.nextToken());
		B = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		int mask = (1 << 15) - 1;
		int stat = (C & mask);
		int a = 0, b = 0, c = C, v, nextstat;
		boolean[] map = new boolean[mask + 1]; 
		map[stat] = true;
		Queue<Integer> q = new LinkedList<Integer>();
		ArrayList<Integer> res = new ArrayList<Integer>();
		q.offer(stat);

		while(!q.isEmpty()) {
			stat = q.poll();
			if (validate(stat))
				res.add(getv(stat, 0));
			c = getv(stat, 0);
			b = getv(stat, 1);
			a = getv(stat, 2);
			if (c > 0) {
				// c to b
				v = Math.min(c, B - b);
				if (v > 0) {
					nextstat = transfer(stat, v, 0, 1);
					if (nextstat != stat && !map[nextstat]) {
						q.offer(nextstat);
						map[nextstat] = true;
					}
				}
				// c to a
				v = Math.min(c, A - a);
				if (v > 0) {
					nextstat = transfer(stat, v, 0, 2);
					if (nextstat != stat && !map[nextstat]) {
						q.offer(nextstat);
						map[nextstat] = true;
					}
				}
			}
			if (b > 0) {
				// b to a
				v = Math.min(b, A - a);
				if (v > 0) {
					nextstat = transfer(stat, v, 1, 2);
					if (nextstat != stat && !map[nextstat]) {
						q.offer(nextstat);
						map[nextstat] = true;
					}
				}
				// b to c
				v = Math.min(b, C - c);
				if (v > 0) {
					nextstat = transfer(stat, v, 1, 0);
					if (nextstat != stat && !map[nextstat]) {
						q.offer(nextstat);
						map[nextstat] = true;
					}
				}
			}

			if (a > 0) {
				// a to b
				v = Math.min(a, B - b);
				if (v > 0) {
					nextstat = transfer(stat, v, 2, 1);
					if (nextstat != stat && !map[nextstat]) {
						q.offer(nextstat);
						map[nextstat] = true;
					}
				}
				// a to c
				v = Math.min(a, C - c);
				if (v > 0) {
					nextstat = transfer(stat, v, 2, 0);
					if (nextstat != stat && !map[nextstat]) {
						q.offer(nextstat);
						map[nextstat] = true;
					}
				}
			}
		}
		int[] ret = new int[res.size()];
		for(int i = 0; i < res.size(); i++) {
			ret[i] = res.get(i);
		}
		Arrays.sort(ret);
		for(int i = 0; i < ret.length - 1; i++) {
			fout.print(ret[i] + " ");
		}
		fout.println(ret[ret.length - 1]);
		fout.close();
		System.exit(0);
	}
}
