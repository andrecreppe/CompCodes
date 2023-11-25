#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    vector<Node*> children;
    int count;
    bool isWord;

    Node() : count(0), isWord(false) {
        children.resize(26, nullptr);
    }
};

Node* root;

void addWord(string word) {
    Node* current = root;

    for (char c : word) {
        int index = c - 'a';

        if (!current->children[index])
            current->children[index] = new Node();

        current = current->children[index];
        current->count++;
    }

    current->isWord = true;
}

void removeWord(string word) {
    Node* current = root;

    for (char c : word) {
        int index = c - 'a';

        if (!current->children[index])
            return; // A palavra não está na árvore

        current = current->children[index];
        current->count--;
    }

    current->isWord = false;
}

int countPrefix(string prefix) {
    Node* current = root;

    for (char c : prefix) {
        int index = c - 'a';

        if (!current->children[index])
            return 0; // Prefixo não encontrado

        current = current->children[index];
    }

    return current->count;
}

int main() {
    int q, t;
    string s;

    root = new Node();

    cin >> q;
    for(int i=0; i<q; i++) {
        cin >> t >> s;

        if (t == 1)
            addWord(s);  // Adicionar palavra na árvore de sufixos
        else if (t == 2)
            removeWord(s); // Remover palavra da árvore de sufixos
        else if (t == 3) {
            // Contar palavras
            int result = countPrefix(s);
            cout << result << endl;
        }
    }

    return 0;
}
