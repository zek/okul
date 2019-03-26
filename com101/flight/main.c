#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void clrscr() {
    system("@cls||clear");
}

typedef struct {
    unsigned int month, year, day;
} Day;

typedef struct {
    unsigned int hour, minute;
} Time;

typedef struct {
    unsigned int num;
    char dep[50];
    char arr[50];
    Day dep_day;
    Time dep_time;
    Day arr_day;
    Time arr_time;
    int pass_count;
} Flight;

typedef struct {
    char first_name[50];
    char last_name[50];
    char dep[50];
    char arr[50];
    Day dep_day;
    Flight *flight;
} Passenger;


Flight *searchFlight(Flight *flights, unsigned int flight_count, unsigned int flight_number) {
    int i;
    for (i = 0; i < flight_count; ++i) {
        if (flights[i].num == flight_number) {
            return &flights[i];
        }
    }
    return 0;
}

void printDay(Day day) {
    printf("%02d/%02d/%04d", day.day, day.month, day.year);
}

void printTime(Time time) {
    printf("%02d:%02d", time.hour, time.minute);
}

void printFlight(Flight flight) {
    printf("%d %s %s", flight.num, flight.dep, flight.arr);
    printf(" ");
    printDay(flight.dep_day);
    printf(" ");
    printTime(flight.dep_time);
    printf(" ");
    printDay(flight.arr_day);
    printf(" ");
    printTime(flight.arr_time);
}

int scanTime(Time *time) {
    if (scanf("%d%*c%d", &time->hour, &time->minute) == 2) {
        if (time->hour <= 23 && time->minute <= 59) {
            return 2;
        }
    }
    printf("Invalid Time\n");
    return 0;
}

int scanDay(Day *day) {
    if (scanf("%d%*c%d%*c%d", &day->day, &day->month, &day->year) == 3) {
        if (day->day > 0 && day->day < 32 && day->month > 0 && day->month < 13) {
            return 3;
        }
    }
    printf("Invalid Date\n");
    return 0;
}

int compareDay(Day a, Day b) {
    return a.year == b.year && a.day == b.day && a.month == b.month;
}

int compareTime(Time a, Time b) {
    if (a.hour > b.hour) {
        return 1;
    } else if (a.hour == b.hour) {
        if (a.minute > b.minute) {
            return 1;
        } else if (a.minute == b.minute) {
            return 0;
        }
    }
    return -1;
}

void makeReservation(Passenger *passenger, Flight *flights, unsigned int flight_count) {
    int i, tempi = -1;
    Time time;
    for (i = 0; i < flight_count; ++i) {
        if (strcmp(passenger->dep, flights[i].dep) == 0 && strcmp(passenger->arr, flights[i].arr) == 0) {
            if (compareDay(passenger->dep_day, flights[i].dep_day)) {
                if (tempi == -1 || compareTime(flights[i].arr_time, time) == -1) {
                    time = flights[i].dep_time;
                    tempi = i;
                }
            }
        }
    }
    if (tempi != -1) {
        passenger->flight = &flights[tempi];
        flights[tempi].pass_count += 1;
    } else {
        printf("%s %s %s %s ", passenger->first_name, passenger->last_name, passenger->dep, passenger->arr);
        printDay(passenger->dep_day);
        printf(" No reservation\n");
    }
}

