struct anode {
  int key;
  char *value;
  struct anode *next;
};

struct hash {
    int size;
    struct anode **table;
};


struct hash make_table(int s);

char *search(struct hash T, int k);

void add(struct hash T, int k, char *v);

void free_table(struct hash T);

void delete(struct hash T, int k);
