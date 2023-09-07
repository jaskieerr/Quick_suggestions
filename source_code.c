#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

const char *favorite_movies[] = {
    "Interstellar", "Schindler's List", "Dune", "Oppenheimer", "Inception", "Pirates of the Caribbean: The Curse of the Black Pearl",
    "Pirates of the Caribbean: Dead Man's Chest", "Pirates of the Caribbean: At World's End", "Pulp Fiction", "Once Upon a Time... in Hollywood", 
    "Inglourious Basterds", "Pirates of the Caribbean: On Stranger Tides", "Pirates of the Caribbean: Dead Men Tell No Tales", "Django Unchained", 
    "Kill Bill: Volume 1", "Kill Bill: Volume 2", "Reservoir Dogs", "The Hateful Eight", "Jackie Brown", "Tenet", "Dunkirk", "Memento", 
    "The Prestige", "The Dark Knight Rises", "Fight Club", "Fight Club", "The Mortal Instruments: City of Bones", "Gone Girl", "The Social Network", 
    "The Curious Case of Benjamin Button", "Blade Runner 2049", "Arrival", "2001: A Space Odyssey", "The Shining", "A Clockwork Orange", 
    "Full Metal Jacket", "Dr. Strangelove or: How I Learned to Stop Worrying and Love the Bomb", "The Worst Person in the World", 
    "Midsommar", "Hereditary", "The Hangover Part 1 2 3", "Druk", "Lord of the Rings Trilogy", 
    "If you didn't watch Marvel movies and TV-shows yet, what are you doing here", "The Nice Guys", "12 Angry Men", "Donnie Brasco", 
    "American Made", "Killers of the Flower Moon", "Goodfellas", "Taxi Driver (1976)", "The Wolf of Wall Street", "The Irishman", 
    "Shutter Island", "The Departed", "Catch Me If You Can", "The Godfather Trilogy", "Mission Impossible Movies", "Free Guy", 
    "Red Notice", "Green Lantern", "The Adam Project", "6 Underground", "The Hitman's Bodyguard", "Bullet Train", "Ghosted", 
    "Face/Off", "The Revenant", "Disturbia", "The Covenant (the edgy one not the soldiers' stuff)", "This Means War", "Easy A", 
    "STAR WARS IN ORDER", "Fury", "Transformers: Dark of the Moon", "Transformers: Revenge of the Fallen", "Constantine", 
    "The Machinist", "Jungle Cruise", "Gulliver's Travels", "The Mummy (1999)", "The Martian", "Gravity", "Ad Astra", 
    "Sunshine", "The Space Between Us", "The Mountain Between Us", "Warm Bodies", "World War Z", "Zombieland Parts 1 & 2", 
    "The Shawshank Redemption", "21 Jump Street Parts 1 & 2", "This Is the End", "Babylon", "The Good, the Bad and the Ugly", 
    "Forrest Gump", "The Matrix", "Goodfellas", "Saving Private Ryan", "The Green Mile", "Parasite", "The Prestige", 
    "Hereditary", "Ghost Rider", "Ghost Rider: Spirit of Vengeance", "Resident Evil (All of Them)", "The Wolf of Snow Hollow", 
    "Jojo Rabbit", "Catch Me If You Can", "Don't Look Up", "Blood Diamond", "Predestination"
};

const char *favorite_tv_shows[] = {
    "Dark", "Attack on Titans", "The Last Kingdom", "Sherlock", "Vinland Saga", "True Detective (Season 1)",
    "Lucifer", "Riverdale", "Fleabag", "The Boys", "Peaky Blinders", "Muhteşem Yüzyıl", "The Protector",
    "If you know me well, you'll know what's this (hhhhhhhhhhhh)", "Midnight at the Pera Palace", "The Flight Attendant",
    "Based On A True Story", "Friends", "Chernobyl", "Arcane (Episode 27)", "Better Call Saul", "Misfits (Stop watching when Nathan dies)",
    "You (especially Season 3)", "Hannibal (Season 2)", "Daredevil", "Hawkeye", "MoonKnight", "Loki", "The Queen's Gambit", "Banshee",
    "One Piece (Netflix)", "The Witcher", "The Walking Dead", "Supernatural", "Stranger Things", "Silo", "The Big Bang Theory",
    "Lost", "1899", "Westworld"
};

