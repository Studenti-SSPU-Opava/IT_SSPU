#include <stdio.h>

#define ZDARMA 2
#define DOPLATEK 20
#define CASY "casy.txt"
#define PLATBY "platby.txt"

typedef struct {
    int hour;
    int min;
    int sec;
} TIME;

void podtrhni() {
    printf("--------------------------------------------\n");
}

void hlavickaplatby(FILE *platby) {
    if (platby != NULL) {
        fprintf(platby, "Parkoviste - P L A T B Y\n");
        fprintf(platby, "------------------------\n");
        fprintf(platby, "pocet hodin parkovani zdarma       : %d\n", ZDARMA);
        fprintf(platby, "hodinova sazba po prekroceni limitu: %d Kc\n", DOPLATEK);
        fprintf(platby, "------------------------------------------------------------------\n");
        fprintf(platby, "poradi  cas vjezdu  cas vyjezdu  doba parkovani  nad limit  platba\n");
        fprintf(platby, "------------------------------------------------------------------\n");
    }

}

void hlavicka() {
    printf("P A R K O V I S T E\n");
    podtrhni();
    printf("poradi   cas      cas      doba parkovani\n");
    printf("         vjezdu   vyjezdu  sekundy    cas\n");
    podtrhni();
}

int seconds(TIME time) {
    return time.hour * 3600 + time.min * 60 + time.sec;
}

void parkTime(int seconds, FILE *pFile) {
    fprintf(pFile, "%02d:%02d:%02d", seconds / 3600, seconds % 3600 / 60, seconds % 60);
}

int main() {
    FILE *casy;
    FILE *platby;
    TIME time1;
    TIME time2;
    int poradi = 0;
    int pplatby = 0;
    int doba;

    if ((casy = fopen(CASY, "r")) == NULL) {
        printf("File %s has had an error opening.\n", CASY);
    } else {
        if ((platby = fopen(PLATBY, "w")) == NULL) {
            printf("File %s has had an error opening.\n", PLATBY);
        }
        hlavickaplatby(platby);
        hlavicka();
        while (fscanf(casy, "%d%d%d%d%d%d", &time1.hour, &time1.min, &time1.sec,
                      &time2.hour, &time2.min, &time2.sec) == 6) {
            poradi++;
            printf("%5d.  %02d:%02d:%02d  %02d:%02d:%02d %5d ", poradi, time1.hour, time1.min, time1.sec,
                   time2.hour, time2.min, time2.sec, seconds(time2) - seconds(time1));
            parkTime(seconds(time2) - seconds(time1), stdout);
            printf("\n");
            if (seconds(time2) - seconds(time1) > ZDARMA * 3600) {
                pplatby++;
                fprintf(platby, "%5d.  %02d:%02d:%02d    %02d:%02d:%02d     ", pplatby, time1.hour, time1.min, time1.sec,
                        time2.hour, time2.min, time2.sec);
                parkTime(seconds(time2) - seconds(time1), platby);
                fprintf(platby, "         ");
                parkTime(seconds(time2) - seconds(time1) - ZDARMA * 3600, platby);
                doba = seconds(time2) - seconds(time1) - ZDARMA * 3600;
                fprintf(platby,"%5d Kc\n", (doba / 3600 + (doba % 3600 > 0)) * DOPLATEK);
                //fprintf(platby,"%5d Kc\n", (doba / 3600 + (doba % 3600 == 0 ? 0 : 1)) * DOPLATEK);
            }
        }
        podtrhni();
        if (fclose(casy) == EOF) {
            printf("The file %s has had an error closing.\n", CASY);
        }
        if (fclose(platby) == EOF) {
            printf("The file %s has had an error closing.\n", PLATBY);
        } else {
            printf("The file %s has been created.\n", PLATBY);
        }
    }
    return 0;
}
