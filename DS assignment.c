#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Match{
 int matchNumber;
 char teamA[50];
char teamB[50];
int scoreA;
int scoreB;
struct Match *next;
};

struct TeamStanding
{
char teamName[50];
int played,wins,draws,losses,goalsScored,goalsConceded,goalDifference,points;
   
};

struct Match *createMatch(int matchNumber, char teamA[], char teamB[]){
struct Match *newMatch;
newMatch = malloc(sizeof(struct Match));

if (newMatch == NULL)
return NULL;
newMatch->matchNumber = matchNumber;
strcpy(newMatch->teamA, teamA);
strcpy(newMatch->teamB, teamB);
newMatch->scoreA = 0;
newMatch->scoreB = 0;
newMatch->next = NULL;
return newMatch;
}

void insertAtHead(struct Match **head,
int matchNumber,
char teamA[],
char teamB[])
{
struct Match *newMatch;
newMatch = createMatch(matchNumber, teamA, teamB);
if (newMatch == NULL)
return;

newMatch->next = *head;
*head = newMatch;
 printf("Match inserted successfully.\n");
}
int countMatches(struct Match *head){
int count = 0;
while (head != NULL){
count++;
head = head->next;
}

return count;
}

void updateScore(struct Match *head,
int matchNumber,
 int scoreA,
int scoreB)
{
if (scoreA < 0 || scoreB < 0){
 printf("Invalid score!\n");
return;
}

while (head != NULL){
if (head->matchNumber == matchNumber)
{
head->scoreA = scoreA;
head->scoreB = scoreB;

printf("Score updated successfully.\n");
return;
}

head = head->next;
 }

printf("Match number %d not found.\n", matchNumber);
}

void searchMatchesByTeam(struct Match *head, char teamName[]){
int found = 0;

while (head != NULL){
if (strcmp(head->teamA, teamName) == 0 ||strcmp(head->teamB, teamName) == 0){
printf("Match %d: %s %d - %d %s\n",
head->matchNumber,head->teamA,head->scoreA,head->scoreB,
 head->teamB);

found = 1;
}

head = head->next;
}

if (!found)
 printf("No match found.\n");
}

int findTeam(struct TeamStanding teams[], int size, char name[])
{
int i;

for (i = 0; i < size; i++){
if (strcmp(teams[i].teamName, name) == 0)
return i;
}

return -1;
}

void generatePointsTable(struct Match *head, char teams[4][50])
{
struct TeamStanding t[4];
struct Match *temp;
int i, j;
for (i = 0; i < 4; i++){
strcpy(t[i].teamName, teams[i]);
t[i].played = 0;
t[i].wins = 0;
t[i].draws = 0;
 t[i].losses = 0;
t[i].goalsScored = 0;
t[i].goalsConceded = 0;
t[i].goalDifference = 0;
t[i].points = 0;
}

temp = head;
while (temp != NULL){
int a = findTeam(t, 4, temp->teamA);
int b = findTeam(t, 4, temp->teamB);

if (a != -1 && b != -1){
t[a].played++;
t[b].played++;
t[a].goalsScored += temp->scoreA;
t[a].goalsConceded += temp->scoreB;
t[b].goalsScored += temp->scoreB;
t[b].goalsConceded += temp->scoreA;

if (temp->scoreA > temp->scoreB){
t[a].wins++;
t[b].losses++;
t[a].points += 3;
}else if (temp->scoreA < temp->scoreB){
t[b].wins++;
t[a].losses++;
t[b].points += 3;
}
else{
t[a].draws++;
 t[b].draws++;
 t[a].points++;
t[b].points++;
}  }

 temp = temp->next;
}

for (i = 0; i < 4; i++){
t[i].goalDifference =
t[i].goalsScored - t[i].goalsConceded;
}

 for (i = 0; i < 3; i++){
for (j = i + 1; j < 4; j++){
int swap = 0;
if (t[j].points > t[i].points)
swap = 1;

else if (t[j].points == t[i].points &&
 t[j].goalDifference > t[i].goalDifference)
 swap = 1;

else if (t[j].points == t[i].points &&
t[j].goalDifference == t[i].goalDifference &&
t[j].goalsScored > t[i].goalsScored)
swap = 1;

else if (t[j].points == t[i].points &&
t[j].goalDifference == t[i].goalDifference &&
t[j].goalsScored == t[i].goalsScored &&
t[j].goalsConceded < t[i].goalsConceded)
swap = 1;
else if (t[j].points == t[i].points &&
t[j].goalDifference == t[i].goalDifference &&
t[j].goalsScored == t[i].goalsScored &&
t[j].goalsConceded == t[i].goalsConceded &&
strcmp(t[j].teamName, t[i].teamName) < 0)
swap = 1;

if (swap){
struct TeamStanding x = t[i];
t[i] = t[j];
t[j] = x;
}
}}
printf("\nRank Team             P W D L GF GA GD Pts\n");

for (i = 0; i < 4; i++){
 printf("%-4d %-16s %d %d %d %d %d %d %d %d\n",i + 1, t[i].teamName, t[i].played, t[i].wins, t[i].draws, t[i].losses, t[i].goalsScored, t[i].goalsConceded, t[i].goalDifference,t[i].points);
}
}

int main(){
struct Match *head = NULL;
char teams[4][50] =
{
 "Germany",
 "Argentina",
 "Brazil",
 "Portugal"
};
insertAtHead(&head, 1, "Germany", "Argentina");
insertAtHead(&head, 2, "Brazil", "Portugal");
insertAtHead(&head, 3, "Germany", "Brazil");
insertAtHead(&head, 4, "Argentina", "Portugal");
insertAtHead(&head, 5, "Germany", "Portugal");
insertAtHead(&head, 6, "Argentina", "Brazil");

printf("\nTotal Matches = %d\n", countMatches(head));

updateScore(head, 1, 2, 1);
updateScore(head, 2, 1, 1);
updateScore(head, 3, 2, 0);
updateScore(head, 4, 1, 1);
updateScore(head, 5, 2, 0);
updateScore(head, 6, 0, 1);

printf("\nMatches of Germany:\n");
searchMatchesByTeam(head, "Germany");

printf("\nPoints Table:\n");
generatePointsTable(head, teams);
return 0;
}
