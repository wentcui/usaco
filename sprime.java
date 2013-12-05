/*
ID: wentcui1
LANG: JAVA
TASK: sprime
 */
import java.io.*;
import java.util.*;

class sprime {
	static boolean isPrime(long n) {
		long i;

		if (n == 2)
			return true;

		if (n % 2 == 0)
			return false;

		for (i = 3; i * i <= n; i += 2)
			if (n % i == 0)
				return false;

		return true;
	}

	public static void main(String[] args) throws IOException {
		// Use BufferedReader rather than RandomAccessFile; it's much faster
		BufferedReader f = new BufferedReader(new FileReader("sprime.in"));
		// input file name goes above
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(
				"sprime.out")));
		// Use StringTokenizer vs. readLine/split -- lots faster
		StringTokenizer st = new StringTokenizer(f.readLine());
		// Get line, break into tokens
		int n = Integer.parseInt(st.nextToken()); // first integer
		long upperbound = (long) Math.pow(10, n);
		Queue<Long> q = new LinkedList<Long>();
		q.offer((long) 2);
		q.offer((long) 3);
		q.offer((long) 5);
		q.offer((long) 7);
		while(!q.isEmpty()) {
			long stat = q.poll();
			if (stat * 10 > upperbound) {
				out.println(stat);
				continue;
			}
			for(int i = 0; i <= 4; i++) {
				long nextstat = 10 * stat + 2 * i + 1;
				if (isPrime(nextstat)) {
					q.offer(nextstat);
				}
			}
		}

		out.close();
		System.exit(0);
	}
}
