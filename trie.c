#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

void destroy();

typedef struct FU_node {
  int alive;
  uint64_t energy;
  uint64_t children_c;
  struct FU_node *father;
} FU_node;

typedef struct T_node {
  struct T_node *children[4];
  struct FU_node *energy;
} T_node;

static T_node *root;

void init() {
  root = calloc(1, sizeof(T_node));
}

T_node *create_t_node() {
  T_node *node = calloc(1, sizeof(T_node));
  if(node == NULL) {
    destroy();
    exit(1);
  }
  node->energy=NULL;
  return node;
}

FU_node *create_fu_node(uint64_t e) {
  FU_node *node = calloc(1, sizeof(FU_node));
  if(node==NULL) {
    destroy();
    exit(1);
  }
  node->alive = 1;
  node->father = node;
  node->energy = e;
  node->children_c = 0;
  return node;
}

FU_node *fu_find(FU_node *node) {
  if(node->father == node) return node;
  return fu_find(node->father);
}

void fu_union(FU_node *a, FU_node *b) {
  FU_node *a_father = fu_find(a);
  FU_node *b_father = fu_find(b);
  if(a_father != b_father) {
    a_father->father = b_father;
    b_father->children_c++;
  }
}

void delete_fu_node_rec(FU_node *node) {
  // printf("eldo\n" );
  if(node->children_c || node->alive) return;
  if(node->father != node) {
    node->father->children_c--;
    delete_fu_node_rec(node->father);
  }
  free(node);
}

void delete_fu_node(FU_node *node) {
  if(!node) return;
  node->alive = 0;
  delete_fu_node_rec(node);
}

void insert_internal(const char *s, T_node *node, int sl) {
  if(node->children[s[0]-'0'] == NULL) {
    node->children[s[0]-'0'] = create_t_node();
    if(node->children[s[0]-'0'] == NULL) {
      destroy();
      exit(1);
    }
  }
  if(--sl) insert_internal(s+1, node->children[s[0]-'0'], sl);
}

void insert(const char *s) {
  int sl = strlen(s);
  if(root->children[s[0]-'0'] == NULL) {
    root->children[s[0]-'0'] = create_t_node();
    if(root->children[s[0]-'0'] == NULL) {
      destroy();
      exit(1);
    }
  }
  if(--sl) insert_internal(s+1, root->children[s[0]-'0'], sl);
  printf("%s\n", "OK");
}

int find_internal(const char *s, T_node *node, int sl) {
  if(node->children[s[0]-'0'] == NULL) return 0;
  if(--sl) return find_internal(s+1, node->children[s[0]-'0'], sl);
  return 1 + (node->children[s[0]-'0']->energy != NULL);
}

int find(const char *s) {
  int sl = strlen(s);
  if(root->children[s[0]-'0'] == NULL)
    return 0;
  if(--sl) return find_internal(s+1, root->children[s[0]-'0'], sl);
  return 1 + (root->children[s[0]-'0']->energy != NULL);
}

void valid(const char *s) {
  if(find(s)!=0) {
    printf("%s\n", "YES");
    return;
  }
  printf("%s\n", "NO");
}

void delete_tree(T_node *node) {
  for(int i=0; i<4; i++) {
    if(node->children[i] != NULL) {
      if(node->children[i]->energy)
        delete_fu_node(node->children[i]->energy);
      node->children[i]->energy = NULL;
      delete_tree(node->children[i]);
      node->children[i] = NULL;
    }
  }
  free(node);
  return;
}

void delete_internal(const char *s, T_node *node, int sl) {
  if(sl==1) {
    if(node->children[s[0]-'0']->energy)
      delete_fu_node(node->children[s[0]-'0']->energy);
    node->children[s[0]-'0']->energy = NULL;
    delete_tree(node->children[s[0]-'0']);
    node->children[s[0]-'0'] = NULL;
    return;
  }
  delete_internal(s+1, node->children[s[0]-'0'], sl-1);
}

