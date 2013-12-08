/*
ID: wentcui1
LANG: JAVA
TASK: frac1
 */
import java.io.*;
import java.util.*;

class frac1 {
	public static class ListNode {
		int a;
		int b;
		ListNode next;
		ListNode(int i, int j) {
			this.a = i;
			this.b = j;
			next = null;
		}
	}
	public static int compare(ListNode n1, ListNode n2) {
		float f1 = (float)n1.a / (float)n1.b;
		float f2 = (float)n2.a / (float)n2.b;
		return Float.compare(f1, f2);
	}
	public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
		if (l1 == null)
			return l2;
		if (l2 == null)
			return l1;
		ListNode head = null, last = null;
		if (compare(l1, l2) < 0) {
			head = l1;
			l1 = l1.next;
		} else {
			head = l2;
			l2 = l2.next;
		}

		last = head;
		while (l1 != null && l2 != null) {
			if (compare(l1, l2) < 0) {
				last.next = l1;
				l1 = l1.next;
			} else {
				last.next = l2;
				l2 = l2.next;
			}
			last = last.next;
		}
		if (l1 != null)
			last.next = l1;
		else
			last.next = l2;
		return head;
	}
	public static ListNode mergeKlists(ArrayList<ListNode> lists, int start, int end) {
		if (start == end)
			return lists.get(start);
		int mid = start + (end - start) / 2;
		return mergeTwoLists(mergeKlists(lists, start, mid), 
				mergeKlists(lists, mid + 1, end));
	}

	public static boolean validate(int a, int b) {
		if (a == 1)
			return true;
		if (b % a == 0)
			return false;
		for(int i = 2; i <= a; i++) {
			if (a % i == 0 && b % i == 0)
				return false;
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("frac1.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(
						"frac1.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int n = Integer.parseInt(st.nextToken());
		if (n == 1) {
			out.println("0/1");
			out.println("1/1");
			out.close();
			System.exit(0);
		}
		ArrayList<ListNode> lists = new ArrayList<ListNode>();
		for(int i = 2; i <= n; i++) {
			ListNode last = null;
			for(int j = 1; j < i; j++) {
				if (!validate(j, i)) continue;
				ListNode node = new ListNode(j, i);
				if (j == 1) {
					lists.add(node);
					last = node;
				} else {
					last.next = node;
					last = node;
				}
			}
		}
		ListNode head = mergeKlists(lists, 0, lists.size() - 1);
		out.println("0/1");
		while(head != null) {
			out.println("" + head.a + "/" + head.b);
			head = head.next;
		}
		out.println("1/1");
		out.close();
		System.exit(0);
	}
}