int main() {
    Flight *flights;
    Passenger *passengers;
    int action_nr;
    char action[50];
    Flight *flight;
    unsigned int flight_count, passenger_count, i, flight_size = 10, passenger_size = 10;
    int flag;
    char first_name[50], last_name[50];

    flights = (Flight *) malloc(sizeof(Flight) * flight_size);
    passengers = (Passenger *) malloc(sizeof(Passenger) * passenger_size);


    while (1) {
        clrscr();

        printf("1. Add a new flight\n");
        printf("2. Add passenger\n");
        printf("3. Show flight list\n");
        printf("4. Search flight\n");
        printf("5. Exist\n");
        printf("Choose an action: ");
        scanf("%d", &action_nr);

        switch (action_nr) {
            case 1:
                printf("Flight Nr: ");
                scanf("%d", &flights[passenger_count].num);
                printf("Departure: ");
                scanf("%s", flights[passenger_count].dep);
                printf("Arrival: ");
                scanf("%s", flights[passenger_count].arr);

                do {
                    printf("Departure Day (dd/mm/yyy): ");
                } while (scanDay(&flights[passenger_count].dep_day) != 3);

                do {
                    printf("Departure Time (hh:mm): ");
                } while (scanTime(&flights[passenger_count].dep_time) != 2);

                do {
                    printf("Arrival Day (dd/mm/yyy): ");
                } while (scanDay(&flights[passenger_count].arr_day) != 3);

                do {
                    printf("Arrival Time (hh:mm): ");
                } while (scanTime(&flights[passenger_count].arr_time) != 2);

                flights[passenger_count].pass_count = 0;
                passenger_count++;
                break;
            case 2:
                scanf("%s %s %s %s", passengers[i].first_name, passengers[i].last_name, passengers[i].dep,
                      passengers[i].arr);
                scanDay(&passengers[i].dep_day);
                makeReservation(&passengers[i], flights, flight_count);
                break;
            case 5:
                return 0;
        }

        continue;
        scanf("%s", action);
        if (strcmp(action, "search") == 0) {
            scanf("%s", action);
            if (strcmp(action, "flightNumber") == 0) {
                scanf("%d", &i);
                flight = searchFlight(flights, flight_count, i);
                if (flight) {
                    printFlight(*flight);
                    printf("\n");
                } else {
                    printf("No flight with number %d\n", i);
                }
                printf("\n");

            } else if (strcmp(action, "departure") == 0) {
                scanf("%s", action);
                flag = 0;
                for (i = 0; i < flight_count; i++) {
                    if (strcmp(flights[i].dep, action) == 0) {
                        flag = 1;
                        printFlight(flights[i]);
                        printf("\n");
                    }
                }

                if (!flag) {
                    printf("No departure city %s\n", action);
                }

                printf("\n");

            } else if (strcmp(action, "arrival") == 0) {

                scanf("%s", action);
                flag = 0;

                for (i = 0; i < flight_count; i++) {
                    if (strcmp(flights[i].arr, action) == 0) {
                        flag = 1;
                        printFlight(flights[i]);
                        printf("\n");
                    }
                }

                if (!flag) {
                    printf("No arrival city %s\n", action);
                }

                printf("\n");

            }
        } else if (strcmp(action, "print") == 0) {
            scanf("%d", &i);
            flight = searchFlight(flights, flight_count, i);
            if (flight) {
                printFlight(*flight);
                printf(" %d\n", flight->pass_count);
            } else {
                printf("No flight with number %d\n", i);
            }
            printf("\n");
        } else if (strcmp(action, "printwP") == 0) {
            scanf("%d", &i);
            flight = searchFlight(flights, flight_count, i);
            if (flight) {
                printFlight(*flight);
                printf(" %d\n", flight->pass_count);
                for (i = 0; i < passenger_count; ++i) {
                    if (passengers[i].flight == flight)
                        printf("%s %s\n", passengers[i].first_name, passengers[i].last_name);
                }
            } else {
                printf("No flight with number %d\n", i);
            }
            printf("\n");
        } else if (strcmp(action, "printR") == 0) {
            scanf("%s %s", first_name, last_name);
            for (i = 0; i < passenger_count; i++) {
                if (strcmp(passengers[i].first_name, first_name) == 0 &&
                    strcmp(passengers[i].last_name, last_name) == 0) {
                    printf("%s %s ", first_name, last_name);
                    printFlight(*passengers[i].flight);
                    printf("\n");
                }
            }
        } else if (strcmp(action, "END") == 0) {
            break;
        }
    }

    return 0;
}