void delete(const char *s) {
  if(!find(s)) {
    printf("%s\n", "OK");
    return;
  }
  int sl = strlen(s);
  if(sl == 1) {
    delete_fu_node(root->children[s[0]-'0']->energy);
    root->children[s[0]-'0']->energy = NULL;
    delete_tree(root->children[s[0]-'0']);
    root->children[s[0]-'0'] = NULL;
    printf("%s\n", "OK");
    return;
  }
  delete_internal(s+1, root->children[s[0]-'0'], sl-1);
  printf("%s\n", "OK");
}

void set_value_internal(const char *s, T_node *node, int sl, uint64_t val) {
  if(sl == 0) {
    if(node->energy == NULL) {
      node->energy = create_fu_node(val);
      if(node->energy == NULL) {
        destroy();
        exit(1);
      }
    }
    else {
      FU_node *e = fu_find(node->energy);
      e->energy = val;
    }
    return;
  }
  set_value_internal(s+1, node->children[s[0]-'0'], sl-1, val);
}

void set_value(const char *s, uint64_t val) {
  if(!(find(s) && val)) {
    fprintf(stderr, "ERROR\n");
    return;
  }
  int sl = strlen(s);
  set_value_internal(s+1, root->children[s[0]-'0'], sl-1, val);
  printf("%s\n", "OK");
}

uint64_t get_value_internal(const char *s, T_node *node, int sl) {
  if(sl==0) {
    FU_node *e = fu_find(node->energy);
    return e->energy;
  }
  return get_value_internal(s+1, node->children[s[0]-'0'], sl-1);
}

void get_value(const char *s) {
  if(find(s) != 2) {
    fprintf(stderr, "ERROR\n");
    return;
  }
  int sl = strlen(s);
  printf("%llu\n", get_value_internal(s+1, root->children[s[0]-'0'], sl-1));
}

T_node *get_t_node(const char *s, T_node *node, int sl) {
  if(sl==0) {
    return node;
  }
  return get_t_node(s+1, node->children[s[0]-'0'], sl-1);
}

void equal(const char *s1, const char *s2) {
  int f1 = find(s1);
  int f2 = find(s2);
  if(strcmp(s1, s2) == 0 && f1 != 0) {
    printf("%s\n", "OK");
    return;
  }
  if((f1 != 2 && f2 != 2) || !(f1>=1 && f2>=1)) {
    fprintf(stderr, "ERROR\n");
    return;
  }
  int sl1 = strlen(s1);
  int sl2 = strlen(s2);
  T_node *n1 = get_t_node(s1+1, root->children[s1[0]-'0'], sl1-1);
  T_node *n2 = get_t_node(s2+1, root->children[s2[0]-'0'], sl2-1);
  if(n1->energy != NULL && n2->energy != NULL) {
    uint64_t e1 = fu_find(n1->energy)->energy;
    uint64_t e2 = fu_find(n2->energy)->energy;
    uint64_t sr = e1/2 + e2/2 + (e1%2==1 && e2%2==1);
    fu_union(n1->energy, n2->energy);
    fu_find(n1->energy)->energy = sr;
  }
  if(n1->energy != NULL && n2->energy == NULL) {
    n2->energy = create_fu_node(0);
    fu_union(n2->energy, n1->energy);
  }
  if(n1->energy == NULL && n2->energy != NULL) {
    n1->energy = create_fu_node(0);
    fu_union(n1->energy, n2->energy);
  }
  printf("%s\n", "OK");
}

void delete_fu_and_trie(T_node *node) {
  for(int i=0; i<4; i++) {
    if(node->children[i] != NULL) {
      delete_fu_and_trie(node->children[i]);
      node->children[i]=NULL;
    }
  }
  if(node->energy) delete_fu_node(node->energy);
  node->energy = NULL;
  free(node);
}

void destroy() {
  delete_fu_and_trie(root);
  root=NULL;
}
