/*
ID: wentcui1
LANG: JAVA
TASK: holstein
 */
import java.io.*;
import java.util.*;


class holstein {
	private static int[] req = null;
	private static int[][] feeds = null;
	private static int types;
	private static int feeds_nr;
	private static ArrayList<Integer> res = new ArrayList<Integer>();
	private static ArrayList<Integer> min_arr = new ArrayList<Integer>();
	private static int minFeedNr = Integer.MAX_VALUE;

	private static boolean validate(int[] cur) {
		for(int i = 0; i < cur.length; i++) {
			if (cur[i] < req[i])
				return false;
		}
		return true;
	}

	public static void dfs(int[] cur, int curindex, ArrayList<Integer> arr) {
		if (validate(cur)) {
			if (arr.size() < minFeedNr) {
				minFeedNr = arr.size();
				res = (ArrayList<Integer>) arr.clone();
			}
			return;
		}
		if (curindex >= feeds_nr)
			return;
		if (arr.size() >= minFeedNr)
			return;
		int i = 0;
		for(i = 0; !validate(cur); i++) {
			for(int j = 0; j < types; j++) {
				cur[j] += feeds[curindex][j];
			}
			arr.add(curindex + 1);
			dfs(cur, curindex + 1, arr);
		}
		for(int j = i; j > 0; j--) {
			arr.remove(arr.size() - 1);
			for(int k = 0; k < types; k++) {
				cur[k] -= feeds[curindex][k];
			}
		}
		dfs(cur, curindex + 1, arr);
	}
	public static void main(String[] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("holstein.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(
						"holstein.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
		types = Integer.parseInt(st.nextToken());
		req = new int[types];

		st = new StringTokenizer(f.readLine());
		for(int i = 0; i < types; i++) {
			req[i] = Integer.parseInt(st.nextToken());
		}

		st = new StringTokenizer(f.readLine());
		feeds_nr = Integer.parseInt(st.nextToken());

		feeds = new int[feeds_nr][types];
		for(int i = 0; i < feeds_nr; i++) {
			st = new StringTokenizer(f.readLine());
			for(int j = 0; j < types; j++) {
				feeds[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		dfs(new int[types], 0, new ArrayList<Integer>());
		out.print(res.size() + " ");
		for(int i = 0; i < res.size() - 1; i++) {
			out.print(res.get(i) + " ");
		}
		out.println(res.get(res.size() - 1));
		out.close();
		return;
	}
}
