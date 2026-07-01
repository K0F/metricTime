#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    time_t unix_time;
    double sub_seconds = 0.0;

    // Pokud je zadán argument, naparsujeme ho jako double (podpora pro sub-sekundy)
    if (argc > 1) {
        double raw_unix = atof(argv[1]);
        unix_time = (time_t)raw_unix;
        sub_seconds = raw_unix - (double)unix_time;
    } else {
        // Jinak vezmeme aktuální vysoce přesný systémový čas
        struct timeval tv;
        gettimeofday(&tv, NULL);
        unix_time = tv.tv_sec;
        sub_seconds = (double)tv.tv_usec / 1000000.0;
    }

    // Převod na lokální čas (bere v potaz nastavení časového pásma systému)
    struct tm *local = localtime(&unix_time);
    if (!local) {
        fprintf(stderr, "Chyba: Nepodařilo se zpracovat čas.\n");
        return 1;
    }

    // Celkový počet standardních sekund od dnešní půlnoci
    double std_secs_today = (local->tm_hour * 3600) + (local->tm_min * 60) + local->tm_sec + sub_seconds;

    // Koeficient pokroku dne (0.000000 až 1.000000)
    double day_fraction = std_secs_today / 86400.0;

    // Výpočet metrických hodin (0 až 20)
    double total_m_hours = day_fraction * 20.0;
    int dh_hours = (int)total_m_hours;

    // Výpočet metrických minut (0 až 100)
    double total_m_minutes = (total_m_hours - dh_hours) * 100.0;
    int dh_minutes = (int)total_m_minutes;

    // Výpočet metrických sekund (0 až 100)
    double total_m_seconds = (total_m_minutes - dh_minutes) * 100.0;
    int dh_seconds = (int)total_m_seconds;

    // Výstup ve formátech, které jsme navrhli
    printf("Standard:     %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
    printf("-------------------------\n");
    printf("Metric UI:    %02d.%02d.%02d\n", dh_hours, dh_minutes, dh_seconds);
    printf("Metric Float: %02d,%02d%02d dh\n", dh_hours, dh_minutes, dh_seconds);

    return 0;
}
