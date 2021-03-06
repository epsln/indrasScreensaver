#ifndef treeExploration
#define treeExploration

void goForward(int *lev, int* tag, int* state, int FSA[19][4], double complex* word, double complex* gens);
void goBackwards(int *lev);
int availableTurn(int *lev, int *tag, int* state, int FSA[19][4]);
void turnForward(int *lev, int *tag,int* state, int FSA[19][4], double complex* word, double complex* gens);

int branchTermRepetends(int lev, int* tag, double complex fixRep[4][4], double complex* word, image_t *img, xStuff x);

void computeDepthFirst(double complex* gens, image_t *img, xStuff x, int numIm);
#endif
