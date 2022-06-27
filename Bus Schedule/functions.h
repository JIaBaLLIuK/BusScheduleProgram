#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

typedef struct 
{
	int busNumber;  // номер автобуса
	char busType;  // тип автобуса
	char destination[50];  // пункт назначения
	int departureDay;  // день отъезда
	int departureMonth;  // месяц отъезда
	char departueTime[6];  // время отъезда
	int arrivalDay;  // день прибытия
	int arrivalMonth;  // месяц прибытия
	char arrivalTime[6];  // время прибытия
} DataBase;

int InputInformation(DataBase*, int);
int CheckTimeInput(char*);
void OutputInformation(DataBase*, int);
int DeleteTripByNumber(DataBase*, int, int);
int ShowTripByDestination(DataBase*, int, char*);
int ShowTripsByDate(DataBase*, int, int, int);
void ChangePassword();