/*
ID: wentcui1
LANG: JAVA
TASK: clocks
 */
import java.io.*;
import java.util.*;

class clocks {
	static boolean success = false;
	static int mask = (1 << 27) - 1;
	static int maskhigh = 0xFB6DB6DB;
	static BufferedReader f = null;
	static PrintWriter out = null;
	static int[][] map={{0},{1,2,4,5},{1,2,3},{2,3,5,6},{1,4,7},{2,4,5,6,8},{3,6,9},{4,5,7,8},{7,8,9},{5,6,8,9}};

	public static boolean validate(int clock) {
		if ((clock & mask) == 0)
			return true;
		return false;
	}
	public static int flip(int clock, int op) {
		clock += (1 << (3 * op));
		clock &= mask;
		clock &= maskhigh;
		return clock;
	}

	public static int transfer(int clock, int[] op, int o) {
		for(int i = 0; i < op.length; i++) {
			int opi = op[i] - 1;
			clock = flip(clock, opi);
		}
		return clock;
	}
	public static void dfs(int curclock, int[] path, int p, int[] opsmap) {
		if (success) return;
		int lastop = 1;
		if (p > 0)
			lastop = path[p - 1];

		for(int i = lastop; i <= 9 && !success; i++) {
			opsmap[i]++;
			if (opsmap[i] <= 3) {
				path[p] = i;
				int nextclock = transfer(curclock, map[i], i);	
				if (validate(nextclock)) {
					String ress = "";
					for(i = 0; i < p; i++) {
						ress += ("" + path[i] + " ");
					}
					ress += path[i];
					out.println(ress);
					out.close();	

					success = true;
					return;
				}

				dfs(nextclock, path, p + 1, opsmap);
			}
			opsmap[i]--;
		}
	}
	public static void main (String [] args) throws IOException {
    	f = new BufferedReader(new FileReader("clocks.in"));
    	out = new PrintWriter(new BufferedWriter(new FileWriter("clocks.out")));
		int[] path = new int[27];
		int[] opsmap = new int[10];

		StringTokenizer st;
		int clock = 0;
		int pos = 0;
		for(int i = 0; i < 3; i++) {
			st = new StringTokenizer(f.readLine());
			int v = Integer.parseInt(st.nextToken()) % 12;
			clock += ((v / 3) << (3 * pos));
			pos++;

			v = Integer.parseInt(st.nextToken()) % 12;
			clock += ((v / 3) << (3 * pos));
			pos++;

			v = Integer.parseInt(st.nextToken()) % 12;
			clock += ((v / 3) << (3 * pos));
			pos++;
		}
		clock = clock & mask;
		dfs(clock, path, 0, opsmap);
		System.exit(0);
	}

}
