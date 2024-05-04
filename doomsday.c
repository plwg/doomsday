#include <stdio.h>
#include <stdlib.h>

int calc_anchor_day(int year);
int calc_index_day(int year);
int is_leap_year(int year);
int get_month_doomsday(int year, int month);
int check_valid_date(int year, int month, int day);

int main(int argc, char *argv[])
{
    int year = atoi(argv[1]);
    int month = atoi(argv[2]);
    int day = atoi(argv[3]);

    if (check_valid_date(year, month, day))
    {
        int anchor, doomsday, offset, weekday;
        anchor = calc_anchor_day(year);
        doomsday = get_month_doomsday(year, month);
        offset = ((offset = day - doomsday) >= 0 ? offset % 7 : (offset % 7) + 7);
        weekday = (anchor + offset) % 7;
        printf("anchor: %d doomsday: %d offset: %d weekday: %d\n", anchor, doomsday, offset, weekday);
        return 0;
    }
    else
    {
        printf("Not a valid date.");
        return -1;
    }
}

int check_valid_date(int year, int month, int day)
{
    if (year < 0)
    {
        return 0;
    }
    else if (month < 1 || month > 12)
    {
        return 0;
    }
    else
    {
        if (day < 1)
        {
            return 0;
        }
        else
        {
            const int month_max_day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            if (month == 2)
            {
                return day <= (month_max_day[month - 1] + is_leap_year(year));
            }
            else
            {
                return day <= month_max_day[month - 1];
            }
        }
    }
}

int calc_index_day(int year)
{
    const int index_day[] = {2, 0, 5, 3};

    return index_day[(year / 100) % 4];
}

int calc_anchor_day(int year)
{
    int last_two_digit_of_year = year % 100;
    int offset_from_index = (last_two_digit_of_year + last_two_digit_of_year / 4) % 7;
    int index = calc_index_day(year);

    return (offset_from_index + index) % 7;
}

int is_leap_year(int year)
{
    if (year % 100 != 0)
    {
        return (year % 4 == 0);
    }
    else
    {
        return (year % 400 == 0);
    }
}

int get_month_doomsday(int year, int month)
{
    const int doomsday[] = {3, 28, 0, 4, 9, 6, 11, 8, 5, 10, 7, 12};

    if (month <= 2)
    {
        return is_leap_year(year) + doomsday[month - 1];
    }
    else
    {
        return doomsday[month - 1];
    }
}
