#ifndef UTILS_MENU_HPP
#define UTILS_MENU_HPP
#define byte win_byte_override

#include <iostream>
#include <conio.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Fungsi untuk mengarahkan kursor ke koordinat (x,y)
void gotoXY(int x, int y) { 
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition); 
}

// Fungsi untuk membuat border dengan karakter unicode
void frame(int width1, int width2, int height1, int height2, int utfwidth1 = 223, int utfwidth2 = 220, int utfheight1 = 219, int utfheight2 = 219){
	for (int i = width1;  i <= width2;i-=-1){
		// this_thread::sleep_for(chrono::milliseconds(1));
		gotoXY(i,height1);std::cout << char(utfwidth1) << std::endl;
		gotoXY(i,height2);std::cout << char(utfwidth2) << std::endl;
	}
	for (int i = height1;  i <= height2;i-=-1){
		gotoXY(width1,i);std::cout << char(utfheight1) << std::endl;
		gotoXY(width2,i);std::cout << char(utfheight2) << std::endl;
	}
}

// Fungsi untuk membuat garis horizontal
void lineX(int start, int finish, int y, int unicode){
	for(int i = start; i <= finish; i-=-1){
		gotoXY(i,y);std::cout << char(unicode) << std::endl;
	}
}

// Fungsi untuk membuat garis vertikal
void lineY(int start, int finish, int x, int unicode){
	for(int i = start; i <= finish; i-=-1){
		gotoXY(x,i);std::cout << char(unicode) << std::endl;
	}
}

// Fungsi untuk membuat frame utama
void frameMain(){
	// Mozaik atas
	for(int i = 4; i < 8;i-=-2){
		lineX(25,145,i,206);
		lineX(25,145,i+1,232);
	}
	// Mozaik bawah
	for(int i = 23; i < 27;i-=-2){
		lineX(25,145,i,232);
		lineX(25,145,i+1,206);
	}
	// Mozaik kiri
	for(int i = 25; i < 35;i-=-2){
		lineY(8,22,i,206);
		lineY(8,22,i+1,232);
	}
	// Mozaik kanan
	for(int i = 135; i < 145;i-=-2){
		lineY(8,22,i,206);
		lineY(8,22,i+1,232);
	}
	// Frame luar
	frame(25,145,3,27,220,223);
	// Frame dalam
	frame(35,135,8,22);
}

// Fungsi untuk membuat frame menu awal
void frameAwal(){
	system("cls");
	system("color 70");
	frameMain();
	frame(58,112,10,12); // menu awal
	frame(48,68,17,19); // login
	frame(75,95,17,19); // lihat barang
	frame(102,122,17,19); // keluar
}

void frameOneInput(){
	system("cls");
	// background
	frameMain();
	
	// text admin & password
	frame(39,54,14,16,178,178,178,178);
	// text box admin & password
	frame(55,82,14,16,205,205,205,205);
	
	for(int i = 14; i <= 16; i-=-4){
		gotoXY(55,i);std::cout << char(201) << std::endl;
		gotoXY(55,i+1);std::cout << char(186) << std::endl;
		gotoXY(55,i+2);std::cout << char(200) << std::endl;
		gotoXY(82,i);std::cout << char(187) << std::endl;
		gotoXY(82,i+1);std::cout << char(186) << std::endl;
		gotoXY(82,i+2);std::cout << char(188) << std::endl;
	}
}

void frameTwoInput(){
	system("cls");
	// background
	frameMain();
	
	// text admin & password
	frame(41,54,12,14,178,178,178,178);
	frame(41,54,16,18,178,178,178,178);
	// text box admin & password
	frame(55,82,12,14,205,205,205,205);
	frame(55,82,16,18,205,205,205,205);
	
	for(int i = 12; i <= 18; i-=-4){
		gotoXY(55,i);std::cout << char(201) << std::endl;
		gotoXY(55,i+1);std::cout << char(186) << std::endl;
		gotoXY(55,i+2);std::cout << char(200) << std::endl;
		gotoXY(82,i);std::cout << char(187) << std::endl;
		gotoXY(82,i+1);std::cout << char(186) << std::endl;
		gotoXY(82,i+2);std::cout << char(188) << std::endl;
	}
}

