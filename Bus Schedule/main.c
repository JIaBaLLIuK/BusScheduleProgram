#include "functions.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool finishProgram = false;
	int tripsAmount = 0;
	DataBase* tripsInformation = NULL;
	do
	{
		system("CLS");
		int check, user;
		printf("Выберите тип входа в систему:\n1. Администратор.\n2. Пользователь.\n0. Завершить работу программы.\n");
		// ввод типа входа в систему и его проверка
		check = scanf_s("%d", &user);
		while (!check || user < 0 || user > 2)
		{
			rewind(stdin);
			printf("Ошибка. Повторите ввод:\n");
			check = scanf_s("%d", &user);
		}
		system("CLS");
		switch (user)
		{
		case 1:
		{
			// файл, содержащий в себе корректный пароль
			FILE* correctPasswordFile = fopen("CorrectPasswordFile.txt", "r+");
			if (!correctPasswordFile)
			{
				printf("Произошла ошибка! Завершение работы...\n");
				return -1;
			}
			fseek(correctPasswordFile, 0, SEEK_END);
			char correctPassword[20] = { 0 };
			char adminPassword[20] = { 0 };
			int fileSize = ftell(correctPasswordFile);
			if (fileSize == 0)
			{
				printf("Вы ни разу не входили в систему! Введите желаемый пароль админиистратора:\n");
				rewind(stdin);
				gets(adminPassword);
				fprintf(correctPasswordFile, "%s", adminPassword);
			}
			else
			{
				rewind(correctPasswordFile);
				if (fscanf(correctPasswordFile, "%s", correctPassword) <= 0)
				{
					printf("Произошла ошибка! Завершение работы...\n");
					return -1;
				}
				printf("Введите пароль администратора:\n");
				rewind(stdin);
				// ввод пароля администратора и его проверка
				gets(adminPassword);
				int attemptCount = 4;
				while (strcmp(adminPassword, correctPassword))
				{
					attemptCount--;
					if (attemptCount == 0)
					{
						fclose(correctPasswordFile);
						printf("У вас закончились попытки ввода парля. Программа завершает свою работу!\n");
						return 0;
					}
					printf("Вы ввели неверный пароль администратора! Осталось попыток: %d.\n", attemptCount);
					printf("Повторите ввод пароля:\n");
					rewind(stdin);
					gets(adminPassword);
				}
			}
			system("CLS");
			bool isFinishedAdmin = false;
			fclose(correctPasswordFile);
			do
			{
				printf("Выберите действие:\n1. Ввести данные в базу.\n2. Просмотреть базу данных.\n3. Очистить базу данных.\n");
				printf("4. Удалить рейс по заданному номеру автобуса.\n5. Изменить пароль администратора.\n");
				printf("0. Завершить работу в качестве администратора.\n");
				int administratorChoice;
				check = scanf_s("%d", &administratorChoice);
				while (!check || administratorChoice < 0 || administratorChoice > 5)
				{
					rewind(stdin);
					printf("Ошибка. Повторите ввод:\n");
					check = scanf_s("%d", &administratorChoice);
				}
				switch (administratorChoice)
				{
				case 1:
				{
					int stop = 0;
					do
					{
						system("CLS");
						tripsAmount++;
						DataBase* temp = (DataBase*)realloc(tripsInformation, tripsAmount * sizeof(DataBase));
						if (!temp)
						{
							printf("Произошла ошибка при выделении памяти!\n");
							return -1;
						}
						else
							tripsInformation = temp;
						tripsAmount = InputInformation(tripsInformation, tripsAmount);
						printf("Завершить ввод?\n0 - нет\n1 - да\n");
						check = scanf_s("%d", &stop);
						while (!check || stop != 0 && stop != 1)
						{
							rewind(stdin);
							printf("Ошибка. Повторите ввод:\n");
							check = scanf_s("%d", &stop);
						}
					} while (!stop);
					system("CLS");
					break;
				}
				case 2:
					system("CLS");
					OutputInformation(tripsInformation, tripsAmount);
					break;
				case 3:
					system("CLS");
					free(tripsInformation);
					tripsInformation = NULL;
					tripsAmount = 0;
					printf("База данных очищена.\n");
					break;
				case 4:
				{
					system("CLS");
					printf("Введите номер автобуса, информацию о котором необходимо удалить:\n");
					int numberForDelete;
					check = scanf_s("%d", &numberForDelete);
					while (!check || numberForDelete < 1)
					{
						rewind(stdin);
						printf("Ошибка. Повторите ввод:\n");
						check = scanf_s("%d", &numberForDelete);
					}
					system("CLS");
					int checkDelete = DeleteTripByNumber(tripsInformation, tripsAmount, numberForDelete);
					if (checkDelete == -1)
						printf("Автобусного рейса с таким номером не существует!\n");
					else
					{
						printf("Автобусный рейс удален!\n");
						tripsAmount = checkDelete;
						if (tripsAmount == 0)
						{
							free(tripsInformation);
							tripsInformation = NULL;
						}
						else
						{
							DataBase* temp = (DataBase*)realloc(tripsInformation, tripsAmount * sizeof(DataBase));
							if (!temp)
							{
								printf("Произошла ошибка при выделении памяти!\n");
								return -1;
							}
							else
								tripsInformation = temp;
						}
					}
					break;
				}
				case 5:
				{
					system("CLS");
					ChangePassword();
					system("CLS");
					break;
				}
				case 0:
					system("CLS");
					isFinishedAdmin = true;
					break;
				}
			} while (!isFinishedAdmin);
			break;
		}
		case 2:
		{
			bool isFinishedUser = false;
			do
			{
				printf("Выберите действие:\n1. Список всех доступных автобусных рейсов.\n");
				printf("2. Список автобусных рейсов, отправляющихся до определенного пункта назначения.\n");
				printf("3. Список автобусных рейсов, которые отбывают в заданный день.\n");
				printf("0. Завершить работу в качестве пользователя.\n");
				int userChoice;
				check = scanf_s("%d", &userChoice);
				while (!check || userChoice < 0 || userChoice > 3)
				{
					rewind(stdin);
					printf("Ошибка. Повторите ввод:\n");
					check = scanf_s("%d", &userChoice);
				}
				switch (userChoice)
				{
				case 1:
					system("CLS");
					OutputInformation(tripsInformation, tripsAmount);
					break;
				case 2:
				{
					system("CLS");
					printf("Введите интересующий Вас пункт назначения:\n");
					rewind(stdin);
					char userDestination[50];
					gets(userDestination);
					system("CLS");
					if (ShowTripByDestination(tripsInformation, tripsAmount, userDestination) == -1)
						printf("Автобусного рейса до данного пункта назначения нет!\n");
					break;
				}
				case 3:
				{
					system("CLS");
					int userDay, userMonth;
					printf("Введите желаемый день отправления:\n");
					check = scanf_s("%d", &userDay);
					while (!check || userDay < 1 || userDay > 30)
					{
						rewind(stdin);
						printf("Ошибка. Повторите ввод:\n");
						check = scanf_s("%d", &userDay);
					}
					printf("Введите желаемый месяц отправления:\n");
					check = scanf_s("%d", &userMonth);
					while (!check || userMonth < 1 || userMonth > 12)
					{
						rewind(stdin);
						printf("Ошибка. Повторите ввод:\n");
						check = scanf_s("%d", &userMonth);
					}
					if (ShowTripsByDate(tripsInformation, tripsAmount, userDay, userMonth) == -1)
						printf("В заданный день нет автобусных рейсов!\n");
					break;
				}
				case 0:
					isFinishedUser = true;
					break;
				}
			} while (!isFinishedUser);
			break;
		case 0:
			finishProgram = true;
			break;
		}
		}
	} while (!finishProgram);
	free(tripsInformation);
	return 0;
}