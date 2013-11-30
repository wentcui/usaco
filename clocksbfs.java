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
	private static class stat {
		int clock = 0x00000000;
		int[] path = new int[27];
		int pos = 0;
		int[] ops = new int[10];
		public stat() {
		}

		public boolean validate() {
			if ((clock & mask) == 0)
				return true;
			return false;
		}
		public void flip(int op) {
			this.clock += (1 << (3 * op));
			this.clock &= mask;
			this.clock &= maskhigh;
		}
		
		public stat transfer(int[] op, int o) {
			if (this.ops[o] == 3)
				return null;
			this.ops[o]++;
			stat news = new stat();
			news.clock = this.clock;
			for(int i = 0; i < op.length; i++) {
				int opi = op[i] - 1;
				news.flip(opi);
			}
			System.arraycopy(this.path, 0, news.path, 0, 27);
			news.pos = this.pos;
			news.path[news.pos++] = o;
		
			System.arraycopy(this.ops, 0, news.ops, 0, 10);
			return news;
		}
	}
	public static void main (String [] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("clocks.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("clocks.out")));
		Queue<stat> q = new LinkedList<stat>();

		StringTokenizer st;
		int map[][]={{0},{1,2,4,5},{1,2,3},{2,3,5,6},{1,4,7},{2,4,5,6,8},{3,6,9},{4,5,7,8},{7,8,9},{5,6,8,9}};
		stat start = new stat();
		stat finalstat = null;
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
		start.clock = clock & mask;
		
		q.offer(start);
		if (start.validate()) {
			finalstat = start;
			success = true;
		}
		while(!success && !q.isEmpty()) {
			stat root = q.poll();
			int last = 1;
			if (root.pos > 0) {
				last = root.path[root.pos - 1];
			}
			for(int i = last; i <= 9; i++) {
				stat child = root.transfer(map[i], i);
				if (child == null) continue;
				if (child.validate()) {
					finalstat = child;
					success = true;
					break;
				}
				q.offer(child);
			}
		}
		String ress = "";
		if (finalstat != null) {
			int i = 0;
			for(i = 0; i < finalstat.pos - 1; i++) {
				ress += ("" + finalstat.path[i] + " ");
			}
			ress += finalstat.path[i];
		}		
		out.println(ress);
		out.close();                                  // close the output file
		System.exit(0);
	}
}