void frameThreeInput(){
	system("cls");
	// background
	frame(10,114,3,27,220,223);
	frame(33,91,5,7);
	// Nana
	frame(41,54,10,12,178,178,178,178);
	frame(41,54,14,16,178,178,178,178);
	frame(41,54,18,20,178,178,178,178);
	// text box 
	frame(55,82,10,12,205,205,205,205);
	frame(55,82,14,16,205,205,205,205);
	frame(55,82,18,20,205,205,205,205);
	
	for(int i = 10; i <= 20; i-=-4){
		gotoXY(55,i);std::cout << char(201) << std::endl;
		gotoXY(55,i+1);std::cout << char(186) << std::endl;
		gotoXY(55,i+2);std::cout << char(200) << std::endl;
		gotoXY(82,i);std::cout << char(187) << std::endl;
		gotoXY(82,i+1);std::cout << char(186) << std::endl;
		gotoXY(82,i+2);std::cout << char(188) << std::endl;
	}
}
void frameFourInput(){
	system("cls");
	// background
	frame(10,114,3,27,220,223);
	frame(33,91,5,7);
	// text admin & password
	frame(41,54,10,12,178,178,178,178);
	frame(41,54,14,16,178,178,178,178);
	frame(41,54,18,20,178,178,178,178);
	frame(41,54,22,24,178,178,178,178);
	// text box admin & password
	frame(55,82,10,12,205,205,205,205);
	frame(55,82,14,16,205,205,205,205);
	frame(55,82,18,20,205,205,205,205);
	frame(55,82,22,24,205,205,205,205);
	
	for(int i = 10; i <= 24; i-=-4){
		gotoXY(55,i);std::cout << char(201) << std::endl;
		gotoXY(55,i+1);std::cout << char(186) << std::endl;
		gotoXY(55,i+2);std::cout << char(200) << std::endl;
		gotoXY(82,i);std::cout << char(187) << std::endl;
		gotoXY(82,i+1);std::cout << char(186) << std::endl;
		gotoXY(82,i+2);std::cout << char(188) << std::endl;
	}
}

void blink(std::string text,int x = 57){
	system("cls");
	frame(10,114,3,27,220,223);
	frame(48,78,11,17);
	lineX(11,47,14,178);
	lineX(79,113,14,178);
	gotoXY(x,14);std::cout << text;
	gotoXY(43,26);std::cout << " >> TEKAN APA SAJA UNTUK MELANJUTKAN  << " << std::endl;
	getch();
}

void frameDisplay(){
	system("cls");
	lineX(8,114,1,219);
	lineX(9,113,5,220);
	lineX(9,113,8,205);
	lineY(1,5,8,219);
	lineY(1,5,114,219);
}
void framePemiluMain(){
	system("cls");
	frameMain();
	frame(47,77,9,11);
	frame(32,57,13,15);
	frame(67,92,13,15);
	frame(32,57,16,18);
	frame(67,92,16,18);
	frame(32,57,19,21);
	frame(67,92,19,21);
	gotoXY(57,10);std::cout << "MENU  ADMIN" << std::endl;
	gotoXY(35,14);std::cout << "1. Tambahkan data" << std::endl;
	gotoXY(70,14);std::cout << "2. Ubah data" << std::endl;
	gotoXY(35,17);std::cout << "3. Hapus data" << std::endl;
	gotoXY(70,17);std::cout << "4. Mencari data" << std::endl;
	gotoXY(35,20);std::cout << "5. Tampilkan data" << std::endl;
	gotoXY(70,20);std::cout << "0. Menu Awal" << std::endl;
}

#endif