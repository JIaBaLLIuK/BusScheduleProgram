#include "functions.h"

int InputInformation(DataBase* tripsInformation, int lastTripNumber)
{
	int tripNumber = lastTripNumber;
	int check;
	// ввод номера автобуса и его проверка
	printf("Введите номер автобуса:\n");
	check = scanf_s("%d", &tripsInformation[tripNumber - 1].busNumber);
	while (!check || tripsInformation[tripNumber - 1].busNumber < 1)
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		check = scanf_s("%d", &tripsInformation[tripNumber - 1].busNumber);
	}
	// ввод типа автобуса и его проверка
	printf("Введите тип автобуса (М - малые; С - средние; Б - большие):\n");
	rewind(stdin);
	tripsInformation[tripNumber - 1].busType = getchar();
	while (tripsInformation[tripNumber - 1].busType != 'М' && tripsInformation[tripNumber - 1].busType != 'С' &&
		tripsInformation[tripNumber - 1].busType != 'Б')
	{
		printf("Вы ввели некорреткный тип автобуса. Повторите ввод:\n");
		rewind(stdin);
		tripsInformation[tripNumber - 1].busType = getchar();
	}
	// ввод пункта назначения
	printf("Введите пункт назначения:\n");
	rewind(stdin);
	gets(tripsInformation[tripNumber - 1].destination);
	// ввод дня отъезда и его проверка
	printf("Введите день отъезда(1-30):\n");
	check = scanf_s("%d", &tripsInformation[tripNumber - 1].departureDay);
	bool isLastDay = false;
	while (!check || tripsInformation[tripNumber - 1].departureDay < 1 || tripsInformation[tripNumber - 1].departureDay > 30)
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		check = scanf_s("%d", &tripsInformation[tripNumber - 1].departureDay);
	}
	if (tripsInformation[tripNumber - 1].departureDay >= 29)
		isLastDay = true;
	// ввод месяца отъезда и его проверка
	printf("Введите месяц отъезда(1-12):\n");
	check = scanf_s("%d", &tripsInformation[tripNumber - 1].departureMonth);
	while (!check || tripsInformation[tripNumber - 1].departureMonth < 1 || tripsInformation[tripNumber - 1].departureMonth > 12)
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		check = scanf_s("%d", &tripsInformation[tripNumber - 1].departureMonth);
	}
	// ввод времени отъезда и её проверка
	printf("Введите время отъезда(в формате чч:мм):\n");
	rewind(stdin);
	gets(tripsInformation[tripNumber - 1].departueTime);
	while (!CheckTimeInput(tripsInformation[tripNumber - 1].departueTime))
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		gets(tripsInformation[tripNumber - 1].departueTime);
	}
	// ввод дня приезда и его проверка
	printf("Введите день приезда:\n");
	check = scanf_s("%d", &tripsInformation[tripNumber - 1].arrivalDay);
	while (!check || tripsInformation[tripNumber - 1].arrivalDay < 1 || tripsInformation[tripNumber - 1].arrivalDay > 30 || 
		 !isLastDay && tripsInformation[tripNumber - 1].arrivalDay < tripsInformation[tripNumber - 1].departureDay ||
		 tripsInformation[tripNumber - 1].arrivalDay >= tripsInformation[tripNumber - 1].departureDay + 4)
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		check = scanf_s("%d", &tripsInformation[tripNumber - 1].arrivalDay);
	}
	// ввод месяца приезда в случае, если день отъезда больше либо равен 29
	if (tripsInformation[tripNumber - 1].departureDay >= 29)
	{
		printf("Введите месяц приезда:\n");
		check = scanf_s("%d", &tripsInformation[tripNumber - 1].arrivalMonth);
		while (!check || tripsInformation[tripNumber - 1].arrivalMonth < tripsInformation[tripNumber - 1].departureMonth ||
			tripsInformation[tripNumber - 1].arrivalMonth > tripsInformation[tripNumber - 1].departureMonth + 1)
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &tripsInformation[tripNumber - 1].arrivalMonth);
		}
	}
	else
		tripsInformation[tripNumber - 1].arrivalMonth = tripsInformation[tripNumber - 1].departureMonth;
	// проверка, если приезд происходит в следующем месяце, чтобы день не был больше 2 (маршрут у автобусов не бывает таким долгим)
	if (tripsInformation[tripNumber - 1].arrivalMonth == tripsInformation[tripNumber - 1].departureMonth + 1 &&
		tripsInformation[tripNumber - 1].arrivalDay > 2)
	{
		printf("При введённых выше данных день приезда не может быть больше 2! Повторите ввод дня приезда:\n");
		check = scanf_s("%d", &tripsInformation[tripNumber - 1].arrivalDay);
		while (!check || tripsInformation[tripNumber - 1].arrivalDay < 1 || tripsInformation[tripNumber - 1].arrivalDay > 3)
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &tripsInformation[tripNumber - 1].arrivalDay);
		}
	}
	// ввод времени приезда и его проверка
	printf("Введите время приезда(в формате чч:мм):\n");
	rewind(stdin);
	gets(tripsInformation[tripNumber - 1].arrivalTime);
	while (!CheckTimeInput(tripsInformation[tripNumber - 1].arrivalTime) || 
		tripsInformation[tripNumber - 1].arrivalDay == tripsInformation[tripNumber - 1].departureDay &&
		tripsInformation[tripNumber - 1].arrivalTime[1] <= tripsInformation[tripNumber - 1].departueTime[1] &&
		tripsInformation[tripNumber - 1].arrivalTime[0] <= tripsInformation[tripNumber - 1].departueTime[0])
	{
		rewind(stdin);
		printf("Ошибка. Повторите ввод:\n");
		gets(tripsInformation[tripNumber - 1].arrivalTime);
	}
	return tripNumber;
}
// проверка корректности ввода времени
int CheckTimeInput(char* time)  
{
	if (time[0] < '0' || time[0] > '2')
		return 0;
	else if (time[2] != ':')
		return 0;
	else if (time[3] < '0' || time[3] > '5')
		return 0;
	else if (time[0] == '2' && time[1] >= '4' || time[1] < '0')
		return 0;
	else 
		return 1;
}
// вывод информации на экран
void OutputInformation(DataBase* tripsInformation, int tripsAmount)
{
	if (!tripsInformation)
	{
		printf("Информация о рейсах отсутсвует.\n");
		return;
	}
	for (int i = 0; i < tripsAmount; i++)
		printf("Автобус под номером %d отбывает %d числа %d месяца в %s и прибывает %d числа %d месяца в %s. Тип автобуса %c. Пункт назначения %s.\n",
			tripsInformation[i].busNumber, tripsInformation[i].departureDay, tripsInformation[i].departureMonth, tripsInformation[i].departueTime,
			tripsInformation[i].arrivalDay, tripsInformation[i].arrivalMonth, tripsInformation[i].arrivalTime, 
			tripsInformation[i].busType, tripsInformation[i].destination);
}
// удаление рейса по заданному номеру
int DeleteTripByNumber(DataBase* tripsInformation, int tripsAmount, int numberForDelete)
{
	bool isDeleted = false;
	for (int i = 0; i < tripsAmount; i++)
	{
		if (tripsInformation[i].busNumber == numberForDelete && tripsAmount > 1)
		{
			for (int j = i; j < tripsAmount - 1; j++)
			{
				tripsInformation[j] = tripsInformation[j + 1];
				tripsAmount--;
				isDeleted = true;
			}
		}
		else if (tripsInformation[i].busNumber == numberForDelete && tripsAmount == 1)
		{
			tripsAmount = 0;
			return tripsAmount;
		}
	}
	if (isDeleted)
		return tripsAmount;
	else
		return -1;
}
// вывод атобусного рейса до заданного пункта назначения
int ShowTripByDestination(DataBase* tripsInformation, int tripsAmount, char* userDestination)
{
	bool isNeededBus = false;
	for (int i = 0; i < tripsAmount; i++)
	{
		if (!strcmp(tripsInformation[i].destination, userDestination))
		{
			printf("Автобус под номером %d отбывает %d числа %d месяца в %s и прибывает %d числа %d месяца в %s. Тип автобуса %c. Пункт назначения %s.\n",
				tripsInformation[i].busNumber, tripsInformation[i].departureDay, tripsInformation[i].departureMonth, tripsInformation[i].departueTime,
				tripsInformation[i].arrivalDay, tripsInformation[i].arrivalMonth, tripsInformation[i].arrivalTime,
				tripsInformation[i].busType, tripsInformation[i].destination);
			isNeededBus = true;
		}
	}
	if (isNeededBus)
		return 1;
	else
		return -1;
}
// вывод автобусных рейсов по заданной дате
int ShowTripsByDate(DataBase* tripsInformation, int tripsAmount, int userDay, int userMonth)
{
	bool isNeededDate = false;
	for (int i = 0; i < tripsAmount; i++)
	{
		if (tripsInformation[i].departureDay == userDay && tripsInformation[i].departureMonth == userMonth)
		{
			printf("Автобус под номером %d отбывает %d числа %d месяца в %s и прибывает %d числа %d месяца в %s. Тип автобуса %c. Пункт назначения %s.\n",
				tripsInformation[i].busNumber, tripsInformation[i].departureDay, tripsInformation[i].departureMonth, tripsInformation[i].departueTime,
				tripsInformation[i].arrivalDay, tripsInformation[i].arrivalMonth, tripsInformation[i].arrivalTime,
				tripsInformation[i].busType, tripsInformation[i].destination);
			isNeededDate = true;
		}
	}
	if (isNeededDate)
		return 1;
	else
		return -1;
}
// функция изменения пароля администратора
void ChangePassword()
{
	printf("Введите новый пароль администратора:\n");
	char newPassword[20] = { 0 };
	rewind(stdin);
	gets(newPassword);
	FILE* correctPasswordFile = fopen("CorrectPasswordFile.txt", "w");
	if (!correctPasswordFile)
	{
		printf("Произошла ошибка! Завершение работы...\n");
		return;
	}
	fprintf(correctPasswordFile, "%s", newPassword);
	fclose(correctPasswordFile);
}