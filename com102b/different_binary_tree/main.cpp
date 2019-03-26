#include <iostream>
#include <string>

/*
 * Diff test komutları

 g++ main.cpp && ./a.out < test_data/alphabet.txt | diff test_data/alphabet_out.txt -
 g++ main.cpp && ./a.out < test_data/names_short1.txt | diff test_data/names_short1_out.txt -
 g++ main.cpp && ./a.out < test_data/names_short2.txt | diff test_data/names_short2_out.txt -
 g++ main.cpp && ./a.out < test_data/names_short3.txt | diff test_data/names_short3_out.txt -
 g++ main.cpp && ./a.out < test_data/names1.txt | diff test_data/names1_out.txt -
 g++ main.cpp && ./a.out < test_data/names2.txt | diff test_data/names2_out.txt -
 */

using namespace std;

struct node {
    string word;
    node *left;
    node *right;
    node *father;
};

void printPreOrder(node *root) {
    if (root) {
        cout << root->word << endl;
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPostOrder(node *root) {
    if (root) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        cout << root->word << endl;

    }
}

void printInOrder(node *root) {
    if (root) {
        printInOrder(root->left);
        cout << root->word << endl;
        printInOrder(root->right);
    }
}

void printNoChild(node *root) {
    if (root) {
        int found = 0;
        if (root->left) {
            found = 1;
            printNoChild(root->left);
        }
        if (root->right) {
            found = 1;
            printNoChild(root->right);
        }
        if (found == 0) {
            cout << root->word << endl;
        }
    }
}

int countNodes(node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int bitcount(int num) {
    int n = 0;
    while (num) {
        num /= 2;
        n++;
    }
    return n;
}


/*
 * Algoritma detayı:
 *
 * 1. countNodes ile nodun kendisi + node 'a bağlı eleman sayısı toplamı bulunur.
 * 2. node'a bağlı eleman sayısı örneğin 13 ( binary 1101 )
 * 3. Komutları sırayla işlemek için ters çevirildi. (1011) (en sağdaki komut gözardı edilir.)
 * 4. Her bir komut için bu binary 1 sağa kaydırılır ve 2 ile modu alınır. Sırayla 1, 0, 1 döndürür.
 * 5. 1 sağdaki noda git, 0 ise soldaki node a git komutu olacak şekilde sırayla işlenir.
 * 6. en son ulaşılan adres insert etmek istediğimiz verinin adresidir.
 */
void insert(node **current, string word) {
    node* father = NULL;

    int pos = countNodes(*current) + 1; // nodeların sayısı + yeni eklenecek node
    int bc = bitcount(pos) - 1; // bit(komut) sayısını bul ve atılan en soldaki 1 den dolayı 1 eksilt.
    int commands = 0;

    /**
     * Komutları sırayla işlemek için bitleri ters çevir.
     */
    while (pos) {
        commands = commands * 2;
        commands = commands + pos % 2;
        pos /= 2;
    }
    while (bc) {//işlenilecek bit komutu olduğu sürece
        /*
         * Bir sonraki bit komutunu getir.
         */
        father = *current;
        if ((commands >>= 1) % 2) {  /// Bir sonraki bit komutu 1 ise
            current = &((*current)->right);
        } else {
            current = &((*current)->left);
        }
        bc--;
    }
    *current = new node;
    (*current)->left = NULL;
    (*current)->right = NULL;
    (*current)->word = word;
    (*current)->father = father;
}


int main() {
    node *root = NULL;
    string word;
    while (1) {
        cin >> word;
        if (word == "end") {
            break;
        }
        insert(&root, word);
    }
    int i;
    while (scanf("%d", &i) == 1) {
        if (i == 1) {
            cout << "*****"<< endl;
            printPreOrder(root);
        } else if (i == 2) {
            cout << "*****"<< endl;
            printPostOrder(root);
        } else if (i == 3) {
            cout << "*****"<< endl;
            printInOrder(root);
        } else if (i == 4) {
            cout << "*****" << endl;
            printNoChild(root);
        } else if (i < 0) {
            break;
        }
    }
    cout << "Done!";
}