const char *My_top_10[] = {
    "Interstellar", "Dark", "Attack on Titans", "The Last Kingdom", "Blood Diamond", "Sherlock", "Schindler's List",
    "Django Unchained", "2001: A Space Odyssey", "Vinland Saga"
};

#define MAX_WATCHLIST_SIZE 100

const char *watchlist[MAX_WATCHLIST_SIZE];
int watchlist_count = 0;

const char *previous_suggestion = NULL;

void displayMainMenu() {
    printf("Merhba bik who ever u are except if ur a flat earther pls fuck off\n");
    printf("Choice 0: one Random favorite movie\n");
    printf("Choice 1: one Random favorite TV show\n");
    printf("Choice 2: one of my top 10\n");
    printf("Choice 3: watchlist\n");
    printf("Choice 5: Add item to watchlist\n");
    printf("Choice 6: Exit\n");
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

bool isItemInWatchlist(const char *item) {
    char lowercase_item[100];
    strcpy(lowercase_item, item);
    toLowerCase(lowercase_item);

    for (int i = 0; i < watchlist_count; i++) {
        if (strcmp(lowercase_item, watchlist[i]) == 0) {
            return true;
        }
    }
    return false;
}

void addToWatchlist(const char *item) {
    if (watchlist_count < MAX_WATCHLIST_SIZE) {
        watchlist[watchlist_count] = item;
        watchlist_count++;
        printf("%s added to your watchlist.\n", item);
    }
}

void saveWatchlistToFile() {
    FILE *file = fopen("watchlist.txt", "w");
    if (file == NULL) {
        printf("jreb trunini as admin if u can't save.\n");
        return;
    }

    for (int i = 0; i < watchlist_count; i++) {
        fprintf(file, "%s\n", watchlist[i]);
    }

    fclose(file);
    printf("intresting choice\n");
}

void loadWatchlistFromFile() {
    FILE *file = fopen("watchlist.txt", "r");
    if (file == NULL) {
        printf("Makayen bou watchlist.\n");
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        addToWatchlist(buffer);
    }

    fclose(file);
    printf("Watchlist loaded successfully.\n");
}

int main() {
    srand(time(NULL));

    loadWatchlistFromFile();

    while (1) {
        int choice;

        displayMainMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 0: {
                int random_movie_index;
                do {
                    random_movie_index = rand() % (sizeof(favorite_movies) / sizeof(favorite_movies[0]));
                } while (isItemInWatchlist(favorite_movies[random_movie_index]) || favorite_movies[random_movie_index] == previous_suggestion);
                previous_suggestion = favorite_movies[random_movie_index];
                printf("One Random favorite movie: %s\n", favorite_movies[random_movie_index]);
                break;
            }
            case 1: {
                int random_tv_show_index;
                do {
                    random_tv_show_index = rand() % (sizeof(favorite_tv_shows) / sizeof(favorite_tv_shows[0]));
                } while (isItemInWatchlist(favorite_tv_shows[random_tv_show_index]) || favorite_tv_shows[random_tv_show_index] == previous_suggestion);
                previous_suggestion = favorite_tv_shows[random_tv_show_index];
                printf("One Random favorite TV show: %s\n", favorite_tv_shows[random_tv_show_index]);
                break;
            }
            case 2: {
                int random_top_10_index;
                do {
                    random_top_10_index = rand() % (sizeof(My_top_10) / sizeof(My_top_10[0]));
                } while (isItemInWatchlist(My_top_10[random_top_10_index]) || My_top_10[random_top_10_index] == previous_suggestion);
                previous_suggestion = My_top_10[random_top_10_index];
                printf("One of my top 10: %s\n", My_top_10[random_top_10_index]);
                break;
            }
            case 3:
                printf("Watchlist:\n");
                for (int i = 0; i < watchlist_count; i++) {
                    printf("%d: %s\n", i + 1, watchlist[i]);
                }
                break;
            case 5:
                printf("add item to watchlist: ");
                char newItem[100];
                scanf("%s", newItem);
                addToWatchlist(newItem);
                break;
            case 6:
                saveWatchlistToFile();
                printf("ur welcome ;)\n");
                return 0;
            default:
                printf("picki 1 /2/3 ... , if the program goes mad click Ctrl + C\n");
        }
    }

    return 0;
}
