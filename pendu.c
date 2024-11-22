#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 900
#define MAX_WORD_LENGTH 100

// affiche état du pendu switch declenche instruction en fction de valeur 
void afficherPendu(int tentatives) {
    switch (tentatives) {
        case 0:
            printf("    ____\n   |    |\n   |    \n   |    \n   |    \n   |    \n  _|_\n");
            break;
        case 1:
            printf("    ____\n   |    |\n   |    o\n   |    \n   |    \n   |    \n  _|_\n");
            break;
        case 2:
            printf("    ____\n   |    |\n   |    o\n   |    |\n   |    \n   |    \n  _|_\n");
            break;
        case 3:
            printf("    ____\n   |    |\n   |    o\n   |   /|\n   |    \n   |    \n  _|_\n");
            break;
        case 4:
            printf("    ____\n   |    |\n   |    o\n   |   /|\\\n   |    \n   |    \n  _|_\n");
            break;
        case 5:
            printf("    ____\n   |    |\n   |    o\n   |   /|\\\n   |    |\n   |    \n  _|_\n");
            break;
        case 6:
            printf("    ____\n   |    |\n   |    o\n   |   /|\\\n   |    |\n   |   /\n  _|_\n");
            break;
        case 7:
            printf("    ____\n   |    |\n   |    o\n   |   /|\\\n   |    |\n   |   / \\\n  _|_\n");
            break;
        default:
            break;
    }
}

// affiche le mot avec des underscores
void afficherMotAvecUnderscores(const char *mot, const char *lettresDevinees) {
    int longueur = strlen(mot);
    for (int i = 0; i < longueur; i++) {
        if (strchr(lettresDevinees, mot[i])) {
            printf("%c ", mot[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Fonction pour lire mots frm word txt
int lireMots(char mots[MAX_WORDS][MAX_WORD_LENGTH], const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier: %s\n", nomFichier);
        return 0;
    }
    
    int count = 0;
    while (count < MAX_WORDS && fgets(mots[count], MAX_WORD_LENGTH, fichier)) {
        mots[count][strcspn(mots[count], "\n")] = '\0'; 
        count++;
    }
    fclose(fichier);
    return count; //nombre de mots lus 
}


int main() {
    char name[33];
    char mots[MAX_WORDS][MAX_WORD_LENGTH];
    srand(time(NULL)); // a tt les temps a la millisc ya un nb attribuer au moment exact ou je lance le prog le nb de ce temps la = mot dans fichier 
    // Charger les mots depuis le fichier
    int nbMots = lireMots(mots, "words.txt");
    
    if (nbMots == 0) {
        printf("Aucun mot trouvé dans le fichier.\n");
        return 1;
    }

    printf("Quel est ton prénom s'il te plaît ?\n");
    scanf("%s", name);
    printf("Bonne chance, %s !\n", name);

    char rejouer[10];
    do {
        int indexAleatoire = rand() % nbMots; 
        // Choisi un mot aléatoire
        char *mot = mots[indexAleatoire];
        printf("mots :%s \n",mot);//test de commande pr afficher le mot secret (enlever le printf pr ne plus avoir ce mot)
        int longMot = strlen(mot);

        char motDevine[MAX_WORD_LENGTH]; //tab mot deviné
        for (int i = 0; i < longMot; i++) {
            motDevine[i] = '_'; // Initialiser avec des underscores
        }
        motDevine[longMot] = '\0'; // Caractère de fin de tableau

        int tentatives = 0;
        char lettresTentees[26] = {0}; // Les lettres tentées
        int lettresDejaTentees = 0; // Compteur des lettres tentées

        printf("Et bienvenue au jeu du Pendu !\n");

        while (tentatives < 7) {
            afficherPendu(tentatives);
            printf("Mot à deviner : %s\n", motDevine);
            printf("Les lettres que tu as tentées : %s\n", lettresTentees);
            afficherMotAvecUnderscores(mot, lettresTentees);

            char lettre;
            printf("Propose une lettre : ");
            scanf(" %c", &lettre);

            // Lettre tentée ?
            if (strchr(lettresTentees, lettre)) {
                printf("Tu as déjà essayé cette lettre\n");
                continue;
            }

            // Ajout de la lettre aux lettres tentées
            lettresTentees[lettresDejaTentees++] = lettre;

            //  lettre est dans le mot ?
            int lettreTrouvee = 0;
            for (int i = 0; i < longMot; i++) {
                if (mot[i] == lettre) {
                    motDevine[i] = lettre; // '_' = lettres deviner 
                    lettreTrouvee = 1;
                }
            }

            if (!lettreTrouvee) {
                tentatives++;
                printf("La lettre n'est pas correcte, ressaisis-toi !\n");
            }

            // Le joueur a gagné ?
            if (strcmp(motDevine, mot) == 0) { //strcmp compare mot et modevien si = cest bon
                afficherPendu(tentatives);
                printf("Félicitations ! Tu as deviné le mot : %s !\n", mot);
                break;
            }
        }

        if (tentatives == 7) {
            afficherPendu(tentatives);
            printf("Dommage ! Le mot était : %s\n", mot);
        }

        // Demander si le joueur veut rejouer
        printf("veux-tu rejouer ? (yes pour Oui, autre chose pour Non) : ");
        scanf("%s", rejouer);
    } while (strcmp(rejouer, "yes") == 0);

    printf("Merci d'avoir joué, %s ! on ce refais ça quand tu veux !\n", name);
    return 0;
}