#include <stdio.h> 
#include <string.h>
#include <vector>

struct suffix_t {
	char v;
	int level;
	vector<struct suffix_t *> childs;
};

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
		node->v = *str;
		node->level = root->level + 1;
		(root->childs).push_back(node);
	}

	return ret + insert_and_count(node, str + 1);
}

int build_and_count(char *str) {
	struct suffix_t *root = NULL;
	int len = strlen(str);
	root = (struct suffix_t *)malloc(sizeof(struct suffix_t));
	if (!root)
		return 0;
	root->v = 0;
	root->level = 0;
	for(int i = 0; i < str; i++) {
		
	}
}
