#include <stdio.h>
int n;
int in[100003];
int in_idx[1000003]; // inorder에서 번호 i는 in_idx[i]번째에 위치함
int post[100003];
int pre[100003];
void solve(int in_st, int post_st, int len) { // in[in_st:in_st+len], post[post_st:post_st+len]를 보고 pre order를 출력하는 함수
	if (len == 0)
		return;
	if (len == 1) {
		printf("%d ", post[post_st]);
		return;
	}
	printf("%d ", post[post_st + len - 1]); //  post[post_st+len-1]이 현재 subtree의 root의 값이다. preorder이므로 일단 출력.
	int rootidx_in = in_idx[post[post_st + len - 1]]; //rootidx_in에는 inorder 상에서의 index가 들어간다.
	int len_leftSubtree = rootidx_in - in_st;
	solve(in_st, post_st, len_leftSubtree); // left subtree 먼저
	int len_rightSubtree = len - len_leftSubtree - 1;
	solve(rootidx_in + 1, post_st + len_leftSubtree, len_rightSubtree);
}
int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &in[i]);
		in_idx[in[i]] = i;
	}
	for (int i = 0; i < n; i++)
		scanf("%d", &post[i]);
	solve(0, 0, n);
}
