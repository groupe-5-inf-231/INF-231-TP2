#include <stdio.h>
#include <stdlib.h>

//==============================//
//   DEFINITION DES STRUCTURES  //
//==============================//

// Liste simplement chaînée
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Liste doublement chaînée
typedef struct DNode {
    int data;
    struct DNode *prev, *next;
} DNode;

//==============================//
//   1. SUPPRIMER LES OCCURENCES //
//==============================//

Node* supprimerOccurences(Node* head, int val) {
    Node *prev = NULL, *curr = head;

    while (curr != NULL) {
        if (curr->data == val) {
            if (prev == NULL) { // cas tête
                head = curr->next;
                free(curr);
                curr = head;
            } else {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

//==============================//
//   2. INSERTION DANS LISTE S.C TRIÉE //
//==============================//

Node* insererTrieSC(Node* head, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL || val < head->data) {
        newNode->next = head;
        return newNode;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->data < val)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

//==============================//
//   3. INSERTION LISTE D.C TRIÉE //
//==============================//

DNode* insererTrieDC(DNode* head, int val) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = val;
    newNode->prev = newNode->next = NULL;

    if (head == NULL || val < head->data) {
        newNode->next = head;
        if (head) head->prev = newNode;
        return newNode;
    }

    DNode* temp = head;
    while (temp->next != NULL && temp->next->data < val)
        temp = temp->next;

    newNode->next = temp->next;
    if (temp->next) temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

//==============================//
//   4. LISTE S.C CIRCULAIRE //
//==============================//

Node* insererTeteSC_Circ(Node* tail, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;

    if (tail == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    newNode->next = tail->next;
    tail->next = newNode;
    return tail;
}

Node* insererQueueSC_Circ(Node* tail, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;

    if (tail == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    newNode->next = tail->next;
    tail->next = newNode;
    return newNode; // new tail
}

//==============================//
//   5. LISTE D.C CIRCULAIRE //
//==============================//

DNode* insererTeteDC_Circ(DNode* tail, int val) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = val;

    if (tail == NULL) {
        newNode->next = newNode->prev = newNode;
        return newNode;
    }

    newNode->next = tail->next;
    newNode->prev = tail;
    tail->next->prev = newNode;
    tail->next = newNode;
    return tail; 
}

DNode* insererQueueDC_Circ(DNode* tail, int val) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = val;

    if (tail == NULL) {
        newNode->next = newNode->prev = newNode;
        return newNode;
    }

    newNode->next = tail->next;
    newNode->prev = tail;
    tail->next->prev = newNode;
    tail->next = newNode;
    return newNode; // new tail
}

//==============================//
//   FONCTIONS D’AFFICHAGE //
//==============================//

void afficherSC(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void afficherDC(DNode* head) {
    DNode* temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void afficherSC_Circ(Node* tail) {
    if (tail == NULL) return;
    Node* temp = tail->next;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != tail->next);
    printf("(circ)\n");
}

void afficherDC_Circ(DNode* tail) {
    if (tail == NULL) return;
    DNode* temp = tail->next;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != tail->next);
    printf("(circ)\n");
}

//==============================//
//   MAIN INTERACTIF //
//==============================//

int main() {
    int choix, val, n, i;

    Node* sc = NULL;        // Liste simplement chaînée
    DNode* dc = NULL;       // Liste doublement chaînée
    Node* sc_circ = NULL;   // Liste simplement circulaire
    DNode* dc_circ = NULL;  // Liste doublement circulaire

    do {
        printf("\n=== MENU ===\n");
        printf("1. Insertion triée dans une liste simplement chaînée\n");
        printf("2. Supprimer toutes les occurrences dans une liste simplement chaînée\n");
        printf("3. Insertion triée dans une liste doublement chaînée\n");
        printf("4. Insertion en tête et queue dans une liste simplement chaînée circulaire\n");
        printf("5. Insertion en tête et queue dans une liste doublement chaînée circulaire\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Combien de valeurs à insérer ? ");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    printf("Valeur %d : ", i+1);
                    scanf("%d", &val);
                    sc = insererTrieSC(sc, val);
                }
                printf("Liste SC : ");
                afficherSC(sc);
                break;

            case 2:
                printf("Valeur à supprimer : ");
                scanf("%d", &val);
                sc = supprimerOccurences(sc, val);
                printf("Liste SC après suppression : ");
                afficherSC(sc);
                break;

            case 3:
                printf("Combien de valeurs à insérer ? ");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    printf("Valeur %d : ", i+1);
                    scanf("%d", &val);
                    dc = insererTrieDC(dc, val);
                }
                printf("Liste DC : ");
                afficherDC(dc);
                break;

            case 4:
                printf("Valeur en tête : ");
                scanf("%d", &val);
                sc_circ = insererTeteSC_Circ(sc_circ, val);
                printf("Valeur en queue : ");
                scanf("%d", &val);
                sc_circ = insererQueueSC_Circ(sc_circ, val);
                printf("Liste SC circulaire : ");
                afficherSC_Circ(sc_circ);
                break;

            case 5:
                printf("Valeur en tête : ");
                scanf("%d", &val);
                dc_circ = insererTeteDC_Circ(dc_circ, val);
                printf("Valeur en queue : ");
                scanf("%d", &val);
                dc_circ = insererQueueDC_Circ(dc_circ, val);
                printf("Liste DC circulaire : ");
                afficherDC_Circ(dc_circ);
                break;

            case 0:
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
