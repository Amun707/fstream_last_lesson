#include <iostream>
#include <fstream>
#include <string>

//1. Задание 
bool file_inser(std::string path, int pos, std::string str);


int main() {
	system("chcp 1251>nul");
	int n, m;
	const std::string path = "file.txt";

	//Класс fstream для чтения и записи в файл

	std::fstream fs;
	fs.open(path, std::ios::in | std::ios::app);//открытие файла в нескольких режимах с помощью перегрузки операции битового или
	// | - битовое или


	//seekg - seek get pointer (переместить курсор считывания)
	//seekp - seek put pointer (переместить курсор записи)
	//begin
	//end
	//current

	if (fs.is_open()) {
		std::cout << "Файл открыт.\n";

		//Ввод данных в файл
		std::cout << "Введите строку -> \n";
		std::string str;
		std::getline(std::cin, str);
		fs << str << '\n';

		//перемещение курсора для считывания в начало файла
		fs.seekg(0, std::ios::beg);

		//Чтение данных из файла
		std::cout << "Содержимое файла:\n";
		char sym;
		while (fs.get(sym))
			std::cout << sym;
		std::cout << std::endl;

	}
	else {
		std::cout << "Ошибка открытия файла!";
	}


	fs.close();

	//Задание 1 "вставка в середину файла"
	if (file_inser(path, 3, "###"))
		std::cout << "Строка вставлена успешно.\n";
	else
		std::cout << "Ошибка выполнения функции!\n\n";

	//Задача 2. Парсинг дата
	std::cout << "Задача 2.\nДата: ";
	std::ifstream in;
	in.open("date.txt");

	if (in.is_open()) {
		std::string date;
		in >> date;
		std::cout << date << std::endl;

		int day = std::stoi(date);
		int month = std::stoi(date.substr(date.find('.') + 1));
		int year = std::stoi(date.substr(date.rfind('.') + 1));

		std::cout << "День: " << day << std::endl;
		std::cout << "Месяц: " << month << std::endl;
		std::cout << "Год: " << year << std::endl;
	}
	in.close();


	return 0;
}

//1. Задание
bool file_inser(std::string path, int pos, std::string str) {
	static std::fstream fs;
	fs.open(path, std::ios::in);

	if (!fs.is_open())
		return false;

	std::string file, line;//строка для содержимого файла и для построчного считывания(file, line)
	while (std::getline(fs, line))
		file += line + '\n';

	fs.close();

	file.insert(pos, str);

	fs.open(path, std::ios::out);//открываем файл в режиме out
	if (!fs.is_open())
		return false;

	fs << file;//вставляем содержимое
	fs.close();
	return true;
}