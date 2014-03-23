#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

int P, Q;

struct suffix_t {
	char v;
	int level;
	vector<struct suffix_t *> childs;
};

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void free_nodes(struct suffix_t *root) {
	struct suffix_t *cur;
	queue<struct suffix_t *> q;	
	q.push(root);
	while(!q.empty()) {
		cur = q.front();
		q.pop();
		for(int i = 0; i < cur->childs.size(); i++) {
			q.push(cur->childs[i]);
		}
		free(cur);
	}
}

struct suffix_t *get_node(vector<struct suffix_t *> childs, char v) {
	for(int i = 0; i < childs.size(); i++) {
		if (childs[i]->v == v)
			return childs[i];
	}
	return NULL;
}

int insert_and_count(struct suffix_t *root, char *str) {
	struct suffix_t *node = NULL;
	int ret = 0;
	if (*str == '\0')
		return 0;

	node = get_node(root->childs, *str);
	if (!node) {
		ret = 1;
		node = (struct suffix_t *)malloc(sizeof(struct suffix_t));
		if (!node)
			return 0;
		memset(node, 0, sizeof(struct suffix_t));
		node->v = *str;
		node->level = root->level + 1;
		(root->childs).push_back(node);
	}
	return ret + insert_and_count(node, str + 1);
}

long long int build_and_count(char *str) {
	struct suffix_t *root = NULL;
	int len = strlen(str), curlen, ret, v;
	long long int sum = 0;
	if (len < P)
		return 0;
	root = (struct suffix_t *)malloc(sizeof(struct suffix_t));
	if (!root)
		return 0;
	memset(root, 0, sizeof(struct suffix_t));
	root->v = 0;
	root->level = 0;
	for(int i = 0; i < len; i++) {
		curlen = len - i;
		if (curlen < P)
			break;
		ret = insert_and_count(root, str + i);
		if (!ret)
			continue;
		//printf("%s, ret: %d, curlen: %d, Q: %d, P: %d\n", str + i, ret, curlen, Q, P);
		v = min(curlen, Q) - max(curlen - ret, P);
		//printf("%d, %d, v: %d\n", min(curlen, Q), max(curlen - ret, P), v);
		if (v < 0)
			continue;
		sum += v;
		if (curlen - ret < P)
			sum++;
		//printf("%llu\n", sum);
	}
	free_nodes(root);
	return sum;
}

int main() {
	int cases, caseno = 0;
	char str[10001];
	scanf("%d", &cases);
	while(cases--) {
		memset(str, '\0', sizeof(char) * 101);
		scanf("%s", str);
		scanf("%d %d", &P, &Q);
		printf("Case %d: %lld\n", ++caseno, build_and_count(str));
	}
	return 0;
}
